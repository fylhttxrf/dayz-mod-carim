#ifndef CARIM_MissionServer
#define CARIM_MissionServer

modded class MissionServer {
    override void OnInit() {
        super.OnInit();
#ifdef CARIM_ENABLE_PARTY
        CarimManagerPartyRegistrationServerSingleton.Get();
        CarimManagerPartyMarkerServerSingleton.Get();
        CarimManagerPartyPositionServerSingleton.Get();
#endif
    }
}

#endif
