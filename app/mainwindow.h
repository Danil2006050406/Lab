#pragma once
#include <QMainWindow>
#include <QStandardItemModel>
#include <memory>

#include "Library.h"     // чтобы тип Library был полным в заголовке

class QLineEdit;
class QTableView;
class QLabel;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void loadBooks();
    void loadReaders();
    void refreshView();
    void filterTextChanged(const QString&);
    void issueSelected();
    void returnSelected();

    void showReaders();   // <<< НОВОЕ: показать всех читателей

private:
    void setupUi();
    void fillModel();

    std::unique_ptr<Library> lib_;
    QStandardItemModel* model_{};
    QTableView* table_{};
    QLineEdit* filter_{};
    QLabel* status_{};
    QString lastBooksPath_;
    QString lastReadersPath_;
};
