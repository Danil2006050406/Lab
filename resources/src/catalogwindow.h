#pragma once
#include <QMainWindow>
#include <QItemSelection>


class QTableView;
class QStandardItemModel;
class QComboBox;
class QLineEdit;
class QLabel;


class CatalogWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit CatalogWindow(QWidget* parent = nullptr);


private slots:
    void onRefresh(); // handler 5
    void onAdd(); // handler 6
    void onEdit(); // handler 7
    void onDelete(); // handler 8
    void onFilterText(const QString&);// handler 9
    void onFilterMode(int); // handler 10
    void onActivated(const QModelIndex&); // handler 11 (double click / activate)
    void onSelectionChanged(const QItemSelection&, const QItemSelection&); // handler 12


private:
    void setupUi();
    void loadData();
    void applyFilter();


    QTableView* table_{};
    QStandardItemModel* model_{};
    QComboBox* filterMode_{};
    QLineEdit* filterEdit_{};
    QLabel* countLabel_{};
};
