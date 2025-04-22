#ifndef CARIM_CarimManagerPartyPositionServer
#define CARIM_CarimManagerPartyPositionServer

class CarimManagerPartyPositionServer extends Managed {
    ref CarimRPCPartyPositions rpc = new CarimRPCPartyPositions;

    void CarimManagerPartyPositionServer() {
        // TODO: stagger this so it doesn't send to everyone at once
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Send, 10000, true);
    }

    void ~CarimManagerPartyPositionServer() {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Send);
    }

    void Send() {
        map<string, PlayerBase> idMap = CarimUtil.GetServerIdPlayerMap();
        map<string, ref CarimModelPartyPlayer> players = new map<string, ref CarimModelPartyPlayer>;

        // Harvest the relevant information
        foreach(string id, PlayerBase player : idMap) {
            CarimLogging.Trace("PartyPositionServer Harvest " + id);
            auto playerInfo = new CarimModelPartyPlayer(id, player.GetPosition(), player.GetHealthLevel());
            CarimLogging.Trace("PartyPositionServer Harvested " + playerInfo.Repr());
            players.Insert(id, playerInfo);
        }

        // Send the information to each recipient's mutual party members
        auto parties = CarimManagerPartyRegistrationServerSingleton.Get().parties;
        auto ids = parties.mutuals.GetKeyArray();
        foreach(string recipient : ids) {
            if (parties.mutuals.Contains(recipient)) {
                array<CarimModelPartyPlayer> sharedInfo = new array<CarimModelPartyPlayer>;
                foreach(string mutual : parties.mutuals.Get(recipient).ToArray()) {
                    if (players.Contains(mutual)) {
                        sharedInfo.Insert(players.Get(mutual));
                    }
                }
                Param1<array<CarimModelPartyPlayer>> params = new Param1<array<CarimModelPartyPlayer>>(sharedInfo);
                rpc.Send(idMap.Get(recipient), params, idMap.Get(recipient).GetIdentity());
            }
        }
    }
}

typedef CarimSingleton<CarimManagerPartyPositionServer> CarimManagerPartyPositionServerSingleton;

#endif
