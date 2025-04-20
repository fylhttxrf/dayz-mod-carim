class CarimModelSettings extends CarimModelBase {
    // TODO: split this out to server and both
    // TODO: change to -1
    static const int DEFAULT_VERBOSITY = 99;

    int verbosity = DEFAULT_VERBOSITY;
    ref array<string> adminIds = new array<string>;

    // TODO: allow disabling pieces of mod
    bool enableAutorun = false;
    bool enableChat = false;
    bool enableCompass = false;
    bool enableNoVehicleDamage = false;
    bool enableParty = false;

    override void LoadDefaultsIfMissing() {
        if (verbosity == 0) {
            verbosity = DEFAULT_VERBOSITY;
        }
    }
}

typedef CarimDAL<CarimModelSettings> CarimModelSettingsDAL;
