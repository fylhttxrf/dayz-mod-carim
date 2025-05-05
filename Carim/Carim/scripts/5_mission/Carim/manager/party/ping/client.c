class CarimManagerPartyPingClient extends Managed {
    ref CarimModelPartyPings markers;
    ref map<string, ref CarimModelPartyPings> serverMarkers = new map<string, ref CarimModelPartyPings>;
    ref CarimRPCPartyPings rpc = new CarimRPCPartyPings;

    void CarimManagerPartyPingClient(CarimModelPartyPings inputMarkers, CarimModelMapMarkers inputMapMarkers, CarimModelPartyRegistrations inputRegistrations) {
        markers = inputMarkers;
        mapMarkers = inputMapMarkers;
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.InitialRegistration, 2000, true);
    }

    void ~CarimManagerPartyPingClient() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.InitialRegistration);
    }

    void InitialRegistration() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) {
            Send();
            GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.InitialRegistration);
        }
    }

    void OnUpdate(float timeslice) {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UACarimPartyPing")) {
                vector position = GetRaycastPosition();
                if (position != vector.Zero) {
                    CarimLogging.Debug(this, "Input ping");
                    Add(position);
                }
            }
            if (CarimUtil.CheckInput("UACarimPartyPingClear")) {
                CarimLogging.Debug(this, "Input clear");
                Reset();
            }
        }
    }

    void AddServer(string id, CarimModelPartyPings inputMarkers) {
        serverMarkers.Set(id, inputMarkers);
        SyncMenus();
    }

    void Add(vector position) {
        markers.Add(position);
        SyncMenus();
        Send();
    }

    void Reset() {
        markers.Clear();
        SyncMenus();
        Send();
    }

    void Send() {
        Param2<string, CarimModelPartyPings> params = new Param2<string, CarimModelPartyPings>("", markers);
        rpc.Send(GetGame().GetPlayer(), params);
    }

    static vector GetRaycastPosition() {
        vector begin = GetGame().GetCurrentCameraPosition() + GetGame().GetCurrentCameraDirection();
        vector end = begin + GetGame().GetCurrentCameraDirection() * 8000;
        vector contactPos;
        vector contactDir;
        int contactComponent;
        if (DayZPhysics.RaycastRV(begin, end, contactPos, contactDir, contactComponent)) {
            return contactPos;
        }
        return vector.Zero;
    }
}
