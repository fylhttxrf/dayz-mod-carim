$steamRoot = "S:\SteamLibrary\steamapps\common"
$clientDir = "$steamRoot\DayZ"
$serverDir = "$steamRoot\DayZServer"
$localMods = "S:\DayZDevOutput"
$workshopMods = "$clientDir\!Workshop"

$mission = "P:\missions\dayzOffline.chernarusplus"
$mod = "$localmods\@Carim"

Start-Process -FilePath "$clientDir\DayZDiag_x64.exe" -WorkingDirectory "$clientDir" -ArgumentList "-mod=$mod -profiles=$mission\profilesServer -doLogs -server -config=$mission\serverDZ.cfg -limitFPS=1000"
Start-Process -FilePath "$clientDir\DayZDiag_x64.exe" -WorkingDirectory "$clientDir" -ArgumentList "-mod=$mod -profiles=$mission\profilesClient -doLogs -name=cnofafva -connect=127.0.0.1 -port=2302"
