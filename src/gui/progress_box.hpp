#pragma once

#include <QLayout>
#include <QMessageBox>
#include <QProgressBar>

#include "utilities/progress_tracker.hpp"

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE

class ProgressBox : public QMessageBox, public ProgressObserver {
  Q_OBJECT

  QProgressBar* m_progress_bar;

 public:
  explicit ProgressBox(QWidget* parent = nullptr) : QMessageBox(parent) {
    setStandardButtons(QMessageBox::NoButton);
    setWindowFlag(Qt::WindowCloseButtonHint, false);

    m_progress_bar = new QProgressBar(this);
    m_progress_bar->setRange(0, 1000);
    layout()->addWidget(m_progress_bar);
  }

  void update_progress(double proportion) { m_progress_bar->setValue(proportion * 1000); }

 private:
};
