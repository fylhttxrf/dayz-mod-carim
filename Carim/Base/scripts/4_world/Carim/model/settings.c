#ifndef CARIM_CarimModelSettings
#define CARIM_CarimModelSettings

class CarimModelSettings extends CarimModelBase {
    static const int DEFAULT_VERBOSITY = -1;

    int verbosity = DEFAULT_VERBOSITY;

    override void LoadDefaultsIfMissing() {
        if (verbosity == 0) {
            verbosity = DEFAULT_VERBOSITY;
        }
    }
}

typedef CarimDAL<CarimModelSettings> CarimModelSettingsDAL;

#endif
