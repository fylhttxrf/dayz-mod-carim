class CfgPatches {
    class Carim {
        requiredAddons[] = {"DZ_Scripts"};
    };
};

class CfgMods {
    class Carim {
        name = "Carim";
        action = "https://github.com/schana/dayz-mod-carim";
        author = "cnofafva";
        inputs = "Carim/inputs.xml";
        type = "mod";
        dependencies[] = {"World", "Mission"};

        class defs {
            class worldScriptModule {
                files[] = {
                    "Carim/scripts/4_world",
                };
            };

            class missionScriptModule {
                files[] = {
                    "Carim/scripts/5_mission",
                };
            };
        };
    };
};
