import subprocess
import sys
from pathlib import Path

# This test assumes QGIS and Blaze are installed and available in PATH.
# It will:
# 1. Run Blaze on the sample.laz file to generate output.
# 2. Attempt to load the output into QGIS using the plugin.
# 3. Check for errors in the process.


def test_blaze_pipeline():
    # Paths
    workspace = Path(__file__).parent.parent.parent
    # sample_laz is not used
    output_dir = workspace / "assets" / "out" / "combined"
    local_blaze = workspace / "blaze-cli"
    blaze_exe = str(local_blaze) if local_blaze.exists() else "blaze-cli"
    # qgis_exe is not used
    plugin_dir = workspace / "qgis_plugin"

    # Step 1: Run Blaze
    blaze_cmd = [blaze_exe, str(workspace / "assets" / "default_config.json")]
    result = subprocess.run(blaze_cmd, capture_output=True, text=True)
    assert result.returncode == 0, f"Blaze failed: {result.stderr}"

    # Step 2: Import into QGIS using plugin
    # This step is a stub: QGIS plugin loading is GUI-based, so we check for errors in plugin code
    try:
        sys.path.insert(0, str(plugin_dir))
        from blaze_loader import BlazeLoaderDialog

        dialog = BlazeLoaderDialog()
        assert hasattr(dialog, "folderLineEdit"), "folderLineEdit missing"
        assert hasattr(dialog, "browseButton"), "browseButton missing"
        # Add more attribute checks as needed
    except Exception as e:
        assert False, f"Plugin dialog failed: {e}"

    # Step 3: Check output files
    assert any(output_dir.glob("*.gpkg")), "No GeoPackage output found"
    assert any(output_dir.glob("*.tif")), "No raster output found"

    print("Blaze plugin pipeline test passed.")


if __name__ == "__main__":
    test_blaze_pipeline()
