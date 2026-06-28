#include "progress_box.hpp"

#include <QException>
#include <QFutureWatcher>
#include <QProgressBar>
#include <QTimer>
#include <QtConcurrent>
#include <chrono>
#include <cmath>
#include <sstream>

#include "error_dialog.hpp"
#include "ui_progress_box.h"
#include "utilities/memory_tracker.hpp"
#include "utilities/progress_tracker.hpp"
#include "utilities/trace_recorder.hpp"

namespace {

class DecimalProgressBar : public QProgressBar {
 public:
  using QProgressBar::QProgressBar;
  QString text() const override {
    double pct = static_cast<double>(value()) / static_cast<double>(maximum()) * 100.0;
    if (std::abs(pct - std::round(pct)) < 0.05)
      return QString("%1%").arg(static_cast<int>(std::round(pct)));
    return QString("%1%").arg(pct, 0, 'f', 1);
  }
};

}  // namespace

void ProgressBox::abort() { done(1); }

ProgressBox::ProgressBox(QWidget* parent)
    : QDialog(parent), ui(new Ui::ProgressBox), m_start_time(std::chrono::steady_clock::now()) {
  ui->setupUi(this);
  setWindowFlag(Qt::WindowCloseButtonHint, false);

  // ETA label is defined in the .ui file
  m_eta_label = ui->etaLabel;
  m_eta_label->setStyleSheet("QLabel { color: #888; font-size: 11px; }");

  // Timer to refresh elapsed every second even when no progress events fire
  auto* elapsed_timer = new QTimer(this);
  connect(elapsed_timer, &QTimer::timeout, this, &ProgressBox::update_elapsed);
  elapsed_timer->start(1000);

  connect(this, &ProgressBox::send_progress_bars, this, &ProgressBox::receive_progress_bars);
  connect(this, &ProgressBox::send_status_text, this, &ProgressBox::receive_status_text);
}

static std::string format_duration(double seconds) {
  int total_secs = static_cast<int>(std::round(seconds));
  if (total_secs < 60) {
    return std::to_string(total_secs) + "s";
  }
  int mins = total_secs / 60;
  int secs = total_secs % 60;
  if (mins < 60) {
    return std::to_string(mins) + "m " + std::to_string(secs) + "s";
  }
  int hrs = mins / 60;
  mins = mins % 60;
  return std::to_string(hrs) + "h " + std::to_string(mins) + "m " + std::to_string(secs) + "s";
}

void ProgressBox::receive_progress_bars(std::vector<std::pair<double, bool>> bars) {
  for (size_t i = 0; i < bars.size(); i++) {
    if (i >= m_progress.size()) {
      auto* bar = new DecimalProgressBar(ui->barsContainer);
      auto* lbl = new QLabel(ui->barsContainer);
      bar->setMaximum(10000);
      lbl->setWordWrap(true);
      lbl->hide();
      m_progress.push_back({bar, lbl});
      ui->verticalLayout_3->addWidget(bar);
      ui->verticalLayout_3->addWidget(lbl);
    }
    bool vis = bars[i].second;
    m_progress[i].bar->setVisible(vis);
    m_progress[i].bar->setValue(static_cast<int>(bars[i].first * 10000.0));
  }
  for (size_t i = bars.size(); i < m_progress.size(); i++) {
    ui->verticalLayout_3->removeWidget(m_progress[i].bar);
    ui->verticalLayout_3->removeWidget(m_progress[i].label);
    delete m_progress[i].bar;
    delete m_progress[i].label;
  }
  m_progress.resize(bars.size());

  if (!bars.empty()) m_last_overall = bars[0].first;
  update_elapsed();
}

void ProgressBox::receive_status_text(std::string text, int depth) {
  int idx = depth - 1;
  if (idx >= 0 && static_cast<size_t>(idx) < m_progress.size()) {
    if (text.empty()) {
      m_progress[idx].label->hide();
    } else {
      m_progress[idx].label->setText(QString::fromStdString(text));
      m_progress[idx].label->show();
    }
  }
}

void ProgressBox::update_elapsed() {
  auto now = std::chrono::steady_clock::now();
  double elapsed = std::chrono::duration<double>(now - m_start_time).count();
  const std::string mem = blaze::memory_tracker::format_summary();

  if (m_last_overall > 0.999) {
    std::ostringstream ss;
    ss << "Total time: " << format_duration(elapsed) << "  |  " << mem;
    m_eta_label->setText(QString::fromStdString(ss.str()));
    m_eta_label->setStyleSheet("QLabel { color: #4a4; font-size: 12px; font-weight: bold; }");
  } else if (m_last_overall > 0.001) {
    double eta = elapsed * (1.0 - m_last_overall) / m_last_overall;
    std::ostringstream ss;
    ss << "Elapsed: " << format_duration(elapsed) << "  |  ETA: " << format_duration(eta)
       << " remaining"
       << "  |  " << mem;
    m_eta_label->setText(QString::fromStdString(ss.str()));
  } else if (elapsed > 1.0) {
    std::ostringstream ss;
    ss << "Elapsed: " << format_duration(elapsed) << "  |  Estimating…"
       << "  |  " << mem;
    m_eta_label->setText(QString::fromStdString(ss.str()));
  }
}

void ProgressBox::update_progress(double _) {
  (void)_;
  std::vector<std::pair<double, bool>> bars;
  ProgressTracker* child = this->child();
  while (child != nullptr) {
    bars.emplace_back(child->proportion(), child->is_visible());
    child = child->child();
  }
  emit send_progress_bars(std::move(bars));
}

void ProgressBox::text_update(const std::string& text, int depth) {
  emit send_status_text(text, depth);
}

class TaskException : public QException {
  std::string m_what;

 public:
  TaskException(const char* what) : QException(), m_what(what) {}
  void raise() const { throw *this; }
  QException* clone() const { return new TaskException(*this); }
  inline virtual const char* what() const noexcept { return m_what.c_str(); }
};

void ProgressBox::start_task(std::function<void()> task, std::function<void()> on_finish,
                             std::function<void(const QString&)> on_error) {
  m_start_time = std::chrono::steady_clock::now();
  QFutureWatcher<int>* watcher = new QFutureWatcher<int>(this);
  connect(watcher, &QFutureWatcher<int>::finished, this, [this, watcher, on_finish, on_error] {
    if (watcher->future().isCanceled()) {
      QString message = "Unknown error";
      try {
        watcher->future().result();
      } catch (TaskException& e) {
        message = e.what();
      }
      this->done(1);
      if (on_error) {
        on_error(message);
      } else {
        show_error_message(this, "Error running task", message);
      }
    } else {
      this->done(0);
      on_finish();
    }
  });
  watcher->setFuture(QtConcurrent::run([task] {
    try {
      task();
    } catch (std::exception& e) {
      throw TaskException(e.what());
    }
    return 0;
  }));
}
