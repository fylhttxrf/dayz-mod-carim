class CarimManagerPartyRegistrationClient extends Managed {
    ref CarimMenuPartyRegister menu;
    ref array<string> mutual = new array<string>;

    void CarimManagerPartyRegistrationClient() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.RenewRegistration, 15000, true);
    }

    void ~CarimManagerPartyRegistrationClient() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.RenewRegistration);
    }

    void OnUpdate() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && GetUApi() && !GetGame().GetUIManager().IsMenuOpen(MENU_CHAT_INPUT)) {
            if (CarimUtil.CheckInput("UAUIBack")) {
                if (menu && GetGame().GetUIManager().GetMenu() == menu) {
                    menu.UnlockControls();
                    menu.Close();
                }
            }
            if (CarimUtil.CheckInput("UACarimPartyMenu")) {
                if (menu) {
                    menu.Close();
                } else if (GetGame().GetUIManager().GetMenu() == NULL) {
                    GetGame().GetUIManager().EnterScriptedMenu(CarimMenuParty.REGISTER, NULL);
                }
            }
        }
    }

    void SetMutual(array<string> players) {
        mutual.Clear();
        mutual.Copy(players);
    }

    void RenewRegistration() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity()) {
            array<string> registrations = CarimModelPartyRegistrationsDAL.Get().registrations.GetKeyArray();
            auto params = new Param1<array<string>>(registrations);
            CarimRPCPartyRegister.Send(player, params, true);
        }
    }

    void AddPlayerToParty(string id) {
        CarimModelPartyRegistrationsDAL.Get().Add(id, CarimUtil.GetClientPlayerIdentities().Get(id));
        RenewRegistration();
    }

    void RemovePlayerFromParty(string id) {
        CarimModelPartyRegistrationsDAL.Get().Remove(id);
        mutual.RemoveItem(id);
        RenewRegistration();
    }
}

typedef CarimSingleton<CarimManagerPartyRegistrationClient> CarimManagerPartyRegistrationClientSingleton;
