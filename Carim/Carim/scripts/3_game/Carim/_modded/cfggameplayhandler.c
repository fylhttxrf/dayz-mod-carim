modded class CfgGameplayHandler {
    // Carim
    static bool GetCarimInitialized() {
        return m_Data.CarimData.initialized;
    }

    static array<string> GetCarimAdminIds() {
        return m_Data.CarimData.adminIds;
    }

    // Autorun
    static bool GetCarimAutorunEnabled() {
        return m_Data.CarimData.CarimAutorunData.enabled;
    }

    // Chat
    static bool GetCarimChatEnabled() {
        return m_Data.CarimData.CarimChatData.enabled;
    }

    static int GetCarimChatColorDirect() {
        return m_Data.CarimData.CarimChatData.colorDirect;
    }

    static int GetCarimChatColorGlobal() {
        return m_Data.CarimData.CarimChatData.colorGlobal;
    }

    static int GetCarimChatColorServer() {
        return m_Data.CarimData.CarimChatData.colorServer;
    }

    static int GetCarimChatColorAlert() {
        return m_Data.CarimData.CarimChatData.colorAlert;
    }

    // Compass
    static bool GetCarimCompassEnabled() {
        return m_Data.CarimData.CarimCompassData.enabled;
    }

    static bool GetCarimCompassRequireNavItem() {
        return m_Data.CarimData.CarimCompassData.requireNavItem;
    }

    // Map
    static bool GetCarimMapEnabled() {
        return m_Data.CarimData.CarimMapData.enabled;
    }

    // Party
    static bool GetCarimPartyEnabled() {
        return m_Data.CarimData.CarimPartyData.enabled;
    }

    static int GetCarimPartyMaxPartySize() {
        return m_Data.CarimData.CarimPartyData.maxPartySize;
    }

    static int GetCarimPartyMaxPings() {
        return m_Data.CarimData.CarimPartyData.maxPings;
    }
}
