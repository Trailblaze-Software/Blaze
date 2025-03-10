#pragma once

#include "las/las_file.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"

class Layer {
 protected:
  std::string m_name;

 public:
  virtual Extent3D extent() const = 0;
  virtual std::string projection() const = 0;
  virtual std::string name() { return m_name; }
  virtual ~Layer() = default;
};

class PointLayer : public Layer {
 public:
  virtual ~PointLayer() = default;
};

class LASLayer : public PointLayer {
  LASFile m_las_file;

 public:
  LASLayer(const fs::path &file) : m_las_file(file, ProgressTracker()) {
    m_name = file.filename().string();
  }

  virtual Extent3D extent() const override { return m_las_file.bounds(); }
  virtual std::string projection() const override { return m_las_file.projection().to_string(); }
  virtual ~LASLayer() = default;

  const LASFile &las_file() const { return m_las_file; }
};
