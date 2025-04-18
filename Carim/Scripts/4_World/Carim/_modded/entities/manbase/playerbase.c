modded class PlayerBase {
    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) {
        super.OnRPC(sender, rpc_type, ctx);
        switch (rpc_type) {
            case CarimRPCChat.GetType():
                CarimRPCChat.OnRPC(sender, ctx);
                break;
            case CarimRPCAutorun.GetType():
                CarimRPCAutorun.OnRPC(sender, ctx);
                break;
            case CarimRPCPartyMarkers.GetType():
                CarimRPCPartyMarkers.OnRPC(sender, ctx);
                break;
            case CarimRPCPartyPositions.GetType():
                CarimRPCPartyPositions.OnRPC(sender, ctx);
                break;
            case CarimRPCPartyRegister.GetType():
                CarimRPCPartyRegister.OnRPC(sender, ctx);
                break;
        }
    }
}
