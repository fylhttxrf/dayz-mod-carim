class CarimManagerPartyPositionClient extends Managed {
    ref map<string, ref CarimModelPartyPlayer> serverPositions = new map<string, ref CarimModelPartyPlayer>;
    ref map<string, ref CarimMenuPartyNametag> menus = new map<string, ref CarimMenuPartyNametag>;

    void CarimManagerPartyPositionClient() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.SyncMenus, 2000, true);
    }

    void ~CarimManagerPartyPositionClient() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.SyncMenus);
    }

    void SetPositions(array<CarimModelPartyPlayer> positions) {
        serverPositions.Clear();
        foreach(CarimModelPartyPlayer position : positions) {
            serverPositions.Insert(position.id, position);
        }
    }

    void SyncMenus() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player && player.GetIdentity() && player.IsAlive()) {
            AddAndUpdateNametags();
            RemoveInvalidNametags();
            UpdateNametagsWithLocalPlayers();
            UpdateMenuListSorting();
        }
    }

    void AddAndUpdateNametags() {
        foreach(string id, CarimModelPartyPlayer position : serverPositions) {
            string name = id.Substring(0, 4);
            if (CarimModelPartyRegistrationsDAL.Get().registrations.Contains(id)) {
                name = CarimModelPartyRegistrationsDAL.Get().registrations.Get(id);
            }
            if (!menus.Contains(id)) {
                menus.Insert(id, new CarimMenuPartyNametag(name, position.position));
            }
            menus.Get(id).carimName = name;
            menus.Get(id).carimPosition = position.position;
            menus.Get(id).carimHealthLevel = position.healthLevel;
        }
    }

    void RemoveInvalidNametags() {
        foreach(string id : menus.GetKeyArray()) {
            if (!serverPositions.Contains(id)) {
                menus.Get(id).CarimRemove();
                menus.Remove(id);
            }
        }
    }

    void UpdateNametagsWithLocalPlayers() {
        string activePlayerId;
        PlayerBase activePlayer = PlayerBase.Cast(GetGame().GetPlayer());
        if (activePlayer && activePlayer.GetIdentity()) {
            activePlayerId = activePlayer.GetIdentity().GetId();
        }
        foreach(PlayerBase player : CarimUtil.GetClientPlayerBases()) {
            if (player && player.GetIdentity() && player.IsAlive()) {
                string id = player.GetIdentity().GetId();
                if (menus.Contains(id) && serverPositions.Contains(id)) {
                    menus.Get(id).carimPlayer = player;
                }
            }
        }
    }

    void UpdateMenuListSorting() {
        // menu ids should always be in registrations
        // if there's duplicate indicies (i.e. overlapping list items), then
        // that assumption is false for some reason and needs fixed here
        auto sortedIds = CarimUtil.GetSortedIdsByLowerName(CarimModelPartyRegistrationsDAL.Get().registrations);
        int index = 0;
        foreach(auto id : sortedIds) {
            if (menus.Contains(id)) {
                menus.Get(id).carimListIndex = index;
                ++index;
            }
        }
    }
}

typedef CarimSingleton<CarimManagerPartyPositionClient> CarimManagerPartyPositionClientSingleton;
