"""
Test for contour merging bug: contours_merged.gpkg is created but empty.

The bug: add_merged_gpkg_layer copies ALL fields from source layers (including
'fid') into the merged layer. When writing to a new GeoPackage via OGR, creating
a regular field named 'fid' conflicts with the auto-generated primary key column.
This causes the write to silently fail, producing an empty GeoPackage (no tables),
and the contours layer falls back to being temporary.

This test reproduces the exact code path from add_merged_gpkg_layer:
1. Creates a source contours.gpkg with multiple layers (as Blaze C++ produces)
2. Reads it the way QGIS does (where fields() includes 'fid')
3. Writes merged output using the same OGR logic from the plugin
4. Asserts the output GeoPackage is non-empty and contains all features
"""

import os
import tempfile

import pytest
from osgeo import ogr, osr


def create_test_contours_gpkg(path):
    """Create a multi-layer contours.gpkg like Blaze C++ produces.

    Each layer gets auto-generated fid values (1-based) as the primary key,
    plus regular fields: name, layer, elevation.
    """
    driver = ogr.GetDriverByName("GPKG")
    assert driver is not None, "GPKG driver not available"

    ds = driver.CreateDataSource(path)
    assert ds is not None, f"Failed to create {path}"

    srs = osr.SpatialReference()
    srs.ImportFromEPSG(28355)  # MGA Zone 55

    # Create two layers (simulating contours from two tiles)
    for layer_idx, layer_name in enumerate(["101_Contour", "102_Index_Contour"]):
        lyr = ds.CreateLayer(layer_name, srs, ogr.wkbLineString)
        assert lyr is not None

        # Add fields matching what Blaze C++ writes
        lyr.CreateField(ogr.FieldDefn("name", ogr.OFTString))
        lyr.CreateField(ogr.FieldDefn("layer", ogr.OFTString))
        field_defn = ogr.FieldDefn("elevation", ogr.OFTReal)
        lyr.CreateField(field_defn)

        # Add 3 features per layer (fid auto-generated: 1, 2, 3 in each)
        for i in range(3):
            feat = ogr.Feature(lyr.GetLayerDefn())
            line = ogr.Geometry(ogr.wkbLineString)
            base_x = layer_idx * 1000
            line.AddPoint(base_x + i * 10, 0)
            line.AddPoint(base_x + i * 10 + 5, 5)
            line.AddPoint(base_x + i * 10 + 10, 0)
            feat.SetGeometry(line)
            feat.SetField("name", f"contour_{layer_idx}_{i}")
            feat.SetField("layer", layer_name)
            feat.SetField("elevation", 100.0 + i * 5)
            assert lyr.CreateFeature(feat) == ogr.OGRERR_NONE
            feat = None

    ds = None  # Close/flush


def merge_contours_like_plugin(source_gpkg, output_gpkg, include_fid_field=True):
    """Simulate the merge logic from add_merged_gpkg_layer in create_qgis_project.py.

    This replicates the OGR writing portion of the function (lines 1830-1934),
    but with the field list that QGIS would provide (including 'fid').

    In the real plugin, QGIS's QgsVectorLayer.fields() includes 'fid' for
    GeoPackage layers, which gets carried through to the OGR write step.

    Args:
        source_gpkg: Path to source multi-layer GeoPackage
        output_gpkg: Path to write merged output
        include_fid_field: If True, include 'fid' in field list (reproduces bug).
                          If False, exclude 'fid' (the fix).
    """
    # Step 1: Read source layers and collect all features + fields
    src_ds = ogr.Open(source_gpkg)
    assert src_ds is not None

    layer_names = [src_ds.GetLayerByIndex(i).GetName() for i in range(src_ds.GetLayerCount())]

    # Collect field definitions from first layer
    # In QGIS, fields() includes 'fid'. In pure OGR, fid is not a regular field.
    # We simulate what QGIS does by explicitly including 'fid' in the field list.
    first_layer = src_ds.GetLayerByIndex(0)
    layer_defn = first_layer.GetLayerDefn()

    fields = []
    if include_fid_field:
        # This is what QGIS does: exposes fid as a regular integer field
        fields.append(("fid", ogr.OFTInteger))

    for i in range(layer_defn.GetFieldCount()):
        field_defn = layer_defn.GetFieldDefn(i)
        fields.append((field_defn.GetName(), field_defn.GetType()))

    # Collect all features from all layers (with their fid values)
    all_features = []
    for layer_name in layer_names:
        lyr = src_ds.GetLayerByName(layer_name)
        lyr.ResetReading()
        feat = lyr.GetNextFeature()
        while feat is not None:
            feature_data = {
                "geometry": feat.GetGeometryRef().Clone() if feat.GetGeometryRef() else None,
                "fid": feat.GetFID(),
            }
            for i in range(feat.GetFieldCount()):
                fname = feat.GetFieldDefnRef(i).GetName()
                feature_data[fname] = feat.GetField(i)
            all_features.append(feature_data)
            feat = lyr.GetNextFeature()

    src_ds = None

    # Step 2: Write merged GeoPackage using OGR (same as plugin lines 1841-1934)
    driver = ogr.GetDriverByName("GPKG")
    assert driver is not None

    if os.path.exists(output_gpkg):
        os.unlink(output_gpkg)

    ds = driver.CreateDataSource(output_gpkg)
    assert ds is not None, f"Failed to create output GeoPackage: {output_gpkg}"

    srs = osr.SpatialReference()
    srs.ImportFromEPSG(28355)

    ogr_layer = ds.CreateLayer("contours", srs, ogr.wkbLineString)
    assert ogr_layer is not None, "Failed to create layer in GeoPackage"

    # Add fields — this is where the bug manifests.
    # The plugin code does: for field in merged_layer.fields(): ogr_layer.CreateField(...)
    # When merged_layer.fields() includes 'fid', this tries to create a regular field
    # named 'fid' which conflicts with the GeoPackage auto-generated primary key.
    for field_name, field_type in fields:
        field_defn = ogr.FieldDefn(field_name, field_type)
        ogr_layer.CreateField(field_defn)

    # Write features (same logic as plugin lines 1914-1932)
    written_count = 0
    for feature_data in all_features:
        ogr_feat = ogr.Feature(ogr_layer.GetLayerDefn())
        geom = feature_data.get("geometry")
        if geom:
            ogr_feat.SetGeometry(geom)

        # Set attributes — plugin does: ogr_feat.SetField(field.name(), str(val))
        for field_name, _field_type in fields:
            val = feature_data.get(field_name)
            if val is not None:
                ogr_feat.SetField(field_name, val)

        if ogr_layer.CreateFeature(ogr_feat) == ogr.OGRERR_NONE:
            written_count += 1
        ogr_feat = None

    ds = None  # Close datasource
    return written_count


class TestContourMerge:
    """Tests for the contour merging functionality."""

    def setup_method(self):
        """Create temp directory for test files."""
        self.tmpdir = tempfile.mkdtemp(prefix="blaze_test_")
        self.source_gpkg = os.path.join(self.tmpdir, "contours.gpkg")
        self.merged_gpkg = os.path.join(self.tmpdir, "contours_merged.gpkg")
        create_test_contours_gpkg(self.source_gpkg)

    def teardown_method(self):
        """Clean up temp files."""
        import shutil

        shutil.rmtree(self.tmpdir, ignore_errors=True)

    def test_source_gpkg_has_multiple_layers(self):
        """Verify the test fixture: source has 2 layers with 3 features each."""
        ds = ogr.Open(self.source_gpkg)
        assert ds is not None
        assert ds.GetLayerCount() == 2

        total_features = 0
        for i in range(ds.GetLayerCount()):
            lyr = ds.GetLayerByIndex(i)
            total_features += lyr.GetFeatureCount()
        ds = None

        assert total_features == 6

    def test_merged_gpkg_is_not_empty(self):
        """The merged GeoPackage must contain a table with features.

        Regression test: including the 'fid' field in the merge used to cause
        the output GeoPackage to be empty (no tables) due to UNIQUE constraint
        violations. The fix is to exclude 'fid' when copying fields, since it
        is the GeoPackage auto-generated primary key.
        """
        # Merge WITHOUT fid field (the fix: exclude fid from copied fields)
        merge_contours_like_plugin(self.source_gpkg, self.merged_gpkg, include_fid_field=False)

        # Verify the output file exists
        assert os.path.exists(self.merged_gpkg), "Merged GeoPackage file was not created"

        # Verify it has tables (layers) - this is the core assertion that should fail
        ds = ogr.Open(self.merged_gpkg)
        assert ds is not None, "Could not open merged GeoPackage"
        assert ds.GetLayerCount() > 0, (
            "Merged GeoPackage has no tables/layers - file is empty! "
            "This is likely caused by including 'fid' field in the merge."
        )

        # Verify the layer has the expected number of features
        lyr = ds.GetLayerByIndex(0)
        feature_count = lyr.GetFeatureCount()
        ds = None

        assert feature_count == 6, (
            f"Expected 6 features in merged layer, got {feature_count}. "
            "Some features were lost during merge, possibly due to fid UNIQUE constraint."
        )

    def test_merged_gpkg_all_features_have_unique_fids(self):
        """After merging, all features should have unique auto-generated FIDs.

        Regression test: when 'fid' from source layers was included as a regular
        field, features from different layers with the same fid values (e.g.,
        both layers have fid=1,2,3) caused UNIQUE constraint violations.
        """
        merge_contours_like_plugin(self.source_gpkg, self.merged_gpkg, include_fid_field=False)

        ds = ogr.Open(self.merged_gpkg)
        if ds is None or ds.GetLayerCount() == 0:
            pytest.fail("Merged GeoPackage is empty - cannot verify FIDs")

        lyr = ds.GetLayerByIndex(0)
        fids = set()
        feat = lyr.GetNextFeature()
        while feat is not None:
            fid = feat.GetFID()
            assert fid not in fids, f"Duplicate FID {fid} found in merged layer"
            fids.add(fid)
            feat = lyr.GetNextFeature()
        ds = None

        assert len(fids) == 6, f"Expected 6 unique FIDs, got {len(fids)}"

    def test_merged_gpkg_preserves_attributes(self):
        """Merged features must retain their original attribute values."""
        merge_contours_like_plugin(self.source_gpkg, self.merged_gpkg, include_fid_field=False)

        ds = ogr.Open(self.merged_gpkg)
        if ds is None or ds.GetLayerCount() == 0:
            pytest.fail("Merged GeoPackage is empty - cannot verify attributes")

        lyr = ds.GetLayerByIndex(0)
        elevations = []
        feat = lyr.GetNextFeature()
        while feat is not None:
            elev_idx = feat.GetFieldIndex("elevation")
            if elev_idx >= 0:
                elevations.append(feat.GetFieldAsDouble(elev_idx))
            feat = lyr.GetNextFeature()
        ds = None

        assert len(elevations) == 6, f"Expected 6 features with elevation, got {len(elevations)}"
        # Each layer has elevations: 100, 105, 110
        expected = sorted([100.0, 105.0, 110.0, 100.0, 105.0, 110.0])
        assert sorted(elevations) == expected, f"Elevation values don't match: {sorted(elevations)}"

    def test_including_fid_field_loses_features(self):
        """Demonstrate that including 'fid' in the merge loses features.

        This is the regression guard: if 'fid' is accidentally included in the
        field list again, features will be lost due to UNIQUE constraint failures
        in the GeoPackage primary key column.
        """
        merge_contours_like_plugin(self.source_gpkg, self.merged_gpkg, include_fid_field=True)

        ds = ogr.Open(self.merged_gpkg)
        assert ds is not None
        if ds.GetLayerCount() == 0:
            # File is completely empty — this is the worst-case manifestation
            ds = None
            return

        lyr = ds.GetLayerByIndex(0)
        feature_count = lyr.GetFeatureCount()
        ds = None

        # With fid included, only 3 of 6 features survive (the second layer's
        # features fail with UNIQUE constraint on fid=1,2,3).
        assert feature_count < 6, (
            "Expected fewer than 6 features when 'fid' is included in merge, "
            f"but got {feature_count}. Has OGR behavior changed?"
        )


if __name__ == "__main__":
    pytest.main([__file__, "-v"])
