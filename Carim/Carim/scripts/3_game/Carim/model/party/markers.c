#ifndef CARIM_CarimModelPartyMarkers
#define CARIM_CarimModelPartyMarkers

class CarimModelPartyMarkers extends CarimModelAbcDiskJson {
    ref array<vector> markers = new array<vector>;

    void Add(vector mark) {
        markers.Insert(mark);
        int maxMarkers = CfgGameplayHandler.GetCarimPartyMaxMarkers();
        if (maxMarkers > 0 && markers.Count() > maxMarkers) {
            markers.RemoveOrdered(0);
        }
        Persist();
    }

    void Clear() {
        markers.Clear();
        Persist();
    }
}

#endif
