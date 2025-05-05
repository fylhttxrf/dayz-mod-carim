#ifndef CARIM_MapHandler
#define CARIM_MapHandler

modded class MapHandler {
    override bool OnDoubleClick(Widget w, int x, int y, int button) {
        if (!CarimEnabled.Map()) {
            return super.OnDoubleClick(w, x, y, button);
        }
        super.OnDoubleClick(w, x, y, button);

        CarimLogging.Trace(this, "OnDoubleClick");

        vector mousePos, worldPos;
        mousePos[0] = x;
        mousePos[1] = y;
        worldPos = MapWidget.Cast(w).ScreenToMap(mousePos);
        worldPos[1] = GetGame().SurfaceY(worldPos[0], worldPos[2]);

        MapMenu m = MapMenu.Cast(g_Game.GetUIManager().FindMenu(MENU_MAP));
        m.AddMarker(worldPos, ARGB(255, 255, 0, 0), 0);

        return true;
    }
}

#endif
