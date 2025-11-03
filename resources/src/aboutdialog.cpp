#include "aboutdialog.h"
#include <QtWidgets>


AboutDialog::AboutDialog(QWidget* parent): QDialog(parent) {
    setWindowTitle("Про програму");
    auto v = new QVBoxLayout(this);
    v->addWidget(new QLabel("<b>Lab1_sem3</b><br/>Приклад з 4+ екранами, 20+ контролами, 10+ обробниками подій."));
    auto btn = new QDialogButtonBox(QDialogButtonBox::Ok);
    v->addWidget(btn);
    connect(btn, &QDialogButtonBox::accepted, this, &QDialog::accept);
}
