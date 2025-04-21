#ifndef CARIM_CarimMenuCompass
#define CARIM_CarimMenuCompass

class CarimMenuCompass extends UIScriptedMenu {
    Widget carimRoot;
    Widget carimFrame;
    ImageWidget carimImage;
    bool carimIsVisible;

    void CarimMenuCompass() {
        // TODO: make this not show up before player is loaded
        carimRoot = GetGame().GetWorkspace().CreateWidgets("Carim/gui/layouts/compass.layout");
        carimFrame = carimRoot.FindAnyWidget("FrameCompass");
        carimImage = ImageWidget.Cast(carimRoot.FindAnyWidget("ImageCompass"));
        carimIsVisible = true;
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.CarimUpdate, CARIM_60_FPS_INTERVAL_MS, true);
    }

    void ~CarimMenuCompass() {
        if (carimRoot != null) {
            carimRoot.Show(false);
            carimRoot.Unlink();
        }
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.CarimUpdate);
    }

    void CarimUpdate() {
        if (carimRoot != null && carimIsVisible && GetGame().GetPlayer()) {
            CarimSetCompassPos();
            carimRoot.Update();
            carimRoot.Show(true);
        } else if (carimRoot != null) {
            carimRoot.Show(false);
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
