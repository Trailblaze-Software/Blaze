# Building from Source

This guide covers how to build Blaze from source on Linux and Windows.

## Linux (Ubuntu/Debian)

### Prerequisites

Install the required dependencies:

- CMake (build system)
- GDAL (Geospatial Data Abstraction Library)
- OpenCV (Computer Vision library)
- Qt6 (GUI framework)
- OpenMP (parallel processing)

which on Ubuntu can all be installed with the script

```bash
./scripts/install-ubuntu-deps.sh
```

### Building from Source

#### 1. **Configure the build:**
   ```bash
   cmake -B build
   ```

#### 2. **Compile:**
   ```bash
   cmake --build build --config Release -j$(nproc)
   ```

   Or use the provided build script:
   ```bash
   ./scripts/linux-build.sh
   ```

#### 3. **Install (optional):**
   ```bash
   sudo cmake --install build
   ```

The following executables will be available in the `build` directory:

- `blaze-cli` - Command-line interface
- `Blaze` - Desktop GUI application (WIP)
- `Blaze3D` - 3D visualization application (very WIP)

## Windows

### Prerequisites

**Option 1: Using vcpkg (Recommended)**

Blaze uses vcpkg for dependency management on Windows. The build system will automatically fetch, configure, and build dependencies but this can take several hours.

**Option 2: Manual Installation**

Install dependencies using Chocolatey:

```powershell
Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process
.\scripts\install-deps-windows.ps1
```

This script installs:

- CMake
- Git
- GDAL
- OpenCV

**Note:** You may need to run PowerShell as Administrator.

### Building from Source

#### 1. **Configure the build:**
   ```cmd
   cmake -B build
   ```

   For CLI-only build (without GUI):
   ```cmd
   cmake -B build -DBLAZE_CLI_ONLY=ON
   ```

   To disable vcpkg and use system packages:
   ```cmd
   cmake -B build -DBLAZE_USE_VCPKG=OFF
   ```

#### 2. **Compile:**
   ```cmd
   cmake --build build --config Release --parallel
   ```

#### 3. **Install (optional):**
   ```cmd
   cmake --install build --config Release
   ```

The executables will be available in the `build` directory:

- `blaze-cli.exe` - Command-line interface
- `Blaze.exe` - Desktop GUI application
- `Blaze3D.exe` - 3D visualization application

### Windows Installer

A Windows installer (NSIS) can be created using CPack:

```cmd
cd build
cpack -C Release -G NSIS
```

### Speeding up Builds (vcpkg Caching)

Blaze supports binary caching via GitHub Packages. This allows you to download pre-compiled dependencies instead of building them locally.

1. **Install NuGet CLI**:
   If you don't have it already, install it via Chocolatey (run as Administrator):
   ```powershell
   choco install nuget.commandline
   ```

2. **Generate a Personal Access Token (PAT)**:
   Go to GitHub **Settings > Developer settings > Personal access tokens (classic)** and create a token with `read:packages` (and `write:packages` if you want to contribute binaries) scope.

3. **Add the NuGet source**:
   ```powershell
   nuget sources add -Name "GitHub" `
     -Source "https://nuget.pkg.github.com/Trailblaze-Software/index.json" `
     -UserName "YOUR_GITHUB_USERNAME" `
     -Password "YOUR_PAT"
   ```

4. **Enable the cache**:
   Set the following environment variable before running CMake:
   ```powershell
   $env:VCPKG_BINARY_SOURCES="clear;nuget,GitHub,readwrite"
   ```
