class CarimManagerMarker extends Managed {
    // Local
    ref CarimModelMapMarkers marks;
    ref CarimModelPartyPings pings;

    // Server
    ref CarimModelPartyMarkers serverMarkers;
    ref CarimModelPartyPositions positions;

    ref CarimModelPartyRegistrations registrations;

    ref array<ref CarimMenuMarker> menus = new array<ref CarimMenuMarker>;
    ref array<ref CarimMenuPartyList> listMenus = new array<ref CarimMenuPartyList>;

    void CarimManagerMarker(CarimModelPartyPings iPings, CarimModelMapMarkers iMarks, CarimModelPartyMarkers iServerMarkers, CarimModelPartyPositions iPositions, CarimModelPartyRegistrations iRegistrations) {
        pings = iPings;
        marks = iMarks;
        serverMarkers = iServerMarkers;
        positions = iPositions;
        registrations = iRegistrations;

        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.SyncMenus, 10000, true);
    }

    void ~CarimManagerMarker() {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.SyncMenus);
    }

    void OnUpdate(float timeslice) {
        foreach(CarimMenuMarker menu : menus) {
            if (menu) {
                menu.Update(timeslice);
            }
        }
        foreach(CarimMenuPartyList listMenu : listMenus) {
            if (listMenu) {
                listMenu.Update(timeslice);
            }
        }

        if (pings.changed || serverMarkers.changed || positions.changed || marks.changed) {
            SyncMenus();
            pings.changed = false;
            serverMarkers.changed = false;
            positions.changed = false;
            marks.changed = false;
        }
    }

    void SyncMenus() {
        int index = 0;
        if (CarimEnabled.Party()) {
            index = Sync(pings, index);
            index = Sync(serverMarkers, index);
            index = Sync(positions, index);
            SyncList(positions);
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
        foreach(array<ref CarimMapMarker> markerArray : markers.markers) {
            foreach(CarimMapMarker marker : markerArray) {
                CarimLogging.Debug(this, string.Format("Adding %1: <%2, %3, %4> at index %5", markers.ClassName(), marker.carimPlayerId, marker.GetMarkerText(), marker.GetMarkerPos(), index));
                if (menus.Count() <= index) {
                    CarimLogging.Trace(this, "Creating new");
                    auto menu = new CarimMenuMarker(marker);
                    menu.Init();
                    menus.Insert(menu);
                } else {
                    CarimLogging.Trace(this, "Using existing");
                    menus.Get(index).carimMarker = marker;
                }
                ++index;
            }
        }
        return index;
    }

    void SyncList(CarimModelAbcMarkers markers) {
        auto sortedIds = CarimUtil.GetSortedIdsByLowerName(registrations.registrations);
        int index = 0;
        foreach(auto id : sortedIds) {
            if (markers.markers.Contains(id)) {
                auto markerArray = markers.markers.Get(id);
                if (markerArray.Count() == 1) { // Should only have one position per id
                    auto marker = markerArray.Get(0);
                    CarimLogging.Debug(this, string.Format("Adding %1: <%2, %3, %4> at index %5", markers.ClassName(), marker.carimPlayerId, marker.GetMarkerText(), marker.GetMarkerPos(), index));
                    if (listMenus.Count() <= index) {
                        CarimLogging.Trace(this, "Creating new");
                        auto menu = new CarimMenuPartyList(marker);
                        menu.Init();
                        menu.carimListIndex = index;
                        listMenus.Insert(menu);
                    } else {
                        CarimLogging.Trace(this, "Using existing");
                        listMenus.Get(index).carimMarker = marker;
                        listMenus.Get(index).carimListIndex = index;
                    }
                    ++index;
                }
            }
        }
        for (int i = listMenus.Count() - 1; i >= index; --i) {
            CarimLogging.Debug(this, "Closing list menu at index " + i.ToString());
            listMenus.Get(i).Close();
        }
        listMenus.Resize(index);
    }
}
