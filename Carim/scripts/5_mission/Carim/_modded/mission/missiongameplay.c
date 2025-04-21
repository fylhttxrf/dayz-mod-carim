#ifndef CARIM_MissionGameplay
#define CARIM_MissionGameplay

modded class MissionGameplay {
    override void OnUpdate(float timeslice) {
        super.OnUpdate(timeslice);
        if (CarimEnabled.Autorun()) {
            CarimManagerAutorunSingleton.Get().OnUpdate();
        }
        if (CarimEnabled.Chat()) {
            CarimManagerChatSingleton.Get().OnUpdate();
        }
        if (CarimEnabled.Compass()) {
            CarimManagerCompassSingleton.Get().OnUpdate();
        }
        if (CarimEnabled.Party()) {
            CarimManagerPartyRegistrationClientSingleton.Get().OnUpdate();
            CarimManagerPartyMarkerClientSingleton.Get().OnUpdate();
        }
    }
}

#endif
