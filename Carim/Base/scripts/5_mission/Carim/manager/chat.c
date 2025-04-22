#ifndef CARIM_CarimManagerChat
#define CARIM_CarimManagerChat

class CarimManagerChat extends Managed {
    bool isChannelGlobal = true;

    void OnUpdate() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UACarimChatChannel")) {
                isChannelGlobal = !isChannelGlobal;
                GetGame().Chat("Channel switched to " + getChannelName(), "colorAction");
            }
            if (CarimUtil.CheckInput("UACarimChatSizeDown")) {
                CarimModelChatSettingsDAL.Get().size = Math.Max(12, CarimModelChatSettingsDAL.Get().size - 1);
                CarimModelChatSettingsDAL.Save();
                MissionGameplay.Cast(GetGame().GetMission()).m_Chat.CarimUpdateSize();
            }
            if (CarimUtil.CheckInput("UACarimChatSizeUp")) {
                CarimModelChatSettingsDAL.Get().size = Math.Min(30, CarimModelChatSettingsDAL.Get().size + 1);
                CarimModelChatSettingsDAL.Save();
                MissionGameplay.Cast(GetGame().GetMission()).m_Chat.CarimUpdateSize();
            }
        }
    }

    string getChannelName() {
        if (isChannelGlobal) {
            return "Global";
        } else {
            return "Direct";
        }
    }
}

typedef CarimSingleton<CarimManagerChat> CarimManagerChatSingleton;

#endif
