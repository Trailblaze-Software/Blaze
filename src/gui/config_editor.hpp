#pragma once

#include <QToolBox>

#include "config_input/config_input.hpp"

namespace Ui {
class ConfigEditor;
}

class ConfigEditor : public QToolBox {
  Q_OBJECT

 public:
  explicit ConfigEditor(QWidget *parent = nullptr);

 private:
  Config m_config;
  std::unique_ptr<Ui::ConfigEditor> ui;
};
