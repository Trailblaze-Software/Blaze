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
    "downsample_factor": 3
  },
  "ground": {
    "outlier_removal_height_diff": 0.3,
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

Controls the resolution of the digital elevation model (DEM).

- `bin_resolution`: Size of each grid cell in meters. We generally want about 5-10 points per cell for good contour generation, so this should be set based on your point density. For recent ACT LIDAR, this can be as low as 0.5m, whilst for the sparser NSW data 3m is a good choice.
- `downsample_factor`: Factor to downsample the grid for smoother contours elevation model.

### Ground

Parameters for ground point classification and filtering.

- `outlier_removal_height_diff`: Minimum height difference for removing spikes.
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
