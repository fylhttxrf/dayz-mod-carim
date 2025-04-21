#ifndef CarimMissionGameplay
#define CarimMissionGameplay

modded class MissionGameplay {
    override void OnUpdate(float timeslice) {
        super.OnUpdate(timeslice);
#ifndef CARIM_DISABLE_AUTORUN
        CarimManagerAutorunSingleton.Get().OnUpdate();
#endif
#ifndef CARIM_DISABLE_CHAT
        CarimManagerChatSingleton.Get().OnUpdate();
#endif
#ifndef CARIM_DISABLE_COMPASS
        CarimManagerCompassSingleton.Get().OnUpdate();
#endif
#ifndef CARIM_DISABLE_PARTY
        CarimManagerPartyRegistrationClientSingleton.Get().OnUpdate();
        CarimManagerPartyMarkerClientSingleton.Get().OnUpdate();
#endif
    }
}

#endif
