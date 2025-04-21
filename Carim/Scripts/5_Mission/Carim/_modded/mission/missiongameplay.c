#ifndef CarimMissionGameplay
#define CarimMissionGameplay

modded class MissionGameplay {
    override void OnUpdate(float timeslice) {
        super.OnUpdate(timeslice);
#ifdef CARIM_ENABLE_AUTORUN
        CarimManagerAutorunSingleton.Get().OnUpdate();
#endif
#ifdef CARIM_ENABLE_CHAT
        CarimManagerChatSingleton.Get().OnUpdate();
#endif
#ifdef CARIM_ENABLE_COMPASS
        CarimManagerCompassSingleton.Get().OnUpdate();
#endif
#ifdef CARIM_ENABLE_PARTY
        CarimManagerPartyRegistrationClientSingleton.Get().OnUpdate();
        CarimManagerPartyMarkerClientSingleton.Get().OnUpdate();
#endif
    }
}

#endif
