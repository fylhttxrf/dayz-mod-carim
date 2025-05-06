modded class MissionGameplay {
    ref CarimManagerMarker carimManagerMarker;

    ref CarimManagerAutorun carimManagerAutorun;
    ref CarimManagerChat carimManagerChat;
    ref CarimManagerCompass carimManagerCompass;
    ref CarimManagerPartyClient carimManagerPartyClient;

    ref CarimModelChatSettings carimModelChatSettings;

    ref CarimModelMapMarkers carimModelMapMarkers;
    ref CarimModelPartyPings carimModelPartyPings;
    ref CarimModelPartyMarkers carimModelPartyMarkers;
    ref CarimModelPartyPositions carimModelPartyPositions;

    ref CarimModelPartyRegistrations carimModelPartyRegistrations;

    override void OnGameplayDataHandlerLoad() {
        super.OnGameplayDataHandlerLoad();

        if (CarimEnabled.Autorun() && !carimManagerAutorun) {
            // Manager
            carimManagerAutorun = new CarimManagerAutorun;
        }
        if (CarimEnabled.Chat() && !carimManagerChat) {
            // Local
            carimModelChatSettings = new CarimModelChatSettings;
            carimModelChatSettings.Load();

            // Manager
            carimManagerChat = new CarimManagerChat;
        }
        if (CarimEnabled.Compass() && !carimManagerCompass) {
            // Manager
            carimManagerCompass = new CarimManagerCompass;
        }
        if (CarimEnabled.Map()) {
            // Local
            carimModelMapMarkers = new CarimModelMapMarkers;
            carimModelMapMarkers.Load();
        }
        if (CarimEnabled.Party() && !carimManagerPartyClient) {
            // Local
            carimModelPartyPings = new CarimModelPartyPings;
            carimModelPartyPings.Load();
            carimModelPartyRegistrations = new CarimModelPartyRegistrations;
            carimModelPartyRegistrations.Load();

            // From Server
            carimModelPartyMarkers = new CarimModelPartyMarkers;
            carimModelPartyPositions = new CarimModelPartyPositions;

            // Manager
            carimManagerPartyClient = new CarimManagerPartyClient(carimModelPartyMarkers, carimModelPartyPings, carimModelPartyPositions, carimModelPartyRegistrations);
        }

        if (!carimManagerMarker) {
            // Manager
            carimManagerMarker = new CarimManagerMarker(carimModelMapMarkers, carimModelPartyPings, carimModelPartyMarkers, CarimModelPartyPositions);
        }
    }

    // ---------- RPC callbacks

    override void CarimPartyClientAddMarkers(string id, CarimModelPartyMarkers markers) {
        if (carimModelPartyMarkers) {
            carimModelPartyMarkers.Replace(id, markers);
        }
    }

    override void CarimPartyClientSetPositions(CarimModelPartyPositions positions) {
        if (carimModelPartyPositions) {
            carimModelPartyPositions.Clear();
            foreach(CarimModelPartyPlayer position : positions) {
                carimModelPartyPositions.Insert(position.id, position);
            }
        }
    }

    override void CarimPartyClientSetMutual(array<string> ids) {
        if (carimManagerPartyClient) {
            carimManagerPartyClient.SetMutual(ids);
        }
    }

    // ---------- RPC callbacks end

    override void OnUpdate(float timeslice) {
        super.OnUpdate(timeslice);

        CarimEnabled.Initialize(true);

        if (carimManagerMarker) {
            carimManagerMarker.OnUpdate(timeslice);
        }

        if (CarimEnabled.Autorun() && carimManagerAutorun) {
            carimManagerAutorun.OnUpdate();
        }
        if (CarimEnabled.Chat() && carimManagerChat) {
            carimManagerChat.OnUpdate(carimModelChatSettings);
        }
        if (CarimEnabled.Compass() && carimManagerCompass) {
            carimManagerCompass.OnUpdate(timeslice);
        }
        if (CarimEnabled.Party() && carimManagerPartyRegistrationClient && carimManagerPartyPingClient && carimManagerPartyPositionClient) {
            carimManagerPartyRegistrationClient.OnUpdate(timeslice);
            carimManagerPartyPingClient.OnUpdate(timeslice);
            carimManagerPartyPositionClient.OnUpdate(timeslice);
        }
    }

    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu;
        if (!CarimEnabled.Map() || id != MENU_MAP) {
            menu = super.CreateScriptedMenu(id);
        }
        if (!menu) {
            if (CarimEnabled.Party()) {
                switch (id) {
                    case CarimMenuParty.REGISTER:
                        menu = new CarimMenuPartyRegister(carimManagerPartyRegistrationClient);
                        break;
                }
            }
            if (CarimEnabled.Map()) {
                switch (id) {
                    case MENU_MAP:
                        menu = new CarimMenuMap;
                        break;
                }
            }
            if (menu) {
                menu.SetID(id);
            }
        }
        return menu;
    }
}
