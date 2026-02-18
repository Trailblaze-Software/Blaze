<div align="center">

  <style>
    .blaze-header {
      display: flex;
      align-items: center;
      justify-content: center;
      gap: 10px;
    }
    .blaze-header img {
      vertical-align: middle;
    }
    .blaze-title {
      font-family: 'Courier New', 'Consolas', 'Monaco', monospace;
      font-size: 2.8em;
      font-weight: 700;
      letter-spacing: 0.05em;
      color: #f36f21;
      display: inline-block;
      text-shadow: 1px 1px 2px rgba(128, 128, 128, 0.15);
    }
    @media (max-width: 768px) {
      .blaze-title {
        font-size: 2em;
        padding: 0.15em 0.3em;
      }
      .blaze-header {
        gap: 5px;
      }
    }
  </style>

  <h1 class="blaze-header">
    <img src="assets/images/blaze_icon.png" alt="Blaze Icon" width="60">
    <span class="blaze-title">BLAZE</span>
  </h1>

  <p><strong>A LIDAR mapping tool for processing point cloud data</strong></p>

  <p>
    <a href="https://cmake.org/"><img src="https://img.shields.io/badge/CMake-3.20+-064F8C?style=flat-square&logo=cmake"></a>
    <a href="https://isocpp.org/"><img src="https://img.shields.io/badge/C++-20-00599C?style=flat-square&logo=c%2B%2B"></a>
    <a href="LICENSE"><img src="https://img.shields.io/badge/license-GPLv3-blue?style=flat-square"></a>
    <a href="https://Trailblaze-Software.github.io/Blaze/"><img src="https://img.shields.io/badge/docs-latest-brightgreen?style=flat-square"></a>
    <a href="https://github.com/Trailblaze-Software/Blaze"><img src="https://img.shields.io/badge/platform-Linux%20%7C%20Windows-lightgrey?style=flat-square"></a>
  </p>

</div>

---

NOTE: This repository is currently a work in progress and subject to significant change.

## Overview

**Blaze** is a LIDAR mapping tool designed for processing, analyzing, and visualizing point cloud data from LAS/LAZ files. Built with modern C++20, Blaze provides both command-line (`blaze-cli`) and graphical interfaces (`Blaze` and eventually `Blaze3D`).

Blaze is free and open-source, however if you generate maps using Blaze, we would appreciate a simple acknowledgement and link to [https://trailblaze-software.github.io/Blaze](https://trailblaze-software.github.io/Blaze).

If you run into any problems, please [submit an issue](https://github.com/Trailblaze-Software/Blaze/issues) and we will get back to you. Alternately, feel free to fix it yourself and submit a pull request :)

## Documentation

Full documentation, including installation guides, usage examples, and API reference, is available at:

**[https://Trailblaze-Software.github.io/Blaze/](https://Trailblaze-Software.github.io/Blaze/)**

*   **[Installation Guide](https://Trailblaze-Software.github.io/Blaze/installation/)**
*   **[Quick Start Guide](https://Trailblaze-Software.github.io/Blaze/usage/quick-guide/)**
*   **[Developers Reference (C++ API)](https://Trailblaze-Software.github.io/Blaze/reference/)**

### Local Development

To preview the documentation locally with live-reloading:

```bash
./scripts/serve-docs.sh
```

This will start a local server at `http://127.0.0.1:8000`.

## Installation

Download pre-built binaries from the [GitHub Releases page](https://github.com/Trailblaze-Software/Blaze/releases).

## Building from source

### Linux (Ubuntu/Debian)

#### Prerequisites

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

#### Building from Source

1. **Configure the build:**
   ```bash
   cmake -B build
   ```

2. **Compile:**
   ```bash
   cmake --build build --config Release -j$(nproc)
   ```

   Or use the provided build script:
   ```bash
   ./scripts/linux-build.sh
   ```

3. **Install (optional):**
   ```bash
   sudo cmake --install build
   ```

The following executables will be available in the `build` directory:
- `blaze-cli` - Command-line interface
- `Blaze` - Desktop GUI application (WIP)
- `Blaze3D` - 3D visualization application (very WIP)

### Windows

#### Prerequisites

**Option 1: Using vcpkg (Recommended)**

Blaze uses vcpkg for dependency management on Windows. The build system will automatically fetch, configure, and build dependencies but this can take several hours.

**Option 2: Manual Installation**

Install dependencies using Chocolatey:

```powershell
Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process
   .\scripts\install-deps-windows.ps1
.\scripts\install-deps-windows.ps1
```

This script installs:
- CMake
- Git
- GDAL
- OpenCV

**Note:** You may need to run PowerShell as Administrator.

#### Building from Source

1. **Configure the build:**
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

2. **Compile:**
   ```cmd
   cmake --build build --config Release --parallel
   ```

3. **Install (optional):**
   ```cmd
   cmake --install build --config Release
   ```

The executables will be available in the `build` directory:
- `blaze-cli.exe` - Command-line interface
- `Blaze.exe` - Desktop GUI application
- `Blaze3D.exe` - 3D visualization application

#### Windows Installer

A Windows installer (NSIS) can be created using CPack:

```cmd
cd build
cpack -C Release -G NSIS
```

## Usage

### Command-Line Interface

Process a LAS/LAZ file:

```bash
./blaze-cli configs/config.json filename.las
```

Or with a single file:

```bash
./blaze-cli filename.laz
```

### GUI Applications

Launch the desktop GUI:

```bash
./Blaze
```

## Building

### Build Options

- `BLAZE_CLI_ONLY`: Build only the command-line tool (default: `OFF`)
- `BLAZE_USE_PDAL`: Use PDAL for LAS I/O (default: `OFF`)
- `BLAZE_USE_VCPKG`: Use vcpkg for dependency management on Windows (default: `ON`)

## Requirements

- **CMake**: 3.20 or higher
- **C++ Compiler**: Supporting C++20 standard
- **GDAL**: Geospatial Data Abstraction Library
- **OpenCV**: 4.x or higher
- **Qt6**: Required for GUI applications (Widgets, Concurrent, Core, Svg, OpenGL)
- **OpenMP**: For parallel processing

## Contributing

Contributions are welcome! Please feel free to submit issues or pull requests. All contributors retain copywrite to their code but agree to it being licensed under the GPLv3 license.

## License

Blaze is licensed under the GPLv3 License. See [LICENSE](LICENSE) for details. You can pretty much do whatever you like with it, however any distributed modifications must remain open-source.

This project uses third-party libraries that are subject to their own licenses. See [THIRD_PARTY_LICENSES.md](THIRD_PARTY_LICENSES.md) for complete license information for all dependencies.

---
