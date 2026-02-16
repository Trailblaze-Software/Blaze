#include "config_editor.hpp"

#include <qdebug.h>

#include <QColorDialog>
#include <QDoubleValidator>
#include <QFileDialog>
#include <QIntValidator>
#include <QListWidget>
#include <QPainter>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <filesystem>

#include "assert/assert.hpp"
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

bool color_equals(const ColorVariant& v1, const ColorVariant& v2) {
  if (v1.index() != v2.index()) return false;
  if (std::holds_alternative<RGBColor>(v1)) {
    const auto& c1 = std::get<RGBColor>(v1);
    const auto& c2 = std::get<RGBColor>(v2);
    return c1.getRed() == c2.getRed() && c1.getGreen() == c2.getGreen() &&
           c1.getBlue() == c2.getBlue() && c1.getAlpha() == c2.getAlpha();
  } else {
    const auto& c1 = std::get<CMYKColor>(v1);
    const auto& c2 = std::get<CMYKColor>(v2);
    return c1.getCyan() == c2.getCyan() && c1.getMagenta() == c2.getMagenta() &&
           c1.getYellow() == c2.getYellow() && c1.getBlack() == c2.getBlack();
  }
}

QString get_color_name(const ColorVariant& color) {
  for (const auto& [name, map_color] : COLOR_MAP) {
    if (color_equals(color, map_color)) {
      return QString::fromStdString(name);
    }
  }
  return "";
}

QIcon create_color_icon(const ColorVariant& color) {
  QPixmap pixmap(16, 16);
  pixmap.fill(Qt::transparent);
  QPainter painter(&pixmap);

  RGBColor rgb = to_rgb(color);
  QColor qcolor(rgb.getRed(), rgb.getGreen(), rgb.getBlue(), rgb.getAlpha());

  painter.setBrush(qcolor);
  painter.setPen(Qt::black);
  painter.drawRect(0, 0, 15, 15);

  return QIcon(pixmap);
}

bool ConfigEditor::is_valid() const {
  bool all_las_files_exist = std::all_of(
      m_config->las_files.begin(), m_config->las_files.end(),
      [this](const fs::path& las_file) { return m_config->get_las_files(las_file).size(); });
  return validated(ui->scale_dropdown) && validated(ui->dpi_dropdown) &&
         validated(ui->out_dir_line_edit) && !m_config->processing_steps.empty() &&
         !m_config->las_files.empty() && all_las_files_exist;
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

  connect(ui->add_las_button, &QPushButton::clicked, this, &ConfigEditor::add_las_file);
  connect(ui->add_las_folder_button, &QPushButton::clicked, this, &ConfigEditor::add_las_folder);
  connect(ui->remove_las_button, &QPushButton::clicked, this, &ConfigEditor::remove_las_file);

  connect(ui->out_dir_button, &QPushButton::clicked, this, &ConfigEditor::open_output_directory);

  for (const auto& [checkbox, step] : std::vector<std::pair<QCheckBox*, ProcessingStep>>{
           {ui->process_tiles_checkbox, ProcessingStep::Tiles},
           {ui->combine_tiles_checkbox, ProcessingStep::Combine}}) {
    ProcessingStep ps = step;
    connect(checkbox, &QCheckBox::checkStateChanged, [this, ps](Qt::CheckState state) {
      if (state == Qt::CheckState::Checked) {
        m_config->processing_steps.insert(ps);
      } else {
        m_config->processing_steps.erase(ps);
      }
      config_changed();
    });
  }

  // General Tab
  ui->grid_bin_resolution->setValidator(new QDoubleValidator(0.0, 1000.0, 3, this));
  ui->ground_outlier_removal->setValidator(new QDoubleValidator(0.0, 1000.0, 3, this));
  ui->border_width->setValidator(new QDoubleValidator(0.0, 10000.0, 2, this));

  auto connect_general = [this](QWidget* widget) {
    if (auto* le = qobject_cast<QLineEdit*>(widget)) {
      connect(le, &QLineEdit::textChanged, this, &ConfigEditor::update_general_from_ui);
    } else if (auto* sb = qobject_cast<QSpinBox*>(widget)) {
      connect(sb, QOverload<int>::of(&QSpinBox::valueChanged), this,
              &ConfigEditor::update_general_from_ui);
    }
  };
  connect_general(ui->grid_bin_resolution);
  connect_general(ui->grid_downsample_factor);
  connect_general(ui->ground_outlier_removal);
  connect_general(ui->ground_min_intensity);
  connect_general(ui->ground_max_intensity);
  connect(ui->buildings_color, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &ConfigEditor::update_general_from_ui);
  connect_general(ui->border_width);

  // Contours Tab
  connect(ui->contours_list_widget, &QListWidget::itemSelectionChanged, this,
          &ConfigEditor::on_contour_selected);
  connect(ui->add_contour_button, &QPushButton::clicked, this, &ConfigEditor::add_contour);
  connect(ui->remove_contour_button, &QPushButton::clicked, this, &ConfigEditor::remove_contour);

  // Use currentIndexChanged for combos to handle "Add new color"
  connect(ui->contour_color_combo, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &ConfigEditor::update_contour_from_ui);

  auto connect_contour = [this](QWidget* widget) {
    if (auto* le = qobject_cast<QLineEdit*>(widget)) {
      connect(le, &QLineEdit::textChanged, this, &ConfigEditor::update_contour_from_ui);
    } else if (auto* sb = qobject_cast<QSpinBox*>(widget)) {
      connect(sb, QOverload<int>::of(&QSpinBox::valueChanged), this,
              &ConfigEditor::update_contour_from_ui);
    }
  };
  connect_contour(ui->contour_name_edit);
  connect_contour(ui->contour_interval_edit);
  connect_contour(ui->contour_min_points_edit);
  // contour_color_combo connected separately
  connect_contour(ui->contour_width_edit);

  // Water Tab
  connect(ui->water_list_widget, &QListWidget::itemSelectionChanged, this,
          &ConfigEditor::on_water_selected);
  connect(ui->add_water_button, &QPushButton::clicked, this, &ConfigEditor::add_water);
  connect(ui->remove_water_button, &QPushButton::clicked, this, &ConfigEditor::remove_water);

  connect(ui->water_color_combo, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &ConfigEditor::update_water_from_ui);

  auto connect_water = [this](QWidget* widget) {
    if (auto* le = qobject_cast<QLineEdit*>(widget)) {
      connect(le, &QLineEdit::textChanged, this, &ConfigEditor::update_water_from_ui);
    }
  };
  connect_water(ui->water_name_edit);
  connect_water(ui->water_catchment_edit);
  // water_color_combo connected separately
  connect_water(ui->water_width_edit);

  // Vegetation Tab
  connect(ui->vege_list_widget, &QListWidget::itemSelectionChanged, this,
          &ConfigEditor::on_vege_selected);
  connect(ui->add_vege_button, &QPushButton::clicked, this, &ConfigEditor::add_vege);
  connect(ui->remove_vege_button, &QPushButton::clicked, this, &ConfigEditor::remove_vege);
  connect(ui->add_vege_color_button, &QPushButton::clicked, this, &ConfigEditor::add_vege_color);
  connect(ui->remove_vege_color_button, &QPushButton::clicked, this,
          &ConfigEditor::remove_vege_color);
  connect(ui->vege_colors_table, &QTableWidget::cellChanged, this,
          &ConfigEditor::update_vege_color_from_ui);

  connect(ui->vege_bg_color_combo, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &ConfigEditor::update_vege_from_ui);

  auto connect_vege = [this](QWidget* widget) {
    if (auto* le = qobject_cast<QLineEdit*>(widget)) {
      connect(le, &QLineEdit::textChanged, this, &ConfigEditor::update_vege_from_ui);
    }
  };
  connect_vege(ui->vege_name_edit);
  connect_vege(ui->vege_min_height_edit);
  connect_vege(ui->vege_max_height_edit);

  // Colors Tab
  connect(ui->colors_list_widget, &QListWidget::itemSelectionChanged, this,
          &ConfigEditor::on_color_selected);
  connect(ui->add_color_button, &QPushButton::clicked, this, &ConfigEditor::add_color);
  connect(ui->remove_color_button, &QPushButton::clicked, this, &ConfigEditor::remove_color);
  connect(ui->pick_color_button, &QPushButton::clicked, this, &ConfigEditor::pick_color);
  connect(ui->color_type_combo, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &ConfigEditor::on_color_type_changed);

  auto connect_color = [this](QWidget* widget) {
    if (auto* le = qobject_cast<QLineEdit*>(widget)) {
      connect(le, &QLineEdit::textChanged, this, &ConfigEditor::update_color_from_ui);
    } else if (auto* sb = qobject_cast<QSpinBox*>(widget)) {
      connect(sb, QOverload<int>::of(&QSpinBox::valueChanged), this,
              &ConfigEditor::update_color_from_ui);
    }
  };
  connect_color(ui->color_name_edit);
  connect_color(ui->color_c1_spin);
  connect_color(ui->color_c2_spin);
  connect_color(ui->color_c3_spin);
  connect_color(ui->color_c4_spin);

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

void ConfigEditor::add_las_file() {
  fs::path directory;
  QStringList las_file_names = QFileDialog::getOpenFileNames(
      this, ("Open LAS file/s"), m_config->relative_path_to_config.string().c_str(),
      ("LAS Files (*.las *.laz);;All files (*)"), nullptr, QFileDialog::ReadOnly);
  if (las_file_names.isEmpty()) {
    return;
  }
  for (const QString& las_file_name : las_file_names) {
    m_config->las_files.push_back(las_file_name.toStdString());
  }
  set_ui_to_config(*m_config);
}

void ConfigEditor::remove_las_file() {
  QList<QTreeWidgetItem*> items = ui->treeWidget->selectedItems();
  for (QTreeWidgetItem* item : items) {
    m_config->las_files.erase(std::remove(m_config->las_files.begin(), m_config->las_files.end(),
                                          item->text(1).toStdString()),
                              m_config->las_files.end());
    delete item;
  }
  set_ui_to_config(*m_config);
}

void ConfigEditor::add_las_folder() {
  fs::path directory;
  QString las_folder_name = QFileDialog::getExistingDirectory(
      this, tr("Choose LAS Folder"), m_config->relative_path_to_config.string().c_str(),
      QFileDialog::DontResolveSymlinks);
  if (las_folder_name.isEmpty()) {
    return;
  }
  m_config->las_files.push_back(las_folder_name.toStdString());
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
  config_changed();
}

void ConfigEditor::populate_color_combo(QComboBox* combo) {
  bool was_blocked = combo->blockSignals(true);
  combo->clear();
  for (const auto& [name, color] : COLOR_MAP) {
    combo->addItem(create_color_icon(color), QString::fromStdString(name));
  }
  combo->addItem("Add new color...");
  combo->blockSignals(was_blocked);
}

void ConfigEditor::set_ui_to_config(const Config& config) {
  m_updating_ui = true;

  // 1. Populate all color combos first
  populate_color_combo(ui->buildings_color);
  populate_color_combo(ui->contour_color_combo);
  populate_color_combo(ui->water_color_combo);
  populate_color_combo(ui->vege_bg_color_combo);

  ui->out_dir_line_edit->setText(config.output_path().string().c_str());

  ui->scale_dropdown->setCurrentText(double_to_string(config.render.scale).c_str());
  ui->dpi_dropdown->setCurrentText(double_to_string(config.render.dpi).c_str());

  ui->process_tiles_checkbox->setChecked(
      std::find(config.processing_steps.begin(), config.processing_steps.end(),
                ProcessingStep::Tiles) != config.processing_steps.end());
  ui->combine_tiles_checkbox->setChecked(
      std::find(config.processing_steps.begin(), config.processing_steps.end(),
                ProcessingStep::Combine) != config.processing_steps.end());

  ui->treeWidget->clear();
  ui->treeWidget->setColumnWidth(0, 60);
  for (const fs::path& path : config.las_files) {
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(1, path.string().c_str());
    std::vector<fs::path> las_files = config.get_las_files(path);
    item->setExpanded(las_files.size() > 1);
    item->setText(0, QString::number(las_files.size()));
    item->setTextAlignment(0, Qt::AlignCenter);
    ui->treeWidget->addTopLevelItem(item);
    if (las_files.size() == 0) {
      item->setForeground(0, QBrush(Qt::red));
      item->setForeground(1, QBrush(Qt::red));
    } else if (fs::is_directory(path)) {
      for (const fs::path& entry : las_files) {
        QTreeWidgetItem* child = new QTreeWidgetItem(item);
        child->setText(1, entry.string().c_str());
        child->setDisabled(true);
        item->addChild(child);
      }
    }
  }

  // 2. Set General Tab fields and specific color selections
  ui->grid_bin_resolution->setText(QString::number(config.grid.bin_resolution));
  ui->grid_downsample_factor->setValue(config.grid.downsample_factor);
  ui->ground_outlier_removal->setText(QString::number(config.ground.outlier_removal_height_diff));
  ui->ground_min_intensity->setValue(config.ground.min_ground_intensity);
  ui->ground_max_intensity->setValue(config.ground.max_ground_intensity);
  ui->buildings_color->setCurrentText(get_color_name(config.buildings.color));
  ui->border_width->setText(QString::number(config.border_width));

  ui->vege_bg_color_combo->setCurrentText(get_color_name(config.vege.background_color));

  // 3. Populate Lists (these trigger detail loading for the first items via signals)
  // Since combos are already populated, details loading will correctly set the selections.
  populate_contour_list();
  populate_water_list();
  populate_vege_list();
  populate_color_list();

  m_updating_ui = false;
  config_changed();
}

// Helpers for General Tab
void ConfigEditor::update_general_from_ui() {
  if (m_updating_ui) return;

  if (ui->buildings_color->currentText() == "Add new color...") {
    ui->tabWidget->setCurrentWidget(ui->Colors_tab);
    add_color();
    return;
  }

  m_config->grid.bin_resolution = ui->grid_bin_resolution->text().toDouble();
  m_config->grid.downsample_factor = ui->grid_downsample_factor->value();
  m_config->ground.outlier_removal_height_diff = ui->ground_outlier_removal->text().toDouble();
  m_config->ground.min_ground_intensity = ui->ground_min_intensity->value();
  m_config->ground.max_ground_intensity = ui->ground_max_intensity->value();
  m_config->border_width = ui->border_width->text().toDouble();

  QString b_color = ui->buildings_color->currentText();
  if (COLOR_MAP.count(b_color.toStdString())) {
    m_config->buildings.color = COLOR_MAP.at(b_color.toStdString());
  }

  config_changed();
}

// Helpers for Contours
void ConfigEditor::populate_contour_list() {
  QString selected;
  if (auto* item = ui->contours_list_widget->currentItem()) {
    selected = item->text();
  }

  ui->contours_list_widget->clear();
  for (const auto& [name, config] : m_config->contours.configs) {
    ui->contours_list_widget->addItem(QString::fromStdString(name));
  }

  if (!selected.isEmpty()) {
    auto items = ui->contours_list_widget->findItems(selected, Qt::MatchExactly);
    if (!items.empty()) {
      ui->contours_list_widget->setCurrentItem(items.front());
    } else if (ui->contours_list_widget->count() > 0) {
      ui->contours_list_widget->setCurrentRow(0);
    }
  } else if (ui->contours_list_widget->count() > 0) {
    ui->contours_list_widget->setCurrentRow(0);
  }
}

void ConfigEditor::add_contour() {
  std::string name = "new_contour";
  int i = 1;
  while (m_config->contours.configs.count(name)) {
    name = "new_contour_" + std::to_string(i++);
  }
  m_config->contours.configs[name] = ContourConfig();
  populate_contour_list();
}

void ConfigEditor::remove_contour() {
  auto items = ui->contours_list_widget->selectedItems();
  if (items.empty()) return;
  std::string name = items.front()->text().toStdString();
  m_config->contours.configs.erase(name);
  populate_contour_list();
}

void ConfigEditor::on_contour_selected() {
  auto items = ui->contours_list_widget->selectedItems();
  if (items.empty()) return;
  load_contour_details(items.front()->text().toStdString());
}

void ConfigEditor::load_contour_details(const std::string& name) {
  bool was_updating = m_updating_ui;
  m_updating_ui = true;
  const auto& config = m_config->contours.configs.at(name);
  ui->contour_name_edit->setText(QString::fromStdString(name));
  ui->contour_interval_edit->setText(QString::number(config.interval));
  ui->contour_min_points_edit->setValue(config.min_points);
  ui->contour_width_edit->setText(QString::number(config.width));
  ui->contour_color_combo->setCurrentText(get_color_name(config.color));
  m_updating_ui = was_updating;
}

void ConfigEditor::update_contour_from_ui() {
  if (m_updating_ui) return;
  auto items = ui->contours_list_widget->selectedItems();
  if (items.empty()) return;

  if (ui->contour_color_combo->currentText() == "Add new color...") {
    ui->tabWidget->setCurrentWidget(ui->Colors_tab);
    add_color();
    return;
  }

  std::string old_name = items.front()->text().toStdString();
  std::string new_name = ui->contour_name_edit->text().toStdString();

  ContourConfig config = m_config->contours.configs.at(old_name);
  config.interval = ui->contour_interval_edit->text().toDouble();
  config.min_points = ui->contour_min_points_edit->value();
  config.width = ui->contour_width_edit->text().toDouble();

  QString color = ui->contour_color_combo->currentText();
  if (COLOR_MAP.count(color.toStdString())) {
    config.color = COLOR_MAP.at(color.toStdString());
  }

  if (old_name != new_name && !new_name.empty() && !m_config->contours.configs.count(new_name)) {
    m_config->contours.configs.erase(old_name);
    m_config->contours.configs[new_name] = config;
    items.front()->setText(QString::fromStdString(new_name));
  } else {
    m_config->contours.configs[old_name] = config;
  }

  config_changed();
}

// Helpers for Water
void ConfigEditor::populate_water_list() {
  QString selected;
  if (auto* item = ui->water_list_widget->currentItem()) {
    selected = item->text();
  }

  ui->water_list_widget->clear();
  for (const auto& [name, config] : m_config->water.configs) {
    ui->water_list_widget->addItem(QString::fromStdString(name));
  }

  if (!selected.isEmpty()) {
    auto items = ui->water_list_widget->findItems(selected, Qt::MatchExactly);
    if (!items.empty()) {
      ui->water_list_widget->setCurrentItem(items.front());
    } else if (ui->water_list_widget->count() > 0) {
      ui->water_list_widget->setCurrentRow(0);
    }
  } else if (ui->water_list_widget->count() > 0) {
    ui->water_list_widget->setCurrentRow(0);
  }
}

void ConfigEditor::add_water() {
  std::string name = "new_water";
  int i = 1;
  while (m_config->water.configs.count(name)) {
    name = "new_water_" + std::to_string(i++);
  }
  m_config->water.configs[name] = WaterConfig();
  populate_water_list();
}

void ConfigEditor::remove_water() {
  auto items = ui->water_list_widget->selectedItems();
  if (items.empty()) return;
  std::string name = items.front()->text().toStdString();
  m_config->water.configs.erase(name);
  populate_water_list();
}

void ConfigEditor::on_water_selected() {
  auto items = ui->water_list_widget->selectedItems();
  if (items.empty()) return;
  load_water_details(items.front()->text().toStdString());
}

void ConfigEditor::load_water_details(const std::string& name) {
  bool was_updating = m_updating_ui;
  m_updating_ui = true;
  const auto& config = m_config->water.configs.at(name);
  ui->water_name_edit->setText(QString::fromStdString(name));
  ui->water_catchment_edit->setText(QString::number(config.catchment));
  ui->water_width_edit->setText(QString::number(config.width));
  ui->water_color_combo->setCurrentText(get_color_name(config.color));
  m_updating_ui = was_updating;
}

void ConfigEditor::update_water_from_ui() {
  if (m_updating_ui) return;
  auto items = ui->water_list_widget->selectedItems();
  if (items.empty()) return;

  if (ui->water_color_combo->currentText() == "Add new color...") {
    ui->tabWidget->setCurrentWidget(ui->Colors_tab);
    add_color();
    return;
  }

  std::string old_name = items.front()->text().toStdString();
  std::string new_name = ui->water_name_edit->text().toStdString();

  WaterConfig config = m_config->water.configs.at(old_name);
  config.catchment = ui->water_catchment_edit->text().toDouble();
  config.width = ui->water_width_edit->text().toDouble();

  QString color = ui->water_color_combo->currentText();
  if (COLOR_MAP.count(color.toStdString())) {
    config.color = COLOR_MAP.at(color.toStdString());
  }

  if (old_name != new_name && !new_name.empty() && !m_config->water.configs.count(new_name)) {
    m_config->water.configs.erase(old_name);
    m_config->water.configs[new_name] = config;
    items.front()->setText(QString::fromStdString(new_name));
  } else {
    m_config->water.configs[old_name] = config;
  }
  config_changed();
}

// Helpers for Vegetation
void ConfigEditor::populate_vege_list() {
  QString selected;
  if (auto* item = ui->vege_list_widget->currentItem()) {
    selected = item->text();
  }

  ui->vege_list_widget->clear();
  for (const auto& config : m_config->vege.height_configs) {
    ui->vege_list_widget->addItem(QString::fromStdString(config.name));
  }

  if (!selected.isEmpty()) {
    auto items = ui->vege_list_widget->findItems(selected, Qt::MatchExactly);
    if (!items.empty()) {
      ui->vege_list_widget->setCurrentItem(items.front());
    } else if (ui->vege_list_widget->count() > 0) {
      ui->vege_list_widget->setCurrentRow(0);
    }
  } else if (ui->vege_list_widget->count() > 0) {
    ui->vege_list_widget->setCurrentRow(0);
  }
}

void ConfigEditor::add_vege() {
  VegeHeightConfig config;
  config.name = "new_vege";
  m_config->vege.height_configs.push_back(config);
  populate_vege_list();
}

void ConfigEditor::remove_vege() {
  int row = ui->vege_list_widget->currentRow();
  if (row < 0 || row >= (int)m_config->vege.height_configs.size()) return;
  m_config->vege.height_configs.erase(m_config->vege.height_configs.begin() + row);
  populate_vege_list();
}

void ConfigEditor::on_vege_selected() {
  int row = ui->vege_list_widget->currentRow();
  if (row < 0) return;
  load_vege_details(row);
}

void ConfigEditor::load_vege_details(int index) {
  if (index < 0 || index >= (int)m_config->vege.height_configs.size()) return;
  bool was_updating = m_updating_ui;
  m_updating_ui = true;
  const auto& config = m_config->vege.height_configs[index];
  ui->vege_name_edit->setText(QString::fromStdString(config.name));
  ui->vege_min_height_edit->setText(QString::number(config.min_height));
  ui->vege_max_height_edit->setText(QString::number(config.max_height));

  ui->vege_colors_table->setRowCount(0);
  for (const auto& pair : config.colors) {
    int r = ui->vege_colors_table->rowCount();
    ui->vege_colors_table->insertRow(r);
    ui->vege_colors_table->setItem(r, 0,
                                   new QTableWidgetItem(QString::number(pair.blocking_threshold)));

    QComboBox* combo = new QComboBox();
    populate_color_combo(combo);
    combo->setCurrentText(get_color_name(pair.color));
    connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this, r]() { update_vege_color_from_ui(r, 1); });
    ui->vege_colors_table->setCellWidget(r, 1, combo);
  }
  m_updating_ui = was_updating;
}

void ConfigEditor::update_vege_from_ui() {
  if (m_updating_ui) return;

  if (ui->vege_bg_color_combo->currentText() == "Add new color...") {
    ui->tabWidget->setCurrentWidget(ui->Colors_tab);
    add_color();
    return;
  }

  int row = ui->vege_list_widget->currentRow();
  if (row < 0 || row >= (int)m_config->vege.height_configs.size()) return;

  auto& config = m_config->vege.height_configs[row];
  config.name = ui->vege_name_edit->text().toStdString();
  config.min_height = ui->vege_min_height_edit->text().toDouble();
  config.max_height = ui->vege_max_height_edit->text().toDouble();

  QString bg_color = ui->vege_bg_color_combo->currentText();
  if (COLOR_MAP.count(bg_color.toStdString())) {
    m_config->vege.background_color = COLOR_MAP.at(bg_color.toStdString());
  }

  ui->vege_list_widget->item(row)->setText(QString::fromStdString(config.name));
  config_changed();
}

void ConfigEditor::add_vege_color() {
  int row = ui->vege_list_widget->currentRow();
  if (row < 0 || row >= (int)m_config->vege.height_configs.size()) return;

  m_config->vege.height_configs[row].colors.push_back({0.0, RGBColor(255, 255, 255)});
  load_vege_details(row);
  config_changed();
}

void ConfigEditor::remove_vege_color() {
  int row = ui->vege_list_widget->currentRow();
  if (row < 0 || row >= (int)m_config->vege.height_configs.size()) return;

  int color_row = ui->vege_colors_table->currentRow();
  if (color_row < 0 || color_row >= (int)m_config->vege.height_configs[row].colors.size()) return;

  auto& colors = m_config->vege.height_configs[row].colors;
  colors.erase(colors.begin() + color_row);
  load_vege_details(row);
  config_changed();
}

void ConfigEditor::update_vege_color_from_ui(int row, int column) {
  if (m_updating_ui) return;
  int vege_row = ui->vege_list_widget->currentRow();
  if (vege_row < 0 || vege_row >= (int)m_config->vege.height_configs.size()) return;

  auto& pair = m_config->vege.height_configs[vege_row].colors[row];
  if (column == 0) {
    pair.blocking_threshold = ui->vege_colors_table->item(row, column)->text().toDouble();
  } else if (column == 1) {
    QComboBox* combo = qobject_cast<QComboBox*>(ui->vege_colors_table->cellWidget(row, column));
    if (combo) {
      if (combo->currentText() == "Add new color...") {
        ui->tabWidget->setCurrentWidget(ui->Colors_tab);
        add_color();
        return;
      }
      QString color = combo->currentText();
      if (COLOR_MAP.count(color.toStdString())) {
        pair.color = COLOR_MAP.at(color.toStdString());
      }
    }
  }
  config_changed();
}

// Helpers for Colors
void ConfigEditor::populate_color_list() {
  QString selected;
  if (auto* item = ui->colors_list_widget->currentItem()) {
    selected = item->text();
  }

  ui->colors_list_widget->clear();
  for (const auto& [name, color] : COLOR_MAP) {
    ui->colors_list_widget->addItem(
        new QListWidgetItem(create_color_icon(color), QString::fromStdString(name)));
  }

  if (!selected.isEmpty()) {
    auto items = ui->colors_list_widget->findItems(selected, Qt::MatchExactly);
    if (!items.empty()) {
      ui->colors_list_widget->setCurrentItem(items.front());
    } else if (ui->colors_list_widget->count() > 0) {
      ui->colors_list_widget->setCurrentRow(0);
    }
  } else if (ui->colors_list_widget->count() > 0) {
    ui->colors_list_widget->setCurrentRow(0);
  }
}

void ConfigEditor::add_color() {
  std::string name = "new_color";
  int i = 1;
  while (COLOR_MAP.count(name)) {
    name = "new_color_" + std::to_string(i++);
  }
  COLOR_MAP[name] = RGBColor(255, 255, 255);
  set_ui_to_config(*m_config);  // Re-populate all lists
  // Select the new color in the Colors tab
  auto items = ui->colors_list_widget->findItems(QString::fromStdString(name), Qt::MatchExactly);
  if (!items.empty()) {
    ui->colors_list_widget->setCurrentItem(items.front());
  }
}

void ConfigEditor::remove_color() {
  auto items = ui->colors_list_widget->selectedItems();
  if (items.empty()) return;
  std::string name = items.front()->text().toStdString();
  COLOR_MAP.erase(name);
  set_ui_to_config(*m_config);  // Re-populate all lists
  config_changed();
}

void ConfigEditor::on_color_selected() {
  auto items = ui->colors_list_widget->selectedItems();
  if (items.empty()) return;
  load_color_details(items.front()->text().toStdString());
}

void ConfigEditor::load_color_details(const std::string& name) {
  if (!COLOR_MAP.count(name)) return;
  bool was_updating = m_updating_ui;
  m_updating_ui = true;
  const auto& color = COLOR_MAP.at(name);
  ui->color_name_edit->setText(QString::fromStdString(name));

  if (std::holds_alternative<RGBColor>(color)) {
    ui->color_type_combo->setCurrentIndex(0);  // RGB
    const auto& rgb = std::get<RGBColor>(color);
    ui->color_c1_spin->setValue(rgb.getRed());
    ui->color_c2_spin->setValue(rgb.getGreen());
    ui->color_c3_spin->setValue(rgb.getBlue());
    ui->color_c4_spin->setValue(rgb.getAlpha());
  } else {
    ui->color_type_combo->setCurrentIndex(1);  // CMYK
    const auto& cmyk = std::get<CMYKColor>(color);
    ui->color_c1_spin->setValue(cmyk.getCyan());
    ui->color_c2_spin->setValue(cmyk.getMagenta());
    ui->color_c3_spin->setValue(cmyk.getYellow());
    ui->color_c4_spin->setValue(cmyk.getBlack());
  }
  on_color_type_changed(ui->color_type_combo->currentIndex());  // Update labels
  m_updating_ui = was_updating;
}

void ConfigEditor::on_color_type_changed(int index) {
  if (m_updating_ui) {
    // Just update labels and maximums during loading
    if (index == 0) {  // RGB
      ui->label_c1->setText("Red:");
      ui->label_c2->setText("Green:");
      ui->label_c3->setText("Blue:");
      ui->label_c4->setText("Alpha:");
      ui->color_c1_spin->setMaximum(255);
      ui->color_c2_spin->setMaximum(255);
      ui->color_c3_spin->setMaximum(255);
      ui->color_c4_spin->setMaximum(255);
      ui->pick_color_button->setEnabled(true);
    } else {  // CMYK
      ui->label_c1->setText("Cyan:");
      ui->label_c2->setText("Magenta:");
      ui->label_c3->setText("Yellow:");
      ui->label_c4->setText("Black:");
      ui->color_c1_spin->setMaximum(100);
      ui->color_c2_spin->setMaximum(100);
      ui->color_c3_spin->setMaximum(100);
      ui->color_c4_spin->setMaximum(100);
      ui->pick_color_button->setEnabled(false);
    }
    return;
  }

  // Capture "old" values for conversion
  int v1 = ui->color_c1_spin->value();
  int v2 = ui->color_c2_spin->value();
  int v3 = ui->color_c3_spin->value();
  int v4 = ui->color_c4_spin->value();

  m_updating_ui = true;

  if (index == 0) {  // Switching TO RGB (from CMYK)
    CMYKColor cmyk(v1, v2, v3, v4);
    RGBColor rgb = RGBColor::FromCMYK(cmyk);

    ui->label_c1->setText("Red:");
    ui->label_c2->setText("Green:");
    ui->label_c3->setText("Blue:");
    ui->label_c4->setText("Alpha:");
    ui->color_c1_spin->setMaximum(255);
    ui->color_c2_spin->setMaximum(255);
    ui->color_c3_spin->setMaximum(255);
    ui->color_c4_spin->setMaximum(255);

    ui->color_c1_spin->setValue(rgb.getRed());
    ui->color_c2_spin->setValue(rgb.getGreen());
    ui->color_c3_spin->setValue(rgb.getBlue());
    ui->color_c4_spin->setValue(rgb.getAlpha());

    ui->pick_color_button->setEnabled(true);
  } else {  // Switching TO CMYK (from RGB)
    RGBColor rgb(v1, v2, v3, v4);
    CMYKColor cmyk = CMYKColor::FromRGB(rgb);

    ui->label_c1->setText("Cyan:");
    ui->label_c2->setText("Magenta:");
    ui->label_c3->setText("Yellow:");
    ui->label_c4->setText("Black:");
    ui->color_c1_spin->setMaximum(100);
    ui->color_c2_spin->setMaximum(100);
    ui->color_c3_spin->setMaximum(100);
    ui->color_c4_spin->setMaximum(100);

    ui->color_c1_spin->setValue(cmyk.getCyan());
    ui->color_c2_spin->setValue(cmyk.getMagenta());
    ui->color_c3_spin->setValue(cmyk.getYellow());
    ui->color_c4_spin->setValue(cmyk.getBlack());

    ui->pick_color_button->setEnabled(false);
  }

  m_updating_ui = false;
  update_color_from_ui();
}

void ConfigEditor::update_color_from_ui() {
  if (m_updating_ui) return;
  auto items = ui->colors_list_widget->selectedItems();
  if (items.empty()) return;
  std::string old_name = items.front()->text().toStdString();
  std::string new_name = ui->color_name_edit->text().toStdString();

  ColorVariant new_color;
  if (ui->color_type_combo->currentIndex() == 0) {  // RGB
    new_color = RGBColor(ui->color_c1_spin->value(), ui->color_c2_spin->value(),
                         ui->color_c3_spin->value(), ui->color_c4_spin->value());
  } else {  // CMYK
    new_color = CMYKColor(ui->color_c1_spin->value(), ui->color_c2_spin->value(),
                          ui->color_c3_spin->value(), ui->color_c4_spin->value());
  }

  if (old_name != new_name && !new_name.empty()) {
    if (!COLOR_MAP.count(new_name)) {
      COLOR_MAP.erase(old_name);
      COLOR_MAP[new_name] = new_color;
      items.front()->setText(QString::fromStdString(new_name));
      set_ui_to_config(*m_config);  // Name changed, refresh combos
    }
  } else {
    COLOR_MAP[old_name] = new_color;
    // Color value changed, refresh icons?
    // Yes, need to refresh UI to show new color icons
    set_ui_to_config(*m_config);
  }
  config_changed();
}

void ConfigEditor::pick_color() {
  QColor color =
      QColorDialog::getColor(Qt::white, this, "Pick Color", QColorDialog::ShowAlphaChannel);
  if (color.isValid()) {
    ui->color_type_combo->setCurrentIndex(0);  // Ensure RGB
    ui->color_c1_spin->setValue(color.red());
    ui->color_c2_spin->setValue(color.green());
    ui->color_c3_spin->setValue(color.blue());
    ui->color_c4_spin->setValue(color.alpha());
    // update_color_from_ui called by value changes
  }
}
