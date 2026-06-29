

# File error\_dialog.cpp

[**File List**](files.md) **>** [**gui**](dir_99d0482cf009f9d97a0877749b817f19.md) **>** [**error\_dialog.cpp**](error__dialog_8cpp.md)

[Go to the documentation of this file](error__dialog_8cpp.md)


```C++
#include "error_dialog.hpp"

#include <QDialog>
#include <QDialogButtonBox>
#include <QPlainTextEdit>
#include <QVBoxLayout>

void show_error_message(QWidget* parent, const QString& title, const QString& message) {
  QDialog dialog(parent);
  dialog.setWindowTitle(title);
  dialog.setModal(true);

  auto* layout = new QVBoxLayout(&dialog);

  auto* text = new QPlainTextEdit(message);
  text->setReadOnly(true);
  text->setLineWrapMode(QPlainTextEdit::WidgetWidth);
  text->setMinimumSize(480, 200);
  layout->addWidget(text);

  auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok);
  QObject::connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  layout->addWidget(buttons);

  dialog.resize(560, 320);
  dialog.exec();
}
```


