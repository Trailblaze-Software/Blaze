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

### Windows Installer

To create a standalone installer (NSIS), run:

```cmd
cd build
cpack -C Release -G NSIS
```
