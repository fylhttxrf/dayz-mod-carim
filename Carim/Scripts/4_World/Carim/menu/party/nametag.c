#ifndef CarimMenuPartyNametag
#define CarimMenuPartyNametag

class CarimMenuPartyNametag extends CarimMenuPartyMarker {
    static const int CARIM_HEALTH_LEVELS[] = {GameConstants.STATE_PRISTINE, GameConstants.STATE_WORN, GameConstants.STATE_DAMAGED, GameConstants.STATE_BADLY_DAMAGED, GameConstants.STATE_RUINED};

    ref array<ref ImageWidget> carimHealths = new array<ref ImageWidget>;

    Widget carimListRoot;
    ref array<ref ImageWidget> carimListHealths = new array<ref ImageWidget>;
    TextWidget carimListText;

    // TODO: double-check that this relates to the correct levels to show
    // as the hud shown to the player is different than the icon. Maybe
    // there are more granular levels in the hud?
    int carimHealthLevel = CARIM_HEALTH_LEVELS[0];
    int carimListIndex = 0;

    void CarimMenuPartyNametag(string name, vector position, PlayerBase player) {
        carimListRoot = GetGame().GetWorkspace().CreateWidgets("Carim/gui/layouts/party/list.layout");
        carimListText = TextWidget.Cast(carimListRoot.FindAnyWidget("nametag"));
        foreach(int level : CARIM_HEALTH_LEVELS) {
            carimHealths.Insert(ImageWidget.Cast(carimRoot.FindAnyWidget("IconHealth" + level.ToString())));
            carimListHealths.Insert(ImageWidget.Cast(carimListRoot.FindAnyWidget("IconHealth" + level.ToString())));
        }

        carimIcon.Show(false);
    }

    void ~CarimMenuPartyNametag() {
        if (carimListRoot != null) {
            carimListRoot.Show(false);
            carimListRoot.Unlink();
        }
    }

    override vector CarimGetPosition() {
        if (carimPlayer && carimPlayer.IsAlive()) {
            return carimPlayer.GetPosition();
        } else {
            return super.CarimGetPosition();
        }
    }

    override string CarimGetName() {
        if (carimPlayer && carimPlayer.GetIdentity()) {
            return carimPlayer.GetIdentity().GetName();
        } else {
            return super.CarimGetName();
        }
    }

    int CarimGetHealth() {
        if (carimPlayer) {
            return carimPlayer.GetHealthLevel();
        } else {
            return carimHealthLevel;
        }
    }

    override vector CarimGetMarkerOffset() {
        return "0 1.3 0";
    }

    override void CarimMarkerUpdate() {
        super.CarimMarkerUpdate();
        carimListText.SetText(CarimGetName() + " " + carimDistanceString);

        CarimUpdateHealthIcons();
        CarimUpdateListPosition();
    }

    void CarimUpdateHealthIcons() {
        int currentHealth = CarimGetHealth();
        foreach(int level : CARIM_HEALTH_LEVELS) {
            carimHealths.Get(level).Show(level == currentHealth);
            carimListHealths.Get(level).Show(level == currentHealth);
        }
    }

    void CarimUpdateListPosition() {
        float width, height, x, y;
        carimListRoot.GetSize(width, height);
        carimListRoot.GetPos(x, y);
        // TODO: make list spacing configurable?
        y = (5 + height) * carimListIndex;
        carimListRoot.SetPos(x, y);
    }
}

#endif
