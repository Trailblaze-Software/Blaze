# Quick Guide

Get started with processing LIDAR data using Blaze.

## Command-Line Interface (CLI)

The `blaze-cli` is the core processing engine. You can provide a JSON configuration file to customize the processing pipeline. See the [Configuration Reference](configuration.md) for details.

```bash
./blaze-cli configs/config.json
```

## GUI Application

For a more interactive and user-friendly experience, use the `Blaze` desktop application. This can also be used to load and save configuration files that can be used with the command-line interface.

Launch `Blaze` (or `Blaze.exe` on Windows). You should get a screen that looks something like this.

![Blaze open screen](screenshots/open_screen.png)

You can optionally load a configuration you have saved earlier with `File > Open Config` or `Ctrl + O`.

You can now load your LAS/LAZ files using the `-`, `+`, and `+ Folder` buttons. The `+ Folder` can be used to add an entire folder of LIDAR tiles that will be processed together and combined.

You can now configure the parameters such as scale and output resolution. The most important configuration option to play around with is the "Bin Resolution". For dense LIDAR such as we have in the ACT, 0.5m works well, however for sparser LIDAR such as in NSW, it is generally better to increase it, with 3m generally working well. We highly recommend testing and refining on a single LIDAR tile until you are happy with the output before processing a large area.

![Blaze open screen](screenshots/open_screen.png)

Finally, run the calculation with the `Run Blaze` button. This can take a long time for large amounts of LIDAR. I have found up to 5min/GB depending on processing capability. For large areas, you will need a lot of RAM to hold the final combined maps, or reduce the resolution.

## 3D Visualization

The `Blaze3D` application is currently under development and provides a point cloud viewer for inspecting your data.
