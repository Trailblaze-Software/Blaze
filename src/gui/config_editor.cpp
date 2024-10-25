#include "config_editor.hpp"

#include "ui_config_editor.h"

ConfigEditor::ConfigEditor(QWidget *parent)
    : QToolBox(parent), ui(new Ui::ConfigEditor), m_config() {
  ui->setupUi(this);
}
