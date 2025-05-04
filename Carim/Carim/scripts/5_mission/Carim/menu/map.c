#ifndef CARIM_CarimMenuMap
#define CARIM_CarimMenuMap

class CarimMenuMap extends MapMenu {
    ref array<ref MapMarker> carimMarkers = new array<ref MapMarker>;

    override void AddMarker(vector pos, int color, int icon = 0) {
        CarimLogging.Trace(this, "AddMarker");
        carimMarkers.Insert(new MapMarker(pos, "", color, icon));
        m_MapWidgetInstance.AddUserMark(pos, "", color, MapMarkerTypes.GetMarkerTypeFromID(icon));
    }

    override void LoadMapMarkers() {
        CarimLogging.Trace(this, "LoadMapMarkers");
        foreach(MapMarker marker : carimMarkers) {
            m_MapWidgetInstance.AddUserMark(marker.GetMarkerPos(), marker.GetMarkerText(), marker.GetMarkerColor(), MapMarkerTypes.GetMarkerTypeFromID(marker.GetMarkerIcon()));
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
