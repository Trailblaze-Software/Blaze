# Install dependencies for Blaze on Windows using winget (preferred) and Chocolatey (fallback)
# Run this script from PowerShell: .\install-deps-windows.ps1

Write-Host "=== Installing Blaze Dependencies on Windows ===" -ForegroundColor Cyan

# Check if running as administrator
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if (-not $isAdmin) {
    Write-Host "Warning: Not running as administrator. Some installations may require elevation." -ForegroundColor Yellow
}

$ChocoMaxRetries = 2

function Install-Package {
    param(
        [string]$Name,
        [string]$WingetId = "",
        [string]$ChocoPackage = $Name,
        [string]$ChocoInstallArgs = ""
    )
    # Try winget first when a package id is given (Microsoft's feed is more reliable)
    if ($WingetId -and (Get-Command winget -ErrorAction SilentlyContinue)) {
        Write-Host "Trying winget: $WingetId ..." -ForegroundColor Cyan
        $wingetArgs = @("install", "--id", $WingetId, "--accept-package-agreements", "--accept-source-agreements")
        & winget @wingetArgs 2>$null
        if ($LASTEXITCODE -eq 0) {
            Write-Host "Installed $Name via winget." -ForegroundColor Green
            return $true
        }
        Write-Host "winget install failed or package not found, trying Chocolatey..." -ForegroundColor Yellow
    }
    # Ensure Chocolatey is available for fallback
    if (-not (Get-Command choco -ErrorAction SilentlyContinue)) {
        Write-Host "Chocolatey not available. Install it first or use winget." -ForegroundColor Red
        return $false
    }
    $attempt = 0
    while ($attempt -le $ChocoMaxRetries) {
        $attempt++
        if ($attempt -gt 1) {
            Write-Host "Chocolatey retry $attempt of $($ChocoMaxRetries + 1) for $ChocoPackage..." -ForegroundColor Yellow
            Start-Sleep -Seconds 5
        }
        $chocoArgs = @("install", "-y", $ChocoPackage)
        if ($ChocoInstallArgs) { $chocoArgs += "--installargs"; $chocoArgs += $ChocoInstallArgs }
        & choco @chocoArgs
        if ($LASTEXITCODE -eq 0) {
            Write-Host "Installed $Name via Chocolatey." -ForegroundColor Green
            return $true
        }
    }
    Write-Host "Failed to install $Name after $($ChocoMaxRetries + 1) attempt(s)." -ForegroundColor Red
    return $false
}

# Install Chocolatey only if we might need it (no winget or for packages not on winget)
Write-Host "`n=== Checking Package Managers ===" -ForegroundColor Cyan
$hasWinget = Get-Command winget -ErrorAction SilentlyContinue
$hasChoco = Get-Command choco -ErrorAction SilentlyContinue
if (-not $hasChoco) {
    Write-Host "Chocolatey not found. Installing Chocolatey (used for OpenCV and as fallback)..." -ForegroundColor Yellow
    Set-ExecutionPolicy Bypass -Scope Process -Force
    $protocol = [System.Net.ServicePointManager]::SecurityProtocol
    [System.Net.ServicePointManager]::SecurityProtocol = $protocol -bor 3072
    $installScript = 'https://community.chocolatey.org/install.ps1'
    try {
        iex ((New-Object System.Net.WebClient).DownloadString($installScript))
        Write-Host "Chocolatey installed successfully." -ForegroundColor Green
    } catch {
        Write-Host "Failed to install Chocolatey: $_" -ForegroundColor Red
        exit 1
    }
} else {
    Write-Host "Chocolatey is already installed." -ForegroundColor Green
    choco --version
}
if ($hasWinget) { Write-Host "winget is available (will be used for CMake and Git)." -ForegroundColor Green }

# Refresh environment variables
$env:Path = [System.Environment]::GetEnvironmentVariable("Path", "Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path", "User")

# Install build tools (winget first, then Chocolatey with retries)
Write-Host "`n=== Installing Build Tools ===" -ForegroundColor Cyan
if (-not (Install-Package -Name "CMake" -WingetId "Kitware.CMake" -ChocoPackage "cmake" -ChocoInstallArgs "ADD_CMAKE_TO_PATH=System")) {
    exit 1
}
if (-not (Install-Package -Name "Git" -WingetId "Git.Git" -ChocoPackage "git")) {
    exit 1
}
# Ensure CMake is on PATH (winget doesn't add it system-wide by default)
$cmakePaths = @("C:\Program Files\CMake\bin", "${env:ProgramFiles(x86)}\CMake\bin")
foreach ($p in $cmakePaths) {
    if ((Test-Path $p) -and ($env:Path -notlike "*$p*")) {
        $env:Path = "$p;$env:Path"
        Write-Host "Added CMake to PATH: $p" -ForegroundColor Green
        break
    }
}

# Refresh environment after installing build tools
$env:Path = [System.Environment]::GetEnvironmentVariable("Path", "Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path", "User")

# Install GDAL
Write-Host "`n=== Installing GDAL ===" -ForegroundColor Cyan
# Note: Chocolatey doesn't have a 'gdal' package, so we use conda
Write-Host "Chocolatey doesn't have GDAL package. Installing via conda..." -ForegroundColor Yellow

# Check if conda is available
$condaAvailable = $false
if (Get-Command conda -ErrorAction SilentlyContinue) {
    $condaAvailable = $true
    Write-Host "Conda found. Installing GDAL via conda-forge..." -ForegroundColor Green

    # Accept conda Terms of Service if needed
    Write-Host "Accepting conda Terms of Service..." -ForegroundColor Yellow
    conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/main 2>$null
    conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/r 2>$null
    conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/msys2 2>$null

    conda install -y -c conda-forge gdal
    if ($LASTEXITCODE -eq 0) {
        $condaBase = conda info --base
        Write-Host "GDAL installed via conda at: $condaBase\Library" -ForegroundColor Green
    } else {
        Write-Host "Failed to install GDAL via conda" -ForegroundColor Red
        exit 1
    }
} else {
    # Try to install Miniconda first
    Write-Host "Conda not found. Installing Miniconda..." -ForegroundColor Yellow
    $condaUrl = "https://repo.anaconda.com/miniconda/Miniconda3-latest-Windows-x86_64.exe"
    $condaInstaller = "$env:TEMP\miniconda.exe"
    try {
        Invoke-WebRequest -Uri $condaUrl -OutFile $condaInstaller -UseBasicParsing
        Start-Process -FilePath $condaInstaller `
            -ArgumentList "/InstallationType=JustMe", "/RegisterPython=1", "/S", `
            "/D=$env:ProgramFiles\Miniconda3" -Wait -NoNewWindow
        $env:Path = "$env:ProgramFiles\Miniconda3;$env:ProgramFiles\Miniconda3\Scripts;$env:Path;$env:ProgramFiles\Miniconda3\Library\bin"
        [Environment]::SetEnvironmentVariable("Path", $env:Path, [EnvironmentVariableTarget]::Machine)

        # Accept conda Terms of Service
        Write-Host "Accepting conda Terms of Service..." -ForegroundColor Yellow
        conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/main 2>$null
        conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/r 2>$null
        conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/msys2 2>$null

        conda install -y -c conda-forge gdal
        if ($LASTEXITCODE -eq 0) {
            $condaBase = conda info --base
            Write-Host "GDAL installed via conda at: $condaBase\Library" -ForegroundColor Green
        } else {
            Write-Host "Failed to install GDAL via conda" -ForegroundColor Red
            exit 1
        }
    } catch {
        Write-Host "Failed to install Miniconda: $_" -ForegroundColor Red
        Write-Host "Please install GDAL manually or use the vcpkg-based build." -ForegroundColor Yellow
        exit 1
    }
}

# Refresh environment after installing GDAL
$env:Path = [System.Environment]::GetEnvironmentVariable("Path", "Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path", "User")

# Install OpenCV (Chocolatey only; not on winget)
Write-Host "`n=== Installing OpenCV ===" -ForegroundColor Cyan
if (-not (Install-Package -Name "OpenCV" -ChocoPackage "opencv")) {
    exit 1
}

# Refresh environment after installing OpenCV
$env:Path = [System.Environment]::GetEnvironmentVariable("Path", "Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path", "User")

# Find installed packages and setup CMake paths
Write-Host "`n=== Finding Installed Packages ===" -ForegroundColor Cyan

# Find GDAL installation
$gdalPath = $null

# Check conda installation first
$condaBase = conda info --base 2>$null
if ($condaBase -and (Test-Path "$condaBase\Library")) {
    $gdalPath = "$condaBase\Library"
    Write-Host "Found GDAL in conda: $gdalPath" -ForegroundColor Green
}

# Check other common locations
if (-not $gdalPath) {
    $gdalPaths = @(
        "C:\Program Files\GDAL",
        "C:\OSGeo4W64",
        "$env:ProgramFiles\GDAL",
        "$env:ProgramFiles\Miniconda3\Library"
    )
    foreach ($path in $gdalPaths) {
        if (Test-Path $path) {
            $gdalPath = $path
            break
        }
    }
}

# Find OpenCV installation
$opencvPaths = @(
    "C:\tools\opencv",
    "C:\opencv",
    "$env:ProgramFiles\opencv"
)
$opencvPath = $null
foreach ($path in $opencvPaths) {
    if (Test-Path $path) {
        $opencvPath = $path
        break
    }
}

Write-Host "Found GDAL at: $gdalPath" -ForegroundColor $(if ($gdalPath) { "Green" } else { "Yellow" })
Write-Host "Found OpenCV at: $opencvPath" -ForegroundColor $(if ($opencvPath) { "Green" } else { "Yellow" })

# Build CMAKE_PREFIX_PATH
$cmakePrefixPaths = @()
if ($gdalPath) {
    $cmakePrefixPaths += $gdalPath
    # Try to find GDAL cmake config
    $gdalCmakePath = Join-Path $gdalPath "cmake\gdal"
    if (Test-Path $gdalCmakePath) {
        $env:GDAL_DIR = $gdalCmakePath
        Write-Host "Set GDAL_DIR=$gdalCmakePath" -ForegroundColor Green
    }
}
if ($opencvPath) {
    $cmakePrefixPaths += $opencvPath
    # OpenCV_DIR should point to the build directory or root
    $opencvBuildPath = Join-Path $opencvPath "build"
    if (Test-Path $opencvBuildPath) {
        $env:OpenCV_DIR = $opencvBuildPath
        Write-Host "Set OpenCV_DIR=$opencvBuildPath" -ForegroundColor Green
    } else {
        $env:OpenCV_DIR = $opencvPath
        Write-Host "Set OpenCV_DIR=$opencvPath" -ForegroundColor Green
    }
}

if ($cmakePrefixPaths.Count -gt 0) {
    $cmakePrefixPath = $cmakePrefixPaths -join ";"
    $env:CMAKE_PREFIX_PATH = $cmakePrefixPath
    Write-Host "Set CMAKE_PREFIX_PATH=$cmakePrefixPath" -ForegroundColor Green
}

Write-Host "`n=== Installation Complete ===" -ForegroundColor Green
Write-Host "Environment variables have been set for this session." -ForegroundColor Yellow
Write-Host "To make them permanent, restart your terminal or add them to your system environment variables." -ForegroundColor Yellow
Write-Host "`nYou can now run CMake configuration:" -ForegroundColor Cyan
Write-Host "  cmake -B build -DBLAZE_USE_VCPKG=OFF -DBLAZE_CLI_ONLY=ON -DCMAKE_BUILD_TYPE=Release" -ForegroundColor White
