

#include <ogrsf_frmts.h>
#include <gdal_alg.h>
#include <cstdio>
#include <map>
#include <string>

#include "assert/assert.hpp"
#include "assert/gdal_assert.hpp"
#include "contour/contour.hpp"
#include "gdal_priv.h"
#include "io/gdal_init.hpp"
#include "lib/grid/grid.hpp"
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

  void add_layer(const std::string& layer_name, OGRwkbGeometryType geom_type = wkbLineString) {
    Assert(!projection.empty(), "Projection must not be empty when creating GPKG layer");
    OGRSpatialReference srs;
    // Import projection from WKT string (supports both geographic and projected CRS)
    GDALAssert(srs.importFromWkt(projection.c_str()));
    OGRLayer* layer = dataset->CreateLayer(layer_name.c_str(), &srs, geom_type, nullptr);
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

    if (layer->GetLayerDefn()->GetFieldIndex("name") == -1) {
      OGRFieldDefn defn("name", OFTString);
      GDALAssert(layer->CreateField(&defn));
    }
    if (layer->GetLayerDefn()->GetFieldIndex("layer") == -1) {
      OGRFieldDefn defn("layer", OFTString);
      GDALAssert(layer->CreateField(&defn));
    }
    for (const auto& [field_name, field_value] : data_fields) {
      if (layer->GetLayerDefn()->GetFieldIndex(field_name.c_str()) == -1) {
        if (std::holds_alternative<int>(field_value)) {
          OGRFieldDefn defn(field_name.c_str(), OFTInteger);
          GDALAssert(layer->CreateField(&defn));
        } else if (std::holds_alternative<double>(field_value)) {
          OGRFieldDefn defn(field_name.c_str(), OFTReal);
          GDALAssert(layer->CreateField(&defn));
        } else if (std::holds_alternative<std::string>(field_value)) {
          OGRFieldDefn defn(field_name.c_str(), OFTString);
          GDALAssert(layer->CreateField(&defn));
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

  void write_polygon(
      const Contour& contour, const std::string& layer_name_override,
      const std::map<std::string, std::variant<int, double, std::string>>& data_fields = {}) {
    std::string layer_name = layer_name_override;
    if (std::find(layer_names.begin(), layer_names.end(), layer_name) == layer_names.end()) {
      add_layer(layer_name, wkbPolygon);
    }
    OGRLayer* layer = dataset->GetLayerByName(layer_name.c_str());
    Assert(layer, "Layer " + layer_name + " not found.");
    Assert(wkbFlatten(layer->GetGeomType()) == wkbPolygon,
           "Layer " + layer_name + " is not a polygon layer.");

    OGRPolygon poly;
    OGRLinearRing ring;
    for (const auto& vertex : contour.points()) {
      ring.addPoint(vertex.x(), vertex.y());
    }
    poly.addRing(&ring);

    if (layer->GetLayerDefn()->GetFieldIndex("name") == -1) {
      OGRFieldDefn defn("name", OFTString);
      GDALAssert(layer->CreateField(&defn));
    }
    if (layer->GetLayerDefn()->GetFieldIndex("layer") == -1) {
      OGRFieldDefn defn("layer", OFTString);
      GDALAssert(layer->CreateField(&defn));
    }
    for (const auto& [field_name, field_value] : data_fields) {
      if (layer->GetLayerDefn()->GetFieldIndex(field_name.c_str()) == -1) {
        if (std::holds_alternative<int>(field_value)) {
          OGRFieldDefn defn(field_name.c_str(), OFTInteger);
          GDALAssert(layer->CreateField(&defn));
        } else if (std::holds_alternative<double>(field_value)) {
          OGRFieldDefn defn(field_name.c_str(), OFTReal);
          GDALAssert(layer->CreateField(&defn));
        } else if (std::holds_alternative<std::string>(field_value)) {
          OGRFieldDefn defn(field_name.c_str(), OFTString);
          GDALAssert(layer->CreateField(&defn));
        }
      }
    }
    OGRFeature* feature = OGRFeature::CreateFeature(layer->GetLayerDefn());
    Assert(feature, "Failed to create feature.");

    feature->SetGeometry(&poly);

    if (data_fields.count("category_name")) {
      feature->SetField("name", std::get<std::string>(data_fields.at("category_name")).c_str());
    }
    feature->SetField("layer", layer_name.c_str());

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

  void write_geometry(
      OGRGeometry* geom, const std::string& layer_name_override,
      const std::map<std::string, std::variant<int, double, std::string>>& data_fields = {},
      OGRwkbGeometryType geom_type = wkbMultiPolygon) {
    std::string layer_name = layer_name_override;
    if (std::find(layer_names.begin(), layer_names.end(), layer_name) == layer_names.end()) {
      add_layer(layer_name, geom_type);
    }
    OGRLayer* layer = dataset->GetLayerByName(layer_name.c_str());
    Assert(layer, "Layer " + layer_name + " not found.");

    if (layer->GetLayerDefn()->GetFieldIndex("name") == -1) {
      OGRFieldDefn defn("name", OFTString);
      GDALAssert(layer->CreateField(&defn));
    }
    if (layer->GetLayerDefn()->GetFieldIndex("layer") == -1) {
      OGRFieldDefn defn("layer", OFTString);
      GDALAssert(layer->CreateField(&defn));
    }
    for (const auto& [field_name, field_value] : data_fields) {
      if (layer->GetLayerDefn()->GetFieldIndex(field_name.c_str()) == -1) {
        if (std::holds_alternative<int>(field_value)) {
          OGRFieldDefn defn(field_name.c_str(), OFTInteger);
          GDALAssert(layer->CreateField(&defn));
        } else if (std::holds_alternative<double>(field_value)) {
          OGRFieldDefn defn(field_name.c_str(), OFTReal);
          GDALAssert(layer->CreateField(&defn));
        } else if (std::holds_alternative<std::string>(field_value)) {
          OGRFieldDefn defn(field_name.c_str(), OFTString);
          GDALAssert(layer->CreateField(&defn));
        }
      }
    }
    OGRFeature* feature = OGRFeature::CreateFeature(layer->GetLayerDefn());
    Assert(feature, "Failed to create feature.");

    OGRGeometry* geom_to_write = geom->clone();
    if (wkbFlatten(geom_type) == wkbMultiPolygon) {
      geom_to_write = OGRGeometryFactory::forceToMultiPolygon(geom_to_write);
    }

    if (geom_to_write) {
      feature->SetGeometryDirectly(geom_to_write);
    }

    if (data_fields.count("category_name")) {
      feature->SetField("name", std::get<std::string>(data_fields.at("category_name")).c_str());
    }
    feature->SetField("layer", layer_name.c_str());

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

inline std::string rgb_to_hex(const RGBColor& rgb) {
  char buffer[8];
  std::snprintf(buffer, sizeof(buffer), "#%02X%02X%02X", rgb.getRed(), rgb.getGreen(), rgb.getBlue());
  return std::string(buffer);
}

inline void polygonize_grid_to_gpkg(
    const GeoGrid<int>& grid, const fs::path& filename, const std::string& projection,
    const std::string& layer_name,
    const std::map<int, std::pair<std::string, std::string>>& category_info) {
  TimeFunction timer("writing polygons to gpkg " + filename.string());
  ensure_gdal_initialized();
  GDALDriver* driver = GetGDALDriverManager()->GetDriverByName("GPKG");
  Assert(driver, "GeoPackage driver not available.");

  GDALDataset* dataset =
      driver->Create(filename.string().c_str(), 0, 0, 0, GDT_Unknown, nullptr);
  Assert(dataset, "Failed to create GeoPackage file " + filename.string());
  dataset->SetProjection(projection.c_str());

  OGRSpatialReference srs;
  GDALAssert(srs.importFromWkt(projection.c_str()));
  OGRLayer* layer = dataset->CreateLayer(layer_name.c_str(), &srs, wkbPolygon, nullptr);
  Assert(layer, "Failed to create layer " + layer_name);

  OGRFieldDefn category_id_field("category_id", OFTInteger);
  GDALAssert(layer->CreateField(&category_id_field));
  OGRFieldDefn category_name_field("category_name", OFTString);
  GDALAssert(layer->CreateField(&category_name_field));
  OGRFieldDefn color_field("color", OFTString);
  GDALAssert(layer->CreateField(&color_field));

  GDALDriver* mem_driver = GetGDALDriverManager()->GetDriverByName("MEM");
  Assert(mem_driver, "MEM driver not available.");
  GDALDataset* mem_ds = mem_driver->Create("", grid.width(), grid.height(), 1, GDT_Int32, nullptr);
  Assert(mem_ds, "Failed to create memory dataset for polygonization.");
  mem_ds->SetGeoTransform(const_cast<double*>(grid.transform().get_raw()));
  mem_ds->SetProjection(projection.c_str());
  GDALRasterBand* src_band = mem_ds->GetRasterBand(1);

  std::vector<int> values(grid.width() * grid.height());
  for (size_t i = 0; i < grid.height(); i++) {
    for (size_t j = 0; j < grid.width(); j++) {
      values[i * grid.width() + j] = grid[{j, i}];
    }
  }

  GDALAssert(src_band->RasterIO(GF_Write, 0, 0, grid.width(), grid.height(), values.data(),
                               grid.width(), grid.height(), GDT_Int32, 0, 0));

  int field_index = layer->GetLayerDefn()->GetFieldIndex("category_id");
  Assert(field_index >= 0, "category_id field missing in polygon layer");

  GDALAssert(GDALPolygonize(src_band, nullptr, layer, field_index, nullptr, nullptr, nullptr));

  layer->ResetReading();
  OGRFeature* feature = nullptr;
  std::vector<GIntBig> to_delete;
  while ((feature = layer->GetNextFeature()) != nullptr) {
    int category_id = feature->GetFieldAsInteger(field_index);
    if (category_id == 0) {
      to_delete.push_back(feature->GetFID());
    } else {
      auto it = category_info.find(category_id);
      if (it != category_info.end()) {
        feature->SetField("category_name", it->second.first.c_str());
        feature->SetField("color", it->second.second.c_str());
        GDALAssert(layer->SetFeature(feature));
      }
    }
    OGRFeature::DestroyFeature(feature);
  }

  for (GIntBig fid : to_delete) {
    OGRErr err = layer->DeleteFeature(fid);
    Assert(err == OGRERR_NONE, "Failed to delete empty polygon feature");
  }

  GDALClose(mem_ds);
  GDALClose(dataset);
}

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
