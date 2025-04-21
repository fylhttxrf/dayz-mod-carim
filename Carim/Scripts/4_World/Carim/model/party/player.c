#ifndef CarimModelPartyPlayer
#define CarimModelPartyPlayer

class CarimModelPartyPlayer extends CarimModelBase {
    string id;
    vector position;
    int healthLevel;

    void CarimModelPartyPlayer(string newId, vector newPosition, int newHealthLevel) {
        id = newId;
        position = newPosition;
        healthLevel = newHealthLevel;
    }
}

#endif
