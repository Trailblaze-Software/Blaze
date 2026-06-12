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

  void start_task(std::function<void()> task, std::function<void()> on_finish = [] {});

 private:
};
