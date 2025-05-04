#ifndef CARIM_MissionServer
#define CARIM_MissionServer

modded class MissionServer {
    ref CarimManagerPartyMarkerServer carimManagerPartyMarkerServer;
    ref CarimManagerPartyPositionServer carimManagerPartyPositionServer;
    ref CarimManagerPartyRegistrationServer carimManagerPartyRegistrationServer;
    ref CarimModelPartyParties carimModelPartyParties;

    override void OnGameplayDataHandlerLoad() {
        super.OnGameplayDataHandlerLoad();

        CarimEnabled.Initialize();

        if (CarimEnabled.Party()) {
            carimModelPartyParties = new CarimModelPartyParties;
            carimManagerPartyMarkerServer = new CarimManagerPartyMarkerServer(carimModelPartyParties);
            carimManagerPartyPositionServer = new CarimManagerPartyPositionServer(carimModelPartyParties);
            carimManagerPartyRegistrationServer = new CarimManagerPartyRegistrationServer(carimModelPartyParties);
        }
    }

    override void CarimManagerPartyMarkerServerRegister(string id, CarimModelPartyMarkers markers) {
        if (carimManagerPartyMarkerServer) {
            carimManagerPartyMarkerServer.Register(id, markers);
        }
    }

    override void CarimManagerPartyRegistrationServerRegister(string id, array<string> ids) {
        if (carimManagerPartyRegistrationServer) {
            carimManagerPartyRegistrationServer.Register(id, ids);
        }
    }
}

#endif
