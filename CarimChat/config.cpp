class CfgPatches {
    class CarimChat {
        requiredAddons[] = {};
    };
};

class CfgMods {
    class CarimChat {
        name = "CarimChat";
        action = "https://github.com/schana/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        dependencies[] = {"World", "Mission"};

        class defs {
            class worldScriptModule {
                files[] = {
                    "CarimChat/scripts",
                };
            };

            class missionScriptModule {
                files[] = {
                    "CarimChat/scripts",
                };
            };
        };
    };
};
