class CfgPatches {
    class CarimCompass {
        requiredAddons[] = {};
    };
};

class CfgMods {
    class CarimCompass {
        name = "CarimCompass";
        action = "https://github.com/schana/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        dependencies[] = {"World", "Mission"};

        class defs {
            class worldScriptModule {
                files[] = {
                    "CarimCompass/scripts",
                };
            };

            class missionScriptModule {
                files[] = {
                    "CarimCompass/scripts",
                };
            };
        };
    };
};
