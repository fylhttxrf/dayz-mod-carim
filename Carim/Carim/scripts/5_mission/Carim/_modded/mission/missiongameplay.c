#ifndef CARIM_MissionGameplay
#define CARIM_MissionGameplay

modded class MissionGameplay {
    ref CarimManagerAutorun carimManagerAutorun;
    ref CarimManagerChat carimManagerChat;
    ref CarimManagerCompass carimManagerCompass;
    ref CarimManagerPartyMarkerClient carimManagerPartyMarkerClient;
    ref CarimManagerPartyPositionClient carimManagerPartyPositionClient;
    ref CarimManagerPartyRegistrationClient carimManagerPartyRegistrationClient;

    ref CarimModelChatSettings carimModelChatSettings;
    ref CarimModelPartyMarkers carimModelPartyMarkers;
    ref CarimModelPartyRegistrations carimModelPartyRegistrations;

    override void OnGameplayDataHandlerLoad() {
        super.OnGameplayDataHandlerLoad();

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
        if (CarimEnabled.Party() && !carimManagerPartyMarkerClient && !carimManagerPartyPositionClient && !carimManagerPartyRegistrationClient) {
            carimModelPartyMarkers = new CarimModelPartyMarkers;
            carimModelPartyMarkers.Load();
            carimModelPartyRegistrations = new CarimModelPartyRegistrations;
            carimModelPartyRegistrations.Load();
            carimManagerPartyMarkerClient = new CarimManagerPartyMarkerClient(carimModelPartyMarkers, carimModelPartyRegistrations);
            carimManagerPartyPositionClient = new CarimManagerPartyPositionClient(carimModelPartyRegistrations);
            carimManagerPartyRegistrationClient = new CarimManagerPartyRegistrationClient(carimModelPartyRegistrations);
        }
    }

    override void CarimManagerPartyMarkerClientAddServer(string id, CarimModelPartyMarkers markers) {
        if (carimManagerPartyMarkerClient) {
            carimManagerPartyMarkerClient.AddServer(id, markers);
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

        CarimEnabled.Initialize();

        if (CarimEnabled.Autorun() && carimManagerAutorun) {
            carimManagerAutorun.OnUpdate();
        }
        if (CarimEnabled.Chat() && carimManagerChat) {
            carimManagerChat.OnUpdate(carimModelChatSettings);
        }
        if (CarimEnabled.Compass() && carimManagerCompass) {
            carimManagerCompass.OnUpdate(timeslice);
        }
        if (CarimEnabled.Party() && carimManagerPartyRegistrationClient && carimManagerPartyMarkerClient && carimManagerPartyPositionClient) {
            carimManagerPartyRegistrationClient.OnUpdate(timeslice);
            carimManagerPartyMarkerClient.OnUpdate(timeslice);
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

#endif
