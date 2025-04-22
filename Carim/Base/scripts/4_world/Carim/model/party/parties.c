#ifndef CARIM_CarimModelPartyParties
#define CARIM_CarimModelPartyParties

class CarimModelPartyParties extends Managed {
    ref map<string, ref CarimSet> registered = new map<string, ref CarimSet>;
    ref map<string, ref CarimSet> mutuals = new map<string, ref CarimSet>;

    bool Register(string id, array<string> players) {
        if (!registered.Contains(id)) {
            registered.Insert(id, new CarimSet);
        }

        bool added;
        CarimSet removed = registered.Get(id).Copy();

        foreach(string newPlayer : players) {
            removed.Remove(newPlayer);
            if (!registered.Get(id).Contains(newPlayer)) {
                CarimLogging.Trace("Register " + id + " added " + newPlayer);
                added = true;
                registered.Get(id).Insert(newPlayer);
            }
        }

        foreach(string removedPlayer : removed.ToArray()) {
            registered.Get(id).Remove(removedPlayer);
            UpdateMutual(removedPlayer);
        }

        bool changed = (added || removed.Count() > 0);
        if (changed) {
            UpdateMutual(id);
            foreach(string player : registered.Get(id).ToArray()) {
                UpdateMutual(player);
            }
        }

        return changed;
    }

    void UpdateMutual(string id) {
        CarimLogging.Trace("UpdateMutual " + id);
        if (!registered.Contains(id)) {
            CarimLogging.Trace("No registration found");
            return;
        }
        if (!mutuals.Contains(id)) {
            mutuals.Insert(id, new CarimSet);
        } else {
            mutuals.Get(id).Clear();
        }
        auto admins = CarimModelServerSettingsDAL.Get().adminIds;
        foreach(string player : registered.Get(id).ToArray()) {
            CarimLogging.Trace("Checking if mutual: " + player);
            if (registered.Contains(player) && registered.Get(player).Contains(id)) {
                CarimLogging.Trace("Mutual found: " + player);
                mutuals.Get(id).Insert(player);
            } else if (admins.Find(id) != -1) {
                CarimLogging.Trace("Mutual admin override: " + player);
                mutuals.Get(id).Insert(player);
            }
        }
    }

    string Repr() {
        string jsonRegistered;
        if (CarimLogging.WillLog(CarimLogging.TRACE)) {
            JsonSerializer().WriteToString(registered, false, jsonRegistered);
        }
        string jsonMutuals;
        if (CarimLogging.WillLog(CarimLogging.TRACE)) {
            JsonSerializer().WriteToString(mutuals, false, jsonMutuals);
        }
        return "PartyParties<" + jsonRegistered + ", " + jsonMutuals + ">";
    }
}

#endif
