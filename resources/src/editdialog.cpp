#include "editdialog.h"
#include <QtWidgets>


EditDialog::EditDialog(QWidget* parent): QDialog(parent) {
    setupUi();
}


void EditDialog::setupUi() {
    setWindowTitle("Редактор");
    auto form = new QFormLayout(this);


    nameEdit_ = new QLineEdit;
    qtySpin_ = new QSpinBox; qtySpin_->setRange(0, 100000);
    priceSpin_ = new QDoubleSpinBox; priceSpin_->setRange(0.0, 1e9); priceSpin_->setDecimals(2);
    activeBox_ = new QCheckBox("Активний"); activeBox_->setChecked(true);


    form->addRow("Назва:", nameEdit_);
    form->addRow("Кількість:", qtySpin_);
    form->addRow("Ціна:", priceSpin_);
    form->addRow("Статус:", activeBox_);


    buttons_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    form->addWidget(buttons_);


    connect(nameEdit_, &QLineEdit::textChanged, this, &EditDialog::onNameChanged);
    connect(qtySpin_, QOverload<int>::of(&QSpinBox::valueChanged), this, &EditDialog::onQuantityChanged);
    connect(priceSpin_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &EditDialog::onPriceChanged);
    connect(activeBox_, &QCheckBox::checkStateChanged, this, &EditDialog::onActiveChanged);
    connect(buttons_, &QDialogButtonBox::accepted, this, &EditDialog::onAccept);
    connect(buttons_, &QDialogButtonBox::rejected, this, &QDialog::reject);
}


void EditDialog::setItem(const Item& it) { item_ = it; syncToUi(); }


void EditDialog::syncToUi() {
    nameEdit_->setText(item_.name);
    qtySpin_->setValue(item_.quantity);
    priceSpin_->setValue(item_.price);
    activeBox_->setChecked(item_.active);
}


void EditDialog::onNameChanged(const QString& s) { item_.name = s; }
void EditDialog::onQuantityChanged(int v) { item_.quantity = v; }
void EditDialog::onPriceChanged(double v) { item_.price = v; }
void EditDialog::onActiveChanged(Qt::CheckState st) { item_.active = (st == Qt::Checked); }


void EditDialog::onAccept() {
    if (item_.name.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Помилка", "Назва не може бути порожньою");
        return;
    }
    accept();
}
