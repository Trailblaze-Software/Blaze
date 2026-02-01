# -*- coding: utf-8 -*-
import os
from pathlib import Path

from qgis.PyQt import uic
from qgis.PyQt.QtWidgets import QDialog, QDialogButtonBox, QFileDialog

# Load the UI file
FORM_CLASS, _ = uic.loadUiType(os.path.join(os.path.dirname(__file__), "blaze_loader_dialog_base.ui"))


class BlazeLoaderDialog(QDialog, FORM_CLASS):
    def __init__(self, parent=None, last_folder=None):
        super().__init__(parent)
        self.setupUi(self)

        # Set initial folder if provided
        if last_folder:
            self.folderLineEdit.setText(last_folder)

        # Connect browse buttons
        self.browseButton.clicked.connect(self.browse_folder)
        self.gpkgBrowseButton.clicked.connect(self.browse_gpkg_file)

        # Set up OK button enable/disable logic
        self.ok_button = self.buttonBox.button(QDialogButtonBox.Ok)
        self.ok_button.setEnabled(bool(self.folderLineEdit.text()))
        self.folderLineEdit.textChanged.connect(lambda: self.ok_button.setEnabled(bool(self.folderLineEdit.text())))

        # Connect button box signals
        self.buttonBox.accepted.connect(self.accept)
        self.buttonBox.rejected.connect(self.reject)

    def browse_folder(self):
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

    def get_options(self):
        return {
            "download_topo": self.downloadTopoCheckBox.isChecked(),
            "add_mag_north": self.addMagNorthCheckBox.isChecked(),
            "zoom_to_extent": self.zoomToExtentCheckBox.isChecked(),
            "add_controls": self.addControlsCheckBox.isChecked(),
            "gpkg_output_path": (self.gpkgLineEdit.text() if self.gpkgLineEdit.text() else None),
        }
