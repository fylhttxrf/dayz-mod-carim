class CarimMapMarker extends MapMarker {
    string carimPlayerId;
    int carimHealthLevel = -1;

    [NonSerialized()] PlayerBase carimPlayer;

    override void MapMarker(vector pos, string text, int color, int idx) {
        // Included just for signature reference
    }

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

    void CarimCopyValues(CarimMapMarker other) {
        m_Position = other.m_Position;
        m_Color = other.m_Color;
        m_IconIdx = other.m_IconIdx;
        m_Text = other.m_Text;
        carimPlayerId = other.carimPlayerId;
        carimHealthLevel = other.carimHealthLevel;
    }

    string CarimRepr() {
        return string.Format("%1<%2, %3>", ClassName(), carimPlayerId, GetMarkerPos(), CarimGetHealthLevel());
    }
}

class CarimModelAbcMarkers extends CarimModelAbcDiskJson {
    [NonSerialized()] bool changed = false;

    ref map<string, ref array<ref CarimMapMarker>> markers = new map<string, ref array<ref CarimMapMarker>>;

    void Replace(string id, array<ref CarimMapMarker> marks) {
        markers.Set(id, marks);
        Persist();
        changed = true;
    }

    void Add(CarimMapMarker mark) {
        if (!markers.Contains(mark.carimPlayerId)) {
            markers.Insert(mark.carimPlayerId, new array<ref CarimMapMarker>);
        }
        markers.Get(mark.carimPlayerId).Insert(mark);
        Persist();
        changed = true;
    }

    void Clear(string id) {
        markers.Remove(id);
        Persist();
        changed = true;
    }
}

// Local
class CarimModelMapMarkers extends CarimModelAbcMarkers {}

class CarimModelPartyPings extends CarimModelAbcMarkers {
    override void Add(CarimMapMarker mark) {
        int maxPings = CfgGameplayHandler.GetCarimPartyMaxPings();
        if (maxPings > 0 && markers.Contains(mark.carimPlayerId) && markers.Get(mark.carimPlayerId).Count() >= maxPings) {
            markers.Get(mark.carimPlayerId).RemoveOrdered(0);
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
