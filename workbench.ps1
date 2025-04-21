$sourceRoot = "S:\DayZDevSource\dayz-mod-carim"
$steamRoot = "S:\SteamLibrary"
$toolsDir = "$steamRoot\steamapps\common\DayZ Tools"
$projectDrive = "P:"
$mod = "Carim"

if (!(Test-Path -Path "$projectDrive\$mod")) {
    # Create the symbolic link
    New-Item -Path "$projectDrive\$mod" -Value "$sourceRoot\$mod" -ItemType SymbolicLink
}

# Run the workbench app with this mod
start workbenchApp.exe -wo "$toolsDir\Bin\Workbench" "-mod=$projectDrive\$mod"
