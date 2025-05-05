#ifndef CARIM_CarimModelMapMarkers
#define CARIM_CarimModelMapMarkers

class CarimModelMapMarkers extends CarimModelAbcDiskJson {
    ref array<vector> markers = new array<vector>;

    void Add(vector mark) {
        markers.Insert(mark);
        Persist();
    }

    void Clear() {
        markers.Clear();
        Persist();
    }
}

#endif
