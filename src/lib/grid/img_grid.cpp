#include "img_grid.hpp"

#include <pdal/util/Bounds.hpp>

#include "tif/tif.hpp"

void GeoImgGrid::save_to(const fs::path& path, const pdal::BOX2D& extent) {
  if (path.extension() == ".tif" || path.extension() == ".tiff") {
    GeoGrid<RGBColor> grid = GeoGrid<RGBColor>::FromGeoImg(*this);
    write_to_tif(grid.slice(extent), path);
  } else {
    ImgGrid::save_to(path);
  }
}
