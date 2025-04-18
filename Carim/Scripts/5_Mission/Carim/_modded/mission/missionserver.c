modded class MissionServer {
    override void OnInit() {
        super.OnInit();
        CarimManagerPartyRegistrationServerSingleton.Get();
        CarimManagerPartyMarkerServerSingleton.Get();
        CarimManagerPartyPositionServerSingleton.Get();
    }
}
