class CarimMenuPartyBase extends UIScriptedMenu {
    string carimName;
    vector carimPosition;
    PlayerBase carimPlayer;

    TextWidget carimNametag;
    TextWidget carimDistance;
    ImageWidget carimIcon;

    float carimLastUpdated = 0.0;

    void CarimMenuPartyBase(string name, vector position, PlayerBase player = null) {
        carimName = name;
        carimPosition = position;
        carimPlayer = player;
    }

    void ~CarimMenuPartyBase() {
        if (layoutRoot) {
            layoutRoot.Unlink();
        }
    }

    string CarimGetLayout() {
        CarimLogging.Error(this, "CarimGetLayout() not implemented");
        return "";
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

    string CarimGetName() {
        return carimName;
    }

    vector CarimGetPosition() {
        return carimPosition;
    }

    override void Update(float timeslice) {
        super.Update(timeslice);

        if (layoutRoot) {
            CarimSetRootPosition();

            Mission mission = GetGame().GetMission();
            IngameHud hud = IngameHud.Cast(mission.GetHud());
            if (hud && hud.GetHudVisibility().IsContextFlagActive(IngameHudVisibility.HUD_HIDE_FLAGS)) {
                layoutRoot.Show(false);
            } else {
                layoutRoot.Show(CarimVisibleOnScreen());
            }

            if (carimLastUpdated > CARIM_60_FPS_INTERVAL_SEC) {
                float distance = Math.Round(vector.Distance(CarimGetPosition(), GetGame().GetPlayer().GetPosition()));
                string distanceString = distance.ToString() + "m";
                if (distance > 1000) {
                    distanceString = (Math.Round(distance / 100) / 10).ToString() + "km";
                }
                carimNametag.SetText(CarimGetName());
                carimDistance.SetText(distanceString);
                CarimOnUpdate();
                carimLastUpdated = 0.0;
            } else {
                carimLastUpdated += timeslice;
            }
        }
    }

    bool CarimVisibleOnScreen() {
        return true;
    }

    void CarimSetRootPosition();
    void CarimOnUpdate();
}
