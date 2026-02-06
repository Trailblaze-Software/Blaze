#pragma once

#include "contour/contour.hpp"
#include "isom/colors.hpp"
#include "utilities/coordinate.hpp"

namespace cv {
class Mat;
}

class ImgGrid : public GridData {
 protected:
  std::unique_ptr<cv::Mat> m_img;

 public:
  ImgGrid(size_t height, size_t width, std::optional<int> type = {});
  ~ImgGrid();

  void save_to(const fs::path& path);

  RGBColor get_rgb_color(size_t row, size_t col) const;
};

class GeoImgGrid : public ImgGrid, public GeoGridData {
 public:
  GeoImgGrid(size_t width, size_t height, GeoTransform&& transform, GeoProjection&& projection)
      : ImgGrid(width, height), GeoGridData(std::move(transform), std::move(projection)) {}

  template <typename ColorT, typename = std::enable_if_t<std::is_base_of_v<Color, ColorT>>>
  explicit GeoImgGrid(const GeoGrid<ColorT>& grid);

  void draw(const GeoImgGrid& other, std::optional<int> interpolation = {});

  void draw_point(const Coordinate2D<double>& point, const ColorVariant& color, double size);

  void draw(const Contour& contour, const ColorVariant& color, double width);

  void draw(const std::vector<Coordinate2D<double>>& in_points, const ColorVariant& color,
            double width);

  void save_to(const fs::path& path, const Extent2D& extent);
};
