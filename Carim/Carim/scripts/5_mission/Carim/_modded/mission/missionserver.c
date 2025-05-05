modded class MissionServer {
    ref CarimManagerPartyPingServer carimManagerPartyPingServer;
    ref CarimManagerPartyPositionServer carimManagerPartyPositionServer;
    ref CarimManagerPartyRegistrationServer carimManagerPartyRegistrationServer;
    ref CarimModelPartyParties carimModelPartyParties;

    override void OnGameplayDataHandlerLoad() {
        super.OnGameplayDataHandlerLoad();

        CarimEnabled.Initialize();

        if (CarimEnabled.Party() && !carimManagerPartyPingServer && !carimManagerPartyPositionServer && !carimManagerPartyRegistrationServer) {
            carimModelPartyParties = new CarimModelPartyParties;
            carimManagerPartyPingServer = new CarimManagerPartyPingServer(carimModelPartyParties);
            carimManagerPartyPositionServer = new CarimManagerPartyPositionServer(carimModelPartyParties);
            carimManagerPartyRegistrationServer = new CarimManagerPartyRegistrationServer(carimModelPartyParties);
        }
    }

    override void CarimManagerPartyPingServerRegister(string id, CarimModelPartyPings markers) {
        if (carimManagerPartyPingServer) {
            carimManagerPartyPingServer.Register(id, markers);
        }
    }

    override void CarimManagerPartyRegistrationServerRegister(string id, array<string> ids) {
        if (carimManagerPartyRegistrationServer) {
            carimManagerPartyRegistrationServer.Register(id, ids);
        }
    }
}
