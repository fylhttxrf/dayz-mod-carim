#ifndef CARIM_ChatLine
#define CARIM_ChatLine

modded class ChatLine {
    void ChatLine(Widget root_widget) {
        if (CarimEnabled.Chat()) {
            m_RootWidget = GetGame().GetWorkspace().CreateWidgets("Carim/Base/gui/layouts/chatline.layout", root_widget);
            m_NameWidget = TextWidget.Cast(m_RootWidget.FindAnyWidget("ChatItemSenderWidget"));
            m_TextWidget = TextWidget.Cast(m_RootWidget.FindAnyWidget("ChatItemTextWidget"));
            m_NameWidget.SetTextExactSize(CarimModelChatSettingsDAL.Get().size);
            m_TextWidget.SetTextExactSize(CarimModelChatSettingsDAL.Get().size);
        }
    }

    override void Set(ChatMessageEventParams params) {
        super.Set(params);
        if (CarimEnabled.Chat()) {
            int channel = params.param1;
            if (channel & CCSystem) {
                if (params.param2 == "" && params.param3.IndexOf(" : ") > 0) {
                    CarimSetColour(CarimModelChatSettingsDAL.Get().color_global);
                } else {
                    SetColour(CarimModelChatSettingsDAL.Get().color_alert);
                }
            } else if (channel & CCAdmin) {
                SetColour(CarimModelChatSettingsDAL.Get().color_server);
            } else if (channel == 0 || channel & CCDirect) {
                CarimSetColour(CarimModelChatSettingsDAL.Get().color_direct);
            } else {
                SetColour(CarimModelChatSettingsDAL.Get().color_server);
            }
        }
    }

    void CarimUpdateSize() {
        m_NameWidget.SetTextExactSize(CarimModelChatSettingsDAL.Get().size);
        m_TextWidget.SetTextExactSize(CarimModelChatSettingsDAL.Get().size);
    }

    void CarimSetColour(int colour) {
        m_NameWidget.SetColor(colour);
        m_TextWidget.SetColor(colour);
    }
}

#endif
