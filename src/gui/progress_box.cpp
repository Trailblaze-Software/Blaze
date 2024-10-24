#include "progress_box.hpp"

#include <QException>
#include <QFutureWatcher>
#include <QMessageBox>
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

class TaskException : public QException {
  std::string m_what;

 public:
  TaskException(const char* what) : QException(), m_what(what) {}
  void raise() const { throw *this; }
  QException* clone() const { return new TaskException(*this); }
  inline virtual const char* what() const noexcept { return m_what.c_str(); }
};

void ProgressBox::start_task(std::function<void()> task) {
  QFutureWatcher<int>* watcher = new QFutureWatcher<int>(this);
  connect(watcher, &QFutureWatcher<int>::finished, this, [this, watcher] {
    if (watcher->future().isCanceled()) {
      try {
        watcher->future().result();
      } catch (TaskException& e) {
        QMessageBox::critical(this, "Error running task", e.what());
      }
      this->done(1);
    } else
      this->done(0);
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
