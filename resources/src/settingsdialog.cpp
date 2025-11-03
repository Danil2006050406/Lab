#include "settingsdialog.h"
#include <QtWidgets>


SettingsDialog::SettingsDialog(QWidget* parent): QDialog(parent) {
    setupUi();
}


void SettingsDialog::setupUi() {
    setWindowTitle("Налаштування");
    auto v = new QVBoxLayout(this);


    tabs_ = new QTabWidget;


    // General tab
    auto general = new QWidget; auto g = new QFormLayout(general);
    themeBox_ = new QComboBox; themeBox_->addItems({"Світла","Темна"});
    hintsBox_ = new QCheckBox("Показувати підказки"); hintsBox_->setChecked(true);
    userEdit_ = new QLineEdit; userEdit_->setPlaceholderText("Ім'я користувача");
    g->addRow("Тема:", themeBox_);
    g->addRow("Підказки:", hintsBox_);
    g->addRow("Користувач:", userEdit_);


    // About tab (simple)
    auto about = new QWidget; auto a = new QVBoxLayout(about);
    auto lbl = new QLabel("<b>Lab1_sem3</b><br/>Демонстрація GUI (Qt6)");
    auto link = new QLabel("<a href='https://qt.io'>qt.io</a>"); link->setOpenExternalLinks(true);
    a->addWidget(lbl); a->addWidget(link); a->addStretch();


    tabs_->addTab(general, "Загальні");
    tabs_->addTab(about, "Про програму");


    auto btns = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    v->addWidget(tabs_);
    v->addWidget(btns);


    connect(themeBox_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &SettingsDialog::onThemeChanged);
    connect(hintsBox_, &QCheckBox::checkStateChanged, this, &SettingsDialog::onHintsStateChanged);
    connect(userEdit_, &QLineEdit::textChanged, this, &SettingsDialog::onUserChanged);
    connect(btns, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(btns, &QDialogButtonBox::rejected, this, &QDialog::reject);
}


void SettingsDialog::onThemeChanged(int idx) {
    // apply a very simple theme switch (demo)
    if (idx == 0) { qApp->setStyleSheet(""); }
    else { qApp->setStyleSheet("QWidget{background:#2b2b2b;color:#f0f0f0;} QPushButton{border:1px solid #555;padding:6px;border-radius:6px;}"); }
}


void SettingsDialog::onHintsStateChanged(Qt::CheckState st) {
    QToolTip::setFont(QFont("", st == Qt::Checked ? 10 : 0));
}
void SettingsDialog::onUserChanged(const QString& u) { setWindowTitle("Налаштування — " + u); }



