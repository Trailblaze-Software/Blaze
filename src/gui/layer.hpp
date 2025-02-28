#pragma once

#include "las/las_file.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"

class Layer {
 public:
  virtual Extent3D extent() const = 0;
  virtual ~Layer() = default;
};

class PointLayer : public Layer {
 public:
  virtual Extent3D extent() const = 0;
  virtual ~PointLayer() = default;
};

class LASLayer : public PointLayer {
  LASFile m_las_file;

 public:
  LASLayer(const fs::path &file) : m_las_file(file, ProgressTracker()) {}

  virtual Extent3D extent() const override { return m_las_file.bounds(); }
  virtual ~LASLayer() = default;

  const LASFile &las_file() const { return m_las_file; }
};
