$sourceRoot = "S:\DayZDevSource\dayz-mod-carim"
$steamRoot = "S:\SteamLibrary"
$toolsDir = "$steamRoot\steamapps\common\DayZ Tools"
$projectDrive = "P:"
$mod = "Carim"

if (!(Test-Path -Path "$projectDrive\$mod")) {
    # Create the junction, since pboProject doesn't work with symbolic links
    cmd /c mklink /J "$projectDrive\$mod" "$sourceRoot\$mod"
    #New-Item -Path "$projectDrive\$mod" -Value "$sourceRoot\$mod" -ItemType SymbolicLink
}

$addons = "Base", "Autorun", "Chat", "Compass", "Party"
$mods = $addons -join ";$projectDrive\$mod\"
# Run the workbench app with this mod
Start-Process -FilePath workbenchApp.exe -WorkingDirectory "$toolsDir\Bin\Workbench" -ArgumentList "-mod=$projectDrive\$mod\$mods"
