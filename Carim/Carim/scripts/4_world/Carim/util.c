class CarimUtil {
    static bool CheckInput(string inputName) {
        UAInput inp = GetUApi().GetInputByName(inputName);
        if (inp && inp.LocalPress()) {
            return true;
        }
        return false;
    }

    static map<string, string> GetClientPlayerIdentities() {
        map<string, string> identities = new map<string, string>;
        foreach(SyncPlayer player : ClientData.m_PlayerList.m_PlayerList) {
            identities.Insert(GetIdentifier(player.m_Identity), player.m_Identity.GetName());
        }
        return identities;
    }

    static array<string> GetSortedIdsByLowerName(map<string, string> input) {
        map<string, string> sortingMap = new map<string, string>;
        foreach(string id, string name : input) {
            name.ToLower();
            sortingMap.Insert(name + id, id);
        }
        array<string> sortedKeys = sortingMap.GetKeyArray();
        sortedKeys.Sort();
        array<string> result = new array<string>;
        foreach(string key : sortedKeys) {
            result.Insert(sortingMap.Get(key));
        }
        return result;
    }

    static string GetIdentifier(PlayerIdentity identity) {
        if (identity) {
            if (CfgGameplayHandler.GetCarimUseSteamId()) {
                return identity.GetPlainId();
            } else {
                return identity.GetId();
            }
        }
        return "";
    }
}
