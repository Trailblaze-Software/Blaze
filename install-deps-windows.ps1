# Install dependencies for Blaze on Windows using Chocolatey
# Run this script from PowerShell: .\install-deps-windows.ps1

Write-Host "=== Installing Blaze Dependencies on Windows ===" -ForegroundColor Cyan

# Check if running as administrator
$isAdmin = ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if (-not $isAdmin) {
    Write-Host "Warning: Not running as administrator. Some installations may require elevation." -ForegroundColor Yellow
}

# Install Chocolatey if not already installed
Write-Host "`n=== Checking Chocolatey Installation ===" -ForegroundColor Cyan
if (-not (Get-Command choco -ErrorAction SilentlyContinue)) {
    Write-Host "Chocolatey not found. Installing Chocolatey..." -ForegroundColor Yellow
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

# Refresh environment variables
$env:Path = [System.Environment]::GetEnvironmentVariable("Path", "Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path", "User")

# Install build tools
Write-Host "`n=== Installing Build Tools ===" -ForegroundColor Cyan
choco install -y cmake --installargs 'ADD_CMAKE_TO_PATH=System'
if ($LASTEXITCODE -ne 0) {
    Write-Host "Failed to install CMake" -ForegroundColor Red
    exit 1
}

choco install -y git
if ($LASTEXITCODE -ne 0) {
    Write-Host "Failed to install Git" -ForegroundColor Red
    exit 1
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

# Install OpenCV
Write-Host "`n=== Installing OpenCV ===" -ForegroundColor Cyan
choco install -y opencv
if ($LASTEXITCODE -ne 0) {
    Write-Host "Failed to install OpenCV" -ForegroundColor Red
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
