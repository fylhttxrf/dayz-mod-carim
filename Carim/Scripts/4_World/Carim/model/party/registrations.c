class CarimModelPartyRegistrations extends CarimModelBase {
    ref map<string, string> registrations = new map<string, string>;

    void Add(string id, string name) {
        registrations.Set(id, name);
    }

    void Remove(string id) {
        registrations.Remove(id);
    }
}

typedef CarimDAL<CarimModelPartyRegistrations> CarimModelPartyRegistrationsDAL;
