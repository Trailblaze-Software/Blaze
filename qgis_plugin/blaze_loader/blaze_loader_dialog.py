# -*- coding: utf-8 -*-
import os
from pathlib import Path

from qgis.core import QgsSettings
from qgis.PyQt import uic
from qgis.PyQt.QtWidgets import QDialog, QFileDialog

# Load the UI file
FORM_CLASS, _ = uic.loadUiType(os.path.join(os.path.dirname(__file__), "blaze_loader_dialog_base.ui"))


class BlazeLoaderDialog(QDialog, FORM_CLASS):
    def __init__(self, parent=None, last_folder=None):
        super().__init__(parent)
        self.setupUi(self)

        self.settings = QgsSettings()

        # Set initial folder if provided
        if last_folder:
            self.folderLineEdit.setText(last_folder)

        # Connect browse buttons
        self.browseButton.clicked.connect(self.browse_output_folder)
        self.gpkgBrowseButton.clicked.connect(self.browse_gpkg_file)

        # Set up button enable/disable logic
        self.loadButton.setEnabled(bool(self.folderLineEdit.text()))
        self.folderLineEdit.textChanged.connect(self.update_load_button_state)
        self.useCurrentExtentCheckBox.toggled.connect(self.on_use_current_extent_toggled)

        # Connect button box signals
        self.buttonBox.accepted.connect(self.accept)
        self.buttonBox.rejected.connect(self.reject)

        # Connect load button
        self.loadButton.clicked.connect(self.accept)

    def browse_output_folder(self):
        folder = QFileDialog.getExistingDirectory(
            self,
            "Select Blaze Output Folder",
            self.folderLineEdit.text() or str(Path.home()),
        )
        if folder:
            self.folderLineEdit.setText(folder)

    def browse_gpkg_file(self):
        file_path, _ = QFileDialog.getSaveFileName(
            self,
            "Save NSW Topo GPKG As",
            self.gpkgLineEdit.text() or str(Path.home()),
            "GeoPackage (*.gpkg);;All Files (*)",
        )
        if file_path:
            self.gpkgLineEdit.setText(file_path)

    def get_folder(self):
        return self.folderLineEdit.text()

    def update_load_button_state(self):
        """Update the load button state based on folder or use current extent option."""
        has_folder = bool(self.folderLineEdit.text())
        use_current = self.useCurrentExtentCheckBox.isChecked()
        self.loadButton.setEnabled(has_folder or use_current)

    def on_use_current_extent_toggled(self, checked):
        """Handle the use current extent checkbox toggle."""
        # Disable folder selection when using current extent
        self.folderLineEdit.setEnabled(not checked)
        self.browseButton.setEnabled(not checked)
        # Update load button state
        self.update_load_button_state()
        # Disable zoom to extent when using current extent (it doesn't make sense)
        if checked:
            self.zoomToExtentCheckBox.setChecked(False)
            self.zoomToExtentCheckBox.setEnabled(False)
        else:
            self.zoomToExtentCheckBox.setEnabled(True)

    def get_options(self):
        return {
            "use_current_extent": self.useCurrentExtentCheckBox.isChecked(),
            "download_topo": self.downloadTopoCheckBox.isChecked(),
            "add_mag_north": self.addMagNorthCheckBox.isChecked(),
            "zoom_to_extent": self.zoomToExtentCheckBox.isChecked(),
            "add_controls": self.addControlsCheckBox.isChecked(),
            "gpkg_output_path": (self.gpkgLineEdit.text() if self.gpkgLineEdit.text() else None),
        }

    def accept(self):
        # Allow accept if folder is provided OR use current extent is checked
        if self.get_folder() or self.useCurrentExtentCheckBox.isChecked():
            super().accept()

    def reject(self):
        super().reject()

    @staticmethod
    def get_load_layers_options(parent=None, last_folder=None):
        dialog = BlazeLoaderDialog(parent, last_folder)
        result = dialog.exec_()
        if result:
            return dialog.get_folder(), dialog.get_options()
        return None, None
