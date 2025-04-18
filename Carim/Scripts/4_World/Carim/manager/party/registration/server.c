class CarimManagerPartyRegistrationServer extends Managed {
    ref CarimModelPartyParties parties = new CarimModelPartyParties;

    void CarimManagerPartyRegistrationServer() {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Send, 10000, true);
    }

    void ~CarimManagerPartyRegistrationServer() {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Send);
    }

    void Register(string id, array<string> players) {
        parties.Register(id, players);
    }

    void Send() {
        map<string, PlayerBase> idMap = CarimUtil.GetServerIdPlayerMap();
        foreach(string id, PlayerBase player : idMap) {
            if (player.IsAlive()) {
                array<string> mutuals = new array<string>;
                if (parties.mutuals.Contains(id)) {
                    foreach(string mutual : parties.mutuals.Get(id)) {
                        mutuals.Insert(mutual);
                    }
                }
                Param1<array<string>> params = new Param1<array<string>>(mutuals);
                CarimRPCPartyRegister.Send(player, params, true, player.GetIdentity());
            }
        }
    }
}

typedef CarimSingleton<CarimManagerPartyRegistrationServer> CarimManagerPartyRegistrationServerSingleton;
