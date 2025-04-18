class CarimMenuPartyMarker extends UIScriptedMenu {
    Widget carimRoot;
    TextWidget carimNametag;
    TextWidget carimDistance;
    ImageWidget carimIcon;

    string carimName;
    vector carimPosition;
    string carimDistanceString;
    PlayerBase carimPlayer;

    void CarimMenuPartyMarker(string name, vector position, PlayerBase player = null) {
        carimRoot = Widget.Cast(GetGame().GetWorkspace().CreateWidgets("Carim/GUI/layouts/party/marker.layout"));
        carimNametag = TextWidget.Cast(carimRoot.FindAnyWidget("nametag"));
        carimDistance = TextWidget.Cast(carimRoot.FindAnyWidget("distance"));
        carimIcon = ImageWidget.Cast(carimRoot.FindAnyWidget("icon"));
        carimName = name;
        carimPosition = position;
        carimPlayer = player;
        carimRoot.Show(false);
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.CarimUpdate, CARIM_60_FPS_INTERVAL_MS, true);
    }

    void ~CarimMenuPartyMarker() {
        if (carimRoot != null) {
            carimRoot.Show(false);
            carimRoot.Unlink();
        }
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.CarimUpdate);
    }

    void CarimRemove() {
        carimName = CARIM_DELETE;
    }

    vector CarimGetPosition() {
        return carimPosition;
    }

    string CarimGetName() {
        return carimName;
    }

    void CarimUpdate() {
        if (CarimShouldShow()) {
            CarimMarkerUpdate();
        } else if (carimRoot != null) {
            carimRoot.Show(false);
            delete this;
        }
    }

    bool CarimShouldShow() {
        if (carimRoot == null) {
            return false;
        }
        if (!GetGame().GetPlayer()) {
            return false;
        }
        if (carimName == CARIM_DELETE) {
            return false;
        }
        return true;
    }

    vector CarimGetMarkerOffset() {
        return "0 0.2 0";
    }

    void CarimMarkerUpdate() {
        vector screenPosition = GetGame().GetScreenPos(CarimGetPosition() + CarimGetMarkerOffset());
        float x = Math.Round(screenPosition[0]);
        float y = Math.Round(screenPosition[1]);
        float distance = Math.Round(vector.Distance(CarimGetPosition(), GetGame().GetPlayer().GetPosition()));
        string distanceString = distance.ToString() + "m";
        if (distance > 1000) {
            distanceString = (Math.Round(distance / 100) / 10).ToString() + "km";
        }
        carimDistanceString = distanceString;
        carimRoot.SetPos(x, y);
        carimNametag.SetText(CarimGetName());
        carimDistance.SetText(carimDistanceString);
        carimRoot.Show(CarimVisibleOnScreen());
    }

    bool CarimVisibleOnScreen() {
        vector pos = GetGame().GetScreenPosRelative(CarimGetPosition());
        if (pos[0] >= 1 || pos[0] == 0 || pos[1] >= 1 || pos[1] == 0) {
            return false;
        } else if (pos[2] < 0) {
            return false;
        }
        return true;
    }
}
