class CarimModelAbcMarkers extends CarimModelAbcDiskJson {
    ref array<ref MapMarker> markers = new array<ref MapMarker>;
    bool persist;

    void CarimModelAbcMarkers(bool shouldPersist = true) {
        persist = shouldPersist;
    }

    void Replace(array<MapMarker> marks) {
        markers.Clear();
        foreach(MapMarker mark : marks) {
            markers.Insert(mark);
        }
        if (persist) {
            Persist();
        }
    }

    void Add(MapMarker mark) {
        markers.Insert(mark);
        if (persist) {
            Persist();
        }
    }

    void Clear() {
        markers.Clear();
        if (persist) {
            Persist();
        }
    }
}
