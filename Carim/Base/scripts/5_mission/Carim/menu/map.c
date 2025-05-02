#ifndef CARIM_CarimMenuMap
#define CARIM_CarimMenuMap

class CarimMenuMap extends MapMenu {
    ref array<ref MapMarker> carimMarkers = new array<ref MapMarker>;

    override Widget Init() {
        CarimLogging.Trace(this, "Init");
        auto widget = super.Init();
        m_IsOpenning = false; // BI typo
        SetGPSMarkerVisibility(true);
        SetGPSDirectionVisibility(true);
        SetCompassUIVisibility(true);
        SetUpperLegendVisibility(true);
		m_HasCompass = true;
		m_HasGPS = true;
        return widget;
    }

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

    override void Update(float timeslice) {
        CarimLogging.Trace(this, "Update " + CarimUtil.CheckInput("UAMapToggle").ToString());
        super.Update(timeslice);
    }

    override void SetCompassUIVisibility(bool pState) {
        CarimLogging.Trace(this, "SetCompassUIVisibility " + pState.ToString());
        super.SetCompassUIVisibility(pState);
    }

    override void SetGPSMarkerVisibility(bool pState) {
        CarimLogging.Trace(this, "SetGPSMarkerVisibility " + pState.ToString());
        super.SetGPSMarkerVisibility(pState);
    }

    override void SetGPSDirectionVisibility(bool pState) {
        CarimLogging.Trace(this, "SetGPSDirectionVisibility " + pState.ToString());
        super.SetGPSDirectionVisibility(pState);
    }
}

#endif
