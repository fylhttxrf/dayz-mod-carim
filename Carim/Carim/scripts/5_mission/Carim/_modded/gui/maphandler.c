modded class MapHandler {
    ref CarimMenuEditMarker carimMenuEditMarker;

    override bool OnMouseButtonDown(Widget w, int x, int y, int button) {
        if (carimMenuEditMarker && carimMenuEditMarker.visible) {
            if (MapWidget.Cast(w)) carimMenuEditMarker.Hide();
            return true;
        }
        return super.OnMouseButtonDown(w, x, y, button);
    }

    override bool OnDoubleClick(Widget w, int x, int y, int button) {
        if (!CarimEnabled.Map()) {
            return super.OnDoubleClick(w, x, y, button);
        }
        if (carimMenuEditMarker && carimMenuEditMarker.visible) {
            return true;
        }
        super.OnDoubleClick(w, x, y, button);

        vector mousePos, worldPos;
        mousePos[0] = x;
        mousePos[1] = y;
        worldPos = MapWidget.Cast(w).ScreenToMap(mousePos);
        worldPos[1] = GetGame().SurfaceY(worldPos[0], worldPos[2]);

        CarimLogging.Trace(this, string.Format("OnDoubleClick %1, mouse(%2) world(%3)", button.ToString(), mousePos, worldPos));

        auto mission = MissionGameplay.Cast(GetGame().GetMission());
        auto marker = CarimMapMarker.CarimNew(worldPos, "", CfgGameplayHandler.GetCarimMapColorIconDefault(), eMapMarkerTypes.MARKERTYPE_MAP_BORDER_CROSS, CarimUtil.GetIdentifier(GetGame().GetPlayer().GetIdentity()));

        switch (button) {
            case MouseState.LEFT:
                // Add marker
                mission.carimModelMapMarkers.Add(marker);
                break;
            case MouseState.RIGHT:
                // Edit marker
                auto existingMarker = mission.carimModelMapMarkers.GetClosest(marker);
                if (existingMarker) {
                    CarimLogging.Debug(this, "Open MenuEditMarker");
                    if (!carimMenuEditMarker) {
                        carimMenuEditMarker = new CarimMenuEditMarker(existingMarker, x, y);
                        m_Root.AddChild(carimMenuEditMarker.root);
                    }
                    carimMenuEditMarker.marker = existingMarker;
                    carimMenuEditMarker.x = x;
                    carimMenuEditMarker.y = y;
                    carimMenuEditMarker.Show();
                }
                break;
        }

        return true;
    }

    override bool OnClick(Widget w, int x, int y, int button) {
        if (!CarimEnabled.Map()) {
            return super.OnClick(w, x, y, button);
        }
        super.OnClick(w, x, y, button);

        CarimLogging.Trace(this, "OnClick " + w);

        if (button == MouseState.LEFT && carimMenuEditMarker && carimMenuEditMarker.visible) {
            carimMenuEditMarker.OnClick(w);
        }

        return true;
    }
}
