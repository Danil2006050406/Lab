#pragma once
#include <QMainWindow>

class QLineEdit;
class QPushButton;
class QLabel;
class CatalogWindow;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onOpenCatalog();
    void onOpenSettings();
    void onOpenAbout();
    void onSearchChanged(const QString& text);

private:
    void setupUi();

    QLineEdit*    searchEdit_{};
    QPushButton*  catalogBtn_{};
    QPushButton*  settingsBtn_{};
    QPushButton*  aboutBtn_{};
    QLabel*       statusLabel_{};
    CatalogWindow* catalog_{nullptr};
};
