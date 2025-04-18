class CfgPatches {
    class Carim {
        requiredAddons[] = {"DZ_Scripts"};
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
        inputs = "Carim/Inputs.xml";
        type = "mod";
        dependencies[] = {"World", "Mission"};

        class defs {
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
