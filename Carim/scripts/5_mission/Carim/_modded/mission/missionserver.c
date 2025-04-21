#ifndef CarimMissionServer
#define CarimMissionServer

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
