class CarimMenuMarker extends UIScriptedMenu {
    static const int CARIM_HEALTH_LEVELS[] = {GameConstants.STATE_PRISTINE, GameConstants.STATE_WORN, GameConstants.STATE_DAMAGED, GameConstants.STATE_BADLY_DAMAGED, GameConstants.STATE_RUINED};

    ref CarimMapMarker carimMarker;

    TextWidget carimNametag;
    TextWidget carimDistance;
    ImageWidget carimIcon;
    ref array<ref ImageWidget> carimHealths = new array<ref ImageWidget>;

    float carimLastUpdated = 0.0;

    void CarimMenuMarker(CarimMapMarker marker) {
        carimMarker = marker;
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
            foreach(int level : CARIM_HEALTH_LEVELS) {
                carimHealths.Insert(ImageWidget.Cast(layoutRoot.FindAnyWidget("IconHealth" + level.ToString())));
            }
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
        layoutRoot.Show(!hudHid && CarimVisibleOnScreen());
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

    void CarimUpdateContent() {
        carimNametag.SetText(carimMarker.GetMarkerText());
        carimDistance.SetText(CarimGetDistance());
        CarimUpdateHealths();
        CarimOnUpdate();
    }

    string CarimGetDistance() {
        float distance = Math.Round(vector.Distance(carimMarker.GetMarkerPos(), GetGame().GetPlayer().GetPosition()));
        string distanceString = distance.ToString() + "m";
        if (distance > 1000) {
            distanceString = (Math.Round(distance / 100) / 10).ToString() + "km";
        }
        return distanceString;
    }

    void CarimUpdateHealths() {
        int currentHealth = carimMarker.CarimGetHealthLevel();
        foreach(int level : CARIM_HEALTH_LEVELS) {
            if (carimHealths.Count() > level) {
                carimHealths.Get(level).Show(level == currentHealth);
            }
        }
        if (currentHealth >= 0 && currentHealth < carimHealths.Count()) {
            carimIcon.Show(false);
        } else {
            carimIcon.Show(true);
        }
    }

    void CarimOnUpdate();
}
