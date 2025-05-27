class CarimMenuMap extends MapMenu {
    float carimLastUpdated = 0.0;

    override Widget Init() {
        super.Init();
        LoadMapMarkers();
        return layoutRoot;
    }

    override void Update(float timeslice) {
        super.Update(timeslice);

        if (layoutRoot) {
            if (carimLastUpdated > CARIM_4_FPS_INTERVAL_SEC) {
                m_MapWidgetInstance.ClearUserMarks();
                LoadMapMarkers();
                carimLastUpdated = 0.0;
            } else {
                carimLastUpdated += timeslice;
            }
        }
    }

    override void LoadMapMarkers() {
        auto mission = MissionGameplay.Cast(GetGame().GetMission());
        CarimLoadMapMarkers(mission.carimModelMapMarkers);
        CarimLoadMapMarkers(mission.carimModelPartyPings);
        CarimLoadMapMarkers(mission.carimModelPartyMarkers);
        CarimLoadMapMarkers(mission.carimModelPartyPositions);
        CarimLoadMapMarkers(mission.carimModelStaticMarkers);
        CarimLoadMapMarkers(mission.carimModelStaticOverrideMarkers);
    }

    void CarimLoadMapMarkers(CarimModelAbcMarkers markers) {
        foreach(array<ref CarimMapMarker> markerArray : markers.markers) {
            foreach(CarimMapMarker marker : markerArray) {
                m_MapWidgetInstance.AddUserMark(marker.GetMarkerPos(), marker.GetMarkerText(), marker.GetMarkerColor(), MapMarkerTypes.GetMarkerTypeFromID(marker.GetMarkerIcon()));
            }
        }
    }

    override void CloseMapMenu() {
        CarimLogging.Trace(this, "CloseMapMenu");
        // setting this flag to false makes sure they aren't
        // synced to the map item
        m_WasChanged = false;

        bool isClosedWithShortcut = CfgGameplayHandler.GetMapIgnoreMapOwnership() && GetUApi().GetInputByID(UAMapToggle).LocalPress();
        if (isClosedWithShortcut && m_MapMenuHandler && m_MapMenuHandler.carimMenuEditMarker && m_MapMenuHandler.carimMenuEditMarker.visible) {
            return;
        }

        super.CloseMapMenu();
    }
}
