#ifndef CARIM_CarimMenuMap
#define CARIM_CarimMenuMap

class CarimMenuMap extends MapMenu {
    // TODO: make this more useful and/or combine with CarimModelMapMarkers
    ref array<ref MapMarker> carimMarkers = new array<ref MapMarker>;

    override Widget Init() {
        super.Init();
        LoadMapMarkers();
        return layoutRoot;
    }

    override void AddMarker(vector pos, int color, int icon = 0) {
        CarimLogging.Trace(this, "AddMarker");

        auto mission = MissionGameplay.Cast(GetGame().GetMission());
        mission.carimModelMapMarkers.Add(pos);

        if (CarimEnabled.Party()) {
            // TODO: make this usable even if parties aren't enabled
            mission.carimManagerPartyMarkerClient.SyncMenus();
        }

        carimMarkers.Insert(new MapMarker(pos, "", color, icon));
        m_MapWidgetInstance.AddUserMark(pos, "", color, MapMarkerTypes.GetMarkerTypeFromID(icon));
    }

    override void LoadMapMarkers() {
        CarimLogging.Trace(this, "LoadMapMarkers");
        foreach(MapMarker marker : carimMarkers) {
            m_MapWidgetInstance.AddUserMark(marker.GetMarkerPos(), marker.GetMarkerText(), marker.GetMarkerColor(), MapMarkerTypes.GetMarkerTypeFromID(marker.GetMarkerIcon()));
        }

        auto mission = MissionGameplay.Cast(GetGame().GetMission());
        if (CarimEnabled.Party()) {
            foreach(int index, vector position : mission.carimModelPartyMarkers.markers) {
                m_MapWidgetInstance.AddUserMark(position, (mission.carimModelPartyMarkers.markers.Count() - index).ToString(), ARGB(255, 255, 0, 0), MapMarkerTypes.GetMarkerTypeFromID(0));
            }
        }
        foreach(int mapIndex, vector mapPosition : mission.carimModelMapMarkers.markers) {
            m_MapWidgetInstance.AddUserMark(mapPosition, mapIndex.ToString(), ARGB(255, 0, 255, 0), MapMarkerTypes.GetMarkerTypeFromID(0));
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

#endif
