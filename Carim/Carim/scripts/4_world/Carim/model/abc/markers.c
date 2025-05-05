class CarimMapMarker extends MapMarker {
    string carimPlayerId;
    PlayerBase carimPlayer;
    int carimHealthLevel = -1;

    override vector GetMarkerPos() {
        if (carimPlayer) {
            return carimPlayer.GetPosition();
        } else {
            return super.GetMarkerPos();
        }
    }

    override int GetMarkerIcon() {
        if (CarimGetHealthLevel() > -1) {
            // TODO: get appropriate icon (if possible) here
            // TODO: Also set color appropriately
            return CarimGetHealthLevel();
        } else {
            return super.GetMarkerIcon();
        }
    }

    int CarimGetHealthLevel() {
        if (carimPlayer) {
            return carimPlayer.GetHealthLevel();
        } else {
            return carimHealthLevel;
        }
    }
}

class CarimModelAbcMarkers extends CarimModelAbcDiskJson {
    [NonSerialized()] bool changed = false;

    ref array<ref CarimMapMarker> markers = new array<ref CarimMapMarker>;

    void Replace(array<CarimMapMarker> marks) {
        markers.Clear();
        foreach(CarimMapMarker mark : marks) {
            markers.Insert(mark);
        }
        Persist();
        changed = true;
    }

    void Add(CarimMapMarker mark) {
        markers.Insert(mark);
        Persist();
        changed = true;
    }

    void Clear() {
        markers.Clear();
        Persist();
        changed = true;
    }
}

// Local
class CarimModelMapMarkers extends CarimModelAbcMarkers {}

class CarimModelPartyPings extends CarimModelAbcMarkers {
    override void Add(CarimMapMarker mark) {
        int maxPings = CfgGameplayHandler.GetCarimPartyMaxPings();
        if (maxPings > 0 && markers.Count() >= maxPings) {
            markers.RemoveOrdered(0);
        }
        super.Add(mark);
    }
}

// Server
class CarimModelPartyMarkers extends CarimModelAbcMarkers {
    override void Persist() {
    }
}

class CarimModelPartyPositions extends CarimModelAbcMarkers {
    override void Persist() {
    }
}
