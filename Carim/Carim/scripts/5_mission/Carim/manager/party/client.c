class CarimManagerPartyClient extends Managed {
    ref CarimModelPartyMarkers markers;
    ref CarimModelPartyPings pings;
    ref CarimModelPartyPositions positions;
    ref CarimModelPartyRegistrations registrations;

    ref array<string> mutual = new array<string>;

    ref CarimMenuPartyRegister menuRegister;

    ref CarimRPCPartyPings rpcPing = new CarimRPCPartyPings;
    ref CarimRPCPartyRegister rpcRegister = new CarimRPCPartyRegister;

    void CarimManagerPartyClient(CarimModelPartyMarkers iMarkers, CarimModelPartyPings iPings, CarimModelPartyPositions iPositions, CarimModelPartyRegistrations iRegistrations) {
        markers = iMarkers;
        pings = iPings;
        positions = iPositions;
        registrations = iRegistrations;

        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.InitialSend, 2000, true);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.PeriodicSend, 60000, true);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.UpdatePositionsWithLocalPlayers, 2000, true);
    }

    void ~CarimManagerPartyClient() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.InitialSend);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.PeriodicSend);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.UpdatePositionsWithLocalPlayers);
    }

    void InitialSend() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) {
            PeriodicSend();
            GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.InitialSend);
        }
    }

    void PeriodicSend() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) {
            SendRegistration();
            SendPings();
        }
    }

    void UpdatePositionsWithLocalPlayers() {
        string activePlayerId;
        PlayerBase activePlayer = PlayerBase.Cast(GetGame().GetPlayer());
        if (activePlayer && activePlayer.GetIdentity()) {
            activePlayerId = activePlayer.GetIdentity().GetId();
        }
        auto players = GetClientPlayerBases();
        foreach(PlayerBase player : players) {
            if (player && player.GetIdentity() && player.IsAlive()) {
                string id = player.GetIdentity().GetId();
                if (positions.markers.Contains(id) && positions.markers.Get(id).Count() > 0) {
                    positions.markers.Get(id).Get(0).carimPlayer = player;
                }
            }
        }
    }

    void SendRegistration() {
        array<string> keys = registrations.registrations.GetKeyArray();
        auto params = new Param1<array<string>>(keys);
        rpcRegister.Send(player, params);
    }

    void SendPings() {
        Param2<string, CarimModelPartyPings> params = new Param2<string, CarimModelPartyPings>("", pings);
        rpcPing.Send(GetGame().GetPlayer(), params);
    }

    void OnUpdate(float timeslice) {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UACarimPartyPing")) {
                vector position = GetRaycastPosition();
                if (position != vector.Zero) {
                    CarimLogging.Debug(this, "Input ping");
                    AddPing(position);
                }
            }
            if (CarimUtil.CheckInput("UACarimPartyPingClear")) {
                CarimLogging.Debug(this, "Input clear");
                ResetPings();
            }
            if (CarimUtil.CheckInput("UAUIBack")) {
                if (menuRegister && GetGame().GetUIManager().GetMenu() == menuRegister) {
                    menuRegister.UnlockControls();
                    menuRegister.Close();
                }
            }
            if (CarimUtil.CheckInput("UACarimPartyMenu")) {
                if (menuRegister) {
                    menuRegister.Close();
                } else if (!GetGame().GetUIManager().GetMenu()) {
                    menuRegister = CarimMenuPartyRegister.Cast(GetGame().GetUIManager().EnterScriptedMenu(CarimMenuParty.REGISTER, null));
                }
            }
        }
        if (menuRegister) {
            menuRegister.Update(timeslice);
        }

        if (markers.changed) {
            markers.changed = false;
        }
        if (pings.changed) {
            SendPings();
            pings.changed = false;
        }
        if (positions.changed) {
            positions.changed = false;
        }
        if (registrations.changed) {
            PeriodicSend();
            registrations.changed = false;
        }
    }

    void AddPing(vector position) {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        mark = new CarimMapMarker(position, "", 0xffffffff, 0);
        mark.carimPlayerId = player.GetIdentity().GetId();
        pings.Add(mark);
        SendPings();
    }

    void ResetPings() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        pings.Clear(player.GetIdentity().GetId());
        SendPings();
    }

    void SetMutual(array<string> players) {
        mutual.Clear();
        mutual.Copy(players);
    }

    void AddPlayerToParty(string id) {
        registrations.Add(id, CarimUtil.GetClientPlayerIdentities().Get(id));
        PeriodicSend();
    }

    void RemovePlayerFromParty(string id) {
        registrations.Remove(id);
        mutual.RemoveItem(id);
        PeriodicSend();
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

    static array<PlayerBase> GetClientPlayerBases() {
        array<PlayerBase> players = new array<PlayerBase>;
        foreach(Man m : ClientData.m_PlayerBaseList) {
            players.Insert(PlayerBase.Cast(m));
        }
        return players;
    }
}
