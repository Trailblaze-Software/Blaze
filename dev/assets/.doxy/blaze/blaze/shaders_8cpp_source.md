

# File shaders.cpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**shaders.cpp**](shaders_8cpp.md)

[Go to the documentation of this file](shaders_8cpp.md)


```C++
#include "gui/shaders.hpp"

#include <QFile>
#include <QTextStream>

#include "gui/point_cloud_visualization.hpp"

QString load_shader_source(const QString& resource_path) {
  QFile file(resource_path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    std::cerr << "Failed to open shader resource: " << resource_path.toStdString() << std::endl;
    return QString();
  }
  QTextStream in(&file);
  return in.readAll();
}

QString get_point_vertex_shader() {
  QString source = load_shader_source(":/shaders/point_vertex.glsl");
  if (source.isEmpty()) {
    return QString();
  }

  // Inject classification color function
  QString classification_glsl = QString::fromStdString(classification_color_glsl());
  source.replace("// CLASSIFICATION_COLOR_FUNCTION", classification_glsl);

  return source;
}

QString get_point_fragment_shader() { return load_shader_source(":/shaders/point_fragment.glsl"); }

QString get_mesh_vertex_shader() { return load_shader_source(":/shaders/mesh_vertex.glsl"); }

QString get_mesh_fragment_shader() { return load_shader_source(":/shaders/mesh_fragment.glsl"); }

QString get_textured_mesh_vertex_shader() {
  return load_shader_source(":/shaders/textured_mesh_vertex.glsl");
}

QString get_textured_mesh_fragment_shader() {
  return load_shader_source(":/shaders/textured_mesh_fragment.glsl");
}
```


