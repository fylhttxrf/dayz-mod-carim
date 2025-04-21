#ifndef CarimManagerPartyMarkerClient
#define CarimManagerPartyMarkerClient

class CarimManagerPartyMarkerClient extends Managed {
    ref map<string, ref CarimModelPartyMarkers> serverMarkers = new map<string, ref CarimModelPartyMarkers>;
    ref array<ref CarimMenuPartyMarker> menus = new array<ref CarimMenuPartyMarker>;
    ref CarimRPCPartyMarkers rpc = new CarimRPCPartyMarkers;

    void OnUpdate() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UACarimPartyPing")) {
                vector position = CarimUtil.GetRaycastPosition();
                if (position != vector.Zero) {
                    Add(position);
                }
            }
            if (CarimUtil.CheckInput("UACarimPartyPingClear")) {
                Reset();
            }
        }
    }

    void SyncMenus() {
        // TODO: get the markers from the server and/or locally and show them right
        // away instead of delaying until a marker has been placed
        string name = "null";
        if (GetGame().GetPlayer() && GetGame().GetPlayer().GetIdentity()) {
            name = GetGame().GetPlayer().GetIdentity().GetName();
        }

        int menuIndex = 0;
        foreach(int index, vector position : CarimModelPartyMarkersDAL.Get().markers) {
            // TODO: make the most recent marker index 0
            string markerName = name + " " + (index).ToString();
            if (menus.Count() <= menuIndex) {
                menus.Insert(new CarimMenuPartyMarker(markerName, position));
            } else {
                menus.Get(menuIndex).carimName = markerName;
                menus.Get(menuIndex).carimPosition = position;
            }
            menuIndex++;
        }
        foreach(string id, CarimModelPartyMarkers markers : serverMarkers) {
            int playerIndex = 0;
            foreach(vector mark : markers.markers) {
                if (CarimModelPartyRegistrationsDAL.Get().registrations.Contains(id)) {
                    markerName = CarimModelPartyRegistrationsDAL.Get().registrations.Get(id) + " " + (playerIndex).ToString();
                } else {
                    markerName = id.Substring(0, 4) + " " + (playerIndex).ToString();
                }
                if (menus.Count() <= menuIndex) {
                    menus.Insert(new CarimMenuPartyMarker(markerName, mark));
                } else {
                    menus.Get(menuIndex).carimName = markerName;
                    menus.Get(menuIndex).carimPosition = mark;
                }
                playerIndex++;
                menuIndex++;
            }
        }
        for (int i = menus.Count() - 1; i >= menuIndex; --i) {
            menus.Get(i).CarimRemove();
            menus.Remove(i);
        }
    }

    void AddServer(string id, CarimModelPartyMarkers markers) {
        serverMarkers.Set(id, markers);
        SyncMenus();
    }

    void Add(vector position) {
        CarimModelPartyMarkersDAL.Get().Add(position);
        CarimModelPartyMarkersDAL.Save();
        SyncMenus();
        Send();
    }

    void Reset() {
        CarimModelPartyMarkersDAL.Get().Clear();
        CarimModelPartyMarkersDAL.Save();
        SyncMenus();
        Send();
    }

    void Send() {
        if (CarimModelPartyMarkersDAL.Get()) {
            Param2<string, CarimModelPartyMarkers> params = new Param2<string, CarimModelPartyMarkers>("", CarimModelPartyMarkersDAL.Get());
            rpc.Send(GetGame().GetPlayer(), params);
        }
    }
}

typedef CarimSingleton<CarimManagerPartyMarkerClient> CarimManagerPartyMarkerClientSingleton;

#endif
