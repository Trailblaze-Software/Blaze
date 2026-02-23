

# File gpkg.hpp

[**File List**](files.md) **>** [**io**](dir_65bc51589f8002bfcb72faf47ab41180.md) **>** [**gpkg.hpp**](gpkg_8hpp.md)

[Go to the documentation of this file](gpkg_8hpp.md)


```C++


#include <ogrsf_frmts.h>

#include "assert/assert.hpp"
#include "assert/gdal_assert.hpp"
#include "contour/contour.hpp"
#include "gdal_priv.h"
#include "io/gdal_init.hpp"
#include "polyline/polyline.hpp"
#include "utilities/filesystem.hpp"
#include "utilities/timer.hpp"

class GDALDataset_w {
  GDALDataset* dataset;

 public:
  GDALDataset_w(const std::string& filename, const std::string& projection) {
    ensure_gdal_initialized();
    GDALDriver* driver = GetGDALDriverManager()->GetDriverByName("GPKG");
    Assert(driver, "GeoPackage driver not available.");

    dataset = driver->Create(filename.c_str(), 0, 0, 0, GDT_Unknown, nullptr);
    Assert(dataset, "Failed to create GeoPackage file " + filename);

    // OGRSpatialReference srs;
    // GDALAssert(srs.importFromWkt(projection.c_str()));
    dataset->SetProjection(projection.c_str());
  }

  GDALDataset* operator->() { return dataset; }

  ~GDALDataset_w() { GDALClose(dataset); }
};

class GPKGWriter {
  GDALDataset_w dataset;
  const std::string projection;

  std::vector<std::string> layer_names;
  std::string default_layer_name;

 public:
  GPKGWriter(const std::string& filename, const std::string& projection,
             const std::string& default_layer = "default")
      : dataset(filename, projection), projection(projection), default_layer_name(default_layer) {
    // Create default layer immediately if projection is valid, so the GPKG file is always valid
    if (!projection.empty()) {
      add_layer(default_layer_name);
    }
  }

  void add_layer(const std::string& layer_name) {
    Assert(!projection.empty(), "Projection must not be empty when creating GPKG layer");
    OGRSpatialReference srs;
    // Import projection from WKT string (supports both geographic and projected CRS)
    GDALAssert(srs.importFromWkt(projection.c_str()));
    OGRLayer* layer = dataset->CreateLayer(layer_name.c_str(), &srs, wkbLineString, nullptr);
    Assert(layer, "Failed to create layer " + layer_name);
    layer_names.push_back(layer_name);
  }

  void write_polyline(
      const Polyline& polyline,
      const std::map<std::string, std::variant<int, double, std::string>>& data_fields = {}) {
    std::string layer_name = polyline.layer;
    if (std::find(layer_names.begin(), layer_names.end(), layer_name) == layer_names.end()) {
      add_layer(layer_name);
    }
    OGRLayer* layer = dataset->GetLayerByName(layer_name.c_str());
    Assert(layer, "Layer " + layer_name + " not found.");

    OGRLineString line;
    for (const auto& vertex : polyline.vertices) {
      line.addPoint(vertex.x(), vertex.y());
    }

    if (layer->GetLayerDefn()->GetFieldIndex("name") == -1)
      layer->CreateField(new OGRFieldDefn("name", OFTString));
    if (layer->GetLayerDefn()->GetFieldIndex("layer") == -1)
      layer->CreateField(new OGRFieldDefn("layer", OFTString));
    for (const auto& [field_name, field_value] : data_fields) {
      if (layer->GetLayerDefn()->GetFieldIndex(field_name.c_str()) == -1) {
        if (std::holds_alternative<int>(field_value)) {
          layer->CreateField(new OGRFieldDefn(field_name.c_str(), OFTInteger));
        } else if (std::holds_alternative<double>(field_value)) {
          layer->CreateField(new OGRFieldDefn(field_name.c_str(), OFTReal));
        } else if (std::holds_alternative<std::string>(field_value)) {
          layer->CreateField(new OGRFieldDefn(field_name.c_str(), OFTString));
        } else {
          Assert(false, "Unknown field type.");
        }
      }
    }
    OGRFeature* feature = OGRFeature::CreateFeature(layer->GetLayerDefn());
    Assert(feature, "Failed to create feature.");

    feature->SetGeometry(&line);

    feature->SetField("name", polyline.name.c_str());
    feature->SetField("layer", polyline.layer.c_str());

    for (const auto& [field_name, field_value] : data_fields) {
      if (std::holds_alternative<int>(field_value)) {
        feature->SetField(field_name.c_str(), std::get<int>(field_value));
      } else if (std::holds_alternative<double>(field_value)) {
        feature->SetField(field_name.c_str(), std::get<double>(field_value));
      } else if (std::holds_alternative<std::string>(field_value)) {
        feature->SetField(field_name.c_str(), std::get<std::string>(field_value).c_str());
      }
    }

    Assert(layer->CreateFeature(feature) == OGRERR_NONE, "Failed to add feature to layer.");

    OGRFeature::DestroyFeature(feature);
  }
};

inline std::vector<Contour> read_gpkg(const fs::path& filename) {
  TimeFunction timer("reading GPKG " + filename.string());
  std::vector<Contour> contours;

  ensure_gdal_initialized();
  GDALDataset* dataset = (GDALDataset*)GDALOpenEx(filename.string().c_str(), GDAL_OF_VECTOR,
                                                  nullptr, nullptr, nullptr);
  if (!dataset) {
    Fail("Failed to open GPKG file for reading: " + filename.string());
  }

  int layer_count = dataset->GetLayerCount();
  for (int i = 0; i < layer_count; i++) {
    OGRLayer* layer = dataset->GetLayer(i);
    if (!layer) continue;

    OGRFeature* feature;
    layer->ResetReading();
    while ((feature = layer->GetNextFeature()) != nullptr) {
      OGRGeometry* geometry = feature->GetGeometryRef();
      if (!geometry || wkbFlatten(geometry->getGeometryType()) != wkbLineString) {
        OGRFeature::DestroyFeature(feature);
        continue;
      }

      OGRLineString* line = (OGRLineString*)geometry;
      std::vector<Coordinate2D<double>> vertices;
      for (int j = 0; j < line->getNumPoints(); j++) {
        vertices.emplace_back(line->getX(j), line->getY(j));
      }

      // Try to get elevation from the "elevation" field, otherwise from "name" field
      double height = 0.0;
      int elevation_idx = feature->GetFieldIndex("elevation");
      if (elevation_idx >= 0) {
        height = feature->GetFieldAsDouble(elevation_idx);
      } else {
        int name_idx = feature->GetFieldIndex("name");
        if (name_idx >= 0) {
          const char* name = feature->GetFieldAsString(name_idx);
          try {
            height = std::stod(name);
          } catch (...) {
            // If name can't be parsed as double, use 0.0
          }
        }
      }

      if (vertices.size() > 1) {
        contours.emplace_back(Contour(height, std::move(vertices)));
      }

      OGRFeature::DestroyFeature(feature);
    }
  }

  GDALClose(dataset);
  return contours;
}
```


