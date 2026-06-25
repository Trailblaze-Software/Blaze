#pragma once

#include <QDialog>
#include <QLayout>
#include <QProgressBar>

#include "ui_progress_box.h"
#include "utilities/progress_tracker.hpp"

QT_BEGIN_NAMESPACE
class QLabel;
namespace Ui {
class ProgressBox;
}
QT_END_NAMESPACE

class ProgressBox : public QDialog, public ProgressObserver {
  Q_OBJECT

  std::unique_ptr<Ui::ProgressBox> ui;

  struct BarRow {
    QProgressBar* bar = nullptr;
    QLabel* label = nullptr;
  };
  std::vector<BarRow> m_progress;
  QLabel* m_eta_label = nullptr;
  double m_last_overall = 0.0;

  std::chrono::steady_clock::time_point m_start_time;

 private slots:
  void receive_progress_bars(std::vector<std::pair<double, bool>> bars);
  void receive_status_text(std::string text, int depth);
  void update_elapsed();

  void abort();

 signals:
  void send_progress_bars(std::vector<std::pair<double, bool>> bars);
  void send_status_text(std::string text, int depth);

 public:
  explicit ProgressBox(QWidget* parent = nullptr);

  void update_progress(double proportion) override;
  void text_update(const std::string& text, int depth = 0) override;

  // Runs `task` on a worker thread. On success `on_finish` is invoked on the
  // GUI thread. On failure `on_error` is invoked with the error message; if no
  // `on_error` is supplied a modal error dialog is shown instead. Supplying an
  // `on_error` lets callers (e.g. the headless Blaze3D-launched run) handle the
  // failure without a blocking dialog that would prevent automatic shutdown.
  void start_task(
      std::function<void()> task, std::function<void()> on_finish = [] {},
      std::function<void(const QString&)> on_error = {});

 private:
};
