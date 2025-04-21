#ifndef CARIM_CarimModelServerSettings
#define CARIM_CarimModelServerSettings

class CarimModelServerSettings extends CarimModelBase {
    ref array<string> adminIds = new array<string>;
}

typedef CarimDAL<CarimModelServerSettings> CarimModelServerSettingsDAL;

#endif
