class CarimRPCPartyPings extends CarimRPCBase<Param2<string, CarimModelPartyPings>> {
    override int GetType() {
        return CarimRPCTypesParty.PINGS;
    }

    override void HandleServer(PlayerIdentity sender, Param2<string, CarimModelPartyPings> params) {
        MissionBaseWorld.Cast(GetGame().GetMission()).CarimPartyServerAddPings(sender.GetId(), params.param2);
    }

    override void HandleClient(PlayerIdentity sender, Param2<string, CarimModelPartyPings> params) {
        MissionBaseWorld.Cast(GetGame().GetMission()).CarimPartyClientAddMarkers(params.param1, params.param2);
    }
}
