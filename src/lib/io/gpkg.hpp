

#include <ogrsf_frmts.h>

#include "assert/gdal_assert.hpp"
#include "dxf/dxf.hpp"
#include "gdal_priv.h"

class GDALDataset_w {
  GDALDataset* dataset;

 public:
  GDALDataset_w(const std::string& filename, const std::string& projection) {
    GDALAllRegister();
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

 public:
  GPKGWriter(const std::string& filename, const std::string& projection)
      : dataset(filename, projection), projection(projection) {}

  void add_layer(const std::string& layer_name) {
    OGRSpatialReference srs;
    srs.SetWellKnownGeogCS(projection.c_str());
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
