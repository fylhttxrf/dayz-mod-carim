class CfgPatches {
    class CarimChat {};
};

class CfgMods {
    class CarimChat {
        name = "CarimChat";
        action = "https://github.com/schana/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        dependencies[] = {"Core"};

        class defs {
            class gameScriptModule {
                files[] = {
                    "CarimChat/scripts/1_core",
                };
            };
        };
    };
};
