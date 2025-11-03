#include "mainwindow.h"
#include "catalogwindow.h"
#include "settingsdialog.h"
#include "aboutdialog.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi();
    statusBar()->showMessage("Готово");
}

void MainWindow::setupUi()
{
    // Центральный виджет и базовый layout
    auto central = new QWidget(this);
    auto layout = new QVBoxLayout(central);

    // Заголовок
    auto title = new QLabel("<b>Lab1_sem3 — головне меню</b>");
    searchEdit_ = new QLineEdit;
    searchEdit_->setPlaceholderText("Пошук...");

    // Кнопки
    catalogBtn_ = new QPushButton("Відкрити каталог");
    settingsBtn_ = new QPushButton("Налаштування");
    aboutBtn_    = new QPushButton("Про програму");

    auto btnRow = new QHBoxLayout;
    btnRow->addWidget(catalogBtn_);
    btnRow->addWidget(settingsBtn_);
    btnRow->addWidget(aboutBtn_);

    statusLabel_ = new QLabel("Стан: очікування");

    layout->addWidget(title);
    layout->addWidget(searchEdit_);
    layout->addLayout(btnRow);
    layout->addWidget(statusLabel_);
    setCentralWidget(central);

    // Меню
    auto fileMenu = menuBar()->addMenu("Файл");
    auto openAct  = fileMenu->addAction("Каталог", this, &MainWindow::onOpenCatalog);
    openAct->setShortcut(QKeySequence::Open);
    fileMenu->addSeparator();
    fileMenu->addAction("Вихід", this, &QWidget::close);

    auto helpMenu = menuBar()->addMenu("Довідка");
    helpMenu->addAction("Про програму", this, &MainWindow::onOpenAbout);

    // Сигналы
    connect(catalogBtn_, &QPushButton::clicked, this, &MainWindow::onOpenCatalog);
    connect(settingsBtn_, &QPushButton::clicked, this, &MainWindow::onOpenSettings);
    connect(aboutBtn_,   &QPushButton::clicked, this, &MainWindow::onOpenAbout);
    connect(searchEdit_, &QLineEdit::textChanged, this, &MainWindow::onSearchChanged);
}

// ---------- Слоты ----------

void MainWindow::onOpenCatalog()
{
    if (!catalog_)
        catalog_ = new CatalogWindow(this);
    catalog_->show();
    catalog_->raise();
    catalog_->activateWindow();
    statusLabel_->setText("Каталог відкрито");
}

void MainWindow::onOpenSettings()
{
    SettingsDialog dlg(this);
    dlg.exec();
}

void MainWindow::onOpenAbout()
{
    AboutDialog dlg(this);
    dlg.exec();
}

void MainWindow::onSearchChanged(const QString& text)
{
    statusBar()->showMessage(QString("Пошук: %1").arg(text));
}
