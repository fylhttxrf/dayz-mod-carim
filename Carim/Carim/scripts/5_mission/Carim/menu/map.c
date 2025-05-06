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
        CarimLogging.Trace(this, "LoadMapMarkers");

        auto mission = MissionGameplay.Cast(GetGame().GetMission());
        CarimLoadMapMarkers(mission.carimModelMapMarkers);
        CarimLoadMapMarkers(mission.carimModelPartyPings);
        CarimLoadMapMarkers(mission.carimModelPartyMarkers);
        CarimLoadMapMarkers(mission.carimModelPartyPositions);
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
        // TODO: make it so the markers are synced somewhere
        // but setting this flag to false makes sure they aren't
        // synced to the map item
        m_WasChanged = false;
        super.CloseMapMenu();
    }
}
