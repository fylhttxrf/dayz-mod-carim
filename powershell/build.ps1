# run from root directory

$pboProject = "C:\Program Files (x86)\Mikero\DePboTools\bin\pboProject.exe"

$source = "P:\Carim"
$key = "S:\Drive\DayZKeys\schana.biprivatekey"
$outputs = Get-ChildItem build | Where-Object { $_.PSISContainer }

foreach ($output in $outputs) {
    Start-Process $pboProject -Wait -ArgumentList "$source", "+M=$PWD\build\$output", "+E=DAYZSA", "+K=$key", "+T", "+H", "+$", "+Z", "+B", "+C", "-P"

    Write-Host $output    

    if (!($output.ToString() -eq "@Carim") -and !$output.ToString().EndsWith("Autorun")) {
        Get-ChildItem -Path "$PWD\build\$output\addons" -Filter "Autorun*" | Remove-Item
    }

    if (!($output.ToString() -eq "@Carim") -and !$output.ToString().EndsWith("Chat")) {
        Get-ChildItem -Path "$PWD\build\$output\addons" -Filter "Chat*" | Remove-Item
    }

    if (!($output.ToString() -eq "@Carim") -and !$output.ToString().EndsWith("Compass")) {
        Get-ChildItem -Path "$PWD\build\$output\addons" -Filter "Compass*" | Remove-Item
    }

    if (!($output.ToString() -eq "@Carim") -and !$output.ToString().EndsWith("Party")) {
        Get-ChildItem -Path "$PWD\build\$output\addons" -Filter "Party*" | Remove-Item
    }
}

