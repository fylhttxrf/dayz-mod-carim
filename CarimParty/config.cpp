class CfgPatches {
    class CarimParty {
        requiredAddons[] = {};
    };
};

class CfgMods {
    class CarimParty {
        name = "CarimParty";
        action = "https://github.com/schana/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        dependencies[] = {"World", "Mission"};

        class defs {
            class worldScriptModule {
                files[] = {
                    "CarimParty/scripts",
                };
            };

            class missionScriptModule {
                files[] = {
                    "CarimParty/scripts",
                };
            };
        };
    };
};
