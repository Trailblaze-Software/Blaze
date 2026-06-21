#pragma once

#include <cpl_error.h>
#include <ogrsf_frmts.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <variant>
#include <vector>

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

    // SetProjection on a 0x0x0 dataset triggers a spurious "0 band" error
    // in some GDAL builds. Suppress it — layers add dimensions later.
    CPLPushErrorHandler(CPLQuietErrorHandler);
    dataset->SetProjection(projection.c_str());
    CPLPopErrorHandler();
  }

  GDALDataset* operator->() { return dataset; }

  ~GDALDataset_w() { GDALClose(dataset); }
};

class GPKGWriter {
  GDALDataset_w dataset;
  const std::string projection;

  std::vector<std::string> layer_names;
  std::set<std::string> layers_with_fields;
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
    OGRLayer* layer = get_or_create_layer(polyline.layer);

    OGRLineString line;
    for (const auto& vertex : polyline.vertices) {
      line.addPoint(vertex.x(), vertex.y());
    }

    write_feature(layer, &line, polyline.name, polyline.layer, data_fields);
  }

  // Write a polygon (with optional holes) to the GPKG.
  void write_polygon(
      const std::string& layer_name, const std::string& name,
      const std::vector<Coordinate2D<double>>& exterior_ring,
      const std::vector<std::vector<Coordinate2D<double>>>& holes,
      const std::map<std::string, std::variant<int, double, std::string>>& data_fields = {}) {
    OGRLayer* layer = get_or_create_layer(layer_name, wkbPolygon);

    OGRPolygon polygon;
    OGRLinearRing ext_ring;
    populate_ring(ext_ring, exterior_ring);
    Assert(polygon.addRing(&ext_ring) == OGRERR_NONE, "Failed to add exterior ring to polygon");

    for (const auto& hole : holes) {
      OGRLinearRing int_ring;
      populate_ring(int_ring, hole);
      Assert(polygon.addRing(&int_ring) == OGRERR_NONE, "Failed to add interior ring to polygon");
    }

    write_feature(layer, &polygon, name, layer_name, data_fields);
  }

 private:
  OGRLayer* get_or_create_layer(const std::string& layer_name,
                                OGRwkbGeometryType geom_type = wkbLineString) {
    if (std::find(layer_names.begin(), layer_names.end(), layer_name) == layer_names.end()) {
      add_layer(layer_name, geom_type);
    }
    OGRLayer* layer = dataset->GetLayerByName(layer_name.c_str());
    Assert(layer, "Layer " + layer_name + " not found.");
    return layer;
  }

  static void populate_ring(OGRLinearRing& ring,
                            const std::vector<Coordinate2D<double>>& vertices) {
    for (const auto& vertex : vertices) {
      ring.addPoint(vertex.x(), vertex.y());
    }
    ring.closeRings();
  }

  static OGRFieldType field_type_for(const std::variant<int, double, std::string>& value) {
    if (std::holds_alternative<int>(value)) {
      return OFTInteger;
    }
    if (std::holds_alternative<double>(value)) {
      return OFTReal;
    }
    if (std::holds_alternative<std::string>(value)) {
      return OFTString;
    }
    Fail("Unknown field type.");
  }

  void ensure_field(OGRLayer* layer, const std::string& field_name, OGRFieldType field_type) {
    if (layer->GetLayerDefn()->GetFieldIndex(field_name.c_str()) == -1) {
      OGRFieldDefn defn(field_name.c_str(), field_type);
      GDALAssert(layer->CreateField(&defn));
    }
  }

  void ensure_data_fields(
      OGRLayer* layer,
      const std::map<std::string, std::variant<int, double, std::string>>& data_fields) {
    ensure_field(layer, "name", OFTString);
    ensure_field(layer, "layer", OFTString);
    for (const auto& [field_name, field_value] : data_fields) {
      ensure_field(layer, field_name, field_type_for(field_value));
    }
  }

  static void set_data_fields(
      OGRFeature* feature,
      const std::map<std::string, std::variant<int, double, std::string>>& data_fields) {
    for (const auto& [field_name, field_value] : data_fields) {
      if (std::holds_alternative<int>(field_value)) {
        feature->SetField(field_name.c_str(), std::get<int>(field_value));
      } else if (std::holds_alternative<double>(field_value)) {
        feature->SetField(field_name.c_str(), std::get<double>(field_value));
      } else if (std::holds_alternative<std::string>(field_value)) {
        feature->SetField(field_name.c_str(), std::get<std::string>(field_value).c_str());
      }
    }
  }

  void write_feature(
      OGRLayer* layer, OGRGeometry* geometry, const std::string& name,
      const std::string& layer_name,
      const std::map<std::string, std::variant<int, double, std::string>>& data_fields) {
    if (layers_with_fields.insert(layer_name).second) {
      ensure_data_fields(layer, data_fields);
    }

    OGRFeature* feature = OGRFeature::CreateFeature(layer->GetLayerDefn());
    Assert(feature, "Failed to create feature.");
    feature->SetGeometry(geometry);
    feature->SetField("name", name.c_str());
    feature->SetField("layer", layer_name.c_str());
    set_data_fields(feature, data_fields);
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

inline void ensure_dst_layer_fields(OGRLayer* dst_layer, OGRFeatureDefn* src_defn) {
  if (!dst_layer || !src_defn) return;
  for (int i = 0; i < src_defn->GetFieldCount(); i++) {
    OGRFieldDefn* field = src_defn->GetFieldDefn(i);
    if (!field || std::string(field->GetNameRef()) == "fid") continue;
    if (dst_layer->GetLayerDefn()->GetFieldIndex(field->GetNameRef()) < 0) {
      dst_layer->CreateField(field);
    }
  }
}

inline OGRLayer* get_or_create_dst_layer(GDALDataset* dst, OGRLayer* src_layer,
                                         const std::string& layer_name,
                                         OGRwkbGeometryType geom_type) {
  OGRLayer* dst_layer = dst->GetLayerByName(layer_name.c_str());
  if (!dst_layer) {
    dst_layer =
        dst->CreateLayer(layer_name.c_str(), src_layer->GetSpatialRef(), geom_type, nullptr);
    if (!dst_layer) {
      std::cerr << "Warning: failed to create layer " << layer_name << " in combined GPKG\n";
      return nullptr;
    }
    ensure_dst_layer_fields(dst_layer, src_layer->GetLayerDefn());
    return dst_layer;
  }

  if (wkbFlatten(dst_layer->GetLayerDefn()->GetGeomType()) != wkbFlatten(geom_type)) {
    std::cerr << "Warning: geometry type mismatch for layer " << layer_name
              << " in combined GPKG\n";
    return nullptr;
  }
  ensure_dst_layer_fields(dst_layer, src_layer->GetLayerDefn());
  return dst_layer;
}

inline void copy_gpkg_feature(GDALDataset* dst, OGRLayer* src_layer, OGRFeature* feature) {
  if (!dst || !src_layer || !feature) return;

  OGRGeometry* geometry = feature->GetGeometryRef();
  if (!geometry) return;

  std::string layer_name = src_layer->GetName();
  int layer_idx = feature->GetFieldIndex("layer");
  if (layer_idx >= 0) {
    const char* layer_field = feature->GetFieldAsString(layer_idx);
    if (layer_field && layer_field[0] != '\0') {
      layer_name = layer_field;
    }
  }

  OGRLayer* dst_layer =
      get_or_create_dst_layer(dst, src_layer, layer_name, wkbFlatten(geometry->getGeometryType()));
  if (!dst_layer) return;

  OGRFeature* copy = OGRFeature::CreateFeature(dst_layer->GetLayerDefn());
  if (copy->SetFrom(feature) != OGRERR_NONE) {
    std::cerr << "Warning: failed to copy feature in layer " << layer_name << "\n";
  } else if (dst_layer->CreateFeature(copy) != OGRERR_NONE) {
    std::cerr << "Warning: failed to write feature to layer " << layer_name << "\n";
  }
  OGRFeature::DestroyFeature(copy);
}

inline void copy_gpkg_layer(GDALDataset* dst, OGRLayer* src_layer) {
  if (!dst || !src_layer) return;

  src_layer->ResetReading();
  OGRFeature* feature = nullptr;
  bool copied_any = false;
  while ((feature = src_layer->GetNextFeature()) != nullptr) {
    copy_gpkg_feature(dst, src_layer, feature);
    copied_any = true;
    OGRFeature::DestroyFeature(feature);
  }
  (void)copied_any;
}

// Merge several GeoPackage files into one output file. Layers with the same name
// have their features appended. Skips missing inputs and empty layers.
inline void combine_gpkgs(const std::vector<fs::path>& sources, const fs::path& output,
                          const std::string& projection = {}) {
  ensure_gdal_initialized();

  std::vector<fs::path> existing;
  for (const fs::path& src : sources) {
    if (fs::exists(src)) existing.push_back(src);
  }
  if (existing.empty()) return;

  if (fs::exists(output)) {
    GDALDriver* driver = GetGDALDriverManager()->GetDriverByName("GPKG");
    if (driver) {
      driver->Delete(output.string().c_str());
    }
  }

  std::string out_projection = projection;
  if (out_projection.empty()) {
    GDALDataset* probe = (GDALDataset*)GDALOpenEx(existing[0].string().c_str(), GDAL_OF_VECTOR,
                                                  nullptr, nullptr, nullptr);
    if (probe) {
      const char* wkt = probe->GetProjectionRef();
      if (wkt && wkt[0] != '\0') {
        out_projection = wkt;
      }
      GDALClose(probe);
    }
  }

  GDALDriver* driver = GetGDALDriverManager()->GetDriverByName("GPKG");
  if (!driver) {
    std::cerr << "GeoPackage driver not available\n";
    return;
  }

  GDALDataset* dst = driver->Create(output.string().c_str(), 0, 0, 0, GDT_Unknown, nullptr);
  if (!dst) {
    std::cerr << "Failed to create combined GPKG " << output << "\n";
    return;
  }

  if (!out_projection.empty()) {
    CPLPushErrorHandler(CPLQuietErrorHandler);
    dst->SetProjection(out_projection.c_str());
    CPLPopErrorHandler();
  }

  for (const fs::path& src_path : existing) {
    GDALDataset* src = (GDALDataset*)GDALOpenEx(src_path.string().c_str(), GDAL_OF_VECTOR, nullptr,
                                                nullptr, nullptr);
    if (!src) {
      std::cerr << "Warning: failed to open GPKG " << src_path << "\n";
      continue;
    }
    for (int i = 0; i < src->GetLayerCount(); i++) {
      copy_gpkg_layer(dst, src->GetLayer(i));
    }
    GDALClose(src);
  }

  GDALClose(dst);
}
