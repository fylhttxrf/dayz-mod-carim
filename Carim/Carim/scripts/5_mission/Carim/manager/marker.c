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
        int textColor;
        int hideLessThan;
        int hideGreaterThan;
        bool showDistance;
        bool requireLineOfSight;
        if (CarimEnabled.Party()) {
            // Local pings
            textColor = CfgGameplayHandler.GetCarimPartyColorPingTextLocal();
            hideLessThan = CfgGameplayHandler.GetCarimPartyDistancePingHideLessThan();
            hideGreaterThan = CfgGameplayHandler.GetCarimPartyDistancePingHideGreaterThan();
            showDistance = CfgGameplayHandler.GetCarimPartyShowDistancePing();
            requireLineOfSight = CfgGameplayHandler.GetCarimPartyRequirePingLineOfSight();
            index = Sync(pings, index, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);

            // Server pings
            textColor = CfgGameplayHandler.GetCarimPartyColorPingTextServer();
            index = Sync(serverMarkers, index, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);

            // Positions
            textColor = CfgGameplayHandler.GetCarimPartyColorPlayerText();
            hideLessThan = CfgGameplayHandler.GetCarimPartyDistancePlayerHideLessThan();
            hideGreaterThan = CfgGameplayHandler.GetCarimPartyDistancePlayerHideGreaterThan();
            showDistance = CfgGameplayHandler.GetCarimPartyShowDistancePlayer();
            requireLineOfSight = CfgGameplayHandler.GetCarimPartyRequirePlayerLineOfSight();
            index = Sync(positions, index, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);

            SyncList(positions, textColor, hideLessThan, hideGreaterThan);
        }
        if (CarimEnabled.Map()) {
            textColor = CfgGameplayHandler.GetCarimMapColorText();
            hideLessThan = CfgGameplayHandler.GetCarimMapDistanceHideLessThan();
            hideGreaterThan = CfgGameplayHandler.GetCarimMapDistanceHideGreaterThan();
            showDistance = CfgGameplayHandler.GetCarimMapShowDistance();
            requireLineOfSight = CfgGameplayHandler.GetCarimMapRequireLineOfSight();
            index = Sync(marks, index, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);
        }

        for (int i = menus.Count() - 1; i >= index; --i) {
            CarimLogging.Debug(this, "Closing marker menu at index " + i.ToString());
            menus.Get(i).Close();
        }
        menus.Resize(index);
    }

    int Sync(CarimModelAbcMarkers markers, int index, int textColor, int hideLessThan, int hideGreaterThan, bool showDistance, bool requireLineOfSight) {
        foreach(array<ref CarimMapMarker> markerArray : markers.markers) {
            foreach(CarimMapMarker marker : markerArray) {
                CarimLogging.Debug(this, string.Format("Adding %1: <%2, %3, %4> at index %5", markers.ClassName(), marker.carimPlayerId, marker.GetMarkerText(), marker.GetMarkerPos(), index));
                if (menus.Count() <= index) {
                    CarimLogging.Trace(this, "Creating new");
                    auto menu = new CarimMenuMarker(marker, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);
                    menu.Init();
                    menus.Insert(menu);
                } else {
                    CarimLogging.Trace(this, "Using existing");
                    menus.Get(index).CarimSetAttributes(marker, textColor, hideLessThan, hideGreaterThan, showDistance, requireLineOfSight);
                }
                ++index;
            }
        }
        return index;
    }

    void SyncList(CarimModelAbcMarkers markers, int textColor, int hideLessThan, int hideGreaterThan) {
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
                        auto menu = new CarimMenuPartyList(marker, textColor, hideLessThan, hideGreaterThan, true, false);
                        menu.Init();
                        menu.carimListIndex = index;
                        listMenus.Insert(menu);
                    } else {
                        CarimLogging.Trace(this, "Using existing");
                        listMenus.Get(index).CarimSetAttributes(marker, textColor, hideLessThan, hideGreaterThan, true, false);
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
