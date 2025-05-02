#ifndef CARIM_CarimManagerMap
#define CARIM_CarimManagerMap

class CarimManagerMap extends Managed {
    ref CarimMenuMap menu;

    void OnUpdate(float timeslice) {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UAUIBack")) {
                if (menu && GetGame().GetUIManager().GetMenu() == menu) {
                    menu.UnlockControls();
                    menu.Close();
                }
            }
            if (CarimUtil.CheckInput("UACarimMapMenu")) {
                if (menu) {
                    menu.Close();
                } else if (GetGame().GetUIManager().GetMenu() == NULL) {
                    GetGame().GetUIManager().EnterScriptedMenu(CarimMenu.MAP, NULL);
                }
            }
        }
        if (menu) {
            menu.Update(timeslice);
        }
    }
}

#endif
