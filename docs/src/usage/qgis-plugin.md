# QGIS Plugin

The **Blaze Map Loader** plugin simplifies importing processed results into QGIS.

## Features

- **Automated Loading**: Automatically loads output maps created by Blaze.
- **Magnetic North**: Overlays magnetic north lines.
- **Topo Data**: Integrates NSW topographic data where available.
- **Styling**: Applies predefined styles to layers for consistent visualization.

## Installation

1. Copy the `qgis_plugin/blaze_loader` folder to your QGIS plugins directory:
   - **Linux**: `~/.local/share/QGIS/QGIS3/profiles/default/python/plugins/`
   - **Windows**: `%APPDATA%\QGIS\QGIS3\profiles\default\python\plugins`
2. Open QGIS.
3. Go to **Plugins > Manage and Install Plugins**.
4. Enable **Blaze Map Loader**.

## Usage

Once enabled, look for the Blaze icon in your QGIS toolbar or under the **Plugins** menu. Use the dialog to select your Blaze output directory and load the data.
