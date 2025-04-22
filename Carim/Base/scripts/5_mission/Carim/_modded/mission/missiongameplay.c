#ifndef CARIM_MissionGameplay
#define CARIM_MissionGameplay

modded class MissionGameplay {
    CarimManagerAutorun carimManagerAutorun;
    CarimManagerChat carimManagerChat;
    CarimManagerCompass carimManagerCompass;
    CarimManagerPartyMarkerClient carimManagerPartyMarkerClient;
    CarimManagerPartyPositionClient carimManagerPartyPositionClient;
    CarimManagerPartyRegistrationClient carimManagerPartyRegistrationClient;

    CarimModelSettings carimModelSettings;
    CarimModelChatSettings carimModelChatSettings;
    CarimModelPartyMarkers carimModelPartyMarkers;
    CarimModelPartyRegistrations carimModelPartyRegistrations;

    override void OnInit() {
        super.OnInit();

        carimModelSettings = CarimModelSettingsDAL.Get();

        if (CarimEnabled.Autorun()) {
            carimManagerAutorun = CarimManagerAutorunSingleton.Get();
        }
        if (CarimEnabled.Chat()) {
            carimModelChatSettings = CarimModelChatSettingsDAL.Get();
            carimManagerChat = CarimManagerChatSingleton.Get();
        }
        if (CarimEnabled.Compass()) {
            carimManagerCompass = CarimManagerCompassSingleton.Get();
        }
        if (CarimEnabled.Party()) {
            carimModelPartyMarkers = CarimModelPartyMarkersDAL.Get();
            carimModelPartyRegistrations = CarimModelPartyRegistrationsDAL.Get();
            carimManagerPartyMarkerClient = CarimManagerPartyMarkerClientSingleton.Get();
            carimManagerPartyPositionClient = CarimManagerPartyPositionClientSingleton.Get();
            carimManagerPartyRegistrationClient = CarimManagerPartyRegistrationClientSingleton.Get();
        }
    }

    override void OnUpdate(float timeslice) {
        super.OnUpdate(timeslice);
        if (CarimEnabled.Autorun()) {
            CarimManagerAutorunSingleton.Get().OnUpdate();
        }
        if (CarimEnabled.Chat()) {
            CarimManagerChatSingleton.Get().OnUpdate();
        }
        if (CarimEnabled.Compass()) {
            CarimManagerCompassSingleton.Get().OnUpdate();
        }
        if (CarimEnabled.Party()) {
            CarimManagerPartyRegistrationClientSingleton.Get().OnUpdate();
            CarimManagerPartyMarkerClientSingleton.Get().OnUpdate();
        }
    }
}

#endif
