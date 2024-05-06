#include "img_grid.hpp"

void GeoImgGrid::save_to(const fs::path &path) {
  if (path.extension() == ".tif" || path.extension() == ".tiff") {
    GeoGrid<RGBColor> grid = GeoGrid<RGBColor>::FromGeoImg(*this);
    write_to_tif(grid, path);
  } else {
    ImgGrid::save_to(path);
  }
}
