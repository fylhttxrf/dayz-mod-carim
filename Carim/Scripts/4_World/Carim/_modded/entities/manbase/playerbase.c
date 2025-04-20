modded class PlayerBase {
    ref CarimRPCAutorun carimRPCAutorun = new CarimRPCAutorun;
    ref CarimRPCChat carimRPCChat = new CarimRPCChat;
    ref CarimRPCPartyMarkers carimRPCPartyMarkers = new CarimRPCPartyMarkers;
    ref CarimRPCPartyPositions carimRPCPartyPositions = new CarimRPCPartyPositions;
    ref CarimRPCPartyRegister carimRPCPartyRegister = new CarimRPCPartyRegister;

    override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) {
        super.OnRPC(sender, rpc_type, ctx);
        switch (rpc_type) {
            case carimRPCChat.GetType():
                carimRPCChat.OnRPC(sender, ctx);
                break;
            case carimRPCAutorun.GetType():
                carimRPCAutorun.OnRPC(sender, ctx);
                break;
            case carimRPCPartyMarkers.GetType():
                carimRPCPartyMarkers.OnRPC(sender, ctx);
                break;
            case carimRPCPartyPositions.GetType():
                carimRPCPartyPositions.OnRPC(sender, ctx);
                break;
            case carimRPCPartyRegister.GetType():
                carimRPCPartyRegister.OnRPC(sender, ctx);
                break;
        }
    }
}
