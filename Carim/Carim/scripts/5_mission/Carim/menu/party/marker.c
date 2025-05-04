#ifndef CARIM_CarimMenuPartyMarker
#define CARIM_CarimMenuPartyMarker

class CarimMenuPartyMarker extends CarimMenuPartyBase {
    override string CarimGetLayout() {
        return "Carim/Carim/gui/layouts/party/marker.layout";
    }

    vector CarimGetMarkerOffset() {
        return "0 0.2 0";
    }

    override void CarimSetRootPosition() {
        vector screenPosition = GetGame().GetScreenPos(CarimGetPosition() + CarimGetMarkerOffset());
        float x = screenPosition[0];
        float y = screenPosition[1];

        layoutRoot.SetPos(x, y);
    }

    override bool CarimVisibleOnScreen() {
        vector pos = GetGame().GetScreenPosRelative(CarimGetPosition());
        if (pos[0] >= 1 || pos[0] == 0 || pos[1] >= 1 || pos[1] == 0) {
            return false;
        } else if (pos[2] < 0) {
            return false;
        }
        return true;
    }
}

#endif
