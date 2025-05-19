class CarimMenuMarker extends UIScriptedMenu {
    ref CarimMapMarker carimMarker;
    int carimTextColor;
    int carimHideLessThan;
    int carimHideGreaterThan;

    TextWidget carimNametag;
    TextWidget carimDistance;
    ImageWidget carimIcon;

    float carimLastUpdated = 0.0;

    void CarimMenuMarker(CarimMapMarker marker, int textColor, int hideLessThan, int hideGreaterThan) {
        carimMarker = marker;
        carimTextColor = textColor;
        carimHideLessThan = hideLessThan;
        carimHideGreaterThan = hideGreaterThan;
    }

    void ~CarimMenuMarker() {
        if (layoutRoot) {
            layoutRoot.Unlink();
        }
    }

    string CarimGetLayout() {
        return "Carim/Carim/gui/layouts/party/marker.layout";
    }

    override Widget Init() {
        if (!layoutRoot) {
            layoutRoot = Widget.Cast(GetGame().GetWorkspace().CreateWidgets(CarimGetLayout()));
            carimNametag = TextWidget.Cast(layoutRoot.FindAnyWidget("nametag"));
            carimDistance = TextWidget.Cast(layoutRoot.FindAnyWidget("distance"));
            carimIcon = ImageWidget.Cast(layoutRoot.FindAnyWidget("icon"));
        }

        return layoutRoot;
    }

    override void Update(float timeslice) {
        super.Update(timeslice);

        if (layoutRoot) {
            CarimSetRootPosition();
            CarimSetVisibility();

            if (carimLastUpdated > CARIM_60_FPS_INTERVAL_SEC) {
                CarimUpdateContent();
                carimLastUpdated = 0.0;
            } else {
                carimLastUpdated += timeslice;
            }
        }
    }

    void CarimSetRootPosition() {
        vector screenPosition = GetGame().GetScreenPos(carimMarker.GetMarkerPos() + CarimGetMarkerOffset());
        float x = screenPosition[0];
        float y = screenPosition[1];

        layoutRoot.SetPos(x, y);
    }

    vector CarimGetMarkerOffset() {
        if (carimMarker.carimPlayer) {
            return "0 1.3 0";
        } else {
            return "0 0.2 0";
        }
    }

    void CarimSetVisibility() {
        Mission mission = GetGame().GetMission();
        IngameHud hud = IngameHud.Cast(mission.GetHud());
        bool hudHid = hud && hud.GetHudVisibility().IsContextFlagActive(IngameHudVisibility.HUD_HIDE_FLAGS);
        layoutRoot.Show(!hudHid && CarimVisibleOnScreen() && CarimVisibleDistance());
    }

    bool CarimVisibleOnScreen() {
        vector pos = GetGame().GetScreenPosRelative(carimMarker.GetMarkerPos());
        if (pos[0] >= 1 || pos[0] == 0 || pos[1] >= 1 || pos[1] == 0) {
            return false;
        } else if (pos[2] < 0) {
            return false;
        }
        return true;
    }

    bool CarimVisibleDistance() {
        bool canSeeBasedOnDistance = true;
        auto distance = CarimGetDistance();
        if (hideLessThan >= 0 && distance <= hideLessThan) {
            canSeeBasedOnDistance = false;
        }
        if (hideGreaterThan >= 0 && distance >= hideGreaterThan) {
            canSeeBasedOnDistance = false;
        }
        return canSeeBasedOnDistance;
    }

    void CarimUpdateContent() {
        carimNametag.SetText(carimMarker.GetMarkerText());
        carimDistance.SetText(CarimFormatDistance(CarimGetDistance()));
        string imageFile = MapMarkerTypes.GetMarkerTypeFromID(carimMarker.GetMarkerIcon());
        imageFile.Replace("\\DZ", "DZ");
        carimIcon.LoadImageFile(0, imageFile);

        carimIcon.SetColor(carimMarker.GetMarkerColor());
        carimNametag.SetColor(textColor);
        carimDistance.SetColor(textColor);
        CarimOnUpdate();
    }

    float CarimGetDistance() {
        auto player = GetGame().GetPlayer();
        if (player) {
            return Math.Round(vector.Distance(carimMarker.GetMarkerPos(), player.GetPosition()));
        }
        return -1;
    }

    string CarimFormatDistance(float distance) {
        if (distance < 0) {
            return "";
        }
        string distanceString = distance.ToString() + "m";
        if (distance > 1000) {
            distanceString = (Math.Round(distance / 100) / 10).ToString() + "km";
        }
        return distanceString;
    }

    void CarimOnUpdate();
}
