class CfgPatches {
    class CarimCompass {};
};

class CfgMods {
    class CarimCompass {
        name = "CarimCompass";
        action = "https://github.com/CarimDayZ/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        inputs = "Carim/Compass/inputs.xml";
        dependencies[] = {"Core"};

        class defs {
            class engineScriptModule {
                files[] = {
                    "Carim/Compass/scripts/1_core",
                };
            };
        };
    };
};
