class CfgPatches {
    class CarimAutorun {};
};

class CfgMods {
    class CarimAutorun {
        name = "CarimAutorun";
        action = "https://github.com/CarimDayZ/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        inputs = "Carim/Autorun/inputs.xml";
        dependencies[] = {"Core"};

        class defs {
            class engineScriptModule {
                files[] = {
                    "Carim/Autorun/scripts/1_core",
                };
            };
        };
    };
};
