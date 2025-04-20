class CarimMenuPartyRegister extends UIScriptedMenu {
    bool carimInitialized;
    TextListboxWidget carimPlayers;
    TextListboxWidget carimRegistered;
    ButtonWidget carimAdd;
    ButtonWidget carimRemove;

    void ~CarimMenuPartyRegister() {
        // TODO: disable mouse controlling character, but leave
        // other controls intact (like inventory). Might have to
        // do this within mission
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.CarimUpdateLists);
        GetGame().GetUIManager().Back();
        GetGame().GetUIManager().ShowCursor(true);
        GetGame().GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        if (layoutRoot) {
            layoutRoot.Unlink();
        }
    }

    override Widget Init() {
        if (!carimInitialized) {
            layoutRoot = GetGame().GetWorkspace().CreateWidgets("Carim/gui/layouts/party/register.layout");
            carimPlayers = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("players"));
            carimRegistered = TextListboxWidget.Cast(layoutRoot.FindAnyWidget("registered"));
            carimAdd = ButtonWidget.Cast(layoutRoot.FindAnyWidget("add"));
            carimRemove = ButtonWidget.Cast(layoutRoot.FindAnyWidget("remove"));

            carimInitialized = true;
        }

        return layoutRoot;
    }

    override void OnShow() {
        super.OnShow();
        CarimUpdateLists();
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.CarimUpdateLists, 500, true);
    }

    override void OnHide() {
        super.OnHide();
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.CarimUpdateLists);
        GetGame().GetUIManager().Back();
        GetGame().GetUIManager().ShowCursor(true);
        GetGame().GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        Close();
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        int selectedRow;
        Param1<string> id;
        switch (w) {
            case carimAdd:
                selectedRow = carimPlayers.GetSelectedRow();
                if (selectedRow == -1) {
                    break;
                }
                carimPlayers.GetItemData(selectedRow, 0, id);
                CarimManagerPartyRegistrationClientSingleton.Get().AddPlayerToParty(id.param1);
                CarimUpdateLists();
                return true;
                break;
            case carimRemove:
                selectedRow = carimRegistered.GetSelectedRow();
                if (selectedRow == -1) {
                    break;
                }
                carimRegistered.GetItemData(selectedRow, 0, id);
                CarimManagerPartyRegistrationClientSingleton.Get().RemovePlayerFromParty(id.param1);
                carimRegistered.SelectRow(selectedRow - 1);
                CarimUpdateLists();
                return true;
                break;
        }
        return super.OnClick(w, x, y, button);
    }

    void CarimUpdateLists() {
        CarimUpdateList(carimPlayers, CarimUtil.GetClientPlayerIdentities());
        CarimUpdateList(carimRegistered, CarimModelPartyRegistrationsDAL.Get().registrations);
        CarimUpdateColors();
    }

    void CarimUpdateList(TextListboxWidget targetList, map<string, string> values) {
        auto sortedIds = CarimUtil.GetSortedIdsByLowerName(values);
        int row = 0;
        foreach(string id : sortedIds) {
            if (row < targetList.GetNumItems()) {
                targetList.SetItem(row, values.Get(id), new Param1<string>(id), 0);
            } else {
                targetList.AddItem(values.Get(id), new Param1<string>(id), 0);
            }
            row++;
        }
        while (row < targetList.GetNumItems()) {
            targetList.RemoveRow(row);
        }
        if (targetList.GetSelectedRow() >= row) {
            targetList.SelectRow(row - 1);
        }
    }

    void CarimUpdateColors() {
        auto onlinePlayers = CarimUtil.GetClientPlayerIdentities();
        int selectedRow;
        int i;
        Param1<string> id;
        for (i = 0; i < carimRegistered.GetNumItems(); ++i) {
            carimRegistered.GetItemData(i, 0, id);
            if (onlinePlayers.Contains(id.param1)) {
                // Green 400
                carimRegistered.SetItemColor(i, 0, 0xFF66BB6A);
            } else if (onlinePlayers.Contains(id.param1) && CarimManagerPartyRegistrationClientSingleton.Get().mutual.Find(id.param1) < 0) {
                // Light Blue 400
                carimRegistered.SetItemColor(i, 0, 0xFF29B6F6);
            } else {
                // Gray 400
                carimRegistered.SetItemColor(i, 0, 0xFFBDBDBD);
            }
        }
        for (i = 0; i < carimPlayers.GetNumItems(); ++i) {
            // Gray 400
            carimPlayers.SetItemColor(i, 0, 0xFFBDBDBD);
        }
    }
}
