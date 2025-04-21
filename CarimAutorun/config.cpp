class CfgPatches {
    class CarimAutorun {
        requiredAddons[] = {};
    };
};

class CfgMods {
    class CarimAutorun {
        name = "CarimAutorun";
        action = "https://github.com/schana/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        dependencies[] = {"World", "Mission"};

        class defs {
            class worldScriptModule {
                files[] = {
                    "CarimAutorun/scripts",
                };
            };

            class missionScriptModule {
                files[] = {
                    "CarimAutorun/scripts",
                };
            };
        };
    };
};
