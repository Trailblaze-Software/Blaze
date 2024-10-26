#include "config_editor.hpp"

#include <QFileDialog>
#include <QPushButton>

#include "ui_config_editor.h"

ConfigEditor::ConfigEditor(QWidget* parent)
    : QWidget(parent), ui(new Ui::ConfigEditor), m_config(Config::Default()) {
  ui->setupUi(this);

  set_ui_to_config(m_config);

  connect(ui->out_dir_button, &QPushButton::clicked, this, &ConfigEditor::open_output_directory);
}

ConfigEditor::~ConfigEditor() { delete ui; }

void ConfigEditor::open_config_file() {
  QString config_file_name = QFileDialog::getOpenFileName(
      this, ("Open Config"), m_config.relative_path_to_config.string().c_str(),
      ("Config Files (*.json *.jsonc);;All files (*)"), nullptr, QFileDialog::ReadOnly);
  if (config_file_name.isEmpty()) {
    return;
  }
  m_config = Config::FromFile(config_file_name.toStdString());
  set_ui_to_config(m_config);
}

void ConfigEditor::save_config_file() {
  QString config_file_name = QFileDialog::getSaveFileName(
      this, ("Save Config"), m_config.relative_path_to_config.string().c_str(),
      ("Config Files (*.json *.jsonc);;All files (*)"), nullptr, QFileDialog::ReadOnly);
  if (config_file_name.isEmpty()) {
    return;
  }
  m_config.write_to_file(config_file_name.toStdString());
}

void ConfigEditor::open_output_directory() {
  QString output_dir_name = QFileDialog::getExistingDirectory(
      this, tr("Choose Output Directory"), m_config.output_path().string().c_str(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (output_dir_name.isEmpty()) {
    return;
  }
  m_config.set_output_directory(output_dir_name.toStdString());
  ui->out_dir_line_edit->setText(output_dir_name);
}

void ConfigEditor::set_ui_to_config(const Config& config) {
  ui->out_dir_line_edit->setText(config.output_path().c_str());

  ui->scale_dropdown->setCurrentText(std::to_string(config.render.scale).c_str());
  ui->dpi_dropdown->setCurrentText(
      std::to_string(config.render.dpi.in(au::unos / au::inches)).c_str());

  ui->extract_borders_checkbox->setChecked(
      std::find(config.processing_steps.begin(), config.processing_steps.end(),
                ProcessingStep::TmpBorders) != config.processing_steps.end());
  ui->process_tiles_checkbox->setChecked(
      std::find(config.processing_steps.begin(), config.processing_steps.end(),
                ProcessingStep::Tiles) != config.processing_steps.end());
  ui->combine_tiles_checkbox->setChecked(
      std::find(config.processing_steps.begin(), config.processing_steps.end(),
                ProcessingStep::Combine) != config.processing_steps.end());
}
