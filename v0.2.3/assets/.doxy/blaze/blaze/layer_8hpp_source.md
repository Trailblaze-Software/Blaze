

# File layer.hpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**layer.hpp**](layer_8hpp.md)

[Go to the documentation of this file](layer_8hpp.md)


```C++
#pragma once

#include "las/las_file.hpp"
#include "utilities/coordinate.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/progress_tracker.hpp"

class Layer : public QObject {
  Q_OBJECT

 protected:
  std::string m_name;

 signals:
  void data_updated() const;

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
  AsyncLASData m_las_file;

 public:
  explicit LASLayer(const fs::path& file, AsyncProgressTracker progress_tracker)
      : m_las_file(file, progress_tracker, {[this] { emit this->data_updated(); }}) {
    m_name = file.filename().string();
  }

  virtual Extent3D extent() const override { return m_las_file.bounds(); }
  virtual std::string projection() const override { return m_las_file.projection().to_string(); }

  const AsyncLASData& las_file() const { return m_las_file; }
  AsyncLASData& las_file() { return m_las_file; }
};
```


