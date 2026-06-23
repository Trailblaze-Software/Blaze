#include "main_3d_window.hpp"

#include <qmessagebox.h>
#include <qtreewidget.h>

#include <QCheckBox>
#include <QColorDialog>
#include <QComboBox>
#include <QCoreApplication>
#include <QFileInfo>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QOpenGLWidget>
#include <QProcessEnvironment>
#include <QPushButton>
#include <QShortcut>
#include <QSignalBlocker>
#include <QSizePolicy>
#include <QSlider>
#include <QVBoxLayout>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <utility>

#include "blaze_output_loader.hpp"
#include "gui/point_cloud_visualization.hpp"
#include "ui_main_3d_window.h"
#include "utilities/env.hpp"
#include "utilities/progress_tracker.hpp"

namespace {

bool is_las_extension(const fs::path& path) {
  std::string ext = path.extension().string();
  for (char& c : ext) {
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  }
  return ext == ".las" || ext == ".laz";
}

std::vector<fs::path> collect_open_las_files(const std::vector<std::shared_ptr<Layer>>& layers) {
  std::vector<fs::path> las_files;
  for (const auto& layer : layers) {
    if (layer->kind() != LayerKind::PointCloud) {
      continue;
    }
    const auto* las_layer = dynamic_cast<const LASLayer*>(layer.get());
    if (!las_layer) {
      continue;
    }
    const fs::path& path = las_layer->file_path();
    if (!path.empty() && fs::exists(path) && is_las_extension(path)) {
      las_files.push_back(fs::absolute(path));
    }
  }
  return las_files;
}

QString blaze_gui_executable_path() {
  QString path = QCoreApplication::applicationDirPath();
#ifdef _WIN32
  path += "/Blaze.exe";
#else
  path += "/Blaze";
#endif
  return path;
}

bool is_draped_surface_layer(LayerKind kind) {
  return kind == LayerKind::DemSurface || kind == LayerKind::SlopeSurface ||
         kind == LayerKind::TexturedDem;
}

bool is_surface_style_layer(LayerKind kind) {
  return is_draped_surface_layer(kind) || kind == LayerKind::Contours;
}

QString format_classification_label(uint8_t classification) {
  for (const ClassificationStyle& style : CLASSIFICATION_STYLES) {
    if (style.code == classification) {
      return QString::fromLatin1(style.label);
    }
  }
  return QStringLiteral("Class %1").arg(classification);
}

}  // namespace

Q_DECLARE_METATYPE(std::shared_ptr<Layer>)

Main3DWindow::Main3DWindow() : ui(std::make_unique<Ui::Main3DWindow>()) {
  gl_widget = std::make_unique<GLWidget>(this);
  setWindowTitle(tr("Blaze 3D"));
  try {
    if (!QIcon::hasThemeIcon("list-add")) {
      QIcon::setThemeName("Humanity");
      QIcon::setFallbackThemeName("default");
    }
    ui->setupUi(this);

    connect(ui->actionOpen, &QAction::triggered, this, &Main3DWindow::open_layer_file);
    connect(ui->actionImportBlazeOutput, &QAction::triggered, this,
            &Main3DWindow::import_blaze_output);
    connect(ui->actionRunBlaze, &QAction::triggered, this, &Main3DWindow::run_blaze_on_layers);
    if (!m_blaze_process) {
      m_blaze_process = std::make_unique<QProcess>(this);
      m_blaze_process->setProcessChannelMode(QProcess::MergedChannels);
      connect(m_blaze_process.get(), &QProcess::readyReadStandardOutput, this, [this] {
        const QByteArray chunk = m_blaze_process->readAllStandardOutput();
        m_blaze_output.append(QString::fromLocal8Bit(chunk));
        // Echo Blaze's output to Blaze3D's console so it can be followed live.
        std::cout << chunk.toStdString() << std::flush;
      });
      connect(m_blaze_process.get(), &QProcess::finished, this,
              &Main3DWindow::handle_blaze_process_finished);
    }
    ui->horizontalLayout->addWidget(gl_widget.get(), 1);
    gl_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gl_widget->setMinimumSize(320, 240);
    gl_widget->set_point_pick_callback([this](const std::optional<PointPickResult>& pick) {
      if (pick) {
        show_point_pick_details(*pick);
      } else {
        clear_point_pick_details();
      }
    });

    qRegisterMetaType<std::shared_ptr<Layer>>();
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, &QTreeWidget::customContextMenuRequested, this,
            &Main3DWindow::on_treeWidget_customContextMenuRequested);
    connect(ui->treeWidget, &QTreeWidget::currentItemChanged, this,
            [this](QTreeWidgetItem* current, QTreeWidgetItem* previous) {
              (void)previous;
              (void)current;
              update_layer_panels_for_selection();
            });
    setup_animation_panel();
    setup_point_cloud_panel();
    setup_surface_layer_panel();
    setup_point_details_panel();
    auto* remove_shortcut = new QShortcut(QKeySequence::Delete, ui->treeWidget);
    connect(remove_shortcut, &QShortcut::activated, this, &Main3DWindow::remove_selected_layer);

  } catch (const std::exception& e) {
    QMessageBox::critical(this, "Error", e.what());
    exit(1);
  }
}

Main3DWindow::~Main3DWindow() {}

void Main3DWindow::setup_animation_panel() {
  auto* panel = new QGroupBox(tr("Animation"), this);
  auto* layout = new QVBoxLayout(panel);

  // Type selector
  auto* type_label = new QLabel(tr("Type"), panel);
  layout->addWidget(type_label);
  auto* type_combo = new QComboBox(panel);
  type_combo->addItem(tr("None"), static_cast<int>(GLWidget::AnimType::None));
  type_combo->addItem(tr("Orbit"), static_cast<int>(GLWidget::AnimType::Orbit));
  type_combo->addItem(tr("Wobble"), static_cast<int>(GLWidget::AnimType::Wobble));
  layout->addWidget(type_combo);

  // Orbit settings
  auto* orbit_group = new QWidget(panel);
  auto* orbit_layout = new QVBoxLayout(orbit_group);
  orbit_layout->setContentsMargins(0, 0, 0, 0);
  auto* orbit_period_label = new QLabel(tr("Period (s)"), orbit_group);
  orbit_layout->addWidget(orbit_period_label);
  auto* orbit_period_slider = new QSlider(Qt::Horizontal, orbit_group);
  orbit_period_slider->setRange(2, 120);
  orbit_period_slider->setValue(static_cast<int>(gl_widget->orbit_period()));
  auto* orbit_period_value = new QLabel(orbit_group);
  orbit_period_value->setNum(static_cast<int>(gl_widget->orbit_period()));
  orbit_period_value->setMinimumWidth(36);
  orbit_period_value->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  auto* orbit_period_row = new QHBoxLayout();
  orbit_period_row->addWidget(orbit_period_slider);
  orbit_period_row->addWidget(orbit_period_value);
  orbit_layout->addLayout(orbit_period_row);
  layout->addWidget(orbit_group);

  // Wobble settings
  auto* wobble_group = new QWidget(panel);
  auto* wobble_layout = new QVBoxLayout(wobble_group);
  wobble_layout->setContentsMargins(0, 0, 0, 0);

  auto* wobble_period_label = new QLabel(tr("Period (s)"), wobble_group);
  wobble_layout->addWidget(wobble_period_label);
  auto* wobble_period_slider = new QSlider(Qt::Horizontal, wobble_group);
  wobble_period_slider->setRange(3, 100);  // 0.3 to 10.0 seconds in 0.1 increments
  wobble_period_slider->setValue(static_cast<int>(gl_widget->wobble_period() * 10.0));
  auto* wobble_period_value = new QLabel(wobble_group);
  wobble_period_value->setText(QString::number(gl_widget->wobble_period(), 'f', 1));
  wobble_period_value->setMinimumWidth(36);
  wobble_period_value->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  auto* wobble_period_row = new QHBoxLayout();
  wobble_period_row->addWidget(wobble_period_slider);
  wobble_period_row->addWidget(wobble_period_value);
  wobble_layout->addLayout(wobble_period_row);

  auto* wobble_amp_label = new QLabel(tr("Amplitude (deg)"), wobble_group);
  wobble_layout->addWidget(wobble_amp_label);
  auto* wobble_amp_slider = new QSlider(Qt::Horizontal, wobble_group);
  wobble_amp_slider->setRange(1, 50);  // 0.1 to 5.0 degrees
  wobble_amp_slider->setValue(static_cast<int>(gl_widget->wobble_amplitude() * 10.0));
  auto* wobble_amp_value = new QLabel(wobble_group);
  wobble_amp_value->setText(QString::number(gl_widget->wobble_amplitude(), 'f', 1));
  wobble_amp_value->setMinimumWidth(36);
  wobble_amp_value->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  auto* wobble_amp_row = new QHBoxLayout();
  wobble_amp_row->addWidget(wobble_amp_slider);
  wobble_amp_row->addWidget(wobble_amp_value);
  wobble_layout->addLayout(wobble_amp_row);
  layout->addWidget(wobble_group);

  // Show/hide settings based on type
  auto update_visibility = [=](int type) {
    orbit_group->setVisible(type == static_cast<int>(GLWidget::AnimType::Orbit));
    wobble_group->setVisible(type == static_cast<int>(GLWidget::AnimType::Wobble));
  };
  update_visibility(static_cast<int>(GLWidget::AnimType::None));
  wobble_group->hide();
  orbit_group->hide();

  // Connections
  connect(type_combo, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this, type_combo, update_visibility](int /*idx*/) {
            int t = type_combo->currentData().toInt();
            update_visibility(t);
            gl_widget->set_anim_type(t);
          });
  connect(orbit_period_slider, &QSlider::valueChanged, this, [this, orbit_period_value](int v) {
    orbit_period_value->setNum(v);
    gl_widget->set_orbit_period(static_cast<double>(v));
  });
  connect(wobble_period_slider, &QSlider::valueChanged, this, [this, wobble_period_value](int v) {
    double secs = static_cast<double>(v) * 0.1;
    wobble_period_value->setText(QString::number(secs, 'f', 1));
    gl_widget->set_wobble_period(secs);
  });
  connect(wobble_amp_slider, &QSlider::valueChanged, this, [this, wobble_amp_value](int v) {
    double deg = static_cast<double>(v) * 0.1;
    wobble_amp_value->setText(QString::number(deg, 'f', 1));
    gl_widget->set_wobble_amplitude(deg);
  });

  ui->verticalLayout->insertWidget(0, panel);
}

void Main3DWindow::setup_point_cloud_panel() {
  m_point_cloud_panel = new QGroupBox(tr("Point Cloud"), this);
  auto* layout = new QVBoxLayout(m_point_cloud_panel);

  auto* size_label = new QLabel(tr("Point radius (m)"), m_point_cloud_panel);
  m_point_size_slider = new QSlider(Qt::Horizontal, m_point_cloud_panel);
  m_point_size_slider->setRange(8, 1200);
  m_point_size_slider->setValue(150);
  m_point_size_value_label = new QLabel(m_point_cloud_panel);
  m_point_size_value_label->setMinimumWidth(60);
  m_point_size_value_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  auto* size_row = new QHBoxLayout();
  size_row->addWidget(m_point_size_slider);
  size_row->addWidget(m_point_size_value_label);
  layout->addWidget(size_label);
  layout->addLayout(size_row);

  auto* alpha_label = new QLabel(tr("Opacity"), m_point_cloud_panel);
  m_point_alpha_slider = new QSlider(Qt::Horizontal, m_point_cloud_panel);
  m_point_alpha_slider->setRange(0, 100);
  m_point_alpha_slider->setValue(100);
  m_point_alpha_value_label = new QLabel(m_point_cloud_panel);
  m_point_alpha_value_label->setMinimumWidth(52);
  m_point_alpha_value_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  auto* alpha_row = new QHBoxLayout();
  alpha_row->addWidget(m_point_alpha_slider);
  alpha_row->addWidget(m_point_alpha_value_label);
  layout->addWidget(alpha_label);
  layout->addLayout(alpha_row);

  auto* budget_label = new QLabel(tr("Stream budget (ms)"), m_point_cloud_panel);
  m_point_stream_budget_slider = new QSlider(Qt::Horizontal, m_point_cloud_panel);
  m_point_stream_budget_slider->setRange(8, 200);
  m_point_stream_budget_slider->setValue(30);
  m_point_stream_budget_slider->setToolTip(
      tr("Target GPU time per streaming frame. Higher = denser points when zoomed out, slower."));
  m_point_stream_budget_value_label = new QLabel(m_point_cloud_panel);
  m_point_stream_budget_value_label->setMinimumWidth(52);
  m_point_stream_budget_value_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  auto* budget_row = new QHBoxLayout();
  budget_row->addWidget(m_point_stream_budget_slider);
  budget_row->addWidget(m_point_stream_budget_value_label);
  layout->addWidget(budget_label);
  layout->addLayout(budget_row);

  auto* color_label = new QLabel(tr("Color mode"), m_point_cloud_panel);
  m_point_color_mode_combo = new QComboBox(m_point_cloud_panel);
  m_point_color_mode_combo->addItem(tr("From file"), static_cast<int>(PointColorMode::File));
  m_point_color_mode_combo->addItem(tr("Classification"),
                                    static_cast<int>(PointColorMode::Classification));
  m_point_color_mode_combo->addItem(tr("Fixed color"), static_cast<int>(PointColorMode::Fixed));
  layout->addWidget(color_label);
  layout->addWidget(m_point_color_mode_combo);

  m_point_fixed_color_button = new QPushButton(tr("Choose color..."), m_point_cloud_panel);
  layout->addWidget(m_point_fixed_color_button);

  ui->verticalLayout->insertWidget(1, m_point_cloud_panel);
  m_point_cloud_panel->hide();

  connect(m_point_size_slider, &QSlider::valueChanged, this, [this](int) {
    update_point_cloud_value_labels();
    apply_point_cloud_style_from_ui();
  });
  connect(m_point_alpha_slider, &QSlider::valueChanged, this, [this](int) {
    update_point_cloud_value_labels();
    apply_point_cloud_style_from_ui();
  });
  connect(m_point_stream_budget_slider, &QSlider::valueChanged, this, [this](int) {
    update_point_cloud_value_labels();
    apply_point_cloud_style_from_ui();
  });
  update_point_cloud_value_labels();
  connect(m_point_color_mode_combo, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this](int) { apply_point_cloud_style_from_ui(); });
  connect(m_point_fixed_color_button, &QPushButton::clicked, this, [this] {
    auto layer = m_active_las_layer.lock();
    if (!layer) {
      return;
    }
    const std::array<uint8_t, 3>& rgb = layer->fixed_point_color();
    const QColor initial(rgb[0], rgb[1], rgb[2]);
    const QColor chosen = QColorDialog::getColor(initial, this, tr("Point cloud color"),
                                                 QColorDialog::DontUseNativeDialog);
    if (!chosen.isValid()) {
      return;
    }
    layer->set_fixed_point_color(
        {{static_cast<uint8_t>(chosen.red()), static_cast<uint8_t>(chosen.green()),
          static_cast<uint8_t>(chosen.blue())}});
    layer->set_point_color_mode(PointColorMode::Fixed);
    m_updating_point_cloud_ui = true;
    m_point_color_mode_combo->setCurrentIndex(
        m_point_color_mode_combo->findData(static_cast<int>(PointColorMode::Fixed)));
    m_updating_point_cloud_ui = false;
    update_layer_panels_for_selection();
    gl_widget->update();
  });
}

void Main3DWindow::setup_surface_layer_panel() {
  m_surface_layer_panel = new QGroupBox(tr("Surface Layer"), this);
  auto* layout = new QVBoxLayout(m_surface_layer_panel);

  auto* opacity_label = new QLabel(tr("Opacity"), m_surface_layer_panel);
  m_surface_opacity_slider = new QSlider(Qt::Horizontal, m_surface_layer_panel);
  m_surface_opacity_slider->setRange(0, 100);
  m_surface_opacity_slider->setValue(100);
  m_surface_opacity_value_label = new QLabel(m_surface_layer_panel);
  m_surface_opacity_value_label->setMinimumWidth(52);
  m_surface_opacity_value_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  auto* opacity_row = new QHBoxLayout();
  opacity_row->addWidget(m_surface_opacity_slider);
  opacity_row->addWidget(m_surface_opacity_value_label);
  layout->addWidget(opacity_label);
  layout->addLayout(opacity_row);

  ui->verticalLayout->insertWidget(2, m_surface_layer_panel);
  m_surface_layer_panel->hide();

  connect(m_surface_opacity_slider, &QSlider::valueChanged, this, [this](int) {
    update_surface_layer_value_labels();
    apply_surface_layer_style_from_ui();
  });
  update_surface_layer_value_labels();
}

void Main3DWindow::setup_point_details_panel() {
  m_point_details_panel = new QGroupBox(tr("Selected Point"), this);
  auto* layout = new QVBoxLayout(m_point_details_panel);
  m_point_details_label =
      new QLabel(tr("Click a point in the viewer to inspect it."), m_point_details_panel);
  m_point_details_label->setWordWrap(true);
  m_point_details_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
  layout->addWidget(m_point_details_label);
  ui->verticalLayout->insertWidget(3, m_point_details_panel);
}

void Main3DWindow::show_point_pick_details(const PointPickResult& pick) {
  if (!m_point_details_label) {
    return;
  }

  const OctreePoint& point = pick.point;
  QString color_line;
  if (point.has_file_rgb) {
    color_line = tr("RGB: %1, %2, %3").arg(point.file_r).arg(point.file_g).arg(point.file_b);
  } else {
    color_line = tr("RGB: (not stored)");
  }

  m_point_details_label->setText(tr("Layer: %1\n"
                                    "World X: %2\n"
                                    "World Y: %3\n"
                                    "World Z: %4\n"
                                    "Intensity: %5\n"
                                    "Classification: %6 (%7)\n"
                                    "%8")
                                     .arg(QString::fromStdString(pick.layer_name))
                                     .arg(pick.world_x, 0, 'f', 3)
                                     .arg(pick.world_y, 0, 'f', 3)
                                     .arg(pick.world_z, 0, 'f', 3)
                                     .arg(point.intensity)
                                     .arg(point.classification)
                                     .arg(format_classification_label(point.classification))
                                     .arg(color_line));
}

void Main3DWindow::clear_point_pick_details() {
  if (m_point_details_label) {
    m_point_details_label->setText(tr("Click a point in the viewer to inspect it."));
  }
}

void Main3DWindow::update_layer_panels_for_selection() {
  update_point_cloud_panel_for_selection();
  update_surface_layer_panel_for_selection();
}

void Main3DWindow::update_point_cloud_panel_for_selection() {
  QTreeWidgetItem* item = ui->treeWidget->currentItem();
  std::shared_ptr<LASLayer> las_layer;
  if (item) {
    const auto layer = item->data(0, Qt::UserRole).value<std::shared_ptr<Layer>>();
    las_layer = std::dynamic_pointer_cast<LASLayer>(layer);
  }
  m_active_las_layer = las_layer;
  if (!las_layer) {
    m_point_cloud_panel->hide();
    return;
  }

  m_updating_point_cloud_ui = true;
  m_point_size_slider->setValue(
      static_cast<int>(std::lround(las_layer->point_radius_m() * 1000.0f)));
  m_point_alpha_slider->setValue(static_cast<int>(std::lround(las_layer->point_alpha() * 100.0f)));
  m_point_stream_budget_slider->setValue(
      static_cast<int>(std::lround(las_layer->point_stream_budget_ms())));
  const int mode_index =
      m_point_color_mode_combo->findData(static_cast<int>(las_layer->point_color_mode()));
  if (mode_index >= 0) {
    m_point_color_mode_combo->setCurrentIndex(mode_index);
  }
  const std::array<uint8_t, 3>& rgb = las_layer->fixed_point_color();
  m_point_fixed_color_button->setStyleSheet(
      QString("background-color: rgb(%1,%2,%3);").arg(rgb[0]).arg(rgb[1]).arg(rgb[2]));
  m_point_fixed_color_button->setEnabled(las_layer->point_color_mode() == PointColorMode::Fixed);
  m_point_cloud_panel->show();
  update_point_cloud_value_labels();
  m_updating_point_cloud_ui = false;
}

void Main3DWindow::update_surface_layer_panel_for_selection() {
  QTreeWidgetItem* item = ui->treeWidget->currentItem();
  std::shared_ptr<Layer> surface_layer;
  if (item) {
    const auto layer = item->data(0, Qt::UserRole).value<std::shared_ptr<Layer>>();
    if (layer && is_surface_style_layer(layer->kind())) {
      surface_layer = layer;
    }
  }
  m_active_surface_layer = surface_layer;
  if (!surface_layer) {
    m_surface_layer_panel->hide();
    return;
  }

  m_updating_surface_ui = true;
  m_surface_opacity_slider->setValue(
      static_cast<int>(std::lround(surface_layer->opacity() * 100.0f)));
  m_surface_layer_panel->show();
  update_surface_layer_value_labels();
  m_updating_surface_ui = false;
}

void Main3DWindow::update_surface_layer_value_labels() {
  if (!m_surface_opacity_slider || !m_surface_opacity_value_label) {
    return;
  }
  m_surface_opacity_value_label->setText(QString("%1%").arg(m_surface_opacity_slider->value()));
}

void Main3DWindow::apply_surface_layer_style_from_ui() {
  if (m_updating_surface_ui) {
    return;
  }
  auto layer = m_active_surface_layer.lock();
  if (!layer || !m_surface_opacity_slider) {
    return;
  }
  layer->set_opacity(static_cast<float>(m_surface_opacity_slider->value()) / 100.0f);
  gl_widget->update();
}

void Main3DWindow::update_point_cloud_value_labels() {
  if (!m_point_size_value_label || !m_point_alpha_value_label ||
      !m_point_stream_budget_value_label || !m_point_size_slider || !m_point_alpha_slider ||
      !m_point_stream_budget_slider) {
    return;
  }
  const double radius_m = m_point_size_slider->value() / 1000.0;
  m_point_size_value_label->setText(radius_m >= 0.1 ? QString("%1 m").arg(radius_m, 0, 'f', 2)
                                                    : QString("%1 m").arg(radius_m, 0, 'f', 3));
  m_point_alpha_value_label->setText(QString("%1%").arg(m_point_alpha_slider->value()));
  m_point_stream_budget_value_label->setText(
      tr("%1 ms").arg(m_point_stream_budget_slider->value()));
}

void Main3DWindow::apply_point_cloud_style_from_ui() {
  if (m_updating_point_cloud_ui) {
    return;
  }
  auto layer = m_active_las_layer.lock();
  if (!layer || !m_point_size_slider || !m_point_alpha_slider || !m_point_stream_budget_slider ||
      !m_point_color_mode_combo) {
    return;
  }
  layer->set_point_radius_m(static_cast<float>(m_point_size_slider->value()) / 1000.0f);
  layer->set_point_alpha(static_cast<float>(m_point_alpha_slider->value()) / 100.0f);
  layer->set_point_stream_budget_ms(static_cast<float>(m_point_stream_budget_slider->value()));
  const PointColorMode mode =
      static_cast<PointColorMode>(m_point_color_mode_combo->currentData().toInt());
  layer->set_point_color_mode(mode);
  m_point_fixed_color_button->setEnabled(mode == PointColorMode::Fixed);
  gl_widget->update();
}

AsyncProgressTracker Main3DWindow::add_progress_tracker() {
  ProgressTrackerBar* bar = new ProgressTrackerBar(ui->statusBar);
  ui->statusBar->addPermanentWidget(bar);
  // Claimed by the next add_layer() and keyed to that layer.
  m_pending_progress_bar = bar;
  return bar->tracker();
}

void Main3DWindow::add_layer_to_tree(std::shared_ptr<Layer> layer) {
  QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
  item->setText(0, QString::fromStdString(layer->name()));
  item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
  item->setCheckState(0, layer->visible() ? Qt::Checked : Qt::Unchecked);
  item->setData(0, Qt::UserRole, QVariant::fromValue(layer));
  ui->treeWidget->addTopLevelItem(item);
  ui->treeWidget->resizeColumnToContents(0);
}

void Main3DWindow::add_layer(std::unique_ptr<Layer> layer) {
  auto shared = std::shared_ptr<Layer>(std::move(layer));
  m_layers.push_back(shared);
  if (m_pending_progress_bar) {
    m_layer_progress_bars[shared.get()] = m_pending_progress_bar;
    m_pending_progress_bar = nullptr;
  }
  add_layer_to_tree(shared);
  gl_widget->add_layer(shared);
  connect(shared.get(), &Layer::data_updated, this, &Main3DWindow::maybe_exit_after_load);
  if (auto* las_layer = dynamic_cast<LASLayer*>(shared.get())) {
    connect(las_layer, &LASLayer::point_colors_changed, this,
            &Main3DWindow::update_point_cloud_panel_for_selection);
  }
  update_render_mode();
  maybe_exit_after_load();
}

void Main3DWindow::open_layer_file() {
  std::string filename =
      QFileDialog::getOpenFileName(this, "Open LAS file", "", "LIDAR Point Clouds (*.las, *.laz)")
          .toStdString();
  if (filename.empty()) {
    return;
  }
  m_defer_render_until_loaded = false;
  add_layer(std::make_unique<LASLayer>(filename, add_progress_tracker(), scene_reference_crs()));
}

void Main3DWindow::import_blaze_output() {
  QString dir = QFileDialog::getExistingDirectory(this, "Import Blaze Output Folder", QString());
  if (dir.isEmpty()) {
    return;
  }
  import_blaze_output_from_path(dir.toStdString());
}

void Main3DWindow::import_blaze_output_from_path(const std::string& directory) {
  m_defer_render_until_loaded = true;
  const BlazeOutputDiscovery discovery = discover_blaze_output_with_info(directory);
  const BlazeOutputSet& outputs = discovery.outputs;
  if (!outputs.filled_dem && !outputs.contours) {
    const std::string message = format_blaze_output_discovery_error(directory, discovery);
    if (isVisible()) {
      QMessageBox::warning(this, "No outputs found", QString::fromStdString(message));
    } else {
      std::cerr << message << std::endl;
      exit(1);
    }
    return;
  }
  if (outputs.filled_dem) {
    if (outputs.final_img) {
      add_layer(std::make_unique<TexturedDemLayer>(*outputs.filled_dem, *outputs.final_img,
                                                   add_progress_tracker(), scene_reference_crs()));
    } else {
      add_layer(std::make_unique<DemLayer>(*outputs.filled_dem, add_progress_tracker(),
                                           std::nullopt, scene_reference_crs()));
    }

    if (outputs.slope) {
      const fs::path& slope_dem =
          outputs.smooth_ground ? *outputs.smooth_ground : *outputs.filled_dem;
      auto slope_layer = std::make_unique<SlopeLayer>(
          slope_dem, *outputs.slope, add_progress_tracker(), scene_reference_crs());
      if (outputs.final_img) {
        slope_layer->set_visible(false);
      }
      add_layer(std::move(slope_layer));
    }
  }

  if (outputs.contours) {
    add_layer(std::make_unique<ContourLayer>(*outputs.contours, add_progress_tracker(),
                                             scene_reference_crs()));
  }
  update_render_mode();
  maybe_exit_after_load();
}

void Main3DWindow::set_exit_after_load(bool exit_after_load) {
  m_exit_after_load = exit_after_load;
  update_render_mode();
}

void Main3DWindow::set_defer_render_until_loaded(bool defer) {
  m_defer_render_until_loaded = defer;
  update_render_mode();
}

void Main3DWindow::update_render_mode() {
  if (!gl_widget) {
    return;
  }
  const bool all_ready = !m_layers.empty() && std::all_of(m_layers.begin(), m_layers.end(),
                                                          [](const std::shared_ptr<Layer>& layer) {
                                                            return layer_is_ready(*layer);
                                                          });
  const char* platform = blaze::get_env("QT_QPA_PLATFORM");
  const bool offscreen = platform != nullptr && std::string(platform) == "offscreen";
  const bool load_only = offscreen || (m_defer_render_until_loaded && !all_ready) ||
                         (m_exit_after_load && !m_exit_after_render);
  gl_widget->set_load_only_mode(load_only);
  if (all_ready && !offscreen) {
    gl_widget->update();
  }
}

bool Main3DWindow::layer_is_ready(const Layer& layer) {
  switch (layer.kind()) {
    case LayerKind::DemSurface:
      return static_cast<const DemLayer&>(layer).raster().ready();
    case LayerKind::SlopeSurface:
      return static_cast<const SlopeLayer&>(layer).raster().ready();
    case LayerKind::TexturedDem:
      return static_cast<const TexturedDemLayer&>(layer).raster().ready();
    case LayerKind::Contours:
      return static_cast<const ContourLayer&>(layer).ready();
    case LayerKind::PointCloud:
      return static_cast<const LASLayer&>(layer).las_data().load_complete();
  }
  return true;
}

void Main3DWindow::maybe_exit_after_load() {
  update_render_mode();
  if (!m_exit_after_load || m_layers.empty()) {
    return;
  }
  for (const auto& layer : m_layers) {
    if (!layer_is_ready(*layer)) {
      return;
    }
  }
  if (!m_exit_after_render) {
    m_exit_after_render = true;
    update_render_mode();
  }
  connect(gl_widget.get(), &QOpenGLWidget::frameSwapped, this,
          &Main3DWindow::finish_exit_after_load, Qt::SingleShotConnection);
  gl_widget->update();
}

void Main3DWindow::finish_exit_after_load() {
  if (!m_exit_after_load || m_exit_after_load_fired) return;
  m_exit_after_load_fired = true;
  std::cout << "All layers loaded successfully." << std::endl;
  if (m_bench_mode) {
    QTimer::singleShot(100, this, [this] { gl_widget->start_bench_orbit(10.0); });
    return;
  }
  QApplication::quit();
}

void Main3DWindow::run_blaze_on_layers() {
  const std::vector<fs::path> las_files = collect_open_las_files(m_layers);
  if (las_files.empty()) {
    QMessageBox::warning(this, "No LAS layers",
                         "Open one or more LAS/LAZ point cloud layers before running Blaze.");
    return;
  }

  if (m_blaze_process->state() != QProcess::NotRunning) {
    QMessageBox::information(this, "Blaze running",
                             "Blaze is already running. Wait for it to finish before starting "
                             "another run.");
    return;
  }

  const QString blaze_exe = blaze_gui_executable_path();
  if (!QFileInfo::exists(blaze_exe)) {
    QMessageBox::critical(this, "Blaze not found",
                          "Could not find the Blaze GUI executable next to Blaze3D:\n" + blaze_exe);
    return;
  }

  const fs::path output_dir = fs::absolute(las_files.front().parent_path() / "out");
  m_pending_blaze_output = output_dir;
  m_blaze_output.clear();

  QStringList args;
  for (const fs::path& las_file : las_files) {
    args << "--las-file" << QString::fromStdString(las_file.string());
  }

  QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  env.insert("BLAZE3D_EXPECT_OUTPUT", QString::fromStdString(output_dir.string()));
  env.insert("BLAZE_EXIT_AFTER_RUN", "1");
  m_blaze_process->setProcessEnvironment(env);
  m_blaze_process->setProgram(blaze_exe);
  m_blaze_process->setArguments(args);
  m_blaze_process->start();

  if (m_blaze_process->state() == QProcess::NotRunning) {
    m_pending_blaze_output.reset();
    QMessageBox::critical(this, "Launch failed",
                          "Failed to start Blaze.\n\nExecutable: " + blaze_exe);
  }
}

void Main3DWindow::handle_blaze_process_finished(int exit_code, QProcess::ExitStatus status) {
  const std::optional<fs::path> output_dir = std::exchange(m_pending_blaze_output, std::nullopt);
  if (!output_dir) {
    return;
  }
  if (status != QProcess::NormalExit || exit_code != 0) {
    QString detail = m_blaze_output.trimmed();
    // Keep the dialog readable: only show the tail of the captured log.
    constexpr int MAX_DETAIL_CHARS = 2000;
    if (detail.size() > MAX_DETAIL_CHARS) {
      detail = "...\n" + detail.right(MAX_DETAIL_CHARS);
    }
    QString message =
        status != QProcess::NormalExit
            ? QString("Blaze crashed before finishing. Output was not imported.")
            : QString("Blaze exited with code %1. Output was not imported.").arg(exit_code);
    if (!detail.isEmpty()) {
      message += "\n\nBlaze output:\n" + detail;
    }
    QMessageBox::warning(this, "Blaze failed", message);
    return;
  }

  import_blaze_output_from_path(output_dir->string());
  QMessageBox::information(this, "Blaze output imported",
                           QString("Imported blaze outputs from:\n%1")
                               .arg(QString::fromStdString(output_dir->string())));
}

void Main3DWindow::on_treeWidget_itemChanged(QTreeWidgetItem* item, int column) {
  if (column != 0) {
    return;
  }
  const auto layer = item->data(0, Qt::UserRole).value<std::shared_ptr<Layer>>();
  if (!layer) {
    return;
  }
  const bool visible = item->checkState(0) == Qt::Checked;
  layer->set_visible(visible);
  gl_widget->set_layer_visible(layer.get(), visible);

  if (visible && is_draped_surface_layer(layer->kind())) {
    for (const std::shared_ptr<Layer>& other : m_layers) {
      if (!other || other == layer || !is_draped_surface_layer(other->kind()) ||
          !other->visible()) {
        continue;
      }
      other->set_visible(false);
      gl_widget->set_layer_visible(other.get(), false);
      if (QTreeWidgetItem* other_item = find_tree_item_for_layer(other.get())) {
        QSignalBlocker blocker(ui->treeWidget);
        other_item->setCheckState(0, Qt::Unchecked);
      }
    }
  }
}

QTreeWidgetItem* Main3DWindow::find_tree_item_for_layer(Layer* layer) const {
  for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
    QTreeWidgetItem* item = ui->treeWidget->topLevelItem(i);
    const auto item_layer = item->data(0, Qt::UserRole).value<std::shared_ptr<Layer>>();
    if (item_layer && item_layer.get() == layer) {
      return item;
    }
  }
  return nullptr;
}

void Main3DWindow::remove_layer(const std::shared_ptr<Layer>& layer) {
  if (!layer) {
    return;
  }
  const auto it =
      std::find_if(m_layers.begin(), m_layers.end(),
                   [&layer](const std::shared_ptr<Layer>& ptr) { return ptr == layer; });
  if (it == m_layers.end()) {
    return;
  }

  disconnect(layer.get(), &Layer::data_updated, this, &Main3DWindow::maybe_exit_after_load);

  if (QTreeWidgetItem* item = find_tree_item_for_layer(layer.get())) {
    item->setData(0, Qt::UserRole, QVariant());
    delete ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
  }

  gl_widget->remove_layer(layer.get());
  m_layers.erase(it);

  if (const auto bar_it = m_layer_progress_bars.find(layer.get());
      bar_it != m_layer_progress_bars.end()) {
    ui->statusBar->removeWidget(bar_it->second);
    delete bar_it->second;
    m_layer_progress_bars.erase(bar_it);
  }

  update_render_mode();
}

void Main3DWindow::remove_selected_layer() {
  const QList<QTreeWidgetItem*> selected = ui->treeWidget->selectedItems();
  if (selected.isEmpty()) {
    return;
  }
  const auto layer = selected.front()->data(0, Qt::UserRole).value<std::shared_ptr<Layer>>();
  remove_layer(layer);
}

void Main3DWindow::on_treeWidget_customContextMenuRequested(const QPoint& pos) {
  QTreeWidgetItem* item = ui->treeWidget->itemAt(pos);
  if (!item) {
    return;
  }
  ui->treeWidget->setCurrentItem(item);

  QMenu menu(this);
  QAction* zoom_action = menu.addAction(tr("Zoom to Layer"));
  menu.addSeparator();
  QAction* remove_action = menu.addAction(tr("Remove Layer"));
  QAction* chosen = menu.exec(ui->treeWidget->viewport()->mapToGlobal(pos));
  if (chosen == zoom_action) {
    const auto layer = item->data(0, Qt::UserRole).value<std::shared_ptr<Layer>>();
    if (layer) {
      gl_widget->zoom_to_layer(layer.get());
    }
  } else if (chosen == remove_action) {
    remove_selected_layer();
  }
}
