modded class MissionGameplay {
    ref CarimManagerMarker carimManagerMarker;

    ref CarimManagerAutorun carimManagerAutorun;
    ref CarimManagerChat carimManagerChat;
    ref CarimManagerCompass carimManagerCompass;
    ref CarimManagerPartyPingClient carimManagerPartyPingClient;
    ref CarimManagerPartyPositionClient carimManagerPartyPositionClient;
    ref CarimManagerPartyRegistrationClient carimManagerPartyRegistrationClient;

    ref CarimModelChatSettings carimModelChatSettings;
    ref CarimModelMapMarkers carimModelMapMarkers;
    ref CarimModelPartyMarkers carimModelPartyMarkers;
    ref CarimModelPartyPings carimModelPartyPings;
    ref CarimModelPartyPositions CarimModelPartyPositions;
    ref CarimModelPartyRegistrations carimModelPartyRegistrations;

    override void OnGameplayDataHandlerLoad() {
        super.OnGameplayDataHandlerLoad();

        if (!carimManagerMarker) {
            carimManagerMarker = new CarimManagerMarker;
        }

        if (CarimEnabled.Autorun() && !carimManagerAutorun) {
            carimManagerAutorun = new CarimManagerAutorun;
        }
        if (CarimEnabled.Chat() && !carimManagerChat) {
            carimModelChatSettings = new CarimModelChatSettings;
            carimModelChatSettings.Load();
            carimManagerChat = new CarimManagerChat;
        }
        if (CarimEnabled.Compass() && !carimManagerCompass) {
            carimManagerCompass = new CarimManagerCompass;
        }
        if (CarimEnabled.Map()) {
            carimModelMapMarkers = new CarimModelMapMarkers;
        }
        if (CarimEnabled.Party() && !carimManagerPartyPingClient && !carimManagerPartyPositionClient && !carimManagerPartyRegistrationClient) {
            carimModelPartyPings = new CarimModelPartyPings;
            carimModelPartyPings.Load();
            carimModelPartyRegistrations = new CarimModelPartyRegistrations;
            carimModelPartyRegistrations.Load();
            carimManagerPartyPingClient = new CarimManagerPartyPingClient(carimModelPartyPings, carimModelMapMarkers, carimModelPartyRegistrations);
            carimManagerPartyPositionClient = new CarimManagerPartyPositionClient(carimModelPartyRegistrations);
            carimManagerPartyRegistrationClient = new CarimManagerPartyRegistrationClient(carimModelPartyRegistrations);
        }
    }

    override void CarimManagerPartyPingClientAddServer(string id, CarimModelPartyPings markers) {
        if (carimManagerPartyPingClient) {
            carimManagerPartyPingClient.AddServer(id, markers);
        }
    }

    override void CarimManagerPartyPositionClientSetPositions(array<CarimModelPartyPlayer> players) {
        if (carimManagerPartyPositionClient) {
            carimManagerPartyPositionClient.SetPositions(players);
        }
    }

    override void CarimManagerPartyRegistrationClientSetMutual(array<string> ids) {
        if (carimManagerPartyRegistrationClient) {
            carimManagerPartyRegistrationClient.SetMutual(ids);
        }
    }

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
