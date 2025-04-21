#ifndef CarimUtil
#define CarimUtil

class CarimUtil {
    static bool CheckInput(string inputName) {
        UAInput inp = GetUApi().GetInputByName(inputName);
        if (inp && inp.LocalPress()) {
            return true;
        }
        return false;
    }

    static void LockControls() {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_MOUSE_ALL);
        GetGame().GetUIManager().ShowUICursor(true);
    }

    static void UnlockControls() {
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor(false);
    }

    static vector GetRaycastPosition() {
        vector begin = GetGame().GetCurrentCameraPosition() + GetGame().GetCurrentCameraDirection();
        vector end = begin + GetGame().GetCurrentCameraDirection() * 8000;
        vector contactPos;
        vector contactDir;
        int contactComponent;
        if (DayZPhysics.RaycastRV(begin, end, contactPos, contactDir, contactComponent)) {
            return contactPos;
        }
        return vector.Zero;
    }

    static map<string, string> GetClientPlayerIdentities() {
        map<string, string> identities = new map<string, string>;
        foreach(SyncPlayer player : ClientData.m_PlayerList.m_PlayerList) {
            identities.Insert(player.m_Identity.GetId(), player.m_Identity.GetName());
        }
        return identities;
    }

    static array<PlayerBase> GetClientPlayerBases() {
        array<PlayerBase> players = new array<PlayerBase>;
        foreach(Man m : ClientData.m_PlayerBaseList) {
            players.Insert(PlayerBase.Cast(m));
        }
        return players;
    }

    static map<string, PlayerBase> GetServerIdPlayerMap() {
        map<string, PlayerBase> idMap = new map<string, PlayerBase>;
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach(Man man : players) {
            PlayerBase player = PlayerBase.Cast(man);
            if (player && player.GetIdentity()) {
                idMap.Insert(player.GetIdentity().GetId(), player);
            }
        }

        return idMap;
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
}

#endif
