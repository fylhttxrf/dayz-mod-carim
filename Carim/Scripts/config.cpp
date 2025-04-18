class CfgPatches {
    class Carim_Scripts {
        requiredAddons[] = {"DZ_Scripts", "Carim_GUI"};
    };
};

class CfgMods {
    class Carim {
        name = "Carim";
        dir = "Carim";
        picture = "";
        action = "https://github.com/schana/dayz-mod-carim";
        author = "cnofafva";
        overview = "";
        inputs = "Carim/Scripts/Inputs.xml";
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};

        class defs {
            class gameScriptModule {
                files[] = {
                    "Carim/Scripts/3_Game",
                };
            };

            class worldScriptModule {
                files[] = {
                    "Carim/Scripts/4_World",
                };
            };

            class missionScriptModule {
                files[] = {
                    "Carim/Scripts/5_Mission",
                };
            };
        };
    };
};
