enum CarimMapMarkerTypes {
    START = -44000,
    ARROW_1,
    ARROW_2,
    ARROW_3,
    HEALTH_0,
    HEALTH_1,
    HEALTH_2,
    HEALTH_3,
    HEALTH_4
}

class CarimMapMarker extends MapMarker {
    string carimPlayerId;
    int carimHealthLevel = -1;

    [NonSerialized()] PlayerBase carimPlayer;

    static CarimMapMarker CarimNew(vector pos, string text, int color, int idx, string playerId, int healthLevel = -1) {
        auto marker = new CarimMapMarker(pos, text, color, idx);
        marker.carimPlayerId = playerId;
        marker.carimHealthLevel = healthLevel;
        return marker;
    }

    override vector GetMarkerPos() {
        if (carimPlayer) {
            return carimPlayer.GetPosition();
        } else {
            return super.GetMarkerPos();
        }
    }

    override int GetMarkerIcon() {
        switch (CarimGetHealthLevel()) {
            case 0:
                return CarimMapMarkerTypes.HEALTH_0;
                break;
            case 1:
                return CarimMapMarkerTypes.HEALTH_1;
                break;
            case 2:
                return CarimMapMarkerTypes.HEALTH_2;
                break;
            case 3:
                return CarimMapMarkerTypes.HEALTH_3;
                break;
            case 4:
                return CarimMapMarkerTypes.HEALTH_4;
                break;
        }
        return super.GetMarkerIcon();
    }

    override int GetMarkerColor() {
        switch (CarimGetHealthLevel()) {
            case 0:
                return CarimColor.HEALTH_WHITE;
                break;
            case 1:
                return CarimColor.HEALTH_WHITE;
                break;
            case 2:
                return CarimColor.HEALTH_YELLOW;
                break;
            case 3:
                return CarimColor.HEALTH_RED;
                break;
            case 4:
                return CarimColor.HEALTH_RED;
                break;
        }
        return super.GetMarkerColor();
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

    void CarimSetMarkerText(string text) {
        m_Text = text;
    }

    void CarimSetMarkerIcon(int icon) {
        m_IconIdx = icon;
    }

    void CarimSetMarkerColor(int color) {
        m_Color = color;
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

    void Remove(CarimMapMarker mark) {
        if (!markers.Contains(mark.carimPlayerId)) {
            return;
        }
        int closest = -1;
        int closestDistance = 1000;
        foreach(int i, auto marker : markers.Get(mark.carimPlayerId)) {
            auto distance = vector.Distance(mark.GetMarkerPos(), marker.GetMarkerPos());

            if (distance < 50) {
                closest = i;
                closestDistance = distance;
            }
        }

        if (closest >= 0) {
            markers.Get(mark.carimPlayerId).RemoveOrdered(closest);
            Persist();
            changed = true;
        }
    }

    CarimMapMarker GetClose(CarimMapMarker mark) {
        if (!markers.Contains(mark.carimPlayerId)) {
            return;
        }
        foreach(int i, auto marker : markers.Get(mark.carimPlayerId)) {
            auto distance = vector.Distance(mark.GetMarkerPos(), marker.GetMarkerPos());

            if (distance < 50) {
                markers.Get(mark.carimPlayerId).RemoveOrdered(i);
                Persist();
                changed = true;
                return;
            }
        }
    }

    void Clear(string id) {
        if (markers.Contains(id)) {
            markers.Get(id).Resize(0);
        } else {
            markers.Insert(id, new array<ref CarimMapMarker>);
        }
        Persist();
        changed = true;
    }
}

// Local
class CarimModelMapMarkers extends CarimModelAbcMarkers {
    int counter = 0;

    override void Clear(string id) {
        counter = 0;
        super.Clear(id);
    }

    override void Add(CarimMapMarker mark) {
        mark.CarimSetMarkerText(mark.GetMarkerText() + counter.ToString());
        ++counter;
        super.Add(mark);
    }
}

class CarimModelPartyPings extends CarimModelAbcMarkers {
    int counter = 0;

    override void Clear(string id) {
        counter = 0;
        super.Clear(id);
    }

    override void Add(CarimMapMarker mark) {
        int maxPings = CfgGameplayHandler.GetCarimPartyMaxPings();
        bool markersLimited = maxPings >= 0;
        int countMarkers = 0;
        if (markers.Contains(mark.carimPlayerId)) {
            countMarkers = markers.Get(mark.carimPlayerId).Count();
        }
        // Remove greater than max markers
        if (markersLimited && countMarkers >= maxPings) {
            markers.Get(mark.carimPlayerId).RemoveOrdered(0);
            --countMarkers;
        }
        // Add marker if it would be less than max
        if (!markersLimited || countMarkers < maxPings) {
            mark.CarimSetMarkerText(mark.GetMarkerText() + " " + counter.ToString());
            ++counter;
            super.Add(mark);
        }
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
