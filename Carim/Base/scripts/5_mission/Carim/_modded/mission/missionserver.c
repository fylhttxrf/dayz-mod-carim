#ifndef CARIM_MissionServer
#define CARIM_MissionServer

modded class MissionServer {
    ref CarimManagerPartyMarkerServer carimManagerPartyMarkerServer;
    ref CarimManagerPartyPositionServer carimManagerPartyPositionServer;
    ref CarimManagerPartyRegistrationServer carimManagerPartyRegistrationServer;
    ref CarimModelServerSettings carimModelServerSettings;
    ref CarimModelPartyParties carimModelPartyParties;

    void MissionServer() {
        carimModelSettings.Load();
        CarimLogging.settings = carimModelSettings;

        carimModelServerSettings = new CarimModelServerSettings;
        carimModelServerSettings.Load();

        if (CarimEnabled.Party()) {
            carimModelPartyParties = new CarimModelPartyParties(carimModelServerSettings.adminIds);
            carimManagerPartyMarkerServer = new CarimManagerPartyMarkerServer(carimModelPartyParties);
            carimManagerPartyPositionServer = new CarimManagerPartyPositionServer(carimModelPartyParties);
            carimManagerPartyRegistrationServer = new CarimManagerPartyRegistrationServer(carimModelPartyParties);
        }
    }

    override void CarimManagerPartyMarkerServerRegister(string id, CarimModelPartyMarkers markers) {
        if (carimManagerPartyMarkerServer) {
            carimManagerPartyMarkerServer.Register(id, markers);
        } else {
            CarimLogging.Warn(this, "carimManagerPartyMarkerServer not set");
        }
    }

    override void CarimManagerPartyRegistrationServerRegister(string id, array<string> ids) {
        if (carimManagerPartyRegistrationServer) {
            carimManagerPartyRegistrationServer.Register(id, ids);
        } else {
            CarimLogging.Warn(this, "carimManagerPartyRegistrationServer not set");
        }
    }
}

#endif
