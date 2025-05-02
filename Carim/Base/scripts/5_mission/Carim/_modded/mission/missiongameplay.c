#ifndef CARIM_MissionGameplay
#define CARIM_MissionGameplay

modded class MissionGameplay {
    ref CarimManagerAutorun carimManagerAutorun;
    ref CarimManagerChat carimManagerChat;
    ref CarimManagerCompass carimManagerCompass;
    ref CarimManagerMap carimManagerMap;
    ref CarimManagerPartyMarkerClient carimManagerPartyMarkerClient;
    ref CarimManagerPartyPositionClient carimManagerPartyPositionClient;
    ref CarimManagerPartyRegistrationClient carimManagerPartyRegistrationClient;

    ref CarimModelChatSettings carimModelChatSettings;
    ref CarimModelPartyMarkers carimModelPartyMarkers;
    ref CarimModelPartyRegistrations carimModelPartyRegistrations;

    void MissionGameplay() {
        carimModelSettings.Load();
        CarimLogging.settings = carimModelSettings;

        if (CarimEnabled.Autorun()) {
            carimManagerAutorun = new CarimManagerAutorun;
        }
        if (CarimEnabled.Chat()) {
            carimModelChatSettings = new CarimModelChatSettings;
            carimModelChatSettings.Load();
            carimManagerChat = new CarimManagerChat;
        }
        if (CarimEnabled.Compass()) {
            carimManagerCompass = new CarimManagerCompass;
        }
        if (CarimEnabled.Map()) {
            carimManagerMap = new CarimManagerMap;
        }
        if (CarimEnabled.Party()) {
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
        carimManagerPartyMarkerClient.AddServer(id, markers);
    }

    override void CarimManagerPartyPositionClientSetPositions(array<CarimModelPartyPlayer> players) {
        carimManagerPartyPositionClient.SetPositions(players);
    }

    override void CarimManagerPartyRegistrationClientSetMutual(array<string> ids) {
        carimManagerPartyRegistrationClient.SetMutual(ids);
    }

    override void OnUpdate(float timeslice) {
        super.OnUpdate(timeslice);
        if (CarimEnabled.Autorun()) {
            carimManagerAutorun.OnUpdate();
        }
        if (CarimEnabled.Chat()) {
            carimManagerChat.OnUpdate(carimModelChatSettings);
        }
        if (CarimEnabled.Compass()) {
            carimManagerCompass.OnUpdate(timeslice);
        }
        if (CarimEnabled.Map()) {
            carimManagerMap.OnUpdate(timeslice);
        }
        if (CarimEnabled.Party()) {
            carimManagerPartyRegistrationClient.OnUpdate(timeslice);
            carimManagerPartyMarkerClient.OnUpdate(timeslice);
            carimManagerPartyPositionClient.OnUpdate(timeslice);
        }
    }

    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (!menu) {
            if (CarimEnabled.Party()) {
                switch (id) {
                    case CarimMenuParty.REGISTER:
                        menu = new CarimMenuPartyRegister(carimManagerPartyRegistrationClient);
                        carimManagerPartyRegistrationClient.menu = CarimMenuPartyRegister.Cast(menu);
                        break;
                }
            }
            if (CarimEnabled.Map()) {
                switch (id) {
                    case CarimMenu.MAP:
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
