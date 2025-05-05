class CarimEnabled {
    static bool autorun;
    static bool chat;
    static bool compass;
    static bool cmap;
    static bool party;

    static bool initialized;

    static bool Autorun() {
        return autorun;
    }

    static bool Chat() {
        return chat;
    }

    static bool Compass() {
        return compass;
    }

    static bool Map() {
        return cmap;
    }

    static bool Party() {
        return party;
    }

    static void Initialize(bool notifyMission = false) {
        if (!initialized && CfgGameplayHandler.GetCarimInitialized()) {
            CarimLogging.Info(null, "Carim configuration loaded");

            autorun = CfgGameplayHandler.GetCarimAutorunEnabled();
            chat = CfgGameplayHandler.GetCarimChatEnabled();
            compass = CfgGameplayHandler.GetCarimCompassEnabled();
            cmap = CfgGameplayHandler.GetCarimMapEnabled();
            party = CfgGameplayHandler.GetCarimPartyEnabled();

            if (notifyMission) {
                GetGame().GetMission().OnGameplayDataHandlerLoad();
            }

            initialized = true;
        }
    }
}
