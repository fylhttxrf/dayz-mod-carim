$sourceRoot = "S:\DayZDevSource\dayz-mod-carim"
$steamRoot = "S:\SteamLibrary"
$toolsDir = "$steamRoot\steamapps\common\DayZ Tools"
$projectDrive = "P:"
$mod = "Carim"

$modSuffixes = "", "Autorun", "Chat", "Compass", "Party"
foreach ($suffix in $modSuffixes) {
    if (!(Test-Path -Path "$projectDrive\$mod$suffix")) {
        # Create the junction, since pboProject doesn't work with symbolic links
        cmd /c mklink /J "$projectDrive\$mod$suffix" "$sourceRoot\$mod$suffix"
        #New-Item -Path "$projectDrive\$mod$suffix" -Value "$sourceRoot\$mod$suffix" -ItemType SymbolicLink
    }
}

# Run the workbench app with this mod
$mods = $modSuffixes -join ";$projectDrive\$mod"
start workbenchApp.exe -wo "$toolsDir\Bin\Workbench" "-mod=$projectDrive\$mod$mods"
