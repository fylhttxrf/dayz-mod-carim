class CarimModelPartyParties extends Managed {
    ref map<string, ref set<string>> registered = new map<string, ref set<string>>;
    ref map<string, ref set<string>> mutuals = new map<string, ref set<string>>;

    void Register(string id, array<string> players) {
        set<string> added = new set<string>;
        set<string> removed = new set<string>;
        set<string> associated = new set<string>;

        foreach(string newPlayer : players) {
            associated.Insert(newPlayer);
            if (!registered.Contains(id) || registered.Get(id).Find(newPlayer) == -1) {
                CarimLogging.Trace("Register " + id + " added " + newPlayer);
                added.Insert(newPlayer);
            }
        }
        if (registered.Contains(id)) {
            foreach(string oldPlayer : registered.Get(id)) {
                if (associated.Find(oldPlayer) == -1) {
                    CarimLogging.Trace("Register " + id + " removed " + oldPlayer);
                    removed.Insert(oldPlayer);
                }
            }
        }

        if (added.Count() > 0 || removed.Count() > 0) {
            registered.Set(id, associated);
            UpdateMutual(id);
            foreach(string addedPlayer : added) {
                UpdateMutual(addedPlayer);
            }
            foreach(string removedPlayer : removed) {
                UpdateMutual(removedPlayer);
            }
        }
    }

    void UpdateMutual(string id) {
        if (!registered.Contains(id)) {
            return;
        }
        if (!mutuals.Contains(id)) {
            mutuals.Insert(id, new set<string>);
        } else {
            mutuals.Get(id).Clear();
        }
        foreach(string player : registered.Get(id)) {
            if (registered.Contains(player) && registered.Get(player).Find(id) >= 0) {
                mutuals.Get(id).Insert(player);
            } else if (CarimModelSettingsDAL.Get().adminIds.Find(id) != -1) {
                mutuals.Get(id).Insert(player);
            }
        }
    }
}
