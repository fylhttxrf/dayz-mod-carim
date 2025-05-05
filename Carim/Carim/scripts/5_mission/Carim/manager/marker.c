class CarimManagerMarker extends Managed {
    // Local
    ref CarimModelMapMarkers marks;
    ref CarimModelPartyPings pings;

    // Server
    ref map<string, ref CarimModelPartyMarkers> serverMarkers;
    ref map<string, ref CarimModelPartyPositions> positions;

    ref array<ref CarimMenuMarker> menus = new array<ref CarimMenuMarker>;

    void CarimManagerPartyPingClient(CarimModelPartyPings iPings, CarimModelMapMarkers iMarks, CarimModelPartyPings iServerPings, CarimModelPartyPositions iPositions) {
        pings = iPings;
        marks = iMarks;
        serverPings = iServerPings;
        positions = iPositions;
    }

    void OnUpdate(float timeslice) {
        foreach(CarimMenuPartyPing menu : menus) {
            if (menu) {
                menu.Update(timeslice);
            }
        }
    }

    void SyncMenus() {
        int index = 0;
        if (CarimEnabled.Party()) {
            index = Sync(pings, index);
            index = Sync(serverPings, index);
            index = Sync(positions, index);
        }
        if (CarimEnabled.Map()) {
            index = Sync(marks, index);
        }

        for (int i = menus.Count() - 1; i >= index; --i) {
            CarimLogging.Debug(this, "Closing marker menu at index " + i.ToString());
            menus.Get(i).Close();
        }
        menus.Resize(index);
    }

    int Sync(CarimModelAbcMarkers markers, int index) {
        foreach(MapMarker marker : markers.markers) {
            CarimLogging.Debug(this, string.Format("Adding %1: <%2, %3> at index %4", markers.ClassName(), marker.GetMarkerText(), marker.GetMarkerPos(), index));
            if (menus.Count() <= index) {
                CarimLogging.Trace(this, "Creating new");
                auto menu = new CarimMenuMarker(marker);
                menu.Init();
                menus.Insert(menu);
            } else {
                CarimLogging.Trace(this, "Using existing");
                menus.Get(index).marker = marker;
            }
            index++;
        }
        return index;
    }
}
