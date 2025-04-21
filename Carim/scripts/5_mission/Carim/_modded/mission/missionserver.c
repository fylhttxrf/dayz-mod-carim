#ifndef CarimMissionServer
#define CarimMissionServer

modded class MissionServer {
    override void OnInit() {
        super.OnInit();
#ifndef CARIM_DISABLE_PARTY
        CarimManagerPartyRegistrationServerSingleton.Get();
        CarimManagerPartyMarkerServerSingleton.Get();
        CarimManagerPartyPositionServerSingleton.Get();
#endif
    }
}

#endif
