class CarimManagerPartyPingServer extends Managed {
    ref map<string, ref CarimModelPartyPings> markers = new map<string, ref CarimModelPartyPings>;
    ref CarimRPCPartyPings rpc = new CarimRPCPartyPings;
    ref CarimModelPartyParties parties;

    void CarimManagerPartyPingServer(CarimModelPartyParties inputParties) {
        parties = inputParties;
    }

    void Register(string id, CarimModelPartyPings playerMarkers) {
        markers.Set(id, playerMarkers);

        // Send markers to mutual members
        if (parties.mutuals.Contains(id)) {
            auto idMap = CarimManagerPartyUtil.GetServerIdPlayerMap();
            auto mutualPlayers = parties.mutuals.Get(id).ToArray();
            foreach(string playerId : mutualPlayers) {
                if (idMap.Contains(playerId)) {
                    PlayerBase player = idMap.Get(playerId);
                    if (player.GetIdentity() && player.IsAlive()) {
                        auto params = new Param2<string, CarimModelPartyPings>(id, playerMarkers);
                        rpc.Send(player, params, player.GetIdentity());
                    }
                }
            }
        }
    }
}
