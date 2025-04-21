#ifndef CarimModelPartyMarkers
#define CarimModelPartyMarkers

class CarimModelPartyMarkers extends CarimModelBase {
    ref array<vector> markers = new array<vector>;

    void Add(vector mark) {
        markers.Insert(mark);
        // TODO: respect server's max markers setting
        if (markers.Count() > 3) {
            markers.RemoveOrdered(0);
        }
    }

    void Clear() {
        markers.Clear();
    }
}

typedef CarimDAL<CarimModelPartyMarkers> CarimModelPartyMarkersDAL;

#endif
