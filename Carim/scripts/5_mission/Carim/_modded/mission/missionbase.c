#ifndef CARIM_MissionBase
#define CARIM_MissionBase

modded class MissionBase {
    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
        if (CarimEnabled.Party() && !menu) {
            switch (id) {
                case CarimMenuParty.REGISTER:
                    menu = new CarimMenuPartyRegister;
                    CarimManagerPartyRegistrationClientSingleton.Get().menu = CarimMenuPartyRegister.Cast(menu);
                    break;
            }
            if (menu) {
                menu.SetID(id);
            }
        }
        return menu;
    }
}

#endif
