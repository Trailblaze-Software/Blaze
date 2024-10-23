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

  std::vector<std::pair<QProgressBar*, QLabel*>> m_progress;

 private slots:
  void receive_progress_bars(std::vector<double> progress);

  void abort();

 signals:
  void send_progress_bars(std::vector<double> progress);

 public:
  explicit ProgressBox(QWidget* parent = nullptr);

  void update_progress(double proportion);

  void start_task(std::function<void()> task);

 private:
};
