Get-ChildItem -Path .\nj -Filter *.jpg -File|Sort-Object -Property {$_.Name.Length}|Write-Output