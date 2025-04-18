modded class MissionBase {
    override UIScriptedMenu CreateScriptedMenu(int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id);
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
        return menu;
    }
}
