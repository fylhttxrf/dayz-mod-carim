class CfgPatches {
    class CarimAutorun {};
};

class CfgMods {
    class CarimAutorun {
        name = "CarimAutorun";
        action = "https://github.com/schana/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        dependencies[] = {"Core"};

        class defs {
            class gameScriptModule {
                files[] = {
                    "CarimAutorun/scripts/1_core",
                };
            };
        };
    };
};
