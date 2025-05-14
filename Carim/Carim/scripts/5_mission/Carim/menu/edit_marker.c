class CarimMenuEditMarker extends Managed {
    ref CarimMapMarker marker;
    int x;
    int y;
    bool visible;

    Widget root;
    EditBoxWidget text;
    ImageWidget icon;

    ButtonWidget previous;
    ButtonWidget next;
    ButtonWidget save;
    ButtonWidget deleteButton;
    ButtonWidget cancel;

    ref array<ref ButtonWidget> colorButtons;

    void CarimMenuEditMarker(CarimMapMarker iMarker, int iX, int iY) {
        marker = iMarker;
        x = iX;
        y = iY;

        root = GetGame().GetWorkspace().CreateWidgets("Carim/Carim/gui/layouts/edit_marker.layout");
        text = EditBoxWidget.Cast(root.FindAnyWidget("text"));
        icon = ImageWidget.Cast(root.FindAnyWidget("icon"));

        previous = ButtonWidget.Cast(root.FindAnyWidget("previous"));
        next = ButtonWidget.Cast(root.FindAnyWidget("next"));
        save = ButtonWidget.Cast(root.FindAnyWidget("save"));
        deleteButton = ButtonWidget.Cast(root.FindAnyWidget("deleteButton"));
        cancel = ButtonWidget.Cast(root.FindAnyWidget("cancel"));

        auto panel = root.FindAnyWidget("panel");

        colorButtons = GetColorButtons(panel);
    }

    static array<ref ButtonWidget> GetColorButtons(Widget panel) {
        // Needs to be 21 for layout to work
        int colors[] = {CarimColor.RED_500,
                        CarimColor.PINK_500,
                        CarimColor.PURPLE_500,
                        CarimColor.DEEP_PURPLE_500,
                        CarimColor.INDIGO_500,
                        CarimColor.BLUE_500,
                        CarimColor.LIGHT_BLUE_500,
                        CarimColor.CYAN_500,
                        CarimColor.TEAL_500,
                        CarimColor.GREEN_500,
                        CarimColor.LIGHT_GREEN_500,
                        CarimColor.LIME_500,
                        CarimColor.YELLOW_500,
                        CarimColor.AMBER_500,
                        CarimColor.ORANGE_500,
                        CarimColor.DEEP_ORANGE_500,
                        CarimColor.BROWN_500,
                        CarimColor.GRAY_500,
                        CarimColor.BLUE_GRAY_500,
                        CarimColor.BLACK,
                        CarimColor.WHITE};

        int currentX = 8;
        int currentY = 48;

        ButtonWidget button;
        array<ref ButtonWidget> buttons = new array<ref ButtonWidget>;

        foreach(int color : colors) {
            CarimLogging.Trace(null, string.Format("%1 (%2, %3)", color, currentX, currentY));
            button = ButtonWidget.Cast(GetGame().GetWorkspace().CreateWidgets("Carim/Carim/gui/layouts/edit_color_button.layout"));
            button.SetPos(currentX, currentY);
            button.SetColor(color);
            panel.AddChild(button);
            if (currentX == 248) {
                currentX = 8;
                currentY += 40;
            } else {
                currentX += 40;
            }
            buttons.Insert(button);
        }

        return buttons;
    }

    void Show() {
        visible = true;
        Refresh();
    }

    void Hide() {
        visible = false;
        Refresh();
    }

    void Refresh() {
        if (root) {
            CarimLogging.Trace(this, "Refresh");

            text.SetText(marker.GetMarkerText());
            icon.LoadImageFile(0, MapMarkerTypes.GetMarkerTypeFromID(marker.GetMarkerIcon()));
            icon.SetColor(marker.GetMarkerColor());

            root.SetPos(x, y);
            root.Show(visible);
        }
    }

    bool OnClick(Widget w) {
        CarimLogging.Trace(this, "OnClick");

        auto mission = MissionGameplay.Cast(GetGame().GetMission());

        switch (w) {
            case cancel:
                CarimLogging.Trace(this, "Cancel");
                Hide();
                break;
            case save:
                CarimLogging.Trace(this, "Save");
                marker.CarimSetMarkerText(text.GetText());
                marker.CarimSetMarkerIcon(0);
                marker.CarimSetMarkerColor(icon.GetColor());
                mission.carimModelMapMarkers.Persist();
                Hide();
                break;
            case deleteButton:
                CarimLogging.Trace(this, "Delete");
                mission.carimModelMapMarkers.Remove(marker);
                Hide();
                break;
            case previous:
                CarimLogging.Trace(this, "Previous");
                break;
            case next:
                CarimLogging.Trace(this, "Next");
                break;
            default:
                foreach(auto button : colorButtons) {
                    if (w == button) {
                        icon.SetColor(button.GetColor());
                        return true;
                    }
                }
                return false;
        }
        return true;
    }
}
