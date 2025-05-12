modded class MapHandler {
    override bool OnDoubleClick(Widget w, int x, int y, int button) {
        if (!CarimEnabled.Map()) {
            return super.OnDoubleClick(w, x, y, button);
        }
        super.OnDoubleClick(w, x, y, button);

        CarimLogging.Trace(this, "OnDoubleClick " + button.ToString());

        vector mousePos, worldPos;
        mousePos[0] = x;
        mousePos[1] = y;
        worldPos = MapWidget.Cast(w).ScreenToMap(mousePos);
        worldPos[1] = GetGame().SurfaceY(worldPos[0], worldPos[2]);

        auto mission = MissionGameplay.Cast(GetGame().GetMission());
        auto marker = CarimMapMarker.CarimNew(worldPos, "", CarimColor.PURPLE_300, CarimMapMarkerTypes.ARROW_3, GetGame().GetPlayer().GetIdentity().GetId());

        switch (button) {
            case MouseState.LEFT:
                // Add marker
                mission.carimModelMapMarkers.Add(marker);
                break;
            case MouseState.RIGHT:
                // Remove marker
                mission.carimModelMapMarkers.Remove(marker);
                break;
        }

        return true;
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if (!CarimEnabled.Map()) {
            return super.OnClick(w, x, y, button);
        }
        super.OnClick(w, x, y, button);

        CarimLogging.Trace(this, "OnClick " + button.ToString());

        vector mousePos, worldPos;
        mousePos[0] = x;
        mousePos[1] = y;
        worldPos = MapWidget.Cast(w).ScreenToMap(mousePos);
        worldPos[1] = GetGame().SurfaceY(worldPos[0], worldPos[2]);

        auto mission = MissionGameplay.Cast(GetGame().GetMission());
        auto marker = CarimMapMarker.CarimNew(worldPos, "", CarimColor.PURPLE_300, CarimMapMarkerTypes.ARROW_3, GetGame().GetPlayer().GetIdentity().GetId());

        switch (button) {
            case MouseState.RIGHT:
                // Edit marker
                auto existingMarker = mission.carimModelMapMarkers.GetClose(marker);
                break;
        }

        return true;
    }
}
