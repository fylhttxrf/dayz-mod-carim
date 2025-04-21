class CfgPatches {
    class CarimCompass {};
};

class CfgMods {
    class CarimCompass {
        name = "CarimCompass";
        action = "https://github.com/schana/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        dependencies[] = {"Core"};

        class defs {
            class gameScriptModule {
                files[] = {
                    "CarimCompass/scripts/1_core",
                };
            };
        };
    };
};
