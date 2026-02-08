# Quick Guide

Get started with processing LIDAR data using Blaze.

## Command-Line Interface (CLI)

The `blaze-cli` is the core processing engine.

### Basic Usage

Process a single file using default settings:

```bash
./blaze-cli path/to/data.laz
```

### Advanced Configuration

You can provide a JSON configuration file to customize the processing pipeline. See the [Configuration Reference](configuration.md) for details.

```bash
./blaze-cli configs/config.json path/to/data.laz
```

## GUI Application

For a more interactive experience, use the `Blaze` desktop application.

1. Launch `Blaze` (or `Blaze.exe` on Windows).
2. Load your LAS/LAZ files via the menu.
3. Configure processing parameters in the sidebar.
4. View the results in the 2D map view.

## 3D Visualization

The `Blaze3D` application is currently under development and provides a point cloud viewer for inspecting your data in 3D space.
