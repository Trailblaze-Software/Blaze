#!/usr/bin/env python3
"""
QGIS Project Creation Script

Creates a QGIS project from Blaze output and adds NSW topo data with styling.

Usage:
    This script is best used via the Blaze Loader plugin in QGIS.
    It will prompt you for the combined directory and output project path.

    Alternatively, you can run the script directly from the command line:
        qgis --code create_qgis_project.py [combined_dir] [output_project]

    Or in QGIS Python Console:
        exec(open('create_qgis_project.py').read())
        create_qgis_project('out/combined', 'out/combined.qgz')
"""

import os
import sys
import tempfile
import time
from pathlib import Path


# Script directory (for finding styles)
def _find_script_dir():
    """Find the blaze_loader plugin directory."""
    # Try __file__ first (works when run directly or imported normally)
    try:
        return Path(__file__).resolve().parent
    except NameError:
        pass

    # Search sys.path for plugin directory (works when exec'd from QGIS plugin)
    for path in sys.path:
        candidate = Path(path) / "blaze_loader"
        if candidate.is_dir() and (candidate / "metadata.txt").exists():
            return candidate

    # Search up from current directory (works when run from project subdirectory)
    for parent in [Path.cwd()] + list(Path.cwd().parents):
        candidate = parent / "qgis_plugin" / "blaze_loader"
        if candidate.is_dir() and (candidate / "create_qgis_project.py").exists():
            return candidate

    # Fallback to current directory
    return Path.cwd()


SCRIPT_DIR = _find_script_dir()
STYLES_DIR = SCRIPT_DIR / "styles"

# Warn if styles directory not found
if not STYLES_DIR.is_dir():
    print(f"WARNING: Styles directory not found at {STYLES_DIR}")
    print(f"  SCRIPT_DIR = {SCRIPT_DIR}")
    print("  QML styles will not be applied.")

try:
    from osgeo import ogr
    from qgis.core import (
        Qgis,
        QgsApplication,
        QgsFeature,
        QgsField,
        QgsFields,
        QgsGeometry,
        QgsMessageLog,
        QgsPointXY,
        QgsProject,
        QgsRasterLayer,
        QgsReferencedRectangle,
        QgsVectorLayer,
    )
    from qgis.PyQt.QtCore import QVariant
except ImportError:
    print("Error: PyQGIS not available. Run this script from QGIS.")
    sys.exit(1)


# Module-level logging function
def log(message):
    """Log message to both console and QGIS Message Log."""
    print(message)
    try:
        QgsMessageLog.logMessage(message, "Blaze", Qgis.Info)
    except Exception:
        pass  # Silently fail if QGIS logging not available


def _extent_area_sq_km(extent, crs):
    """Return the area of the extent in square kilometres, or None on error."""
    try:
        from qgis.core import QgsDistanceArea, QgsGeometry, QgsProject, QgsRectangle

        da = QgsDistanceArea()
        da.setSourceCrs(crs, QgsProject.instance().transformContext())
        da.setEllipsoid(crs.ellipsoidAcronym())
        rect = extent if hasattr(extent, "xMinimum") else QgsRectangle(extent)
        geom = QgsGeometry.fromRect(rect)

        # Try different methods for compatibility across QGIS versions
        area_sq_m = None
        if hasattr(da, "computeAreaForGeometry"):
            # QGIS 3.28+ method
            area_sq_m = da.computeAreaForGeometry(geom)
        elif hasattr(da, "measureArea"):
            # Older QGIS versions
            area_sq_m = da.measureArea(geom)
        elif hasattr(da, "measure"):
            # Fallback to measure method
            area_sq_m = da.measure(geom)
        else:
            # Last resort: use geometry area (less accurate, no ellipsoid)
            area_sq_m = geom.area()

        if area_sq_m is not None and area_sq_m >= 0:
            return area_sq_m / 1e6
    except Exception as e:
        log(f"Could not compute extent area: {e}")
    return None


def install_package_via_qpip(package_name):
    """Try to install a package using QPIP plugin if available.

    Uses the standard Python approach: try to import the module.
    QGIS automatically adds plugin directories to sys.path when plugins are loaded.
    """
    try:
        from qpip import pip_install

        pip_install([package_name])
        return True
    except ImportError:
        log("  QPIP plugin not available (not installed or not loaded)")
        return False
    except Exception as e:
        log(f"  QPIP error: {e}")
        return False


def get_magnetic_declination(lon, lat):
    """Calculate magnetic declination using geomag (WMM model).

    Returns None if geomag is not available.
    To install geomag: install the QPIP plugin, then run: pip.install('geomag')
    """
    try:
        import geomag

        gm = geomag.geomag.GeoMag()
        result = gm.GeoMag(lat, lon, 0)
        declination = result.dec
        log(f"  Magnetic declination at ({lat:.4f}, {lon:.4f}): {declination:.2f}° (via geomag)")
        return declination
    except ImportError:
        log("  geomag not installed - trying QPIP...")
        if install_package_via_qpip("geomag"):
            try:
                import geomag

                gm = geomag.geomag.GeoMag()
                result = gm.GeoMag(lat, lon, 0)
                declination = result.dec
                log(f"  Magnetic declination at ({lat:.4f}, {lon:.4f}): {declination:.2f}° (via geomag)")
                return declination
            except Exception:
                pass
        log("  geomag not available - magnetic north lines will be skipped")
        log("  To enable: install QPIP plugin and run: pip.install('geomag')")
    except Exception as e:
        log(f"  geomag error: {e}")

    return None


def get_grid_convergence(lon, lat, crs_input):
    """
    Calculates the exact analytic grid convergence.

    Returns None if pyproj is not available or if calculation fails.
    To install pyproj: install the QPIP plugin, then run: pip.install('pyproj')
    """

    def _calculate():
        from pyproj import Proj

        # Try multiple methods to get a valid CRS string
        crs_str = None

        # Method 1: Try authid (EPSG:XXXX)
        if hasattr(crs_input, "authid") and crs_input.authid():
            try:
                crs_str = crs_input.authid()
                # Test if it works
                p = Proj(crs_str)
                return p.get_factors(lon, lat).meridian_convergence
            except Exception:
                pass

        # Method 2: Try WKT
        if hasattr(crs_input, "toWkt"):
            try:
                crs_wkt = crs_input.toWkt()
                if crs_wkt:
                    p = Proj(crs_wkt)
                    return p.get_factors(lon, lat).meridian_convergence
            except Exception:
                pass

        # Method 3: Try PROJ string
        if hasattr(crs_input, "toProj"):
            try:
                proj_str = crs_input.toProj()
                if proj_str:
                    p = Proj(proj_str)
                    return p.get_factors(lon, lat).meridian_convergence
            except Exception:
                pass

        # Method 4: Try as string
        try:
            crs_str = str(crs_input)
            if crs_str:
                p = Proj(crs_str)
                return p.get_factors(lon, lat).meridian_convergence
        except Exception:
            pass

        raise ValueError("Could not convert CRS to a format pyproj can use")

    try:
        return _calculate()
    except ImportError:
        log("  pyproj not installed - trying QPIP...")
        if install_package_via_qpip("pyproj"):
            try:
                result = _calculate()
                log("  pyproj installed successfully")
                return result
            except Exception as e:
                log(f"  pyproj installation succeeded but usage failed: {e}")
        log("  pyproj not available - grid convergence calculation will be skipped")
        log("  To enable: install QPIP plugin and run: pip.install('pyproj')")
        return None
    except Exception as e:
        log(f"  pyproj error: {e}")
        return None


def get_grid_magnetic_angle(lon, lat, crs):
    """
    Calculate the angle from grid north to magnetic north.
    This accounts for both magnetic declination and grid convergence.

    Grid-Magnetic angle = Magnetic Declination - Grid Convergence
    (angle to rotate from grid north to get magnetic north)

    Returns None if magnetic declination or grid convergence cannot be calculated.
    """
    declination = get_magnetic_declination(lon, lat)
    if declination is None:
        return None

    convergence = get_grid_convergence(lon, lat, crs)
    if convergence is None:
        log("  Grid convergence calculation failed - magnetic north lines will be skipped")
        return None

    gm_angle = declination - convergence
    log(f"  Magnetic declination: {declination:.2f}°")
    log(f"  Grid convergence: {convergence:.2f}°")
    log(f"  Grid-Magnetic angle: {gm_angle:.2f}°")
    return gm_angle


def create_qgis_project(
    combined_dir="out/combined",
    output_path=None,
    download_topo=True,
    add_mag_north=True,
    zoom_to_extent=True,
    add_controls=False,
    clear_project=False,
    progress_callback=None,
    gpkg_output_path=None,
    # contours_output_path removed, will be set at merge time
    use_current_extent=False,
    current_extent=None,
    current_crs=None,
    parent_window=None,
):
    """Add Blaze layers to the current QGIS project.

    Args:
        combined_dir: Path to Blaze output directory (ignored if use_current_extent=True)
        output_path: Optional path to save project file (if None, doesn't save)
        download_topo: Download NSW topographic layers from spatial.nsw.gov.au
        add_mag_north: Add magnetic north lines based on current declination
        zoom_to_extent: Zoom map to vector layer extent
        add_controls: Add controls layer with control point in center of map
        clear_project: If True, clear existing project first (default: False)
        progress_callback: Optional callback function(message, percent) for progress updates
        gpkg_output_path: Optional path for NSW topo GPKG file (if None, uses combined_dir/nsw_topo.gpkg)
        use_current_extent: If True, use current map extent instead of loading Blaze layers
        current_extent: QgsRectangle for current map extent (required if use_current_extent=True)
        current_crs: QgsCoordinateReferenceSystem for current map (required if use_current_extent=True)
        parent_window: Optional parent window for dialogs (QMainWindow or QWidget)
    """

    def report_progress(message, percent=None):
        """Report progress via callback if available and log to QGIS."""
        log(message)
        if progress_callback:
            progress_callback(message, percent)

    # Track what was loaded for summary popup
    summary = {"loaded": [], "failed": [], "skipped": []}

    project = QgsProject.instance()
    if clear_project:
        project.clear()

    # Disable automatic CRS transformation prompts in headless mode
    if os.environ.get("BLAZE_EXIT_AFTER_RUN"):
        try:
            from qgis.core import QgsSettings

            settings = QgsSettings()
            # Suppress CRS transformation dialogs
            settings.setValue("/projections/promptForCrsTransform", False)
            settings.setValue("/projections/askUserForDatumTransform", False)
            log("Disabled CRS transformation prompts for headless mode")
        except Exception as e:
            log(f"Could not disable CRS prompts: {e}")

    log("Using style path: " + str(STYLES_DIR))

    root = project.layerTreeRoot()

    # Find or create layer groups (top to bottom in render order)
    # Note: Groups higher in tree render on top
    # Check if groups already exist to allow multiple calls
    def find_or_create_group(parent, name):
        """Find existing group by name or create a new one."""
        # First, try to find existing group by iterating through all children
        # Check all children to see if a group with this name already exists
        for child in parent.children():
            try:
                # Check if it's a group node (nodeType == 1) and name matches exactly
                if child.nodeType() == 1:  # 1 = Group node type
                    if child.name() == name:
                        log(f"Found existing group: {name}")
                        return child
            except (AttributeError, TypeError):
                continue

        # If not found, create new group
        log(f"Creating new group: {name}")
        return parent.addGroup(name)

    # Get or create groups
    markup_group = find_or_create_group(root, "Markup")  # Markup on top (magnetic north, controls)
    topo_group = find_or_create_group(root, "NSW Topo")
    vector_group = find_or_create_group(root, "Vectors")  # Contours/streams - below topo
    raster_group = find_or_create_group(root, "Rasters")

    # Track the first raster CRS for project CRS
    project_crs = None
    project_extent = None

    # If using current extent, set project_crs and project_extent from parameters
    if use_current_extent:
        if current_extent is None or current_crs is None:
            log("Error: current_extent and current_crs are required when use_current_extent=True")
            return False
        project_crs = current_crs
        project_extent = current_extent
        log(
            f"Using current map extent: {project_extent.xMinimum():.1f}, {project_extent.yMinimum():.1f} to "
            f"{project_extent.xMaximum():.1f}, {project_extent.yMaximum():.1f}"
        )
        log(f"Using current map CRS: {project_crs.authid() if project_crs.authid() else project_crs.description()}")

        # Set project CRS
        if project_crs and project_crs.isValid():
            project.setCrs(project_crs)
            authid = project_crs.authid() if project_crs.authid() else "Unknown"
            log(f"Project CRS set to: {authid}")

        # Skip loading Blaze layers - go straight to adding topo/magnetic north/controls
        # Note: We'll remove empty groups at the end after all layers are added
    else:
        # Normal flow: load Blaze layers
        combined_path = Path(combined_dir)
        if not combined_path.exists():
            log(f"Error: Directory {combined_dir} does not exist")
            return False

        report_progress("Adding raster layers (building pyramids for performance)...", 5)

        # Add raster layers first (they render on top of vegetation) - all hidden by default
        rasters = [
            "final_img.tif",
            "final_img_extra_contours.tif",
            "ground_intensity.tif",
            "slope.tif",
        ]
        raster_count = 0
        for i, f in enumerate(rasters):
            report_progress(f"Adding raster {f} ({i+1}/{len(rasters)})...", 5 + int((i / len(rasters)) * 10))
            layer = add_raster(combined_path / f, raster_group)
            if layer:
                raster_count += 1
                crs = layer.crs()
                log(f"  {f}: CRS valid={crs.isValid()}, authid={crs.authid()}, desc={crs.description()}")

                # Always check all rasters, don't stop at first one
                # But prefer rasters with authid over those without
                if project_crs is None:
                    # No CRS yet - use this one if valid
                    if crs.isValid():
                        project_crs = crs
                        project_extent = layer.extent()
                        if crs.authid():
                            log(f"  ✓ Detected project CRS from {f}: {crs.authid()}")
                        else:
                            log(f"  ✓ Using CRS from {f} (no authid): {crs.description()}")
                            wkt = crs.toWkt()
                            if wkt:
                                log(f"    WKT: {wkt[:150]}...")
                elif project_crs and not project_crs.authid() and crs.isValid() and crs.authid():
                    # We have a CRS but no authid - upgrade to one with authid if available
                    project_crs = crs
                    project_extent = layer.extent()
                    log(f"  ✓ Upgraded project CRS from {f}: {crs.authid()}")
                # Hide by default
                layer_node = root.findLayer(layer.id())
                if layer_node:
                    layer_node.setItemVisibilityChecked(False)

        if raster_count:
            summary["loaded"].append(f"{raster_count} raster layer{'s' if raster_count != 1 else ''}")
        else:
            summary["failed"].append("Raster layers (no .tif files found)")

        # Summary of CRS detection
        if project_crs:
            log(
                f"CRS Detection Summary: Found CRS - "
                f"valid={project_crs.isValid()}, "
                f"authid={project_crs.authid()}, "
                f"desc={project_crs.description()}"
            )
        else:
            log("CRS Detection Summary: ⚠ NO CRS DETECTED from any raster files")
            log("  This will cause issues with coordinate transformations and magnetic north calculations")
            log("  Please check that your raster files have projection information embedded")

        report_progress("Adding vegetation layers...", 15)

        # Add vegetation layers LAST (so they're at bottom = render behind other rasters)
        vege_dir = combined_path / "raw_vege"
        if vege_dir.exists():
            vege_group = find_or_create_group(raster_group, "Vegetation")

            # Want smoothed_green on top of smoothed_canopy
            # In QGIS: top of layer tree = renders on top
            vege_layers = [
                ("green.tif", False),
                ("smoothed_green.tif", True),  # Add first
                ("canopy.tif", False),
                ("smoothed_canopy.tif", True),
            ]

            vege_count = 0
            for filename, visible in vege_layers:
                path = vege_dir / filename
                if path.exists():
                    layer = add_raster(path, vege_group, prefix="raw_vege_")
                    if layer:
                        vege_count += 1
                        # Also check vegetation rasters for CRS if not already found
                        crs = layer.crs()
                        log(
                            f"  {filename}: CRS valid={crs.isValid()}, "
                            f"authid={crs.authid()}, desc={crs.description()}"
                        )
                        if project_crs is None:
                            if crs.isValid() and crs.authid():
                                project_crs = crs
                                project_extent = layer.extent()
                                log(f"Detected project CRS from {filename}: {crs.authid()}")
                            elif crs.isValid():
                                # CRS is valid but no authid - still use it if we have nothing else
                                project_crs = crs
                                project_extent = layer.extent()
                                log(f"Using CRS from {filename} (no authid): {crs.description()}")
                        style_vegetation(layer, filename)
                        layer_node = root.findLayer(layer.id())
                        if layer_node:
                            layer_node.setItemVisibilityChecked(visible)

            if vege_count:
                summary["loaded"].append(f"{vege_count} vegetation layer{'s' if vege_count != 1 else ''}")

        # Set project CRS from raster FIRST (only when loading from rasters)
        if project_crs and project_crs.isValid():
            project.setCrs(project_crs)
            authid = project_crs.authid() if project_crs.authid() else "Unknown"
            log(f"Project CRS set to: {authid}")
            if not project_crs.authid():
                log(f"  CRS description: {project_crs.description()}")
                wkt = project_crs.toWkt()
                if wkt:
                    log(f"  CRS WKT: {wkt[:200]}...")
        else:
            log("⚠ WARNING: No project CRS detected from rasters")
            log("  This may cause issues with coordinate transformations and magnetic north calculations")

    # Calculate grid-magnetic angle (accounts for both declination and grid convergence)
    gm_angle = None
    if project_extent and project_crs and project_crs.isValid():
        from qgis.core import QgsCoordinateReferenceSystem, QgsCoordinateTransform

        wgs84 = QgsCoordinateReferenceSystem("EPSG:4326")
        try:
            transform = QgsCoordinateTransform(project_crs, wgs84, project)
            transform.setContext(project.transformContext())
            center = project_extent.center()
            log(f"  Project center (projected): ({center.x():.4f}, {center.y():.4f})")
            wgs84_center = transform.transform(center)

            # Validate that we got WGS84 coordinates (lat should be -90 to 90, lon -180 to 180)
            if -180 <= wgs84_center.x() <= 180 and -90 <= wgs84_center.y() <= 90:
                log(f"  Center coordinates (WGS84): ({wgs84_center.x():.4f}°, {wgs84_center.y():.4f}°)")
                gm_angle = get_grid_magnetic_angle(wgs84_center.x(), wgs84_center.y(), project_crs)
            else:
                log(f"  ⚠ Transform result doesn't look like WGS84: ({wgs84_center.x():.4f}, {wgs84_center.y():.4f})")
                log("    This suggests the CRS transform failed. Project CRS may be incorrect.")
        except Exception as e:
            log(f"  ⚠ Failed to transform coordinates to WGS84: {e}")
            log(f"    Project CRS: {project_crs.description() if project_crs else 'None'}")
            import traceback

            log(f"    Traceback: {traceback.format_exc()}")
    else:
        if not project_extent:
            log("  ⚠ Cannot calculate grid-magnetic angle: no project extent")
        if not project_crs:
            log("  ⚠ Cannot calculate grid-magnetic angle: no project CRS")
        elif not project_crs.isValid():
            log("  ⚠ Cannot calculate grid-magnetic angle: project CRS is invalid")

    # Set default DPI to 600
    try:
        # Set DPI in project settings
        project.writeEntry("Layouts", "/DefaultDpi", 600)
        log("Default DPI set to 600")
    except Exception as e:
        log(f"Could not set DPI: {e}")

    # Add NSW topographic layers (downloaded and saved to single GPKG)
    if download_topo and project_extent and project_crs:
        area_sq_km = _extent_area_sq_km(project_extent, project_crs)
        if area_sq_km is not None and area_sq_km > 1000:
            # Skip dialog in headless mode (CI/automated execution)
            if os.environ.get("BLAZE_EXIT_AFTER_RUN") or parent_window is None:
                log(f"Large extent detected ({area_sq_km:,.0f} km²) - proceeding in headless mode")
            else:
                try:
                    from qgis.PyQt.QtWidgets import QMessageBox

                    msg = (
                        f"The map extent is about {area_sq_km:,.0f} km². "
                        "Downloading topographic layers for this area may"
                        " take a long time and use significant bandwidth. Continue?"
                    )
                    reply = QMessageBox.question(
                        parent_window,
                        "Large extent",
                        msg,
                        QMessageBox.Yes | QMessageBox.No,
                        QMessageBox.No,
                    )
                    if reply != QMessageBox.Yes:
                        download_topo = False
                        log("Topographic layer download skipped - user declined for large extent")
                except Exception as e:
                    log(f"Could not show extent confirmation: {e}")
        if download_topo:
            report_progress("Downloading NSW topographic layers...", 40)
            # Use combined_path if available, otherwise use a temp directory for output files
            if use_current_extent:
                output_dir = Path(tempfile.gettempdir()) / "blaze_plugin"
                output_dir.mkdir(parents=True, exist_ok=True)
            else:
                output_dir = combined_path
            topo_results = add_nsw_topo_layers(
                topo_group,
                project_extent,
                project_crs,
                output_dir,
                progress_callback,
                log,
                gpkg_output_path,
                parent_window=parent_window,
            )
            if topo_results and topo_results.get("with_data"):
                topo_count = len(topo_results["with_data"])
                summary["loaded"].append(f"{topo_count} topo layer{'s' if topo_count != 1 else ''}")
                summary["topo_details"] = topo_results
            elif topo_results and (topo_results.get("empty") or topo_results.get("failed")):
                summary["failed"].append("NSW topo layers (no data in area)")
                summary["topo_details"] = topo_results
            else:
                summary["failed"].append("NSW topo layers (download failed)")
        else:
            summary["skipped"].append("NSW topo layers (user declined)")
    elif download_topo:
        summary["skipped"].append("NSW topo layers (no extent/CRS)")
    # Note: Empty group removal happens at the end

    # Add vector layers (contours, streams) AFTER topo layers so they render underneath
    # Only if not using current extent
    vector_extent = None
    if not use_current_extent:
        report_progress("Adding vector layers (contours, streams)...", 50)

        # Add contours - merge all layers into single layer with QML style
        contours_gpkg = combined_path / "contours.gpkg"
        if contours_gpkg.exists():
            default_path = str(combined_path / "contours_merged.gpkg")

            # Skip file dialog in headless mode (CI/automated execution)
            if os.environ.get("BLAZE_EXIT_AFTER_RUN") or parent_window is None:
                merged_contours_path = default_path
            else:
                from qgis.PyQt.QtWidgets import (
                    QDialog,
                    QDialogButtonBox,
                    QFileDialog,
                    QHBoxLayout,
                    QLabel,
                    QLineEdit,
                    QMessageBox,
                    QPushButton,
                    QVBoxLayout,
                )

                merged_contours_path = None
                while merged_contours_path is None:
                    # Create a dialog similar to the folder selection UI
                    contours_dialog = QDialog(parent_window)
                    contours_dialog.setWindowTitle("Merged Contours File")
                    contours_dialog.setMinimumWidth(500)

                    layout = QVBoxLayout(contours_dialog)

                    # Label
                    label = QLabel("Select where to save merged contour file:")
                    layout.addWidget(label)

                    # Path selection (similar to folder selection)
                    path_layout = QHBoxLayout()
                    path_label = QLabel("Path:")
                    path_edit = QLineEdit()
                    path_edit.setText(default_path)
                    browse_btn = QPushButton("Browse...")

                    def browse_contours_file():
                        file_path, _ = QFileDialog.getSaveFileName(
                            contours_dialog,
                            "Save Merged Contours As",
                            path_edit.text() or default_path,
                            "GeoPackage (*.gpkg);;All Files (*)",
                        )
                        if file_path:
                            path_edit.setText(file_path)

                    browse_btn.clicked.connect(browse_contours_file)

                    path_layout.addWidget(path_label)
                    path_layout.addWidget(path_edit)
                    path_layout.addWidget(browse_btn)
                    layout.addLayout(path_layout)

                    # Buttons
                    button_box = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel)
                    button_box.accepted.connect(contours_dialog.accept)
                    button_box.rejected.connect(contours_dialog.reject)
                    layout.addWidget(button_box)

                    # Show dialog
                    if contours_dialog.exec_() == QDialog.Accepted:
                        chosen_path = path_edit.text() or default_path
                    else:
                        # User cancelled - use default
                        chosen_path = default_path

                    # If the file already exists, ask for confirmation before overwriting
                    if Path(chosen_path).exists():
                        reply = QMessageBox.question(
                            parent_window,
                            "File Already Exists",
                            f"{Path(chosen_path).name} already exists.\n\n" "Do you want to overwrite it?",
                            QMessageBox.Yes | QMessageBox.No,
                            QMessageBox.No,
                        )
                        if reply == QMessageBox.Yes:
                            merged_contours_path = chosen_path
                        # else: loop back to file selection dialog
                    else:
                        merged_contours_path = chosen_path
            layer = add_merged_gpkg_layer(contours_gpkg, "contours", vector_group, project_crs, merged_contours_path)
            if layer:
                is_temp = layer.dataProvider().name() == "memory"
                feat_count = layer.featureCount()
                label = f"Contours ({feat_count} features"
                label += ", temporary)" if is_temp else ")"
                summary["loaded"].append(label)
                if is_temp:
                    summary["failed"].append("Contours file save (layer is temporary)")
                # Apply QML style
                qml_path = STYLES_DIR / "contours.qml"
                if qml_path.exists():
                    layer.loadNamedStyle(str(qml_path))
                    # Skip triggerRepaint in headless mode as it may block
                    if not os.environ.get("BLAZE_EXIT_AFTER_RUN"):
                        layer.triggerRepaint()
                    log("Applied style: contours.qml")
                if layer.extent() and not layer.extent().isEmpty():
                    vector_extent = layer.extent()
            else:
                summary["failed"].append("Contours (merge failed)")

        # Add streams with QML style
        streams_gpkg = combined_path / "streams.gpkg"
        if streams_gpkg.exists():
            layers = add_gpkg_layers(streams_gpkg, vector_group, project_crs, root, apply_default_style=False)
            if layers:
                stream_features = sum(lyr.featureCount() for lyr in layers)
                summary["loaded"].append(f"Streams ({stream_features} features)")
            else:
                summary["failed"].append("Streams (no valid layers)")
            for layer in layers:
                # Apply QML style
                qml_path = STYLES_DIR / "streams.qml"
                if qml_path.exists():
                    log("  Found streams.qml, attempting to load...")
                    result = layer.loadNamedStyle(str(qml_path))
                    if result[1]:  # Success (QGIS API returns (errorMessage, success))
                        layer.triggerRepaint()
                        log("Applied style: streams.qml")
                    else:
                        log(
                            f"WARNING: Failed to apply streams.qml style: {result[0] if result[0] else 'Unknown error'}"
                        )
                else:
                    log(f"WARNING: streams.qml not found at {qml_path}")
                if layer and layer.extent() and not layer.extent().isEmpty():
                    if vector_extent is None:
                        vector_extent = layer.extent()
                    else:
                        vector_extent.combineExtentWith(layer.extent())

    # Basemaps disabled - they cause CRS transformation prompts that can't be suppressed
    # To add manually: Layer > Add Layer > Add XYZ Layer > OpenStreetMap

    # Add magnetic north lines (saved to file for persistence)
    # Note: Compass Routes can calculate magnetic declination internally, so we don't require gm_angle
    # However, gm_angle is still needed for map rotation
    if add_mag_north and project_extent and project_crs:
        area_sq_km = _extent_area_sq_km(project_extent, project_crs)
        if area_sq_km is not None and area_sq_km > 1000:
            # Skip dialog in headless mode (CI/automated execution)
            if os.environ.get("BLAZE_EXIT_AFTER_RUN") or parent_window is None:
                log(f"Large extent detected ({area_sq_km:,.0f} km²) - proceeding in headless mode")
            else:
                try:
                    from qgis.PyQt.QtWidgets import QMessageBox

                    msg = (
                        f"The map extent is about {area_sq_km:,.0f} km². "
                        "Generating magnetic north lines may take a long time. Continue?"
                    )
                    reply = QMessageBox.question(
                        parent_window,
                        "Large extent",
                        msg,
                        QMessageBox.Yes | QMessageBox.No,
                        QMessageBox.No,
                    )
                    if reply != QMessageBox.Yes:
                        add_mag_north = False
                        log("Magnetic north lines skipped - user declined for large extent")
                        summary["skipped"].append("Magnetic north lines (user declined)")
                except Exception as e:
                    log(f"Could not show extent confirmation: {e}")
        if add_mag_north:
            report_progress("Adding magnetic north lines...", 90)
            # Use combined_path if available, otherwise use a temp directory
            if use_current_extent:
                output_dir = Path(tempfile.gettempdir()) / "blaze_plugin"
                output_dir.mkdir(parents=True, exist_ok=True)
                # Make filename unique to allow multiple calls

                timestamp = int(time.time())
                north_lines_path = output_dir / f"magnetic_north_lines_{timestamp}.gpkg"
            else:
                north_lines_path = combined_path / "magnetic_north_lines.gpkg"
            # Line spacing: 4cm at 1:25000 scale = 1000m
            layer = add_magnetic_north_lines(project_extent, project_crs, north_lines_path, spacing=1000)
            if layer:
                summary["loaded"].append("Magnetic north lines")
                # Make layer name unique if a layer with this name already exists
                layer_name = layer.name()
                existing_names = set()
                for child in markup_group.children():
                    try:
                        if child.nodeType() == 0:  # 0 = Layer node type
                            existing_layer = child.layer()
                            if existing_layer:
                                existing_names.add(existing_layer.name())
                    except (AttributeError, TypeError):
                        continue
                if layer_name in existing_names:
                    layer.setName(f"{layer_name} ({int(time.time())})")
                markup_group.addLayer(layer)
            else:
                summary["failed"].append("Magnetic north lines")
    elif add_mag_north:
        log("Magnetic north lines skipped - project extent or CRS not available")
        summary["skipped"].append("Magnetic north lines (no extent/CRS)")
    # Add controls layer with control point in center of map
    if add_controls and project_extent and project_crs:
        report_progress("Adding controls layer...", 92)
        # Use combined_path if available, otherwise use a temp directory
        if use_current_extent:
            output_dir = Path(tempfile.gettempdir()) / "blaze_plugin"
            output_dir.mkdir(parents=True, exist_ok=True)
            # Make filename unique to allow multiple calls
            timestamp = int(time.time())
            controls_path = output_dir / f"controls_{timestamp}.gpkg"
        else:
            controls_path = combined_path / "controls.gpkg"
        layer = add_controls_layer(project_extent, project_crs, markup_group, controls_path)
        if layer:
            summary["loaded"].append("Controls layer")
            # Make layer name unique if a layer with this name already exists
            layer_name = layer.name()
            existing_names = set()
            for child in markup_group.children():
                try:
                    if child.nodeType() == 0:  # 0 = Layer node type
                        existing_layer = child.layer()
                        if existing_layer:
                            existing_names.add(existing_layer.name())
                except (AttributeError, TypeError):
                    continue
            if layer_name in existing_names:
                layer.setName(f"{layer_name} ({int(time.time())})")

    # Remove empty groups at the end (after all layers are added)
    # This ensures we only remove groups that are truly empty
    def remove_group_if_empty(group_node):
        """Safely remove a group if it has no children."""
        try:
            if group_node and len(group_node.children()) == 0:
                parent = group_node.parent()
                if parent:
                    parent.removeChildNode(group_node)
                    return True
        except Exception as e:
            log(f"Error removing empty group: {e}")
        return False

    # Remove empty groups
    remove_group_if_empty(markup_group)
    remove_group_if_empty(topo_group)
    remove_group_if_empty(vector_group)
    remove_group_if_empty(raster_group)

    # Rotate map for magnetic north (works for both normal and current extent modes)
    # Skip in headless mode as mapCanvas operations may block
    if not os.environ.get("BLAZE_EXIT_AFTER_RUN"):
        try:
            from qgis.utils import iface

            if iface and iface.mapCanvas():
                # Rotate map so magnetic north is vertical (only if mag north enabled and available)
                if add_mag_north and gm_angle is not None:
                    # Positive gm_angle = magnetic north is east (clockwise) of grid north
                    # Rotate view clockwise (negative) to bring magnetic north up
                    iface.mapCanvas().setRotation(-gm_angle)
                    log(f"Rotated map {-gm_angle:.1f}° for magnetic north")
                    iface.mapCanvas().refresh()
        except Exception as e:
            log(f"Could not rotate map: {e}")

    # Zoom to vector layers extent (only if we have vector layers, not when using current extent)
    if zoom_to_extent and vector_extent and not vector_extent.isEmpty():
        vector_extent.scale(1.05)
        # Skip in headless mode as mapCanvas operations may block
        if not os.environ.get("BLAZE_EXIT_AFTER_RUN"):
            try:
                from qgis.utils import iface

                if iface and iface.mapCanvas():
                    iface.mapCanvas().setExtent(vector_extent)
                    log("Zoomed to vector layers")
                    iface.mapCanvas().refresh()
            except Exception:
                project.viewSettings().setDefaultViewExtent(QgsReferencedRectangle(vector_extent, project_crs))
                log("View extent set to vector layers")
        else:
            # In headless mode, just set the view extent without refreshing canvas
            project.viewSettings().setDefaultViewExtent(QgsReferencedRectangle(vector_extent, project_crs))
            log("View extent set to vector layers (headless mode)")

    # Save project if output_path is provided
    if output_path:
        output = Path(output_path)
        if output.suffix.lower() not in [".qgs", ".qgz"]:
            output = output.with_suffix(".qgz")

        if project.write(str(output)):
            log(f"Project saved: {output}")
        else:
            log("Error saving project")
            return False

    if use_current_extent:
        log("Added layers using current map extent")
    else:
        log("Blaze layers added to current project")

    log("create_qgis_project() completed successfully")
    return summary


def add_magnetic_north_lines(extent, crs, output_path, spacing=1000, margin=500):
    """
    Generates magnetic north lines directly to file (EPSG:4326) with a safety buffer.
    Requires the Compass Routes plugin to be installed.
    """
    from qgis import processing
    from qgis.core import (
        QgsApplication,
        QgsCoordinateReferenceSystem,
        QgsCoordinateTransform,
        QgsLineSymbol,
        QgsProject,
        QgsRectangle,
        QgsSingleSymbolRenderer,
        QgsVectorLayer,
    )

    # Check if Compass Routes plugin is available
    algo_id = "compassroutes:createmagneticnorth"
    registry = QgsApplication.processingRegistry()
    alg = registry.algorithmById(algo_id)

    if not alg:
        error_msg = (
            "Compass Routes plugin is not installed. "
            "Magnetic north lines require the Compass Routes plugin.\n\n"
            "To install:\n"
            "1. Go to Plugins > Manage and Install Plugins\n"
            "2. Search for 'Compass Routes'\n"
            "3. Click Install Plugin\n"
            "4. Restart QGIS and try again"
        )
        log(f"ERROR: {error_msg}")
        try:
            from qgis.core import Qgis, QgsMessageLog

            QgsMessageLog.logMessage(error_msg, "Blaze", Qgis.Critical)
        except Exception:
            pass
        return None

    # 1. Apply Buffer (in project units, usually meters)
    # We clone the extent first to avoid modifying the original object
    buffered_extent = QgsRectangle(extent)
    buffered_extent.grow(margin)

    # 2. Transform Extent to WGS84 (Plugin requirement)
    wgs84 = QgsCoordinateReferenceSystem("EPSG:4326")
    transform = QgsCoordinateTransform(crs, wgs84, QgsProject.instance())
    wgs84_extent = transform.transformBoundingBox(buffered_extent)

    # 3. Dynamic Parameter Setup
    param_names = [p.name() for p in alg.parameterDefinitions()] if alg else []
    out_param = "OutputLayer" if "OutputLayer" in param_names else "OUTPUT"

    # 4. Run Algorithm directly to file
    params = {
        "Extent": wgs84_extent,
        "Distance": spacing,
        "UnitsOfMeasure": 0,  # 0 = meters
        out_param: str(output_path),
    }

    try:
        processing.run(algo_id, params)
    except Exception as e:
        error_msg = f"Error running Compass Routes algorithm: {e}"
        log(f"ERROR: {error_msg}")
        try:
            from qgis.core import Qgis, QgsMessageLog

            QgsMessageLog.logMessage(error_msg, "Blaze", Qgis.Critical)
        except Exception:
            pass
        return None

    # 5. Load & Style
    layer = QgsVectorLayer(str(output_path), "Magnetic North Lines", "ogr")
    if layer.isValid():
        symbol = QgsLineSymbol.createSimple({"color": "#8B0000", "width": "0.15"})
        layer.setRenderer(QgsSingleSymbolRenderer(symbol))
        QgsProject.instance().addMapLayer(layer, False)
        return layer

    return None


def add_controls_layer(extent, crs, group, output_path):
    """Add a controls layer with a control point in the center of the map extent."""
    from qgis.core import QgsCoordinateTransformContext, QgsVectorFileWriter

    # Calculate center point of the extent
    center_x = (extent.xMinimum() + extent.xMaximum()) / 2
    center_y = (extent.yMinimum() + extent.yMaximum()) / 2
    center_point = QgsPointXY(center_x, center_y)

    # Create a feature with the center point
    feat = QgsFeature()
    feat.setGeometry(QgsGeometry.fromPointXY(center_point))

    # Create memory layer
    mem_layer = QgsVectorLayer(f"Point?crs={crs.authid()}", "Controls", "memory")

    # Add fields matching the reference controls layer structure
    # name: String (10.0), description: String (80.0), gap: Integer, setting_name: String (19.0)
    fields = QgsFields()
    fields.append(QgsField("name", QVariant.String, len=10))
    fields.append(QgsField("description", QVariant.String, len=80))
    fields.append(QgsField("gap", QVariant.Int))
    fields.append(QgsField("setting_name", QVariant.String, len=19))
    mem_layer.dataProvider().addAttributes(fields)
    mem_layer.updateFields()

    # Set feature attributes
    feat.setAttributes(["Control 1", "Control point at map center", None, "100"])
    mem_layer.dataProvider().addFeatures([feat])
    mem_layer.updateExtents()

    # Save to GeoPackage
    options = QgsVectorFileWriter.SaveVectorOptions()
    options.driverName = "GPKG"
    error = QgsVectorFileWriter.writeAsVectorFormatV3(
        mem_layer, str(output_path), QgsCoordinateTransformContext(), options
    )

    if error[0] != QgsVectorFileWriter.NoError:
        log(f"Error saving controls layer: {error}")
        return None

    # Load saved layer
    layer = QgsVectorLayer(str(output_path), "Controls", "ogr")
    if not layer.isValid():
        log("Failed to load controls layer")
        return None

    # Apply Controls.qml style
    qml_path = STYLES_DIR / "Controls.qml"
    if qml_path.exists():
        layer.loadNamedStyle(str(qml_path))
        layer.triggerRepaint()
        log("Applied style: Controls.qml")
    else:
        log(f"Warning: Controls.qml not found at {qml_path}, using default style")

    QgsProject.instance().addMapLayer(layer, False)
    group.addLayer(layer)
    log(f"Added: Controls layer (1 control point at center: {center_x:.1f}, {center_y:.1f})")
    return layer


def add_nsw_topo_layers(
    group, extent, crs, output_dir, progress_callback=None, log_func=None, gpkg_output_path=None, parent_window=None
):
    """Download NSW topographic vector layers and save to files.

    Args:
        gpkg_output_path: Optional path for GPKG file. If None, uses output_dir/nsw_topo.gpkg
        parent_window: Optional parent window for dialogs
    """
    import json
    import urllib.error
    import urllib.request

    from qgis.core import QgsCoordinateReferenceSystem, QgsCoordinateTransform, QgsField, QgsFields

    def local_log(message):
        """Log with optional callback support."""
        log(message)  # Use module-level log
        if log_func and log_func is not log:  # Avoid double-logging if log_func is the same as log
            log_func(message)

    def report_progress(message, percent=None):
        local_log(message)
        if progress_callback:
            progress_callback(message, percent)

    wgs84 = QgsCoordinateReferenceSystem("EPSG:4326")
    transform_to_wgs84 = QgsCoordinateTransform(crs, wgs84, QgsProject.instance())
    transform_from_wgs84 = QgsCoordinateTransform(wgs84, crs, QgsProject.instance())

    # Add 500m margin to extent before transforming to WGS84
    from qgis.core import QgsRectangle

    extent_with_margin = QgsRectangle(extent)
    extent_with_margin.grow(500)  # 500m margin
    wgs84_extent = transform_to_wgs84.transformBoundingBox(extent_with_margin)

    log(
        f"NSW Topo: Input extent ({crs.authid()}): "
        f"{extent.xMinimum():.1f}, {extent.yMinimum():.1f} to "
        f"{extent.xMaximum():.1f}, {extent.yMaximum():.1f}"
    )
    log(
        f"NSW Topo: WGS84 extent: "
        f"{wgs84_extent.xMinimum():.6f}, {wgs84_extent.yMinimum():.6f} to "
        f"{wgs84_extent.xMaximum():.6f}, {wgs84_extent.yMaximum():.6f}"
    )

    # Create a buffered extent (original extent + 10km buffer) for cropping
    # Buffer of 10km in meters
    buffer_meters = 10000
    buffered_extent = QgsRectangle(extent)
    buffered_extent.grow(buffer_meters)

    # Create a rectangle geometry from the buffered extent for clipping
    clip_rect = QgsGeometry.fromRect(buffered_extent)

    log(f"NSW Topo: Cropping features to within {buffer_meters/1000:.1f}km of original extent")
    log(
        f"NSW Topo: Buffered extent: "
        f"{buffered_extent.xMinimum():.1f}, {buffered_extent.yMinimum():.1f} to "
        f"{buffered_extent.xMaximum():.1f}, {buffered_extent.yMaximum():.1f}"
    )

    bbox = f"{wgs84_extent.xMinimum()},{wgs84_extent.yMinimum()},{wgs84_extent.xMaximum()},{wgs84_extent.yMaximum()}"

    # NSW topo layers from NSWTopo.qgz - comprehensive list
    # Format: (service_path, name, visible)
    base_url = "https://portal.spatial.nsw.gov.au/server/rest/services"
    layers = [
        # Elevation
        (f"{base_url}/NSW_Elevation_and_Depth_Theme/MapServer/0", "SpotHeight", True),
        (f"{base_url}/NSW_Elevation_and_Depth_Theme/MapServer/1", "RelativeHeight", False),
        # Transport
        (f"{base_url}/NSW_Transport_Theme/MapServer/9", "ClassifiedFireTrail", False),
        (f"{base_url}/NSW_Transport_Theme/MapServer/2", "Crossing", True),
        (f"{base_url}/NSW_Transport_Theme/MapServer/7", "Railway", True),
        (f"{base_url}/NSW_Transport_Theme/MapServer/5", "RoadSegment", True),
        (f"{base_url}/NSW_Transport_Theme/MapServer/6", "RoadNameExtent", True),
        (f"{base_url}/NSW_Transport_Theme/MapServer/4", "Runway", False),
        (f"{base_url}/NSW_Transport_Theme/MapServer/1", "TrafficControlDevice", True),
        # Features of Interest
        (f"{base_url}/NSW_Features_of_Interest_Category/MapServer/3", "BuildingComplexPoint", True),
        (f"{base_url}/NSW_Features_of_Interest_Category/MapServer/6", "ElectricityTransmissionLine", True),
        (f"{base_url}/NSW_Features_of_Interest_Category/MapServer/2", "GeneralCulturalPoint", True),
        (f"{base_url}/NSW_Features_of_Interest_Category/MapServer/5", "GeneralCulturalLine", True),
        (f"{base_url}/NSW_Features_of_Interest_Category/MapServer/0", "TankPoint", True),
        (f"{base_url}/NSW_Features_of_Interest_Category/MapServer/1", "PlacePoint", True),
        (f"{base_url}/NSW_Features_of_Interest_Category/MapServer/4", "UtilityWaterSupplyCanal", True),
        # Administrative
        (f"{base_url}/NSW_Administrative_Boundaries_Theme/MapServer/6", "NPWSReserve", True),
        (f"{base_url}/NSW_Administrative_Boundaries_Theme/MapServer/3", "StateForest", True),
        # Land/Property
        (f"{base_url}/NSW_Land_Parcel_Property_Theme/MapServer/12", "Property", False),
        # Cadastre (from maps.six.nsw.gov.au)
        ("https://maps.six.nsw.gov.au/arcgis/rest/services/public/NSW_Cadastre/MapServer/9", "CadastreLot", True),
        # Physiography
        (f"{base_url}/NSW_Physiography_Category/MapServer/2", "FuzzyExtentLine", True),
        (f"{base_url}/NSW_Physiography_Category/MapServer/4", "FuzzyExtentArea", False),
        (f"{base_url}/NSW_Physiography_Category/MapServer/1", "DLSPoint", True),
        (f"{base_url}/NSW_Physiography_Category/MapServer/3", "DLSLine", True),
        (f"{base_url}/NSW_Physiography_Category/MapServer/5", "DLSArea", True),
        # Water
        (f"{base_url}/NSW_Water_Theme/MapServer/2", "NamedWatercourse", True),
        (f"{base_url}/NSW_Water_Theme/MapServer/0", "HydroPoint", True),
        (f"{base_url}/NSW_Water_Theme/MapServer/6", "HydroArea", True),
        (f"{base_url}/NSW_Water_Theme/MapServer/5", "HydroLine", False),
        (f"{base_url}/NSW_Water_Theme/MapServer/3", "FuzzyExtentWaterLine", True),
        (f"{base_url}/NSW_Water_Theme/MapServer/7", "FuzzyExtentWaterArea", False),
        (f"{base_url}/NSW_Water_Theme/MapServer/4", "Coastline", True),
        (f"{base_url}/NSW_Water_Theme/MapServer/1", "AncillaryHydroPoint", True),
        # Features of Interest (moved to bottom for rendering order)
        (f"{base_url}/NSW_Features_of_Interest_Category/MapServer/9", "GeneralCulturalArea", True),
    ]

    # Create or re-use GPKG file for all NSW topo data
    if gpkg_output_path:
        gpkg_path = Path(gpkg_output_path)
    else:
        gpkg_path = output_dir / "nsw_topo.gpkg"

    # Initialise result tracker early so early returns can use it
    topo_results = {
        "with_data": [],
        "empty": [],
        "failed": [],
        "network_errors": [],
        "total_dupes_skipped": 0,
        "dedup_active": False,
    }

    driver = ogr.GetDriverByName("GPKG")
    if driver is None:
        log("ERROR: GPKG driver not available!")
        return topo_results

    # If GPKG already exists, ask user what to do
    existing_layer_names = set()
    reuse_existing = False
    skip_dedup = False  # "Keep all" mode — append without checking duplicates

    if gpkg_path.exists():
        # Check what layers already exist
        existing_ds = driver.Open(str(gpkg_path), 0)  # read-only
        if existing_ds:
            existing_layer_names = {
                existing_ds.GetLayerByIndex(i).GetName() for i in range(existing_ds.GetLayerCount())
            }
            existing_ds = None

        if existing_layer_names and parent_window and not os.environ.get("BLAZE_EXIT_AFTER_RUN"):
            try:
                from qgis.PyQt.QtWidgets import QMessageBox

                msg = (
                    f"{gpkg_path.name} already exists with {len(existing_layer_names)} layers.\n\n"
                    "• Update without duplicates — download and skip existing features\n"
                    "• Download and keep all — append all features (may create duplicates)\n"
                    "• Delete and re-download — remove existing file and start fresh"
                )
                box = QMessageBox(parent_window)
                box.setWindowTitle("Existing topo data found")
                box.setText(msg)
                update_btn = box.addButton("Update without duplicates", QMessageBox.AcceptRole)
                keep_all_btn = box.addButton("Download and keep all", QMessageBox.ActionRole)
                box.addButton("Delete and re-download", QMessageBox.DestructiveRole)
                box.setDefaultButton(update_btn)
                box.exec_()

                clicked = box.clickedButton()
                if clicked == update_btn:
                    reuse_existing = True
                    log(f"Updating {gpkg_path.name} without duplicates ({len(existing_layer_names)} existing layers)")
                elif clicked == keep_all_btn:
                    reuse_existing = True
                    skip_dedup = True
                    log(f"Appending to {gpkg_path.name} (keeping all, no dedup)")
                else:
                    reuse_existing = False
            except Exception as e:
                log(f"Could not show GPKG dialog: {e}")

        if not reuse_existing:
            try:
                for suffix in ["", "-wal", "-shm"]:
                    p = Path(str(gpkg_path) + suffix)
                    if p.exists():
                        p.unlink()
                existing_layer_names = set()
                log(f"Removed existing {gpkg_path.name}")
            except OSError as e:
                log(f"WARNING: Could not delete existing {gpkg_path.name}: {e}")

    # Open existing or create new GPKG
    if reuse_existing and gpkg_path.exists():
        ds = driver.Open(str(gpkg_path), 1)  # update mode
        if ds is None:
            log(f"WARNING: Could not open existing {gpkg_path.name}, creating new one")
            ds = driver.CreateDataSource(str(gpkg_path))
            existing_layer_names = set()
    else:
        ds = driver.CreateDataSource(str(gpkg_path))

    if ds is None:
        log(f"ERROR: Could not create GPKG at {gpkg_path}")
        return topo_results

    total_layers = len(layers)
    layers_with_data = 0
    total_features = 0

    # Update dedup_active now that reuse_existing / skip_dedup are resolved
    topo_results["dedup_active"] = reuse_existing and not skip_dedup

    log(f"NSW Topo: Querying bbox={bbox}")

    for idx, (service_url, name, visible) in enumerate(layers):
        try:
            # Progress: 50-85% for downloading
            percent = 50 + int((idx / total_layers) * 35)
            report_progress(f"Downloading {name}... ({idx+1}/{total_layers})", percent)

            # Fetch all features with pagination
            # (ArcGIS typically limits to 1000-2000 per request)
            all_features = []
            offset = 0
            page_size = 1000  # Request this many at a time
            max_pages = 1000  # Safety limit
            download_error = None

            while True:
                url = (
                    f"{service_url}/query?"
                    f"geometry={bbox}&geometryType=esriGeometryEnvelope&"
                    f"inSR=4326&outSR=4326&"
                    f"spatialRel=esriSpatialRelIntersects&"
                    f"outFields=*&f=geojson&"
                    f"resultRecordCount={page_size}&resultOffset={offset}"
                )

                # Log full URL for first layer, first page
                if idx == 0 and offset == 0:
                    log(f"First URL: {url}")

                try:
                    with urllib.request.urlopen(url, timeout=60) as response:
                        raw = response.read().decode()
                        data = json.loads(raw)
                except urllib.error.URLError as e:
                    download_error = str(e)
                    log(f"Network error for {name}: {e}")
                    break
                except json.JSONDecodeError as e:
                    download_error = f"Invalid JSON: {e}"
                    log(f"Invalid JSON response for {name}: {e}")
                    break
                except Exception as e:
                    download_error = f"{type(e).__name__}: {e}"
                    log(f"Unexpected error for {name}: {download_error}")
                    break

                # Check for API errors
                if "error" in data:
                    err = data["error"]
                    download_error = f"API error {err.get('code')}: {err.get('message')}"
                    log(f"API error for {name}: code={err.get('code')}, message={err.get('message')}")
                    break

                page_features = data.get("features", [])
                all_features.extend(page_features)

                # Check if there are more features (exceeded transfer limit)
                exceeded_limit = data.get("exceededTransferLimit", False) or data.get("properties", {}).get(
                    "exceededTransferLimit", False
                )

                if len(page_features) < page_size or not exceeded_limit:
                    # No more pages
                    break

                offset += len(page_features)

                # Safety limit check
                if offset // page_size >= max_pages:
                    log(f"  Reached max pages for {name}, stopping at {len(all_features)} features")
                    break

            # Track network/server errors separately from genuinely empty layers
            if download_error and not all_features:
                # Use the base service URL (without query params) for cleaner display
                topo_results["network_errors"].append((name, service_url))
                continue

            features = all_features

            if offset > 0:
                log(f"{name}: {len(features)} features (paginated)")
            else:
                log(f"{name}: {len(features)} features")

            if not features:
                topo_results["empty"].append(name)
                continue

            layers_with_data += 1
            total_features += len(features)

            # Detect geometry type from first feature
            first_geom = features[0].get("geometry", {})
            geojson_geom_type = first_geom.get("type", "Point")
            # Map GeoJSON types to QGIS WKT types
            geom_type_map = {
                "Point": "Point",
                "MultiPoint": "MultiPoint",
                "LineString": "LineString",
                "MultiLineString": "MultiLineString",
                "Polygon": "Polygon",
                "MultiPolygon": "MultiPolygon",
            }
            qgis_geom_type = geom_type_map.get(geojson_geom_type, "Point")
            log(f"Geometry type for {name}: {geojson_geom_type} -> {qgis_geom_type}")

            # Build fields from first feature's properties
            fields = QgsFields()
            sample_props = features[0].get("properties", {})
            for key, val in sample_props.items():
                if isinstance(val, int):
                    fields.append(QgsField(key, QVariant.Int))
                elif isinstance(val, float):
                    fields.append(QgsField(key, QVariant.Double))
                else:
                    fields.append(QgsField(key, QVariant.String))

            # Create memory layer with detected geometry type
            mem_layer = QgsVectorLayer(f"{qgis_geom_type}?crs={crs.authid()}", name, "memory")
            provider = mem_layer.dataProvider()
            provider.addAttributes(fields)
            mem_layer.updateFields()

            # Add features with attributes
            qgs_features = []
            geom_types_seen = set()
            failed_geoms = 0
            cropped_count = 0
            skipped_outside_count = 0
            for idx, feat in enumerate(features):
                geom = feat.get("geometry")
                props = feat.get("properties", {})
                if not geom:
                    continue

                geom_types_seen.add(geom.get("type"))

                qgs_feat = QgsFeature(fields)

                # Set attributes
                for i, field in enumerate(fields):
                    val = props.get(field.name())
                    if val is not None:
                        qgs_feat.setAttribute(i, val)

                geom_created = convert_geojson_geom(geom, transform_from_wgs84)
                if geom_created and not geom_created.isEmpty():
                    # Crop geometry to buffered extent (10km beyond original extent)
                    if geom_created.intersects(clip_rect):
                        # Check if geometry extends beyond buffered extent
                        geom_extent = geom_created.boundingBox()
                        needs_clipping = (
                            geom_extent.xMinimum() < buffered_extent.xMinimum()
                            or geom_extent.xMaximum() > buffered_extent.xMaximum()
                            or geom_extent.yMinimum() < buffered_extent.yMinimum()
                            or geom_extent.yMaximum() > buffered_extent.yMaximum()
                        )

                        if needs_clipping:
                            # Clip the geometry to the buffered extent
                            clipped_geom = geom_created.intersection(clip_rect)
                            if clipped_geom and not clipped_geom.isEmpty():
                                qgs_feat.setGeometry(clipped_geom)
                                qgs_features.append(qgs_feat)
                                cropped_count += 1
                            # else: geometry was completely outside buffered extent after clipping, skip
                        else:
                            # Geometry is within buffered extent, no clipping needed
                            qgs_feat.setGeometry(geom_created)
                            qgs_features.append(qgs_feat)
                    else:
                        # Geometry doesn't intersect buffered extent, skip
                        skipped_outside_count += 1
                else:
                    failed_geoms += 1
                    if idx == 0:
                        log(f"First feature failed! geom_created={geom_created}")

            log(
                f"Geometry types in data: {geom_types_seen}, "
                f"valid: {len(qgs_features)}, failed: {failed_geoms}, "
                f"cropped: {cropped_count}, skipped (outside): "
                f"{skipped_outside_count}"
            )

            if not qgs_features:
                log(f"No valid features for {name}")
                continue

            # Add layer to shared GPKG
            from osgeo import osr

            ogr_geom_types = {
                "Point": ogr.wkbPoint,
                "MultiPoint": ogr.wkbMultiPoint,
                "LineString": ogr.wkbLineString,
                "MultiLineString": ogr.wkbMultiLineString,
                "Polygon": ogr.wkbPolygon,
                "MultiPolygon": ogr.wkbMultiPolygon,
            }
            ogr_geom_type = ogr_geom_types.get(qgis_geom_type, ogr.wkbUnknown)

            srs = osr.SpatialReference()
            srs.ImportFromWkt(crs.toWkt())

            # Get or create layer in GPKG
            ogr_layer = ds.GetLayerByName(name)
            is_existing_layer = ogr_layer is not None

            if ogr_layer is None:
                ogr_layer = ds.CreateLayer(name, srs, ogr_geom_type)
                if ogr_layer is None:
                    log(f"ERROR: Could not create OGR layer for {name}")
                    continue

                # Add fields to new layer
                for field in fields:
                    if field.type() == QVariant.Int:
                        ogr_layer.CreateField(ogr.FieldDefn(field.name(), ogr.OFTInteger64))
                    elif field.type() == QVariant.Double:
                        ogr_layer.CreateField(ogr.FieldDefn(field.name(), ogr.OFTReal))
                    else:
                        fld = ogr.FieldDefn(field.name(), ogr.OFTString)
                        fld.SetWidth(254)
                        ogr_layer.CreateField(fld)

            # Build set of existing feature fingerprints for dedup
            existing_fingerprints = set()
            oid_field_idx = None

            if is_existing_layer and not skip_dedup:
                # Find a unique ID field (OBJECTID is standard for ArcGIS services)
                layer_defn = ogr_layer.GetLayerDefn()
                field_names_in_layer = [layer_defn.GetFieldDefn(i).GetName() for i in range(layer_defn.GetFieldCount())]

                # Use OBJECTID if available (reliable unique key from ArcGIS)
                oid_field = None
                for candidate in ["OBJECTID", "objectid", "ObjectID", "FID"]:
                    if candidate in field_names_in_layer:
                        oid_field = candidate
                        break

                ogr_layer.ResetReading()
                for existing_feat in ogr_layer:
                    if oid_field:
                        oid_val = existing_feat.GetField(oid_field)
                        if oid_val is not None:
                            existing_fingerprints.add(str(oid_val))
                    else:
                        # Fallback: fingerprint from all attribute values as strings
                        fp_parts = []
                        for fn in field_names_in_layer:
                            val = existing_feat.GetField(fn)
                            fp_parts.append(str(val) if val is not None else "")
                        existing_fingerprints.add(tuple(fp_parts))
                ogr_layer.ResetReading()

                if existing_fingerprints:
                    key_type = "OBJECTID" if oid_field else "attrs"
                    log(f"  {name}: {len(existing_fingerprints)} existing features for dedup (key={key_type})")

                # Find OID field index in new features
                for i, field in enumerate(fields):
                    if field.name() in ("OBJECTID", "objectid", "ObjectID", "FID"):
                        oid_field_idx = i
                        break

            # Write features (skipping duplicates when dedup is active)
            saved_count = 0
            skipped_count = 0
            for qf in qgs_features:
                geom = qf.geometry()
                if not geom or geom.isEmpty():
                    continue

                # Check for duplicate
                if existing_fingerprints:
                    if oid_field_idx is not None:
                        oid_val = qf.attribute(oid_field_idx)
                        if oid_val is not None and str(oid_val) in existing_fingerprints:
                            skipped_count += 1
                            continue
                    else:
                        fp_parts = []
                        for i, field in enumerate(fields):
                            val = qf.attribute(i)
                            fp_parts.append(str(val) if val is not None else "")
                        if tuple(fp_parts) in existing_fingerprints:
                            skipped_count += 1
                            continue

                ogr_feat = ogr.Feature(ogr_layer.GetLayerDefn())
                ogr_geom = ogr.CreateGeometryFromWkt(geom.asWkt())
                ogr_feat.SetGeometry(ogr_geom)
                for i, field in enumerate(fields):
                    val = qf.attribute(i)
                    if val is not None:
                        ogr_feat.SetField(field.name(), val)
                if ogr_layer.CreateFeature(ogr_feat) == ogr.OGRERR_NONE:
                    saved_count += 1

            if skipped_count:
                log(f"Added {name}: {saved_count} new, {skipped_count} duplicates skipped")
                topo_results["total_dupes_skipped"] += skipped_count
            else:
                log(f"Added {name}: {saved_count} features")

            total_count = ogr_layer.GetFeatureCount()
            topo_results["with_data"].append((name, total_count, skipped_count))

        except Exception as e:
            import traceback

            log(f"Error loading {name}: {e}")
            traceback.print_exc()
            topo_results["failed"].append(name)

    # Close GPKG datasource to save
    ds = None

    log(f"NSW Topo Summary: {layers_with_data}/{total_layers} layers with data, {total_features} total features")
    log(f"NSW Topo GPKG saved to: {gpkg_path}")

    if layers_with_data == 0:
        log("WARNING: No NSW topo data was downloaded. Check network connectivity and bbox.")
        return topo_results

    report_progress("Adding NSW topo layers to map...", 88)

    # Now load all layers from the single GPKG and add to project
    gpkg_ds = ogr.Open(str(gpkg_path))
    if gpkg_ds:
        layer_count = gpkg_ds.GetLayerCount()
        log(f"Found {layer_count} layers in {gpkg_path.name}")
        layer_names = [gpkg_ds.GetLayerByIndex(i).GetName() for i in range(layer_count)]
        gpkg_ds = None

        layer_visibility = {name: visible for _, name, visible in layers}

        for layer_name in layer_names:

            uri = f"{gpkg_path}|layername={layer_name}"
            layer = QgsVectorLayer(uri, layer_name, "ogr")
            if layer.isValid():
                feat_count = layer.featureCount()
                # Apply QML style from to_qgis/styles
                qml_path = STYLES_DIR / f"{layer_name}.qml"
                # Fallback for CadastreLot to use cadastre.qml
                if layer_name == "CadastreLot" and not qml_path.exists():
                    qml_path = STYLES_DIR / "cadastre.qml"
                if qml_path.exists():
                    result = layer.loadNamedStyle(str(qml_path))
                    if result[1]:
                        log(f"Applied style: {qml_path.name}")
                else:
                    style_nsw_layer(layer, layer_name)

                # Special handling for GeneralCulturalArea: disable "Restricted Area" rule
                if layer_name == "GeneralCulturalArea":
                    from qgis.core import QgsRuleBasedRenderer

                    renderer = layer.renderer()
                    if isinstance(renderer, QgsRuleBasedRenderer):
                        root_rule = renderer.rootRule()

                        # Recursively find and disable "Restricted Area" rules
                        def disable_restricted_area_rules(rule):
                            if "Restricted Area" in rule.label() or "restricted area" in rule.label().lower():
                                rule.setActive(False)
                                log(f"  Disabled rule: {rule.label()}")
                            for child in rule.children():
                                disable_restricted_area_rules(child)

                        disable_restricted_area_rules(root_rule)
                        layer.triggerRepaint()

                QgsProject.instance().addMapLayer(layer, False)
                group.addLayer(layer)

                # Set visibility
                visible = layer_visibility.get(layer_name, True)
                layer_node = QgsProject.instance().layerTreeRoot().findLayer(layer.id())
                if layer_node:
                    layer_node.setItemVisibilityChecked(visible)

                log(f"Added layer: {layer_name} ({feat_count} features, visible={visible})")
            else:
                log(f"WARNING: Failed to load layer: {layer_name}")
    else:
        log(f"WARNING: Could not open GPKG file: {gpkg_path}")

    return topo_results


def convert_geojson_geom(geom, transform):
    """Convert GeoJSON geometry to QgsGeometry, applying coordinate transform."""
    gtype = geom.get("type")
    coords = geom.get("coordinates", [])

    try:
        if gtype == "Point":
            if len(coords) >= 2:
                pt = transform.transform(QgsPointXY(coords[0], coords[1]))
                return QgsGeometry.fromPointXY(pt)
        elif gtype == "MultiPoint":
            points = [transform.transform(QgsPointXY(c[0], c[1])) for c in coords if len(c) >= 2]
            if points:
                return QgsGeometry.fromMultiPointXY(points)
        elif gtype == "LineString":
            points = [transform.transform(QgsPointXY(c[0], c[1])) for c in coords if len(c) >= 2]
            if len(points) >= 2:
                return QgsGeometry.fromPolylineXY(points)
        elif gtype == "MultiLineString":
            lines = []
            for line in coords:
                points = [transform.transform(QgsPointXY(c[0], c[1])) for c in line if len(c) >= 2]
                if len(points) >= 2:
                    lines.append(points)
            if lines:
                return QgsGeometry.fromMultiPolylineXY(lines)
        elif gtype == "Polygon":
            rings = []
            for ring in coords:
                points = [transform.transform(QgsPointXY(c[0], c[1])) for c in ring if len(c) >= 2]
                if len(points) >= 3:
                    rings.append(points)
            if rings:
                return QgsGeometry.fromPolygonXY(rings)
        elif gtype == "MultiPolygon":
            polys = []
            for poly in coords:
                rings = []
                for ring in poly:
                    points = [transform.transform(QgsPointXY(c[0], c[1])) for c in ring if len(c) >= 2]
                    if len(points) >= 3:
                        rings.append(points)
                if rings:
                    polys.append(rings)
            if polys:
                return QgsGeometry.fromMultiPolygonXY(polys)
    except Exception as e:
        log(f"    Geometry conversion error ({gtype}): {e}")
    return None


def try_apply_qml_style(layer, name, styles_dir=None, is_nsw_layer=False):
    """Try to apply a QML style file to a layer. Returns True if successful."""
    if styles_dir is None:
        styles_dir = STYLES_DIR

    if not styles_dir.exists():
        return False

    # Try exact name match first
    qml_path = styles_dir / f"{name}.qml"
    if qml_path.exists():
        result = layer.loadNamedStyle(str(qml_path))
        if result[1]:
            log(f"    Applied style: {name}.qml")
            return True

    # Fallback mappings for common layers
    name_lower = name.lower()
    qml_mappings = {
        "roadsegment": "RoadSegment.qml",
        "road": "RoadSegment.qml",
        "spotheight": "SpotHeight.qml",
        "spot": "SpotHeight.qml",
        "property": "Property.qml",
        "magnetic": "MN.qml",
        "railway": "Railway.qml",
        "crossing": "Crossing.qml",
        "hydroline": "HydroLine.qml",
        "hydroarea": "HydroArea.qml",
        "hydropoint": "HydroPoint.qml",
        "npwsreserve": "NPWSReserve.qml",
        "stateforest": "StateForest.qml",
        "electricitytransmissionline": "ElectricityTransmissionLine.qml",
        "placepoint": "PlacePoint.qml",
        "tankpoint": "TankPoint.qml",
        "trafficcontroldevice": "TrafficControlDevice.qml",
        "dlspoint": "DLSPoint.qml",
        "dlsline": "DLSLine.qml",
        "dlsarea": "DLSArea.qml",
        "fuzzyextentline": "FuzzyExtentLine.qml",
        "fuzzyextentarea": "FuzzyExtentArea.qml",
        "fuzzyextentwaterline": "FuzzyExtentWaterLine.qml",
        "fuzzyextentwaterarea": "FuzzyExtentWaterArea.qml",
        "namedwatercourse": "NamedWatercourse.qml",
        "ancillaryhydropoint": "AncillaryHydroPoint.qml",
        "coastline": "Coastline.qml",
        "generalculturalpoint": "GeneralCulturalPoint.qml",
        "generalculturalline": "GeneralCulturalLine.qml",
        "generalculturalarea": "GeneralCulturalArea.qml",
        "buildingcomplexpoint": "BuildingComplexPoint.qml",
        "roadnameextent": "RoadNameExtent.qml",
        "contours": "contours.qml",
        "contour": "contours.qml",
        "streams": "streams.qml",
        "stream": "streams.qml",
    }

    for keyword, qml_file in qml_mappings.items():
        if keyword in name_lower:
            qml_path = styles_dir / qml_file
            if qml_path.exists():
                result = layer.loadNamedStyle(str(qml_path))
                if result[1]:
                    log(f"    Applied style: {qml_file}")
                    return True
    return False


def style_nsw_layer(layer, name):
    """Apply topographic styling to NSW layers. Try QML styles from styles folder."""
    # Try QML styles (NSW layers have correct attributes)
    if try_apply_qml_style(layer, name, is_nsw_layer=True):
        layer.triggerRepaint()


def style_vegetation(layer, filename):
    """Apply vegetation-specific styling. Try QML styles from styles folder."""
    name = filename.lower()

    if "smoothed_green" in name or name == "green.tif":
        # Try to load QML style (scrubby_vege.qml for smoothed_green)
        if "smoothed_green" in name:
            qml_path = STYLES_DIR / "scrubby_vege.qml"
            if qml_path.exists():
                result = layer.loadNamedStyle(str(qml_path))
                if result[1]:
                    log("Applied style: scrubby_vege.qml")
                    layer.triggerRepaint()
                    return

    elif "smoothed_canopy" in name or name == "canopy.tif":
        # Try to load QML style (canopy.qml)
        qml_path = STYLES_DIR / "canopy.qml"
        if qml_path.exists():
            result = layer.loadNamedStyle(str(qml_path))
            if result[1]:
                log("Applied style: canopy.qml")
                layer.triggerRepaint()
                return


def add_merged_gpkg_layer(gpkg_path, name, group, crs_override, output_gpkg):
    """Load all layers from a GeoPackage and merge into a single layer."""
    from qgis.core import QgsFeature, QgsVectorLayer

    ds = ogr.Open(str(gpkg_path))
    if ds is None:
        log(f"Could not open: {gpkg_path}")
        return None

    layer_names = [ds.GetLayerByIndex(i).GetName() for i in range(ds.GetLayerCount())]
    ds = None

    log(f"GPKG {gpkg_path.name}: merging {len(layer_names)} layers into '{name}'")

    # Create a memory layer with the geometry type from the first layer
    first_uri = f"{gpkg_path}|layername={layer_names[0]}"
    first_layer = QgsVectorLayer(first_uri, "temp", "ogr")
    if not first_layer.isValid():
        log(f"Could not load first layer from {gpkg_path}")
        return None

    # Get geometry type and CRS
    geom_type = first_layer.geometryType()
    geom_type_str = {0: "Point", 1: "LineString", 2: "Polygon"}.get(geom_type, "LineString")
    crs = crs_override if crs_override and crs_override.isValid() else first_layer.crs()

    # Create merged memory layer
    merged_layer = QgsVectorLayer(f"{geom_type_str}?crs={crs.authid()}", name, "memory")
    provider = merged_layer.dataProvider()

    # Copy fields from first layer, excluding 'fid' which is the GeoPackage
    # auto-generated primary key. Including it causes UNIQUE constraint failures
    # when merging multiple layers that each have their own fid sequences.
    provider.addAttributes([f for f in first_layer.fields() if f.name() != "fid"])
    merged_layer.updateFields()

    # Add features from all layers
    total_features = 0
    for layer_name in layer_names:
        uri = f"{gpkg_path}|layername={layer_name}"
        src_layer = QgsVectorLayer(uri, layer_name, "ogr")
        if src_layer.isValid():
            features = []
            for feat in src_layer.getFeatures():
                new_feat = QgsFeature(merged_layer.fields())
                new_feat.setGeometry(feat.geometry())
                # Copy attributes that exist in both
                for field in src_layer.fields():
                    if merged_layer.fields().indexOf(field.name()) >= 0:
                        new_feat.setAttribute(field.name(), feat.attribute(field.name()))
                features.append(new_feat)
            provider.addFeatures(features)
            total_features += len(features)

    merged_layer.updateExtents()
    log(f"  Merged {total_features} features from {len(layer_names)} layers")

    # Save merged layer to disk as GeoPackage using QgsVectorFileWriter.
    # Write to a temp file first, then move to the target path to avoid
    # file-locking issues with existing files on Windows.
    import shutil

    from qgis.core import QgsCoordinateTransformContext, QgsVectorFileWriter

    output_gpkg_path = Path(output_gpkg)
    output_gpkg_path.parent.mkdir(parents=True, exist_ok=True)

    # Write to a temp file first
    tmp_fd, tmp_path = tempfile.mkstemp(suffix=".gpkg")
    os.close(tmp_fd)
    os.unlink(tmp_path)  # QgsVectorFileWriter creates the file itself

    options = QgsVectorFileWriter.SaveVectorOptions()
    options.driverName = "GPKG"
    options.layerName = name

    error, error_msg = QgsVectorFileWriter.writeAsVectorFormatV3(
        merged_layer, tmp_path, QgsCoordinateTransformContext(), options
    )[:2]

    if error != QgsVectorFileWriter.NoError:
        log(f"  Failed to write GeoPackage: {error_msg}")
        try:
            os.unlink(tmp_path)
        except OSError:
            pass
        QgsProject.instance().addMapLayer(merged_layer, False)
        group.addLayer(merged_layer)
        log(f"Added (temporary): {name}")
        return merged_layer

    # Move temp file to target path
    try:
        for suffix in ["", "-wal", "-shm"]:
            target = Path(str(output_gpkg_path) + suffix)
            if target.exists():
                target.unlink()
        shutil.move(tmp_path, str(output_gpkg_path))
    except OSError as e:
        log(f"  Could not move to {output_gpkg_path.name}: {e}, loading from temp file")
        output_gpkg_path = Path(tmp_path)

    # Load the permanent layer from the saved GeoPackage
    load_path = str(output_gpkg_path)
    permanent_layer = QgsVectorLayer(f"{load_path}|layername={name}", name, "ogr")
    if not permanent_layer.isValid():
        log(f"Failed to load saved {output_gpkg_path.name}, using temporary layer")
        QgsProject.instance().addMapLayer(merged_layer, False)
        group.addLayer(merged_layer)
        return merged_layer

    QgsProject.instance().addMapLayer(permanent_layer, False)
    group.addLayer(permanent_layer)
    return permanent_layer


def add_gpkg_layers(gpkg_path, group, crs_override, root, apply_default_style=True):
    """Add all layers from a GeoPackage file. Returns list of added layers."""
    gpkg_path_obj = Path(gpkg_path)
    if not gpkg_path_obj.exists():
        log(f"GeoPackage file does not exist: {gpkg_path}")
        return []

    if gpkg_path_obj.stat().st_size == 0:
        log(f"GeoPackage file is empty: {gpkg_path}")
        return []

    try:
        ds = ogr.Open(str(gpkg_path))
        if ds is None:
            log(f"Could not open GeoPackage (file may be corrupted or invalid format): {gpkg_path}")
            return []
    except (RuntimeError, Exception) as e:
        log(f"Error opening GeoPackage (file may be corrupted, empty, or invalid): {gpkg_path} - {e}")
        return []

    layer_names = [ds.GetLayerByIndex(i).GetName() for i in range(ds.GetLayerCount())]
    ds = None

    if not layer_names:
        log(f"GeoPackage has no layers: {gpkg_path}")
        return []

    log(f"GPKG {gpkg_path_obj.name}: {layer_names}")

    layers = []
    for layer_name in layer_names:
        uri = f"{gpkg_path}|layername={layer_name}"

        layer = add_vector(uri, layer_name, group, crs_override)
        if layer:
            if apply_default_style:
                # Try to apply QML style from styles folder
                if try_apply_qml_style(layer, layer_name, is_nsw_layer=False):
                    layer.triggerRepaint()
            layers.append(layer)
    return layers


def build_raster_pyramids(raster_path):
    """Build tile pyramids (overviews) for a raster to improve visualization performance."""
    try:
        from osgeo import gdal

        # Explicitly set GDAL exception handling to avoid FutureWarning
        gdal.UseExceptions()

        # Check if pyramids already exist
        ds = gdal.Open(str(raster_path), gdal.GA_ReadOnly)
        if ds is None:
            return False

        # Check if overviews already exist
        band = ds.GetRasterBand(1)
        if band.GetOverviewCount() > 0:
            ds = None
            return True  # Already has pyramids
        ds = None

        # Build pyramids - use LZW compression and AVERAGE resampling
        ds = gdal.Open(str(raster_path), gdal.GA_Update)
        if ds is None:
            # Try read-only and build external .ovr file
            ds = gdal.Open(str(raster_path), gdal.GA_ReadOnly)
            if ds is None:
                return False

        # Overview levels: 2, 4, 8, 16, 32
        overview_levels = [2, 4, 8, 16, 32]

        # Build overviews with AVERAGE resampling (good for continuous data like DEMs)
        gdal.SetConfigOption("COMPRESS_OVERVIEW", "LZW")
        result = ds.BuildOverviews("AVERAGE", overview_levels)
        ds = None

        if result == 0:
            log(f"  Built pyramids for: {raster_path.name}")
            return True
        else:
            log(f"  Failed to build pyramids for: {raster_path.name}")
            return False
    except Exception as e:
        log(f"  Pyramid error for {raster_path.name}: {e}")
        return False


def infer_crs_from_description(description):
    """Try to infer proper CRS from description string.

    Examples: "GDA2020 / MGA 55S" -> EPSG:7855, "MGA55S" -> EPSG:7855
    """
    import re

    if not description:
        return None

    # Look for MGA zone patterns (handles both "MGA 55S" and "MGA55S")
    mga_match = re.search(r"MGA\s*(\d+)\s*([NS])", description, re.IGNORECASE)
    if mga_match:
        zone = int(mga_match.group(1))
        hemisphere = mga_match.group(2).upper()

        # GDA2020 MGA zones: EPSG codes 7848-7858 for zones 48-58 (South)
        # MGA 48S = EPSG:7848, MGA 55S = EPSG:7855, etc.
        # Formula: EPSG = 7800 + zone
        if 48 <= zone <= 58:
            epsg = 7800 + zone  # MGA 55S = 7800 + 55 = 7855 ✓
            log(f"  Inferred GDA2020 MGA Zone {zone}{hemisphere} from description -> EPSG:{epsg}")
            return epsg

    # Look for UTM zone patterns
    utm_match = re.search(r"UTM\s+Zone\s+(\d+)\s*([NS])", description, re.IGNORECASE)
    if utm_match:
        zone = int(utm_match.group(1))
        hemisphere = utm_match.group(2).upper()
        # UTM zones: EPSG:32701-32760 (South), EPSG:32601-32660 (North)
        if 1 <= zone <= 60:
            if hemisphere == "S":
                epsg = 32700 + zone
            else:
                epsg = 32600 + zone
            log(f"  Inferred UTM Zone {zone}{hemisphere} from description -> EPSG:{epsg}")
            return epsg

    return None


def add_raster(path, group, prefix="", build_pyramids=True):
    """Add a raster layer and optionally build pyramids for performance."""
    if not path.exists():
        return None
    name = prefix + path.stem

    # Build pyramids before loading
    if build_pyramids:
        build_raster_pyramids(path)

    layer = QgsRasterLayer(str(path), name)
    if not layer.isValid():
        log(f"  ⚠ Failed to load raster: {name}")
        return None

    crs = layer.crs()

    # If CRS is valid but has no authid, try to infer from description
    if crs.isValid() and not crs.authid():
        description = crs.description()
        inferred_epsg = infer_crs_from_description(description)
        if inferred_epsg:
            from qgis.core import QgsCoordinateReferenceSystem

            inferred_crs = QgsCoordinateReferenceSystem()
            if inferred_crs.createFromId(inferred_epsg):
                layer.setCrs(inferred_crs)
                log(f"  Inferred CRS from description for {name}: EPSG:{inferred_epsg}")
            else:
                log(f"  Failed to create CRS from inferred EPSG:{inferred_epsg}")
    elif not crs.isValid():
        log(f"  ⚠ Warning: No valid CRS found for {name}")

    QgsProject.instance().addMapLayer(layer, False)
    group.addLayer(layer)
    log(f"Added: {name}")
    return layer


def add_vector(uri, name, group, crs_override=None):
    """Add a vector layer."""
    layer = QgsVectorLayer(uri, name, "ogr")
    if layer.isValid():
        if crs_override and crs_override.isValid():
            layer.setCrs(crs_override)
        QgsProject.instance().addMapLayer(layer, False)
        group.addLayer(layer)
        log(f"Added: {name}")
        return layer
    return None


def main():
    """Command line entry point."""
    # Check environment variable first (for QGIS --code usage where args after -- aren't passed)
    combined_dir = os.environ.get("BLAZE_COMBINED_DIR")
    output_path = os.environ.get("BLAZE_OUTPUT_PATH")

    # Fall back to command line arguments if environment variables not set
    if not combined_dir:
        if len(sys.argv) >= 3:
            combined_dir, output_path = sys.argv[1], sys.argv[2]
        elif len(sys.argv) == 2:
            combined_dir = sys.argv[1]
            output_path = str(Path(combined_dir).parent / "combined.qgz")
        else:
            combined_dir = "out/combined"
            output_path = "out/combined.qgz"
            log(f"Using defaults: {combined_dir} -> {output_path}")
    else:
        # If combined_dir from env but no output_path, derive it
        if not output_path:
            output_path = str(Path(combined_dir).parent / "combined.qgz")
        log(f"Using environment variables: {combined_dir} -> {output_path}")

    log("Starting create_qgis_project()...")
    try:
        result = create_qgis_project(combined_dir, output_path)
        log(f"create_qgis_project() returned: {result}")
    except Exception as e:
        log(f"Error in create_qgis_project(): {e}")
        import traceback

        log(f"Traceback: {traceback.format_exc()}")
        result = False

    # Exit QGIS when running in headless mode (CI/automated execution)
    # Use BLAZE_EXIT_AFTER_RUN environment variable to signal headless execution
    if os.environ.get("BLAZE_EXIT_AFTER_RUN"):
        log("Script completed. Exiting QGIS...")
        time.sleep(0.5)  # Give a moment for any pending operations

        # Note: QgsApplication.exitQgis() cannot be called from within QGIS
        # It's only for standalone scripts. Use QApplication.quit() instead.
        try:
            from qgis.PyQt.QtWidgets import QApplication

            app = QApplication.instance()
            if app:
                app.quit()
                log("Called QApplication.quit()")
        except Exception as e:
            log(f"Error calling QApplication.quit(): {e}")

        # Force immediate exit - don't wait for cleanup
        exit_code = 0 if result else 1
        log(f"Force exiting with code: {exit_code}")
        os._exit(exit_code)  # Use os._exit() to bypass Python cleanup and force immediate termination

    return result


# Only run main() if this script is executed directly (not when imported/exec'd)
# Check if we're being run as a script (has command line args) vs being exec'd by the plugin
# When exec'd by the plugin, __name__ will be set to "create_qgis_project" (not "__main__")
# When run with --code in headless mode, also execute main() directly
if QgsApplication.instance() is not None:
    if __name__ == "__main__" or os.environ.get("BLAZE_EXIT_AFTER_RUN"):
        main()
