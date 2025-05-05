modded class MissionBaseWorld {
    void CarimManagerPartyPingServerRegister(string id, CarimModelPartyPings markers);
    void CarimManagerPartyPingClientAddServerMarker(string id, CarimModelPartyMarkers markers);
    void CarimManagerPartyPingClientAddServerPings(string id, CarimModelPartyPings markers);

    void CarimManagerPartyPositionClientSetPositions(array<CarimModelPartyPlayer> players);

    void CarimManagerPartyRegistrationClientSetMutual(array<string> ids);
    void CarimManagerPartyRegistrationServerRegister(string id, array<string> ids);
}
