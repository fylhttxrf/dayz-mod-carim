class CarimRPCPartyPositions extends CarimRPCBase<Param1<array<CarimModelPartyPlayer>>> {
    override static int GetType() {
        return CarimRPCTypesParty.POSITIONS;
    }

    override static void HandleClient(PlayerIdentity sender, Param1<array<CarimModelPartyPlayer>> params) {
        CarimManagerPartyPositionClientSingleton.Get().SetPositions(params.param1);
    }
}
