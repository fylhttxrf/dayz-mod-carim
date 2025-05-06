class CarimManagerPartyServer extends Managed {
    ref CarimModelPartyMarkers markers = new CarimModelPartyMarkers;

    ref CarimModelPartyParties parties;

    ref CarimRPCPartyPings rpcPing = new CarimRPCPartyPings;
    ref CarimRPCPartyPositions rpcPositions = new CarimRPCPartyPositions;
    ref CarimRPCPartyRegister rpcRegister = new CarimRPCPartyRegister;

    void CarimManagerPartyServer(CarimModelPartyParties iParties) {
        parties = iParties;
        // TODO: stagger this so it doesn't send to everyone at once
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.SendPositions, 10000, true);
    }

    void ~CarimManagerPartyServer() {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.SendPositions);
    }

    void RegisterMarkers(string id, CarimModelPartyPings playerMarkers) {
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
                        rpcPing.Send(player, params, player.GetIdentity());
                    }
                }
            }
        }
    }

    void RegisterParty(string id, array<string> players) {
        string jsonPlayers;
        if (CarimLogging.TraceEnabled()) {
            JsonSerializer().WriteToString(players, false, jsonPlayers);
        }
        CarimLogging.Trace(this, "Register " + id + ", " + jsonPlayers);
        CarimLogging.Trace(this, "Before: " + parties.Repr());
        bool changed = parties.Register(id, players);
        CarimLogging.Trace(this, "After: " + parties.Repr());
        if (changed) {
            SendParty();
        }
    }

    void SendPositions() {
        map<string, PlayerBase> idMap = CarimManagerPartyUtil.GetServerIdPlayerMap();
        map<string, ref CarimModelPartyPlayer> players = new map<string, ref CarimModelPartyPlayer>;

        // Harvest the relevant information
        foreach(string id, PlayerBase player : idMap) {
            CarimLogging.Trace(this, "PartyPositionServer Harvest " + id);
            auto playerInfo = new CarimModelPartyPlayer(id, player.GetPosition(), player.GetHealthLevel());
            CarimLogging.Trace(this, "PartyPositionServer Harvested " + playerInfo.Repr());
            players.Insert(id, playerInfo);
        }

        // Send the information to each recipient's mutual party members
        auto ids = parties.mutuals.GetKeyArray();
        foreach(string recipient : ids) {
            if (idMap.Contains(recipient) && parties.mutuals.Contains(recipient)) {
                // TODO: clean up registered players that are no longer present
                array<CarimModelPartyPlayer> sharedInfo = new array<CarimModelPartyPlayer>;
                auto mutualPlayers = parties.mutuals.Get(recipient).ToArray();
                foreach(string mutual : mutualPlayers) {
                    if (players.Contains(mutual)) {
                        sharedInfo.Insert(players.Get(mutual));
                    }
                }
                Param1<array<CarimModelPartyPlayer>> params = new Param1<array<CarimModelPartyPlayer>>(sharedInfo);
                rpcPositions.Send(idMap.Get(recipient), params, idMap.Get(recipient).GetIdentity());
            }
        }
    }

    void SendParty() {
        map<string, PlayerBase> idMap = CarimManagerPartyUtil.GetServerIdPlayerMap();
        foreach(string id, PlayerBase player : idMap) {
            array<string> mutuals = new array<string>;
            if (parties.mutuals.Contains(id)) {
                auto mutualPlayers = parties.mutuals.Get(id).ToArray();
                foreach(string mutual : mutualPlayers) {
                    mutuals.Insert(mutual);
                }
            }
            Param1<array<string>> params = new Param1<array<string>>(mutuals);
            rpcRegister.Send(player, params, player.GetIdentity());
        }
    }
}
