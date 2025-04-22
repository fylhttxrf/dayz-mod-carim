class CfgPatches {
    class CarimParty {};
};

class CfgMods {
    class CarimParty {
        name = "CarimParty";
        action = "https://github.com/CarimDayZ/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        inputs = "Carim/Party/inputs.xml";
        dependencies[] = {"Core"};

        class defs {
            class engineScriptModule {
                files[] = {
                    "Carim/Party/scripts/1_core",
                };
            };
        };
    };
};
