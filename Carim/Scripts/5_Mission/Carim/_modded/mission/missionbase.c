#ifndef CarimMissionBase
#define CarimMissionBase

modded class MissionBase {
    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
#ifndef CARIM_DISABLE_PARTY
        if (!menu) {
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
#endif
        return menu;
    }
}

#endif
