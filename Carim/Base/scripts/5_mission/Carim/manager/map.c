#ifndef CARIM_CarimManagerMap
#define CARIM_CarimManagerMap

class CarimManagerMap extends Managed {
    ref CarimMenuMap menu;

    void OnUpdate(float timeslice) {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UAMapToggle")) {
                if (!menu && !GetGame().GetUIManager().GetMenu()) {
                    menu = CarimMenuMap.Cast(GetGame().GetUIManager().EnterScriptedMenu(MENU_MAP, null));
                }
            }
        }
        if (menu) {
            menu.Update(timeslice);
        }
    }
}

#endif
