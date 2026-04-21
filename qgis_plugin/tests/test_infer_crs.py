"""Tests for infer_crs_from_description() in create_qgis_project.py.

This function parses CRS description strings (as found in raster metadata)
and returns the corresponding EPSG code.  It handles:
  - GDA2020 / MGA zones 48-58 (EPSG 7848-7858)
  - UTM zones 1-60 North/South (EPSG 326xx / 327xx)
  - Unknown / missing descriptions (returns None)
"""

import importlib.util
from pathlib import Path

import pytest

# Load create_qgis_project.py directly from file, bypassing the
# blaze_loader package __init__.py (which requires a running QGIS).
# The QGIS module mocks are already installed by conftest.py.
_CQP_PATH = Path(__file__).resolve().parent.parent / "blaze_loader" / "create_qgis_project.py"
_spec = importlib.util.spec_from_file_location("create_qgis_project", str(_CQP_PATH))
_mod = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(_mod)

infer_crs_from_description = _mod.infer_crs_from_description


# ---------------------------------------------------------------------------
# MGA zone tests
# ---------------------------------------------------------------------------


class TestMGAZones:
    """GDA2020 / MGA zone patterns -> EPSG 7800 + zone."""

    def test_mga_zone_55_with_full_description(self):
        """Standard QGIS-style description with spaces."""
        assert infer_crs_from_description("GDA2020 / MGA 55S") == 7855

    def test_mga_zone_55_no_spaces(self):
        """Compact form without spaces (e.g. embedded in WKT)."""
        assert infer_crs_from_description("MGA55S") == 7855

    def test_mga_zone_48_boundary_low(self):
        """Lowest valid MGA zone."""
        assert infer_crs_from_description("MGA 48S") == 7848

    def test_mga_zone_58_boundary_high(self):
        """Highest valid MGA zone."""
        assert infer_crs_from_description("MGA 58S") == 7858

    def test_mga_zone_50(self):
        """Mid-range MGA zone."""
        assert infer_crs_from_description("GDA2020 / MGA 50S") == 7850

    def test_mga_north_hemisphere(self):
        """MGA zone with N hemisphere marker (unusual but valid per regex)."""
        assert infer_crs_from_description("MGA 55N") == 7855

    def test_mga_case_insensitive(self):
        """Lowercase should still match."""
        assert infer_crs_from_description("mga 55s") == 7855

    def test_mga_mixed_case(self):
        """Mixed case."""
        assert infer_crs_from_description("Mga55s") == 7855

    def test_mga_zone_47_below_range(self):
        """Zone 47 is below MGA range, should return None."""
        assert infer_crs_from_description("MGA 47S") is None

    def test_mga_zone_59_above_range(self):
        """Zone 59 is above MGA range, should return None."""
        assert infer_crs_from_description("MGA 59S") is None

    def test_mga_with_surrounding_text(self):
        """MGA pattern embedded in longer description."""
        assert infer_crs_from_description("Some CRS: GDA2020 / MGA 55S (EPSG:7855)") == 7855

    def test_mga_missing_hemisphere(self):
        """MGA pattern without N/S hemisphere marker should not match."""
        assert infer_crs_from_description("MGA 55") is None


# ---------------------------------------------------------------------------
# UTM zone tests
# ---------------------------------------------------------------------------


class TestUTMZones:
    """UTM Zone patterns -> EPSG 326xx (North) or 327xx (South)."""

    def test_utm_zone_55_south(self):
        assert infer_crs_from_description("UTM Zone 55S") == 32755

    def test_utm_zone_33_north(self):
        assert infer_crs_from_description("UTM Zone 33N") == 32633

    def test_utm_zone_1_south_boundary_low(self):
        """Lowest valid UTM zone."""
        assert infer_crs_from_description("UTM Zone 1S") == 32701

    def test_utm_zone_60_north_boundary_high(self):
        """Highest valid UTM zone."""
        assert infer_crs_from_description("UTM Zone 60N") == 32660

    def test_utm_zone_60_south(self):
        assert infer_crs_from_description("UTM Zone 60S") == 32760

    def test_utm_case_insensitive(self):
        assert infer_crs_from_description("utm zone 55s") == 32755

    def test_utm_zone_0_below_range(self):
        """Zone 0 is invalid, should return None."""
        assert infer_crs_from_description("UTM Zone 0S") is None

    def test_utm_zone_61_above_range(self):
        """Zone 61 is invalid, should return None."""
        assert infer_crs_from_description("UTM Zone 61N") is None

    def test_utm_with_surrounding_text(self):
        """UTM pattern embedded in longer description."""
        assert infer_crs_from_description("WGS 84 / UTM Zone 55S (approx)") == 32755

    def test_utm_missing_zone_keyword(self):
        """'UTM 55S' without 'Zone' should not match the UTM regex."""
        assert infer_crs_from_description("UTM 55S") is None


# ---------------------------------------------------------------------------
# Edge cases and invalid inputs
# ---------------------------------------------------------------------------


class TestEdgeCases:
    """Inputs that should return None."""

    def test_none_input(self):
        assert infer_crs_from_description(None) is None

    def test_empty_string(self):
        assert infer_crs_from_description("") is None

    def test_unknown_crs_description(self):
        assert infer_crs_from_description("Some Random Projection") is None

    def test_epsg_code_only(self):
        """Just an EPSG code string, no MGA/UTM pattern."""
        assert infer_crs_from_description("EPSG:7855") is None

    def test_numeric_string(self):
        assert infer_crs_from_description("7855") is None

    def test_wgs84(self):
        """WGS84 is not MGA or UTM zone, should return None."""
        assert infer_crs_from_description("WGS 84") is None

    def test_mga_takes_priority_over_utm(self):
        """If both MGA and UTM patterns are present, MGA is checked first."""
        result = infer_crs_from_description("MGA 55S / UTM Zone 55S")
        assert result == 7855  # MGA match wins


if __name__ == "__main__":
    pytest.main([__file__, "-v"])
