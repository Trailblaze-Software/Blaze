#include "config_editor.hpp"

#include <QFileDialog>
#include <QPushButton>

#include "config_input/config_input.hpp"
#include "printing/to_string.hpp"
#include "ui_config_editor.h"

class ParentFolderExistsValidator : public QValidator {
 public:
  QValidator::State validate(QString& input, [[maybe_unused]] int& pos) const override {
    if (fs::exists(fs::path(input.toStdString()).parent_path())) {
      return QValidator::Acceptable;
    }
    return QValidator::Invalid;
  }
};

template <typename T>
bool validated(T* box) {
  QString text;
  if constexpr (std::is_same_v<T, QLineEdit>) {
    text = box->text();
  } else if constexpr (std::is_same_v<T, QComboBox>) {
    text = box->currentText();
  }
  int pos = 0;
  QValidator::State state = box->validator()->validate(text, pos);
  switch (state) {
    case QValidator::Acceptable:
      box->setStyleSheet("");
      return true;
    case QValidator::Intermediate:
    case QValidator::Invalid:
      box->setStyleSheet("QComboBox { border: 2px solid red; }");
      return false;
  }
  unreachable();
}

bool ConfigEditor::is_valid() const {
  return validated(ui->scale_dropdown) && validated(ui->dpi_dropdown) &&
         validated(ui->out_dir_line_edit) && !m_config->processing_steps.empty() &&
         !m_config->las_files.empty();
}

ConfigEditor::ConfigEditor(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::ConfigEditor),
      m_config(std::make_unique<Config>(Config::Default())) {
  ui->setupUi(this);

  ui->scale_dropdown->setValidator(new QDoubleValidator(100.0, 100000.0, 2, this));
  connect(ui->scale_dropdown, &QComboBox::currentTextChanged, [this](const QString& text) {
    if (validated(ui->scale_dropdown)) {
      m_config->render.scale = std::stod(text.toStdString());
    }
    config_changed();
  });

  ui->out_dir_line_edit->setValidator(new ParentFolderExistsValidator());
  connect(ui->out_dir_line_edit, &QLineEdit::textChanged, [this](const QString& text) {
    if (validated(ui->out_dir_line_edit)) {
      m_config->set_output_directory(text.toStdString());
      config_changed();
    }
  });

  ui->dpi_dropdown->setValidator(new QDoubleValidator(1.0, 2400.0, 2, this));
  connect(ui->dpi_dropdown, &QComboBox::currentTextChanged, [this](const QString& text) {
    if (validated(ui->dpi_dropdown)) {
      m_config->render.dpi = std::stod(text.toStdString());
    }
    config_changed();
  });

  connect(ui->out_dir_button, &QPushButton::clicked, this, &ConfigEditor::open_output_directory);

  for (auto& [checkbox, step] : std::vector<std::pair<QCheckBox*, ProcessingStep>>{
           {ui->extract_borders_checkbox, ProcessingStep::TmpBorders},
           {ui->process_tiles_checkbox, ProcessingStep::Tiles},
           {ui->combine_tiles_checkbox, ProcessingStep::Combine}}) {
    connect(checkbox, &QCheckBox::stateChanged, [this, step](int state) {
      if (state == Qt::Checked) {
        m_config->processing_steps.insert(step);
      } else {
        m_config->processing_steps.erase(step);
      }
      config_changed();
    });
  }

  set_ui_to_config(*m_config);
}

ConfigEditor::~ConfigEditor() {}

void ConfigEditor::open_config_file() {
  QString config_file_name = QFileDialog::getOpenFileName(
      this, ("Open Config"), m_config->relative_path_to_config.string().c_str(),
      ("Config Files (*.json *.jsonc);;All files (*)"), nullptr, QFileDialog::ReadOnly);
  if (config_file_name.isEmpty()) {
    return;
  }
  m_config = std::make_unique<Config>(Config::FromFile(config_file_name.toStdString()));
  set_ui_to_config(*m_config);
}

void ConfigEditor::save_config_file() {
  QString config_file_name = QFileDialog::getSaveFileName(
      this, ("Save Config"), m_config->relative_path_to_config.string().c_str(),
      ("Config Files (*.json *.jsonc);;All files (*)"), nullptr, QFileDialog::ReadOnly);
  if (config_file_name.isEmpty()) {
    return;
  }
  m_config->write_to_file(config_file_name.toStdString());
}

void ConfigEditor::open_output_directory() {
  QString output_dir_name = QFileDialog::getExistingDirectory(
      this, tr("Choose Output Directory"), m_config->output_path().string().c_str(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (output_dir_name.isEmpty()) {
    return;
  }
  m_config->set_output_directory(output_dir_name.toStdString());
  ui->out_dir_line_edit->setText(output_dir_name);
}

void ConfigEditor::set_ui_to_config(const Config& config) {
  ui->out_dir_line_edit->setText(config.output_path().string().c_str());

  ui->scale_dropdown->setCurrentText(double_to_string(config.render.scale).c_str());

  ui->dpi_dropdown->setCurrentText(double_to_string(config.render.dpi).c_str());

  ui->extract_borders_checkbox->setChecked(
      std::find(config.processing_steps.begin(), config.processing_steps.end(),
                ProcessingStep::TmpBorders) != config.processing_steps.end());
  ui->process_tiles_checkbox->setChecked(
      std::find(config.processing_steps.begin(), config.processing_steps.end(),
                ProcessingStep::Tiles) != config.processing_steps.end());
  ui->combine_tiles_checkbox->setChecked(
      std::find(config.processing_steps.begin(), config.processing_steps.end(),
                ProcessingStep::Combine) != config.processing_steps.end());

  ui->treeWidget->clear();
  for (const fs::path& path : config.las_files) {
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, path.string().c_str());
  }
}
