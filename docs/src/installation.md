# Installation

This guide covers how to set up Blaze on Linux and Windows.

## Linux (Ubuntu/Debian)

### Prerequisites

Blaze requires several libraries that can be installed via the provided script:
- CMake (3.20+)
- GDAL
- OpenCV
- Qt6
- OpenMP

Run the following command from the project root:

```bash
./scripts/install-ubuntu-deps.sh
```

### Building from Source

1. **Configure the build:**
   ```bash
   cmake -B build
   ```

2. **Compile:**
   ```bash
   cmake --build build --config Release -j$(nproc)
   ```

   Alternatively, use the provided build script:
   ```bash
   ./scripts/linux-build.sh
   ```

---

## Windows

### Prerequisites

**Option 1: Using vcpkg (Recommended)**

Blaze uses `vcpkg` for dependency management on Windows. The build system will automatically fetch and build dependencies, though this may take some time during the first build.

**Option 2: Manual Installation**

You can install dependencies using Chocolatey:

```powershell
Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process
.\scripts\install-deps-windows.ps1
```

### Building from Source

1. **Configure the build:**
   ```cmd
   cmake -B build
   ```

2. **Compile:**
   ```cmd
   cmake --build build --config Release --parallel
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

2. **Add the NuGet source**:
   ```powershell
   nuget sources add -Name "GitHub" `
     -Source "https://nuget.pkg.github.com/Trailblaze-Software/index.json" `
     -UserName "YOUR_GITHUB_USERNAME" `
     -Password "YOUR_PAT"
   ```

3. **Enable the cache**:
   Set the following environment variable before running CMake:
   ```powershell
   $env:VCPKG_BINARY_SOURCES="clear;nuget,GitHub,readwrite"
   ```

### Windows Installer

To create a standalone installer (NSIS), run:

```cmd
cd build
cpack -C Release -G NSIS
```
