# -*- coding: utf-8 -*-
import json
import os
import re
import sys
import tempfile
from pathlib import Path

from qgis.core import QgsSettings
from qgis.PyQt import uic
from qgis.PyQt.QtCore import QProcess, QProcessEnvironment, QUrl
from qgis.PyQt.QtGui import QDesktopServices
from qgis.PyQt.QtWidgets import QDialog, QFileDialog, QMessageBox

# Load the UI file
FORM_CLASS, _ = uic.loadUiType(os.path.join(os.path.dirname(__file__), "blaze_loader_dialog_base.ui"))


class BlazeLoaderDialog(QDialog, FORM_CLASS):
    def __init__(self, parent=None, last_folder=None, blaze_executable_path=None):
        super().__init__(parent)
        self.setupUi(self)

        self.process = None
        self.config_temp_file = None

        # Hide progress widgets initially
        self.runProgressBar.setVisible(False)
        self.runLogTextEdit.setVisible(False)

        # Resolve blaze executable path
        self.settings = QgsSettings()
        saved_exe = self.settings.value("blaze_loader/blaze_executable", None)

        if saved_exe and os.path.exists(saved_exe):
            self.blaze_executable_path = saved_exe
        elif blaze_executable_path:
            self.blaze_executable_path = blaze_executable_path
        else:
            self.blaze_executable_path = ""

        self.blazeExeLineEdit.setText(self.blaze_executable_path)

        # Set initial folder if provided
        if last_folder:
            self.folderLineEdit.setText(last_folder)

        # Connect browse buttons
        self.browseButton.clicked.connect(self.browse_output_folder)
        self.gpkgBrowseButton.clicked.connect(self.browse_gpkg_file)
        self.lazFolderBrowseButton.clicked.connect(self.browse_laz_folder)
        self.blazeExeBrowseButton.clicked.connect(self.browse_blaze_exe)
        self.runOutputBrowseButton.clicked.connect(self.browse_run_output_folder)

        # Set up button enable/disable logic
        self.loadButton.setEnabled(bool(self.folderLineEdit.text()))
        self.folderLineEdit.textChanged.connect(lambda: self.loadButton.setEnabled(bool(self.folderLineEdit.text())))
        self.runBlazeButton.setEnabled(bool(self.lazFolderLineEdit.text()))
        self.lazFolderLineEdit.textChanged.connect(
            lambda: self.runBlazeButton.setEnabled(bool(self.lazFolderLineEdit.text()))
        )

        # Connect button box signals
        self.buttonBox.accepted.connect(self.accept)
        self.buttonBox.rejected.connect(self.reject)

        # Connect tab-specific buttons
        self.loadButton.clicked.connect(self.accept)
        self.runBlazeButton.clicked.connect(self.run_blaze)

        # Connect text changed signals for auto-generating JSON config
        self.lazFolderLineEdit.textChanged.connect(self.generate_json_config)
        self.scaleLineEdit.textChanged.connect(self.generate_json_config)
        self.blazeExeLineEdit.textChanged.connect(self.generate_json_config)
        self.runOutputLineEdit.textChanged.connect(self.generate_json_config)

    def browse_output_folder(self):
        folder = QFileDialog.getExistingDirectory(
            self,
            "Select Blaze Output Folder",
            self.folderLineEdit.text() or str(Path.home()),
        )
        if folder:
            self.folderLineEdit.setText(folder)

    def browse_laz_folder(self):
        folder = QFileDialog.getExistingDirectory(
            self,
            "Select Folder with LAZ Files",
            self.lazFolderLineEdit.text() or str(Path.home()),
        )
        if folder:
            self.lazFolderLineEdit.setText(folder)

    def browse_run_output_folder(self):
        folder = QFileDialog.getExistingDirectory(
            self,
            "Select Output Folder for Blaze Run",
            self.runOutputLineEdit.text() or str(Path.home()),
        )
        if folder:
            self.runOutputLineEdit.setText(folder)

    def browse_blaze_exe(self):
        filter_str = "Executables (*.exe)" if sys.platform.startswith("win") else "All Files (*)"
        file_path, _ = QFileDialog.getOpenFileName(
            self,
            "Select Blaze Executable",
            self.blazeExeLineEdit.text() or str(Path.home()),
            filter_str,
        )
        if file_path:
            self.blazeExeLineEdit.setText(file_path)

    def browse_gpkg_file(self):
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            "Save NSW Topo GPKG As",
            self.gpkgLineEdit.text() or str(Path.home()),
            "GeoPackage (*.gpkg);;All Files (*)",
        )
        if file_path:
            self.gpkgLineEdit.setText(file_path)

    def generate_json_config(self):
        laz_folder = self.lazFolderLineEdit.text()
        scale = self.scaleLineEdit.text()
        blaze_exe = self.blazeExeLineEdit.text()
        output_folder = self.runOutputLineEdit.text()

        # If we don't have enough info to generate a useful config, maybe wait?
        # But we can at least show the template if we have the exe.

        try:
            scale_val = int(scale) if scale else 10000  # Default fallback
            if scale_val <= 0:
                raise ValueError
        except ValueError:
            self.jsonConfigTextEdit.setPlainText("Invalid scale")
            return

        # Try to locate default_config.json relative to the executable
        config_template_path = None

        if blaze_exe and os.path.exists(blaze_exe):
            exe_dir = Path(os.path.dirname(blaze_exe))
            candidates = [
                exe_dir / "assets" / "default_config.json",  # Windows/Flat: bin/assets
                exe_dir.parent / "assets" / "default_config.json",  # Root: assets/ (exe in bin/)
                exe_dir.parent.parent / "assets" / "default_config.json",  # Build: build/Release/ -> assets/
                exe_dir.parent / "share" / "blaze" / "assets" / "default_config.json",  # Linux Install
            ]

            for candidate in candidates:
                if candidate.exists():
                    config_template_path = candidate
                    break

        if not config_template_path:
            # Can't generate config without the template
            # Keep existing text or clear if empty?
            if not self.jsonConfigTextEdit.toPlainText() or self.jsonConfigTextEdit.toPlainText().startswith("//"):
                checked_paths = "\n".join([str(p) for p in candidates]) if "candidates" in locals() else "None"
                separator = "\n// "
                self.jsonConfigTextEdit.setPlainText(
                    f"// Could not find assets/default_config.json.\n"
                    f"// Please ensure 'assets' folder is near the executable.\n"
                    f"// Checked locations:\n"
                    f"// {checked_paths.replace(os.linesep, separator)}"
                )
            return

        try:
            with open(config_template_path, "r") as f:
                # Strip comments (lines starting with //)
                lines = [line for line in f if not line.strip().startswith("//")]
                config_str = "".join(lines)
                config = json.loads(config_str)

            # Substitute values
            if laz_folder:
                # Blaze run.cpp supports directory paths in las_files
                config["las_files"] = [laz_folder]

            # Handle output directory - ensure it is absolute so it persists after temp dir deletion
            # Default to laz_folder/out if not specified
            if not output_folder:
                if laz_folder:
                    output_folder = str(Path(laz_folder) / "out")
                    self.runOutputLineEdit.setText(output_folder)  # Update UI
            elif not os.path.isabs(output_folder):
                if laz_folder:
                    output_folder = str(Path(laz_folder) / output_folder)

            if output_folder:
                config["output_directory"] = output_folder

            if "render" in config:
                config["render"]["scale"] = scale_val

            self.jsonConfigTextEdit.setPlainText(json.dumps(config, indent=4))

        except Exception as e:
            self.jsonConfigTextEdit.setPlainText(f"// Error loading configuration: {str(e)}")

    def get_folder(self):
        return self.folderLineEdit.text()

    def get_options(self):
        return {
            "download_topo": self.downloadTopoCheckBox.isChecked(),
            "add_mag_north": self.addMagNorthCheckBox.isChecked(),
            "zoom_to_extent": self.zoomToExtentCheckBox.isChecked(),
            "add_controls": self.addControlsCheckBox.isChecked(),
            "gpkg_output_path": (self.gpkgLineEdit.text() if self.gpkgLineEdit.text() else None),
        }

    def accept(self):
        # This is connected to the 'Load Layers' button now
        if self.tabWidget.currentIndex() == 0 and self.get_folder():
            super().accept()
        elif self.tabWidget.currentIndex() == 1:
            # This case is handled by run_blaze, but we keep the dialog open
            pass
        else:
            # If on the first tab but no folder, do nothing.
            pass

    def reject(self):
        super().reject()

    def run_blaze(self):
        # Handle Cancel logic
        if self.process is not None and self.process.state() != QProcess.NotRunning:
            self.process.kill()
            self.process.waitForFinished()
            self.runLogTextEdit.appendPlainText("\n--- Process Cancelled by User ---")
            self.runBlazeButton.setText("Run Blaze")
            self.process = None
            return

        blaze_exe = self.blazeExeLineEdit.text()

        if not blaze_exe or not os.path.exists(blaze_exe):
            msg_box = QMessageBox(self)
            msg_box.setWindowTitle("Blaze Not Found")
            msg_box.setText("Blaze executable not found.")
            msg_box.setInformativeText(
                "Blaze is required to run this feature. Please download and install the latest version."
            )
            download_btn = msg_box.addButton("Download Blaze...", QMessageBox.ActionRole)
            msg_box.addButton(QMessageBox.Cancel)

            msg_box.exec_()

            if msg_box.clickedButton() == download_btn:
                QDesktopServices.openUrl(QUrl("https://github.com/Trailblaze-Software/blaze/releases"))

            return

        # Save the working executable path
        self.settings.setValue("blaze_loader/blaze_executable", blaze_exe)

        json_config_str = self.jsonConfigTextEdit.toPlainText()
        try:
            json.loads(json_config_str)
        except json.JSONDecodeError:
            QMessageBox.critical(self, "Invalid JSON", "The JSON config is not valid.")
            return

        # Create persistent temp file for config (since QProcess is async)
        # We manually delete it in on_process_finished
        try:
            fd, self.config_temp_file = tempfile.mkstemp(suffix=".json", prefix="blaze_config_")
            with os.fdopen(fd, "w") as f:
                f.write(json_config_str)
        except Exception as e:
            QMessageBox.critical(self, "Error", f"Failed to create config file: {e}")
            return

        # Prepare UI
        self.runBlazeButton.setText("Cancel")
        self.runProgressBar.setVisible(True)
        self.runProgressBar.setValue(0)
        self.runLogTextEdit.setVisible(True)
        self.runLogTextEdit.clear()
        self.runLogTextEdit.appendPlainText(
            f"Starting Blaze...\nExecutable: {blaze_exe}\nConfig: {self.config_temp_file}\n"
        )

        # Sanitize environment to avoid QGIS PROJ/GDAL conflicts
        env = QProcessEnvironment.systemEnvironment()
        env.remove("PROJ_LIB")
        env.remove("GDAL_DATA")

        self.process = QProcess(self)
        self.process.setProcessEnvironment(env)
        self.process.setWorkingDirectory(os.path.dirname(blaze_exe))

        # Connect signals
        self.process.readyReadStandardOutput.connect(self.on_process_output)
        self.process.readyReadStandardError.connect(self.on_process_output)  # Merge stderr
        self.process.finished.connect(self.on_process_finished)

        # Start
        self.process.start(blaze_exe, [self.config_temp_file])

    def on_process_output(self):
        if not self.process:
            return

        # Read stdout
        data_out = self.process.readAllStandardOutput()
        if data_out:
            text = bytes(data_out).decode("utf-8", errors="replace")
            self.runLogTextEdit.moveCursor(self.runLogTextEdit.textCursor().End)
            self.runLogTextEdit.insertPlainText(text)
            self.runLogTextEdit.verticalScrollBar().setValue(self.runLogTextEdit.verticalScrollBar().maximum())

            # Parse progress
            match = re.search(r"Progress:\s+([\d.]+)%", text)
            if match:
                try:
                    val = float(match.group(1))
                    self.runProgressBar.setValue(int(val))
                except ValueError:
                    pass

        # Read stderr
        data_err = self.process.readAllStandardError()
        if data_err:
            text = bytes(data_err).decode("utf-8", errors="replace")
            self.runLogTextEdit.moveCursor(self.runLogTextEdit.textCursor().End)
            self.runLogTextEdit.insertPlainText(text)  # Just append stderr to log
            self.runLogTextEdit.verticalScrollBar().setValue(self.runLogTextEdit.verticalScrollBar().maximum())

    def on_process_finished(self, exit_code, exit_status):
        self.runBlazeButton.setText("Run Blaze")

        # Clean up temp file
        if self.config_temp_file and os.path.exists(self.config_temp_file):
            try:
                os.remove(self.config_temp_file)
            except OSError:
                pass
            self.config_temp_file = None

        if exit_code == 0 and exit_status == QProcess.NormalExit:
            self.runProgressBar.setValue(100)
            self.runLogTextEdit.appendPlainText("\n--- Blaze Finished Successfully ---")

            # Determine output directory
            try:
                json_config_str = self.jsonConfigTextEdit.toPlainText()
                config_data = json.loads(json_config_str)
                out_dir = config_data.get("output_directory", "out")
                out_path = Path(out_dir)
                # Should be absolute per generate_json_config, but verify
                if not out_path.is_absolute() and self.blazeExeLineEdit.text():
                    out_path = Path(os.path.dirname(self.blazeExeLineEdit.text())) / out_path

                # Check for 'combined' subfolder which contains the final maps
                if (out_path / "combined").exists():
                    out_path = out_path / "combined"

                self.folderLineEdit.setText(str(out_path))
                self.tabWidget.setCurrentIndex(0)

                QMessageBox.information(
                    self,
                    "Blaze Run Complete",
                    f"Blaze finished successfully.\n"
                    f"Output is in: {out_path}\n\n"
                    f"Click 'Load Layers' to load the results.",
                )
            except Exception as e:
                self.runLogTextEdit.appendPlainText(f"\nError parsing output config: {e}")
        else:
            self.runLogTextEdit.appendPlainText(f"\n--- Blaze Failed (Exit Code: {exit_code}) ---")
            QMessageBox.critical(
                self, "Blaze Error", f"Blaze failed with exit code {exit_code}.\nCheck the log for details."
            )

        self.process = None

    @staticmethod
    def get_run_blaze_options(parent=None, last_folder=None, blaze_executable_path=None):
        dialog = BlazeLoaderDialog(parent, last_folder, blaze_executable_path)

        # Start on the 'Run Blaze' tab
        dialog.tabWidget.setCurrentIndex(1)

        result = dialog.exec_()
        if result and dialog.tabWidget.currentIndex() == 0:
            return dialog.get_folder(), dialog.get_options()
        return None, None

    @staticmethod
    def get_load_layers_options(parent=None, last_folder=None, blaze_executable_path=None):
        dialog = BlazeLoaderDialog(parent, last_folder, blaze_executable_path)
        result = dialog.exec_()
        if result:
            return dialog.get_folder(), dialog.get_options()
        return None, None
