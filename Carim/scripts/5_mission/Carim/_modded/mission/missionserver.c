#ifndef CARIM_MissionServer
#define CARIM_MissionServer

modded class MissionServer {
    override void OnInit() {
        super.OnInit();
        if (CarimEnabled.Party()) {
            CarimManagerPartyRegistrationServerSingleton.Get();
            CarimManagerPartyMarkerServerSingleton.Get();
            CarimManagerPartyPositionServerSingleton.Get();
        }
    }
}

#endif
