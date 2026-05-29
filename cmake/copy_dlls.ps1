# Copy runtime DLLs next to executables. Skips copies when the destination is
# already up to date; fails the build if an update is required but blocked
# (e.g. Blaze.exe still running and holding DLLs in build/Release).
param(
    [string]$Destination = "",
    [string]$DllList = "",
    [string]$VcpkgBinDir = "",
    [string]$ExtraBinDir = ""
)

$ErrorActionPreference = "Stop"

function Copy-OneDll {
    param([string]$Source, [string]$DestDir)
    if (-not $Source) { return }
    if (-not (Test-Path -LiteralPath $Source)) { return }

    $dest = Join-Path $DestDir (Split-Path -Leaf $Source)
    if (Test-Path -LiteralPath $dest) {
        $srcItem = Get-Item -LiteralPath $Source
        $destItem = Get-Item -LiteralPath $dest
        if ($srcItem.Length -eq $destItem.Length -and
            $srcItem.LastWriteTimeUtc -le $destItem.LastWriteTimeUtc) {
            return
        }
    }

    try {
        Copy-Item -LiteralPath $Source -Destination $dest -Force
    } catch {
        $name = Split-Path -Leaf $Source
        Write-Error @"
Failed to copy $name to $DestDir.
The file is in use. Close Blaze.exe, Blaze3D.exe, or any other process using
DLLs in that directory, then rebuild.
"@
    }
}

if ($Destination -and $DllList) {
    foreach ($dll in $DllList.Split("|")) {
        Copy-OneDll -Source $dll -DestDir $Destination
    }
}

if ($Destination -and $VcpkgBinDir -and (Test-Path -LiteralPath $VcpkgBinDir)) {
    Get-ChildItem -LiteralPath $VcpkgBinDir -Filter "*.dll" -File | ForEach-Object {
        Copy-OneDll -Source $_.FullName -DestDir $Destination
    }
}

if ($Destination -and $ExtraBinDir -and (Test-Path -LiteralPath $ExtraBinDir)) {
    Get-ChildItem -LiteralPath $ExtraBinDir -Filter "*.dll" -File | ForEach-Object {
        Copy-OneDll -Source $_.FullName -DestDir $Destination
    }
}
