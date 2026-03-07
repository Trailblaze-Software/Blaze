# -*- coding: utf-8 -*-
"""
/***************************************************************************
 BlazeLoader
                                 A QGIS plugin
 This plugin loads the output maps created by Blaze along with magnetic north lines and NSW topo data if available
 ***************************************************************************/
"""

import importlib
import os
from pathlib import Path

from qgis.core import Qgis, QgsMessageLog
from qgis.PyQt.QtCore import Qt
from qgis.PyQt.QtWidgets import (
    QApplication,
    QDialog,
    QDialogButtonBox,
    QLabel,
    QMessageBox,
    QProgressDialog,
    QTextEdit,
    QVBoxLayout,
)

from .blaze_loader_dialog import BlazeLoaderDialog


def check_qpip_installed():
    """Check if QPIP plugin is installed and available.

    Uses the standard Python approach: try to import the module.
    QGIS automatically adds plugin directories to sys.path when plugins are loaded.
    """
    try:
        import qpip

        # Verify it has the function we need
        if hasattr(qpip, "pip_install"):
            return True
    except ImportError:
        pass

    return False


def check_compass_routes_installed():
    """Check if Compass Routes plugin is installed by checking for its processing algorithm."""
    try:
        from qgis.core import QgsApplication

        registry = QgsApplication.processingRegistry()
        alg = registry.algorithmById("compassroutes:createmagneticnorth")
        return alg is not None
    except Exception:
        return False


def ensure_geomag_installed():
    """Try to install geomag package for accurate magnetic declination.
    Returns: (installed, message)
    """
    try:
        importlib.import_module("geomag")
        return True, "geomag available"
    except ImportError:
        pass

    # Check if QPIP is available
    if not check_qpip_installed():
        return False, "QPIP plugin not installed"

    # Try to install via QPIP
    try:
        # QPIP should be importable if check_qpip_installed() returned True
        from qpip import pip_install

        QgsMessageLog.logMessage("Installing geomag via QPIP...", "Blaze", Qgis.Info)
        pip_install(["geomag"])
        QgsMessageLog.logMessage("geomag installed successfully", "Blaze", Qgis.Info)
        return True, "geomag installed via QPIP"
    except ImportError:
        return False, "QPIP plugin not available for import"
    except Exception as e:
        QgsMessageLog.logMessage(f"Could not install geomag via QPIP: {e}", "Blaze", Qgis.Warning)
        return False, f"Failed to install geomag: {e}"


class BlazeLoader:
    """QGIS Plugin Implementation."""

    def __init__(self, iface):
        self.iface = iface
        self.plugin_dir = os.path.dirname(__file__)
        self.last_folder = None

        # Try to install geomag for accurate magnetic declination
        geomag_ok, geomag_msg = ensure_geomag_installed()
        if not geomag_ok:
            QgsMessageLog.logMessage(
                f"Magnetic declination: {geomag_msg}. "
                "For accurate declination, install QPIP plugin (Plugins > Manage and Install Plugins > search 'qpip'), "
                "then restart QGIS. geomag will be auto-installed.",
                "Blaze",
                Qgis.Warning,
            )

        # Check if Compass Routes plugin is installed (needed for magnetic north lines)
        if not check_compass_routes_installed():
            QgsMessageLog.logMessage(
                "Compass Routes plugin is not installed. "
                "It is required for magnetic north lines. "
                "Install it from Plugins > Manage and Install Plugins > search 'Compass Routes'.",
                "Blaze",
                Qgis.Warning,
            )

    def run(self):
        # Show the dialog and get the options.
        folder, options = BlazeLoaderDialog.get_load_layers_options(
            parent=self.iface.mainWindow(),
            last_folder=self.last_folder,
        )

        if options and (folder or options.get("use_current_extent", False)):
            if folder:
                self.last_folder = folder
            self.load_blaze_project(folder, options)

    def load_blaze_project(self, folder, options):
        """Load Blaze layers into the current QGIS project."""
        use_current_extent = options.get("use_current_extent", False)

        # Get current map extent if requested
        current_extent = None
        current_crs = None
        if use_current_extent:
            canvas = self.iface.mapCanvas()
            if canvas:
                current_extent = canvas.extent()
                current_crs = canvas.mapSettings().destinationCrs()
                if not current_extent or current_extent.isEmpty():
                    QMessageBox.warning(
                        self.iface.mainWindow(),
                        "Blaze Map Loader",
                        "Current map extent is empty. Please zoom to an area first.",
                    )
                    return
            else:
                QMessageBox.warning(
                    self.iface.mainWindow(),
                    "Blaze Map Loader",
                    "Could not get current map extent. Please ensure QGIS map canvas is available.",
                )
                return

        folder_path = Path(folder) if folder else None

        # Show progress dialog with range 0-100
        progress_text = "Using current map extent..." if use_current_extent else "Loading Blaze layers..."
        progress = QProgressDialog(progress_text, None, 0, 100, self.iface.mainWindow())
        progress.setWindowTitle("Blaze Map Loader")
        progress.setWindowModality(Qt.WindowModal)
        progress.setMinimumDuration(0)
        progress.setAutoClose(False)
        progress.setAutoReset(False)
        progress.show()
        QApplication.processEvents()

        def update_progress(message, percent=None):
            """Callback to update the progress dialog."""
            progress.setLabelText(message)
            if percent is not None:
                progress.setValue(percent)
            QApplication.processEvents()

        try:
            # Find the create_qgis_project.py script
            script_path = os.path.join(self.plugin_dir, "create_qgis_project.py")

            if not os.path.exists(script_path):
                raise FileNotFoundError(
                    f"Cannot find create_qgis_project.py in {self.plugin_dir}\n"
                    "Please ensure the plugin is installed correctly."
                )

            update_progress("Loading Blaze module...", 0)

            # Set up module globals before exec
            module_globals = {
                "__file__": script_path,
                "__name__": "create_qgis_project",
            }

            with open(script_path) as f:
                code = compile(f.read(), script_path, "exec")
                exec(code, module_globals)

            # Check if the function was loaded
            if "create_qgis_project" not in module_globals:
                raise RuntimeError(
                    f"Function 'create_qgis_project' not found in module.\n"
                    f"Available keys: {list(module_globals.keys())[:10]}..."
                )

            update_progress("Adding layers to project...", 2)

            # Call the function from the exec'd module (output_path=None means don't save)
            result = module_globals["create_qgis_project"](
                str(folder_path) if folder_path else None,
                output_path=None,  # Don't save - add to current project
                download_topo=options.get("download_topo", True),
                add_mag_north=options.get("add_mag_north", True),
                zoom_to_extent=options.get("zoom_to_extent", True),
                add_controls=options.get("add_controls", False),
                clear_project=False,  # Don't clear existing project
                progress_callback=update_progress,
                gpkg_output_path=options.get("gpkg_output_path"),
                use_current_extent=use_current_extent,
                current_extent=current_extent,
                current_crs=current_crs,
                parent_window=self.iface.mainWindow(),
            )

            update_progress("Complete!", 100)
            progress.close()

            # Refresh the map canvas to ensure new layers are visible
            self.iface.mapCanvas().refresh()

            # Build summary dialog
            self._show_summary_dialog(result, folder_path)

        except Exception as e:
            progress.close()
            QMessageBox.critical(
                self.iface.mainWindow(),
                "Blaze Map Loader Error",
                f"Failed to load project:\n\n{str(e)}",
            )
            import traceback

            traceback.print_exc()

    def _show_summary_dialog(self, result, folder_path):
        """Show a summary dialog with scrollable topo details."""
        dlg = QDialog(self.iface.mainWindow())
        dlg.setWindowTitle("Blaze Map Loader")
        dlg.setMinimumWidth(420)
        layout = QVBoxLayout(dlg)

        # Top section: loaded / failed / skipped (compact)
        top_lines = []
        if isinstance(result, dict):
            if result.get("loaded"):
                top_lines.append("<b>Loaded:</b>")
                for item in result["loaded"]:
                    top_lines.append(f"&nbsp;&nbsp;✓ {item}")
            if result.get("failed"):
                top_lines.append("<b>Failed:</b>")
                for item in result["failed"]:
                    top_lines.append(f"&nbsp;&nbsp;✗ {item}")
            if result.get("skipped"):
                top_lines.append("<b>Skipped:</b>")
                for item in result["skipped"]:
                    top_lines.append(f"&nbsp;&nbsp;– {item}")

        if top_lines:
            top_label = QLabel("<br>".join(top_lines))
            top_label.setTextFormat(Qt.RichText)
            top_label.setWordWrap(True)
            layout.addWidget(top_label)

        # Topo details in a scrollable text area
        topo = result.get("topo_details") if isinstance(result, dict) else None
        if topo and (topo.get("with_data") or topo.get("empty") or topo.get("failed") or topo.get("network_errors")):
            topo_lines = []
            if topo.get("network_errors"):
                topo_lines.append(f"Server errors ({len(topo['network_errors'])}):")
                for entry in topo["network_errors"]:
                    if isinstance(entry, tuple):
                        name, url = entry
                        topo_lines.append(f"  ⚠ {name}: {url}")
                    else:
                        # Backward compatibility
                        topo_lines.append(f"  ⚠ {entry}")
            if topo.get("failed"):
                topo_lines.append(f"Failed ({len(topo['failed'])}):")
                for name in topo["failed"]:
                    topo_lines.append(f"  ✗ {name}")
            if topo.get("with_data"):
                if topo_lines:
                    topo_lines.append("")
                topo_lines.append(f"Layers ({len(topo['with_data'])}):")
                for entry in topo["with_data"]:
                    name, count = entry[0], entry[1]
                    dupes = entry[2] if len(entry) > 2 else 0
                    if dupes:
                        topo_lines.append(f"  ✓ {name} ({count} features, {dupes} duplicates skipped)")
                    else:
                        topo_lines.append(f"  ✓ {name} ({count} features)")
            if topo.get("empty"):
                topo_lines.append(f"\nNo data in area ({len(topo['empty'])}):")
                for name in topo["empty"]:
                    topo_lines.append(f"  – {name}")

            topo_label = QLabel("<b>Topo layers:</b>")
            topo_label.setTextFormat(Qt.RichText)
            layout.addWidget(topo_label)

            topo_text = QTextEdit()
            topo_text.setReadOnly(True)
            topo_text.setPlainText("\n".join(topo_lines))
            topo_text.setMaximumHeight(200)
            layout.addWidget(topo_text)

        # Footer
        has_failures = isinstance(result, dict) and (
            result.get("failed") or (topo or {}).get("failed") or (topo or {}).get("network_errors")
        )
        footer_parts = []
        if has_failures:
            footer_parts.append("See Log Messages (View > Panels > Log Messages > Blaze) for details.")
        if folder_path:
            footer_parts.append(f"Source: {folder_path}")
        if footer_parts:
            footer_label = QLabel("\n".join(footer_parts))
            footer_label.setWordWrap(True)
            layout.addWidget(footer_label)

        # OK button
        buttons = QDialogButtonBox(QDialogButtonBox.Ok)
        buttons.accepted.connect(dlg.accept)
        layout.addWidget(buttons)

        dlg.exec_()
