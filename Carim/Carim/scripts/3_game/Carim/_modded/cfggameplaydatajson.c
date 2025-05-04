#ifndef CARIM_CfgGameplayJson
#define CARIM_CfgGameplayJson

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
    bool enabled = false;
}

class ITEM_CarimChatData extends ITEM_DataBase {
    bool enabled = false;
    int colorDirect = 0xfffafafa; /* grey 50 */
    int colorGlobal = 0xffffd54f; /* amber 300 */
    int colorServer = 0xff4fc3f7; /* light blue 300 */
    int colorAlert = 0xffff8a65;  /* deep orange 300 */
}

class ITEM_CarimCompassData extends ITEM_DataBase {
    bool enabled = false;
    bool requireNavItem = false;
}

class ITEM_CarimMapData extends ITEM_DataBase {
    bool enabled = false;
}

class ITEM_CarimPartyData extends ITEM_DataBase {
    bool enabled = false;
    int maxPartySize = -1;
    int maxMarkers = 3;
}

#endif
