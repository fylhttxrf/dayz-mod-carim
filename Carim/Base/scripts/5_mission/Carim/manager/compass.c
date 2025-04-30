#ifndef CARIM_CarimManagerCompass
#define CARIM_CarimManagerCompass

class CarimManagerCompass extends Managed {
    ref CarimMenuCompass menu;

    void CarimManagerCompass() {
        menu = new CarimMenuCompass;
        menu.Init();
    }

    void OnUpdate(float timeslice) {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UACarimCompassToggle")) {
                menu.CarimToggleHeading();
            }
        }
        menu.Update(timeslice);
    }
}

#endif
