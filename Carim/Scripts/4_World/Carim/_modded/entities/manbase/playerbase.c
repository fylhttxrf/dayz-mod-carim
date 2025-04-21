#ifndef CarimPlayerBase
#define CarimPlayerBase

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
#ifdef CARIM_ENABLE_CHAT
                carimRPCChat.OnRPC(sender, ctx);
#else
                CarimLogging.Trace("Chat disabled");
#endif
                break;
            case carimRPCAutorun.GetType():
#ifdef CARIM_ENABLE_AUTORUN
                carimRPCAutorun.OnRPC(sender, ctx);
#else
                CarimLogging.Trace("Autorun disabled");
#endif
                break;
            case carimRPCPartyMarkers.GetType():
#ifdef CARIM_ENABLE_PARTY
                carimRPCPartyMarkers.OnRPC(sender, ctx);
#else
                CarimLogging.Trace("Party disabled");
#endif
                break;
            case carimRPCPartyPositions.GetType():
#ifdef CARIM_ENABLE_PARTY
                carimRPCPartyPositions.OnRPC(sender, ctx);
#else
                CarimLogging.Trace("Party disabled");
#endif
                break;
            case carimRPCPartyRegister.GetType():
#ifdef CARIM_ENABLE_PARTY
                carimRPCPartyRegister.OnRPC(sender, ctx);
#else
                CarimLogging.Trace("Party disabled");
#endif
                break;
        }
    }
}
#endif
