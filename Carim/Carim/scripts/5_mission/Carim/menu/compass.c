#ifndef CARIM_CarimMenuCompass
#define CARIM_CarimMenuCompass

class CarimMenuCompass extends UIScriptedMenu {
    Widget carimFrame;
    ImageWidget carimImage;
    bool carimIsVisible = true;
    float carimLastUpdated = 0.0;

    override Widget Init() {
        if (!layoutRoot) {
            layoutRoot = GetGame().GetWorkspace().CreateWidgets("Carim/Carim/gui/layouts/compass.layout");
            carimFrame = layoutRoot.FindAnyWidget("FrameCompass");
            carimImage = ImageWidget.Cast(layoutRoot.FindAnyWidget("ImageCompass"));
        }
        return layoutRoot;
    }

    override void Update(float timeslice) {
        super.Update(timeslice);

        if (layoutRoot) {
            if (carimLastUpdated > CARIM_60_FPS_INTERVAL_SEC) {
                Mission mission = GetGame().GetMission();
                IngameHud hud = IngameHud.Cast(mission.GetHud());
                if (hud && hud.GetHudVisibility().IsContextFlagActive(IngameHudVisibility.HUD_HIDE_FLAGS)) {
                    layoutRoot.Show(false);
                } else {
                    if (carimIsVisible) {
                        CarimSetCompassPos();
                        layoutRoot.Update();
                    }
                    layoutRoot.Show(carimIsVisible);
                }
                carimLastUpdated = 0.0;
            } else {
                carimLastUpdated += timeslice;
            }
        }
    }

    void CarimSetCompassPos() {
        float angle = CarimGetAngle();
        float width, height, x, y;
        carimImage.GetPos(x, y);
        carimImage.GetSize(width, height);
        float center_offset = width / -2.0 + 0.5;
        if (angle > 180) {
            angle = angle - 360;
        }
        float offset = angle * (center_offset / 180.0) + center_offset;
        carimImage.SetPos(offset, y);
    }

    float CarimGetAngle() {
        vector direction = GetGame().GetCurrentCameraDirection();
        float angle = direction.VectorToAngles()[0];
        return angle;
    }

    void CarimToggleHeading() {
        carimIsVisible = !carimIsVisible;
    }
}

#endif
