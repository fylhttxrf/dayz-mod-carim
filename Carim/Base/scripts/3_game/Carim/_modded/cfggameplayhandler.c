#ifndef CARIM_CfgGameplayHandler
#define CARIM_CfgGameplayHandler

modded class CfgGameplayHandler {
    static bool GetCarimInitialized() {
        return m_Data.CarimData.initialized;
    }

    static array<string> GetCarimAdminIds() {
        return m_Data.CarimData.adminIds;
    }

    static bool GetCarimAutorunEnabled() {
        return m_Data.CarimData.CarimAutorunData.enabled;
    }

    static bool GetCarimChatEnabled() {
        return m_Data.CarimData.CarimChatData.enabled;
    }

    static bool GetCarimCompassEnabled() {
        return m_Data.CarimData.CarimCompassData.enabled;
    }

    static bool GetCarimMapEnabled() {
        return m_Data.CarimData.CarimMapData.enabled;
    }

    static bool GetCarimPartyEnabled() {
        return m_Data.CarimData.CarimPartyData.enabled;
    }
}

#endif
