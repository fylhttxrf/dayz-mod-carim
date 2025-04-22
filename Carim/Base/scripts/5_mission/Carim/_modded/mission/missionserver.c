#ifndef CARIM_MissionServer
#define CARIM_MissionServer

modded class MissionServer {
    CarimManagerPartyMarkerServer carimManagerPartyMarkerServer;
    CarimManagerPartyPositionServer carimManagerPartyPositionServer;
    CarimManagerPartyRegistrationServer carimManagerPartyRegistrationServer;

    CarimModelSettings carimModelSettings;
    CarimModelServerSettings carimModelServerSettings;

    override void OnInit() {
        super.OnInit();

        carimModelSettings = CarimModelSettingsDAL.Get();
        carimModelServerSettings = CarimModelServerSettingsDAL.Get();

        if (CarimEnabled.Party()) {
            carimManagerPartyMarkerServer = CarimManagerPartyMarkerServerSingleton.Get();
            carimManagerPartyPositionServer = CarimManagerPartyPositionServerSingleton.Get();
            carimManagerPartyRegistrationServer = CarimManagerPartyRegistrationServerSingleton.Get();
        }
    }
}

#endif
