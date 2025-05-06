modded class CfgGameplayJson {
    ref ITEM_CarimData CarimData = new ITEM_CarimData;
}

class ITEM_CarimData extends ITEM_DataBase {
    ref ITEM_CarimAutorunData CarimAutorunData = new ITEM_CarimAutorunData;
    ref ITEM_CarimChatData CarimChatData = new ITEM_CarimChatData;
    ref ITEM_CarimCompassData CarimCompassData = new ITEM_CarimCompassData;
    ref ITEM_CarimMapData CarimMapData = new ITEM_CarimMapData;
    ref ITEM_CarimPartyData CarimPartyData = new ITEM_CarimPartyData;

    bool initialized = false;
    ref array<string> adminIds;

    override bool ValidateServer() {
        // Use initialize to determine if the data has been loaded
        // in the client so we don't have to override the static
        // onRPC in the Handler. So before the client uses any
        // values, it checks if initialized is true, which means
        // the values have been sync'd from the server.
        // We use ValidateServer() since InitServer() is only
        // called when the cfgGameplay.json isn't used.
        initialized = true;
        return true;
    }
}

class ITEM_CarimAutorunData extends ITEM_DataBase {
    bool enabled = true;
}

class ITEM_CarimChatData extends ITEM_DataBase {
    bool enabled = true;
    int colorDirect = CarimColor.GREY_50;
    int colorGlobal = CarimColor.AMBER_300;
    int colorServer = CarimColor.LIGHT_BLUE_300;
    int colorAlert = CarimColor.DEEP_ORANGE_300;
}

class ITEM_CarimCompassData extends ITEM_DataBase {
    bool enabled = true;
    bool requireNavItem = false;
}

class ITEM_CarimMapData extends ITEM_DataBase {
    bool enabled = true;
}

class ITEM_CarimPartyData extends ITEM_DataBase {
    bool enabled = true;
    int maxPartySize = -1;
    int maxPings = 3;
}
