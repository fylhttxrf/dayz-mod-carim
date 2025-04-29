param([switch]$Setup = $false, [switch]$Build = $false, [switch]$Workbench = $false, [switch]$Diag = $false, [switch]$Server = $false)

$mod = "Carim"
$key = "S:\Drive\DayZKeys\schana.biprivatekey"
$dayZExtract = "C:\Program Files\Wardog\DayZ Extract\DayZExtract.exe"
$pboProject = "C:\Program Files (x86)\Mikero\DePboTools\bin\pboProject.exe"
$steamRoot = "S:\SteamLibrary\steamapps\common"
$clientDir = "$steamRoot\DayZ"
$serverDir = "$steamRoot\DayZServer"
$toolsDir = "$steamRoot\DayZ Tools"
$workshopMods = "$clientDir\!Workshop"
$projectDrive = "P:"

$root = $(Convert-Path $(git rev-parse --show-toplevel))
$localMods = "$root\build"
$missions = "$root\missions"
$missionName = "dayzOffline.chernarusplus"

function Setup-Project {
    if (!(Test-Path -Path "$projectDrive\DZ")) {
        # Extract game data to project drive
        Start-Process -Wait -FilePath "$dayZExtract" -ArgumentList "P:"
    }

    if (!(Test-Path -Path "$projectDrive\$mod")) {
        # Create the junction, since pboProject doesn't work with symbolic links
        cmd /c mklink /J "$projectDrive\$mod" "$root\$mod"
        #New-Item -Path "$projectDrive\$mod" -Value "$sourceRoot\$mod" -ItemType SymbolicLink
    }

    if (!(Test-Path -Path "$missions\$missionName")) {
        # Setup the mission used for testing
        Copy-Item "$serverDir\mpmissions\$missionName" -Destination "$missions\$missionName" -Recurse
        Copy-Item "$serverDir\serverDZ.cfg" -Destination "$missions\"
        (Get-Content "$missions\serverDZ.cfg").Replace($missionName, "$missions\$missionName") | Set-Content "$missions\serverDZ.cfg"
        (Get-Content "$missions\$missionName\db\globals.xml").Replace('<var name="TimeLogin" type="0" value="15"/>', '<var name="TimeLogin" type="0" value="1"/>') | Set-Content "$missions\$missionName\db\globals.xml"
    }
}

function Start-Workbench {
    $addons = Get-ChildItem "$root\$mod" | Where-Object { $_.PSISContainer }
    $mods = $addons -join ";$projectDrive\$mod\"
    Start-Process -FilePath workbenchApp.exe -WorkingDirectory "$toolsDir\Bin\Workbench" -ArgumentList "-mod=$projectDrive\$mod\$mods"
}

function Build-Project {
    $outputs = Get-ChildItem "$localMods" | Where-Object { $_.PSISContainer }

    foreach ($output in $outputs) {
        Start-Process $pboProject -Wait -ArgumentList "$projectDrive\$mod", "+M=$localMods\$output", "+E=DAYZSA", "+K=$key", "+T", "+H", "+$", "+Z", "+B", "+C", "-P" 

        if (!($output.ToString() -eq "@Carim") -and !$output.ToString().EndsWith("Autorun")) {
            Get-ChildItem -Path "$localMods\$output\addons" -Filter "Autorun*" | Remove-Item
        }

        if (!($output.ToString() -eq "@Carim") -and !$output.ToString().EndsWith("Chat")) {
            Get-ChildItem -Path "$localMods\$output\addons" -Filter "Chat*" | Remove-Item
        }

        if (!($output.ToString() -eq "@Carim") -and !$output.ToString().EndsWith("Compass")) {
            Get-ChildItem -Path "$localMods\$output\addons" -Filter "Compass*" | Remove-Item
        }

        if (!($output.ToString() -eq "@Carim") -and !$output.ToString().EndsWith("Party")) {
            Get-ChildItem -Path "$localMods\$output\addons" -Filter "Party*" | Remove-Item
        }
    }
}

function Diag-Project {
    Start-Process -FilePath "$clientDir\DayZDiag_x64.exe" -WorkingDirectory "$clientDir" -ArgumentList "-mod=$localMods\@$mod -profiles=$missions\profiles\server -doLogs -server -config=$missions\serverDZ.cfg -limitFPS=1000"
    Start-Process -FilePath "$clientDir\DayZDiag_x64.exe" -WorkingDirectory "$clientDir" -ArgumentList "-mod=$localMods\@$mod -profiles=$missions\profiles\client -doLogs -name=cnofafva -connect=127.0.0.1 -port=2302"
}

function Run-Server {
    Start-Process -FilePath "$serverDir\DayZServer_x64.exe" -WorkingDirectory "$serverDir" -ArgumentList "-mod=$localMods\@$mod -profiles=$missions\profiles\server -doLogs -config=$missions\serverDZ.cfg -limitFPS=1000"
}

if ($Setup) {
    Setup-Project
}
if ($Build) {
    Build-Project
}
if ($Workbench) {
    Start-Workbench
}
if ($Diag) {
    Diag-Project
}
if ($Server) {
    Run-Server
}
