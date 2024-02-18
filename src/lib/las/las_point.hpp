#include <cstdint>
#include <pdal/PointRef.hpp>
#include <utilities/coordinate.hpp>

#include "assert/assert.hpp"

enum class LASClassification : uint8_t {
  CreatedNeverClassified = 0,
  Unclassified = 1,
  Ground = 2,
  LowVegetation = 3,
  MediumVegetation = 4,
  HighVegetation = 5,
  Building = 6,
  LowPoint = 7,
  ModelKeyPoint = 8,
  Water = 9
};

inline std::ostream &operator<<(std::ostream &os, const LASClassification &classification) {
  switch (classification) {
    case LASClassification::CreatedNeverClassified:
      return os << "CreatedNeverClassified";
    case LASClassification::Unclassified:
      return os << "Unclassified";
    case LASClassification::Ground:
      return os << "Ground";
    case LASClassification::LowVegetation:
      return os << "LowVegetation";
    case LASClassification::MediumVegetation:
      return os << "MediumVegetation";
    case LASClassification::HighVegetation:
      return os << "HighVegetation";
    case LASClassification::Building:
      return os << "Building";
    case LASClassification::LowPoint:
      return os << "LowPoint";
    case LASClassification::ModelKeyPoint:
      return os << "ModelKeyPoint";
    case LASClassification::Water:
      return os << "Water";
  }
  __builtin_unreachable();
}

class LASPoint : public Coordinate3D<double> {
  uint16_t m_intensity;
  LASClassification m_classification;

 public:
  LASPoint(double x, double y, double z, uint16_t intensity, LASClassification classification)
      : Coordinate3D<double>(x, y, z), m_intensity(intensity), m_classification(classification) {}

  explicit LASPoint(const pdal::PointRef &point)
      : Coordinate3D<double>(point.getFieldAs<double>(pdal::Dimension::Id::X),
                             point.getFieldAs<double>(pdal::Dimension::Id::Y),
                             point.getFieldAs<double>(pdal::Dimension::Id::Z)),
        m_intensity(point.getFieldAs<uint16_t>(pdal::Dimension::Id::Intensity)),
        m_classification(static_cast<LASClassification>(
            point.getFieldAs<uint8_t>(pdal::Dimension::Id::Classification))) {}

  uint16_t intensity() const { return m_intensity; }
  LASClassification classification() const { return m_classification; }

  void write_to(pdal::PointRef point) const {
    point.setField(pdal::Dimension::Id::X, x());
    point.setField(pdal::Dimension::Id::Y, y());
    point.setField(pdal::Dimension::Id::Z, z());
    point.setField(pdal::Dimension::Id::Intensity, m_intensity);
    point.setField(pdal::Dimension::Id::Classification, static_cast<uint8_t>(m_classification));
  }

  friend std::ostream &operator<<(std::ostream &os, const LASPoint &point) {
    os << "LASPoint((" << point.x() << ", " << point.y() << ", " << point.z()
       << "), I: " << point.intensity() << ", C: " << point.classification() << ")";
    return os;
  }
};
