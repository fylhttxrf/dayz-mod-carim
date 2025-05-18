param([switch]$Setup = $false, [switch]$Build = $false, [switch]$Workbench = $false, [switch]$Diag = $false, [switch]$Server = $false, [switch]$Exp = $false)

$mod = "Carim"
$key = "S:\Drive\DayZKeys\schana.biprivatekey"
$dayZExtract = "C:\Program Files\Wardog\DayZ Extract\DayZExtract.exe"
$pboProject = "C:\Program Files (x86)\Mikero\DePboTools\bin\pboProject.exe"
$steamRoot = "S:\SteamLibrary\steamapps\common"
$expDir = "$steamRoot\DayZ Exp"
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
        (Get-Content "$missions\serverDZ.cfg").Replace("maxPlayers = 60;", "enableCfgGameplayFile=1;`nmaxPlayers = 60;") | Set-Content "$missions\serverDZ.cfg"

        $cfggameplay = Get-Content "$missions\$missionName\cfggameplay.json" -raw | ConvertFrom-Json
        # map config
        $cfggameplay.MapData.ignoreMapOwnership = $true
        $cfggameplay.MapData.ignoreNavItemsOwnership = $true
        $cfggameplay.MapData.displayPlayerPosition = $true
        $cfggameplay.MapData.displayNavInfo = $true
        # unlimited stamina
        $cfggameplay.PlayerData.StaminaData.sprintStaminaModifierErc = 0.0
        $cfggameplay.PlayerData.StaminaData.sprintStaminaModifierCro = 0.0
        $cfggameplay.PlayerData.StaminaData.staminaWeightLimitThreshold = 60000.0
        $cfggameplay.PlayerData.StaminaData.staminaMax = 9999.0
        $cfggameplay.PlayerData.StaminaData.staminaKgToStaminaPercentPenalty = 0.0
        $cfggameplay.PlayerData.StaminaData.staminaMinCap = 9999.0
        $cfggameplay.PlayerData.StaminaData.sprintSwimmingStaminaModifier = 0.0
        $cfggameplay.PlayerData.StaminaData.sprintLadderStaminaModifier = 0.0
        $cfggameplay.PlayerData.StaminaData.meleeStaminaModifier = 0.0
        $cfggameplay.PlayerData.StaminaData.obstacleTraversalStaminaModifier = 0.0
        $cfggameplay.PlayerData.StaminaData.holdBreathStaminaModifier = 0.0
        # write
        $cfggameplay | ConvertTo-Json -Depth 32 -Compress | Set-Content "$missions\$missionName\cfggameplay.json"

        (Get-Content "$missions\$missionName\db\globals.xml").Replace('<var name="TimeLogin" type="0" value="15"/>', '<var name="TimeLogin" type="0" value="1"/>') | Set-Content "$missions\$missionName\db\globals.xml"
    }
}

function Start-Workbench {
    Start-Process -FilePath workbenchApp.exe -WorkingDirectory "$toolsDir\Bin\Workbench" -ArgumentList "-mod=$projectDrive\$mod\$mod"
}

function Build-Project {
    $outputs = Get-ChildItem "$localMods" | Where-Object { $_.PSISContainer }

    foreach ($output in $outputs) {
        $process = (Start-Process $pboProject -PassThru -Wait -ArgumentList "$projectDrive\$mod\$output".Replace('@', ''), "+M=$localMods\$output", "+E=DAYZSA", "+K=$key", "+T", "+H", "+$", "+B", "+C", "-P")
        if ($process.ExitCode) {
            throw "Build failed"
        }
    }
}

function Diag-Project {
    $mods = "$workshopMods\@$mod;$workshopMods\@${mod}MapStyle"
    $exe = "$clientDir\DayZDiag_x64.exe"
    if ($Exp) {
        $exe = "$expDir\DayZDiag_x64.exe"
    }
    
    Start-Process -FilePath "$exe" -WorkingDirectory "$clientDir" -ArgumentList "-mod=$mods -profiles=$missions\profiles\server -doLogs -server -config=$missions\serverDZ.cfg -limitFPS=1000"
    Start-Process -FilePath "$exe" -WorkingDirectory "$clientDir" -ArgumentList "-mod=$mods -profiles=$missions\profiles\client -doLogs -name=cnofafva -connect=127.0.0.1 -port=2302"
}

function Run-Server {
    Start-Process -FilePath "$serverDir\DayZServer_x64.exe" -WorkingDirectory "$serverDir" -ArgumentList "-mod=$workshopMods\@CF;$workshopMods\@TraderPlus;$localMods\@SchanaModParty;$localMods\@SchanaModGlobalChat -profiles=$missions\profiles\server -doLogs -config=$missions\serverDZ.cfg -limitFPS=1000"
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
