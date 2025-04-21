#ifndef CarimRPCPartyRegister
#define CarimRPCPartyRegister

class CarimRPCPartyRegister extends CarimRPCBase<Param1<array<string>>> {
    override int GetType() {
        return CarimRPCTypesParty.REGISTER;
    }

    override void HandleClient(PlayerIdentity sender, Param1<array<string>> params) {
        CarimManagerPartyRegistrationClientSingleton.Get().SetMutual(params.param1);
    }

    override void HandleServer(PlayerIdentity sender, Param1<array<string>> params) {
        CarimManagerPartyRegistrationServerSingleton.Get().Register(sender.GetId(), params.param1);
    }
}

#endif
