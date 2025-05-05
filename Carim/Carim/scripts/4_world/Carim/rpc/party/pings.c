class CarimRPCPartyPings extends CarimRPCBase<Param2<string, CarimModelPartyPings>> {
    override int GetType() {
        return CarimRPCTypesParty.PINGS;
    }

    override void HandleServer(PlayerIdentity sender, Param2<string, CarimModelPartyPings> params) {
        MissionBaseWorld.Cast(GetGame().GetMission()).CarimManagerPartyPingServerRegister(sender.GetId(), params.param2);
    }

    override void HandleClient(PlayerIdentity sender, Param2<string, CarimModelPartyPings> params) {
        MissionBaseWorld.Cast(GetGame().GetMission()).CarimManagerPartyPingClientAddServer(params.param1, params.param2);
    }
}
