#include "catalogwindow.h"
#include "editdialog.h"
#include "datastore.h"
#include <QtWidgets>

CatalogWindow::CatalogWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi();
    DataStore::instance().seed();
    loadData();
}

void CatalogWindow::setupUi() {
    auto central = new QWidget(this);
    auto v = new QVBoxLayout(central);

    // тулбар
    auto toolbar   = addToolBar("Дії");
    auto actRefresh= toolbar->addAction("Оновити");
    auto actAdd    = toolbar->addAction("Додати");
    auto actEdit   = toolbar->addAction("Редагувати");
    auto actDelete = toolbar->addAction("Видалити");

    // фильтры
    auto filterRow = new QHBoxLayout;
    filterMode_ = new QComboBox;
    filterMode_->addItems({"Назва","Активні","Неактивні"});
    filterEdit_ = new QLineEdit;
    filterEdit_->setPlaceholderText("Фільтр за назвою...");
    filterRow->addWidget(new QLabel("Фільтр:"));
    filterRow->addWidget(filterMode_);
    filterRow->addWidget(filterEdit_);

    // таблица
    table_ = new QTableView;
    table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_->setSelectionMode(QAbstractItemView::SingleSelection);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);

    countLabel_ = new QLabel("0 записів");

    v->addLayout(filterRow);
    v->addWidget(table_);
    v->addWidget(countLabel_);
    setCentralWidget(central);

    // сигналы
    connect(actRefresh, &QAction::triggered, this, &CatalogWindow::onRefresh);
    connect(actAdd,     &QAction::triggered, this, &CatalogWindow::onAdd);
    connect(actEdit,    &QAction::triggered, this, &CatalogWindow::onEdit);
    connect(actDelete,  &QAction::triggered, this, &CatalogWindow::onDelete);

    connect(filterEdit_, &QLineEdit::textChanged, this, &CatalogWindow::onFilterText);
    connect(filterMode_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CatalogWindow::onFilterMode);
    connect(table_, &QTableView::activated, this, &CatalogWindow::onActivated);

    // selectionChanged — когда модель появится
    // подключим после loadData(), т.к. нужен selectionModel()
}

void CatalogWindow::loadData() {
    if (model_) { model_->deleteLater(); }
    model_ = new QStandardItemModel(this);
    model_->setHorizontalHeaderLabels({"ID","Назва","Кількість","Ціна","Активний"});

    for (const auto& it : DataStore::instance().all()) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::number(it.id));
        row << new QStandardItem(it.name);
        row << new QStandardItem(QString::number(it.quantity));
        row << new QStandardItem(QString::number(it.price, 'f', 2));
        row << new QStandardItem(it.active ? "Так" : "Ні");
        model_->appendRow(row);
    }

    table_->setModel(model_);
    table_->resizeColumnsToContents();
    countLabel_->setText(QString::number(model_->rowCount()) + " записів");
    applyFilter();

    // теперь можно отследить выделение
    connect(table_->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &CatalogWindow::onSelectionChanged);
}

void CatalogWindow::applyFilter() {
    // Простейший фильтр скрытием строк
    const int mode = filterMode_->currentIndex();
    const QString text = filterEdit_->text().trimmed();

    for (int r = 0; r < model_->rowCount(); ++r) {
        const QString name = model_->item(r,1)->text();
        const QString activeText = model_->item(r,4)->text();

        bool visible = true;
        if (mode == 0) { // Назва (contains)
            visible = name.contains(text, Qt::CaseInsensitive);
        } else if (mode == 1) { // Активні
            visible = (activeText == "Так");
        } else if (mode == 2) { // Неактивні
            visible = (activeText == "Ні");
        }
        table_->setRowHidden(r, !visible);
    }
}

void CatalogWindow::onRefresh() { loadData(); }

void CatalogWindow::onAdd() {
    Item it;
    it.id = DataStore::instance().nextId();
    EditDialog dlg(this); dlg.setItem(it);
    if (dlg.exec() == QDialog::Accepted) {
        DataStore::instance().upsert(dlg.item());
        loadData();
    }
}

void CatalogWindow::onEdit() {
    auto idx = table_->currentIndex();
    if (!idx.isValid()) return;
    const int row = idx.row();
    const int id  = model_->item(row,0)->text().toInt();

    auto it = DataStore::instance().get(id);
    if (!it) return;

    EditDialog dlg(this); dlg.setItem(*it);
    if (dlg.exec() == QDialog::Accepted) {
        DataStore::instance().upsert(dlg.item());
        loadData();
    }
}

void CatalogWindow::onDelete() {
    auto idx = table_->currentIndex();
    if (!idx.isValid()) return;

    const int id = model_->item(idx.row(),0)->text().toInt();
    if (QMessageBox::question(this, "Видалення", "Видалити запис?") == QMessageBox::Yes) {
        DataStore::instance().remove(id);
        loadData();
    }
}

void CatalogWindow::onFilterText(const QString&) { applyFilter(); }
void CatalogWindow::onFilterMode(int)            { applyFilter(); }
void CatalogWindow::onActivated(const QModelIndex&) { onEdit(); }

void CatalogWindow::onSelectionChanged(const QItemSelection&, const QItemSelection&) {
    // тут можно вкл/выкл кнопки Редактировать/Удалить по выделению
}
