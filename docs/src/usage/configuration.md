# Configuration Reference

Blaze uses a JSON configuration file to control the processing pipeline. This file allows you to customize grid generation, contour intervals, feature detection parameters, and output rendering styles.

## Example Configuration

```json
{
  "las_files": [],
  "steps": ["tiles", "combine"],
  "output_directory": "out",
  "grid": {
    "bin_resolution": 0.5,
    "downsample_factor": 3,
    "vegetation_grid_resolution": 3.0,
    "contour_dem_resolution": 9.0
  },
  "ground": {
    "min_ground_intensity": 0,
    "max_ground_intensity": 65535
  },
  "contours": {
    "normal": {
      "interval": 5.0,
      "min_points": 5,
      "color": "brown",
      "width": 0.14
    },
    "index": {
      "interval": 25.0,
      "min_points": 5,
      "color": "brown",
      "width": 0.25
    }
  },
  "water": {
    "stream": {
      "catchment": 0.03,
      "color": "blue",
      "width": 0.18
    }
  },
  "vege": {
    "background_color": "50% yellow",
    "height_configs": [
      {
        "name": "canopy",
        "min_height": 2.5,
        "max_height": 100,
        "colors": [
          {
            "blocking_threshold": 0.1,
            "color": "white"
          }
        ]
      }
    ]
  },
  "buildings": {
    "color": "black"
  },
  "render": {
    "scale": 10000,
    "dpi": 600
  },
  "colors": {
    "primitive": {
      "brown": { "cmyk": [0, 56, 100, 18] },
      "blue": { "cmyk": [100, 0, 0, 0] }
    },
    "composite": {
      "50% yellow": { "yellow": 0.5 }
    }
  }
}
```

## Sections

### Grid

Controls the resolutions used by various stages of the processing pipeline.

- `bin_resolution`: Underlying grid cell size in meters. Raw LiDAR points are binned at this resolution; the ground / building / water / intensity rasters are produced at this resolution. For dense LIDAR (e.g. ACT) values around 0.5m work well; for sparser data this should be increased (e.g. ~2.5m for NSW). Default: `0.5`.
- `downsample_factor`: Integer factor used to downsample the bin grid into the smooth ground DEM that is the basis for slope, hill-shade and `smooth_ground.tif`. Effective smooth-DEM resolution = `bin_resolution * downsample_factor`. Default: `3`.
- `vegetation_grid_resolution`: Resolution (in meters) of the vegetation / canopy maps. Vegetation point counts are aggregated from the bin grid to this resolution. Should be `>= bin_resolution`. Default: `3.0`.
- `contour_dem_resolution`: Resolution (in meters) of the DEM used for contour generation, stream extraction and depression filling. Computed by further downsampling the smooth ground DEM. Should be `>= bin_resolution * downsample_factor`. Larger values produce smoother contours but lose fine terrain detail. Default: `9.0`.

Older configs that only set `bin_resolution` and `downsample_factor` are still accepted; in that case `vegetation_grid_resolution` defaults to `bin_resolution` and `contour_dem_resolution` defaults to `bin_resolution * downsample_factor`, preserving the previous behaviour.

### Ground

Parameters for ground point classification and filtering.

- `min_ground_intensity`: Minimum intensity value for ground points.
- `max_ground_intensity`: Maximum intensity value for ground points.

### Contours

Defines contour lines. You can define multiple types (e.g., normal, index).

- `interval`: Vertical distance between contours in meters.
- `min_points`: Minimum points required to form a contour segment.
- `color`: Name of the color (defined in `colors` section).
- `width`: Line width in mm.

### Water

Defines watercourse detection based on catchment area.

- `catchment`: Threshold for catchment area to define a stream.
- `color`: Color of the water line.
- `width`: Line width in mm.

### Vegetation

Configures vegetation density and height mapping.

- `background_color`: Base color for the vegetation layer.
- `height_configs`: List of height bands (e.g., low vegetation, canopy).
  - `min_height`: Minimum height of vegetation in this band.
  - `max_height`: Maximum height.
  - `colors`: List of colors based on blocking threshold (density).

### Buildings

- `color`: Color for building footprints.

### Render

Output settings.

- `scale`: Map scale (e.g., 10000 for 1:10000).
- `dpi`: Dots per inch for the output image.

### Colors

Defines the color palette.

- `primitive`: Basic colors defined by RGB or CMYK.
  - RGB example: `"red": { "rgb": [255, 0, 0, 255] }`
  - CMYK example: `"cyan": { "cmyk": [100, 0, 0, 0] }` (Values 0-100)
- `composite`: Mixed colors defined by percentage of other colors.
  - Example: `"light_green": { "green": 0.3 }` (30% green)
