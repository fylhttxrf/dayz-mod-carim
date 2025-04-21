class CfgPatches {
    class CarimParty {};
};

class CfgMods {
    class CarimParty {
        name = "CarimParty";
        action = "https://github.com/schana/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        dependencies[] = {"Core"};

        class defs {
            class gameScriptModule {
                files[] = {
                    "CarimParty/scripts/1_core",
                };
            };
        };
    };
};
