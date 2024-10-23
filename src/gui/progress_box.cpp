#include "progress_box.hpp"

#include "ui_progress_box.h"

ProgressBox::ProgressBox(QWidget* parent) : QDialog(parent), ui(new Ui::ProgressBox) {
  ui->setupUi(this);
  setWindowFlag(Qt::WindowCloseButtonHint, false);
}

void ProgressBox::update_progress(double proportion) {
  ui->progressBar1->setValue(proportion * 1000);
}
