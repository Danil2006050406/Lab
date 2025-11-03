#pragma once
#include <QDialog>
#include <Qt>

class QTabWidget; class QComboBox; class QCheckBox; class QLineEdit;


class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget* parent = nullptr);


private slots:
    void onThemeChanged(int); // handler 18
    void onHintsStateChanged(Qt::CheckState); // handler 19
    void onUserChanged(const QString&); // handler 20


private:
    void setupUi();


    QTabWidget* tabs_{};
    QComboBox* themeBox_{};
    QCheckBox* hintsBox_{};
    QLineEdit* userEdit_{};
};
