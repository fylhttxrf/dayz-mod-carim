#ifndef CarimRPCPartyPositions
#define CarimRPCPartyPositions

class CarimRPCPartyPositions extends CarimRPCBase<Param1<array<CarimModelPartyPlayer>>> {
    override int GetType() {
        return CarimRPCTypesParty.POSITIONS;
    }

    override void HandleClient(PlayerIdentity sender, Param1<array<CarimModelPartyPlayer>> params) {
        CarimManagerPartyPositionClientSingleton.Get().SetPositions(params.param1);
    }
}

#endif
