class CarimManagerPartyMarkerServer extends Managed {
    ref map<string, ref CarimModelPartyMarkers> markers = new map<string, ref CarimModelPartyMarkers>;

    void Register(string id, CarimModelPartyMarkers playerMarkers) {
        markers.Set(id, playerMarkers);

        // Send markers to mutual members
        auto parties = CarimManagerPartyRegistrationServerSingleton.Get().parties;
        if (parties.mutuals.Contains(id)) {
            auto idMap = CarimUtil.GetServerIdPlayerMap();
            foreach(string playerId : parties.mutuals.Get(id)) {
                if (idMap.Contains(playerId)) {
                    PlayerBase player = idMap.Get(playerId);
                    if (player.GetIdentity() && player.IsAlive()) {
                        auto params = new Param2<string, CarimModelPartyMarkers>(id, playerMarkers);
                        CarimRPCPartyMarkers.Send(player, params, true, player.GetIdentity());
                    }
                }
            }
        }
    }
}

typedef CarimSingleton<CarimManagerPartyMarkerServer> CarimManagerPartyMarkerServerSingleton;
