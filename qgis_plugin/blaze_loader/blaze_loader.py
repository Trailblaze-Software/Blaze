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
import os.path
import sys
from pathlib import Path

from qgis.core import Qgis, QgsApplication, QgsMessageLog
from qgis.PyQt.QtCore import Qt
from qgis.PyQt.QtWidgets import QApplication, QMessageBox, QProgressDialog

from .blaze_loader_dialog import BlazeLoaderDialog


def check_qpip_installed():
    """Check if QPIP plugin is installed."""
    qpip_path = os.path.join(QgsApplication.qgisSettingsDirPath(), "python", "plugins", "qpip")
    return os.path.exists(qpip_path)


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
        qpip_path = os.path.join(QgsApplication.qgisSettingsDirPath(), "python", "plugins", "qpip")
        sys.path.insert(0, qpip_path)
        from qpip import pip_install

        QgsMessageLog.logMessage("Installing geomag via QPIP...", "Blaze", Qgis.Info)
        pip_install(["geomag"])
        QgsMessageLog.logMessage("geomag installed successfully", "Blaze", Qgis.Info)
        return True, "geomag installed via QPIP"
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

    def run(self):
        self.dlg = BlazeLoaderDialog(parent=self.iface.mainWindow(), last_folder=self.last_folder)

        # Center dialog on parent window
        if self.iface.mainWindow():
            parent_rect = self.iface.mainWindow().geometry()
            dialog_rect = self.dlg.geometry()
            x = parent_rect.x() + (parent_rect.width() - dialog_rect.width()) // 2
            y = parent_rect.y() + (parent_rect.height() - dialog_rect.height()) // 2
            self.dlg.move(x, y)

        result = self.dlg.exec_()
        if result:
            folder = self.dlg.get_folder()
            options = self.dlg.get_options()
            self.last_folder = folder
            self.load_blaze_project(folder, options)

    def load_blaze_project(self, folder, options):
        """Load Blaze layers into the current QGIS project."""
        folder_path = Path(folder)

        # Show progress dialog with range 0-100
        progress = QProgressDialog("Loading Blaze layers...", None, 0, 100, self.iface.mainWindow())
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
            module_globals["create_qgis_project"](
                str(folder_path),
                output_path=None,  # Don't save - add to current project
                download_topo=options.get("download_topo", True),
                add_mag_north=options.get("add_mag_north", True),
                zoom_to_extent=options.get("zoom_to_extent", True),
                add_controls=options.get("add_controls", False),
                clear_project=False,  # Don't clear existing project
                progress_callback=update_progress,
                gpkg_output_path=options.get("gpkg_output_path"),
            )

            update_progress("Complete!", 100)
            progress.close()

            # Refresh the map canvas to ensure new layers are visible
            self.iface.mapCanvas().refresh()

            # Show success message
            QMessageBox.information(
                self.iface.mainWindow(),
                "Blaze Map Loader",
                f"Blaze layers added successfully!\n\nLayers from: {folder_path}\n\n"
                f"Check the Log Messages panel (View > Panels > Log Messages > Blaze) for details.\n\n",
            )

        except Exception as e:
            progress.close()
            QMessageBox.critical(
                self.iface.mainWindow(),
                "Blaze Map Loader Error",
                f"Failed to load project:\n\n{str(e)}",
            )
            import traceback

            traceback.print_exc()
