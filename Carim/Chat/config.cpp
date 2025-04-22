class CfgPatches {
    class CarimChat {};
};

class CfgMods {
    class CarimChat {
        name = "CarimChat";
        action = "https://github.com/CarimDayZ/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        inputs = "Carim/Chat/inputs.xml";
        dependencies[] = {"Core"};

        class defs {
            class engineScriptModule {
                files[] = {
                    "Carim/Chat/scripts/1_core",
                };
            };
        };
    };
};
