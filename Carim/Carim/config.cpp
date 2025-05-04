class CfgPatches {
    class Carim {
        requiredAddons[] = {"DZ_Scripts"};
    };
};

class CfgMods {
    class Carim {
        name = "Carim";
        action = "https://github.com/CarimDayZ/dayz-mod-carim";
        author = "cnofafva";
        type = "mod";
        inputs = "Carim/Carim/inputs.xml";
        dependencies[] = {"Game", "World", "Mission"};

        class defs {
            class gameScriptModule {
                files[] = {
                    "Carim/Carim/scripts/3_game",
                };
            };

            class worldScriptModule {
                files[] = {
                    "Carim/Carim/scripts/4_world",
                };
            };

            class missionScriptModule {
                files[] = {
                    "Carim/Carim/scripts/5_mission",
                };
            };
        };
    };
};
