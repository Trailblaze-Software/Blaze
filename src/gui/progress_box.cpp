#include "progress_box.hpp"

#include <QFutureWatcher>
#include <QtConcurrent>

#include "ui_progress_box.h"
#include "utilities/progress_tracker.hpp"

void ProgressBox::abort() { done(1); }

ProgressBox::ProgressBox(QWidget* parent) : QDialog(parent), ui(new Ui::ProgressBox) {
  ui->setupUi(this);
  setWindowFlag(Qt::WindowCloseButtonHint, false);
  connect(this, &ProgressBox::send_progress_bars, this, &ProgressBox::receive_progress_bars);
}

void ProgressBox::receive_progress_bars(std::vector<double> progress) {
  for (size_t i = 0; i < progress.size(); i++) {
    if (i >= m_progress.size()) {
      m_progress.emplace_back(
          std::pair<QProgressBar*, QLabel*>{new QProgressBar(ui->scrollAreaWidgetContents_2),
                                            new QLabel(ui->scrollAreaWidgetContents_2)});
      ui->verticalLayout_3->addWidget(m_progress.back().first);
      m_progress.back().first->setMaximum(1000);
    }
    m_progress[i].first->setValue(progress[i] * 1000);
  }
  for (size_t i = progress.size(); i < m_progress.size(); i++) {
    ui->verticalLayout_3->removeWidget(m_progress[i].first);
    delete m_progress[i].first;
    delete m_progress[i].second;
  }
  m_progress.resize(progress.size());
}

void ProgressBox::update_progress(double _) {
  (void)_;
  std::vector<double> progress;
  ProgressTracker* child = this->child();
  while (child != nullptr) {
    progress.push_back(child->proportion());
    child = child->child();
  }
  emit send_progress_bars(std::move(progress));
}

void ProgressBox::start_task(std::function<void()> task) {
  QFutureWatcher<void>* watcher = new QFutureWatcher<void>(this);
  connect(watcher, &QFutureWatcher<void>::finished, this, [this] { this->done(0); });
  watcher->setFuture(QtConcurrent::run(task));
}
