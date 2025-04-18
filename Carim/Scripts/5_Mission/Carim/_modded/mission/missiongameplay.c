modded class MissionGameplay {
    override void OnUpdate(float timeslice) {
        super.OnUpdate(timeslice);
        CarimManagerAutorunSingleton.Get().OnUpdate();
        CarimManagerChatSingleton.Get().OnUpdate();
        CarimManagerCompassSingleton.Get().OnUpdate();
        CarimManagerPartyRegistrationClientSingleton.Get().OnUpdate();
        CarimManagerPartyMarkerClientSingleton.Get().OnUpdate();
    }
}
