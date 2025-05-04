#ifndef CARIM_MapHandler
#define CARIM_MapHandler

modded class MapHandler {
    override bool OnDoubleClick(Widget w, int x, int y, int button) {
        if (!CarimEnabled.Map()) {
            return super.OnDoubleClick(w, x, y, button);
        }
        super.OnDoubleClick(w, x, y, button);

        CarimLogging.Trace(this, "OnDoubleClick");
        vector screen_to_map = MapWidget.Cast(w).ScreenToMap(Vector(x, y, 0));
        MapMenu m = MapMenu.Cast(g_Game.GetUIManager().FindMenu(MENU_MAP));
        m.AddMarker(screen_to_map, ARGB(255, 255, 0, 0), 0);

        return true;
    }
}

#endif
