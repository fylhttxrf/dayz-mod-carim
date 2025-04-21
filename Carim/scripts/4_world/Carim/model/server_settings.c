#ifndef CarimModelServerSettings
#define CarimModelServerSettings

class CarimModelServerSettings extends CarimModelBase {
    ref array<string> adminIds = new array<string>;
}

typedef CarimDAL<CarimModelServerSettings> CarimModelServerSettingsDAL;

#endif
