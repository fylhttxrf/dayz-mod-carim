class CarimRPCPartyRegister extends CarimRPCBase<Param1<array<string>>> {
    override static int GetType() {
        return CarimRPCTypesParty.REGISTER;
    }

    override static void HandleClient(PlayerIdentity sender, Param1<array<string>> params) {
        CarimManagerPartyRegistrationClientSingleton.Get().SetMutual(params.param1);
    }

    override static void HandleServer(PlayerIdentity sender, Param1<array<string>> params) {
        CarimManagerPartyRegistrationServerSingleton.Get().Register(sender.GetId(), params.param1);
    }
}
