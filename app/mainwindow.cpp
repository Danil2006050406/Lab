#include "mainwindow.h"
#include <QtWidgets>
#include <fstream>
#include <sstream>

#include "Library.h"
#include "Book.h"
#include "User.h"

// ======== Helper functions (loaders) ========
namespace {

void loadBooksFromFile(Library& lib, const std::string& filename) {
    std::ifstream f(filename);
    if (!f) return;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string title, author, isbn;
        int year = 0, copies = 1;
        std::getline(ss, title,  ';');
        std::getline(ss, author, ';');
        std::getline(ss, isbn,   ';');
        ss >> year; if (ss.peek() == ';') ss.ignore();
        ss >> copies;
        lib.addBook(Book(title, author, isbn, year, copies));
    }
}

void loadReadersFromFile(Library& lib, const std::string& filename) {
    std::ifstream f(filename);
    if (!f) return;
    std::string line;
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string name, id, email;
        std::getline(ss, name,  ';');
        std::getline(ss, id,    ';');
        std::getline(ss, email, ';');
        lib.addReader(name, id, email);
    }
}

} // namespace
// ===========================================

// >>> ВАЖНО: РЕАЛИЗАЦИЯ КОНСТРУКТОРА <<<
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    lib_ = std::make_unique<Library>();
    setupUi();
}

void MainWindow::setupUi() {
    auto central = new QWidget(this);
    auto layout  = new QVBoxLayout(central);

    auto top = new QHBoxLayout;
    auto btnLoadBooks   = new QPushButton("Load Books");
    auto btnLoadReaders = new QPushButton("Load Readers");
    auto btnIssue       = new QPushButton("Issue");
    auto btnReturn      = new QPushButton("Return");
    auto btnReaders     = new QPushButton("Readers");
    filter_ = new QLineEdit;
    filter_->setPlaceholderText("Filter (title/author/ISBN)...");
    top->addWidget(btnLoadBooks);
    top->addWidget(btnLoadReaders);
    top->addWidget(btnIssue);
    top->addWidget(btnReturn);
    top->addWidget(btnReaders);
    top->addStretch();
    top->addWidget(new QLabel("Search:"));
    top->addWidget(filter_);

    table_ = new QTableView;
    model_ = new QStandardItemModel(this);
    model_->setHorizontalHeaderLabels({"Title","Author","ISBN","Year","Total","Available"});
    table_->setModel(model_);
    table_->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_->setSelectionMode(QAbstractItemView::SingleSelection);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);

    status_ = new QLabel("Ready");
    layout->addLayout(top);
    layout->addWidget(table_);
    layout->addWidget(status_);
    setCentralWidget(central);

    auto fileMenu = menuBar()->addMenu("File");
    auto actLoadBooks   = fileMenu->addAction("Load books...");
    auto actLoadReaders = fileMenu->addAction("Load readers...");
    fileMenu->addSeparator();
    fileMenu->addAction("Exit", this, &QWidget::close);

    auto actions = menuBar()->addMenu("Actions");
    auto actIssue       = actions->addAction("Issue selected...");
    auto actReturn      = actions->addAction("Return selected...");
    auto actShowReaders = actions->addAction("Show readers");

    connect(btnLoadBooks,   &QPushButton::clicked, this, &MainWindow::loadBooks);
    connect(btnLoadReaders, &QPushButton::clicked, this, &MainWindow::loadReaders);
    connect(btnIssue,       &QPushButton::clicked, this, &MainWindow::issueSelected);
    connect(btnReturn,      &QPushButton::clicked, this, &MainWindow::returnSelected);
    connect(btnReaders,     &QPushButton::clicked, this, &MainWindow::showReaders);

    connect(actLoadBooks,   &QAction::triggered, this, &MainWindow::loadBooks);
    connect(actLoadReaders, &QAction::triggered, this, &MainWindow::loadReaders);
    connect(actIssue,       &QAction::triggered, this, &MainWindow::issueSelected);
    connect(actReturn,      &QAction::triggered, this, &MainWindow::returnSelected);
    connect(actShowReaders, &QAction::triggered, this, &MainWindow::showReaders);

    connect(filter_, &QLineEdit::textChanged, this, &MainWindow::filterTextChanged);

    resize(1000, 600);
}

void MainWindow::loadBooks() {
    const QString p = QFileDialog::getOpenFileName(this, "Select books.txt", {}, "Text (*.txt);;All (*.*)");
    if (p.isEmpty()) return;
    lastBooksPath_ = p;
    loadBooksFromFile(*lib_, p.toStdString());
    refreshView();
    status_->setText("Books: " + QFileInfo(p).fileName());
}

void MainWindow::loadReaders() {
    const QString p = QFileDialog::getOpenFileName(this, "Select readers.txt", {}, "Text (*.txt);;All (*.*)");
    if (p.isEmpty()) return;
    lastReadersPath_ = p;
    loadReadersFromFile(*lib_, p.toStdString());
    status_->setText("Readers: " + QFileInfo(p).fileName());
}

void MainWindow::refreshView() {
    fillModel();
    table_->resizeColumnsToContents();
}

void MainWindow::fillModel() {
    model_->removeRows(0, model_->rowCount());
    for (const auto& b : lib_->getBooks()) {
        QList<QStandardItem*> row;
        row << new QStandardItem(QString::fromStdString(b.getTitle()));
        row << new QStandardItem(QString::fromStdString(b.getAuthor()));
        row << new QStandardItem(QString::fromStdString(b.getISBN()));
        row << new QStandardItem(QString::number(b.getYear()));
        row << new QStandardItem(QString::number(b.getTotal()));
        row << new QStandardItem(b.isAvailable() ? "Yes" : "No");
        model_->appendRow(row);
    }
}

void MainWindow::filterTextChanged(const QString& t) {
    const auto s = t.trimmed();
    for (int r = 0; r < model_->rowCount(); ++r) {
        bool vis = true;
        if (!s.isEmpty()) {
            bool hit = false;
            for (int c = 0; c < model_->columnCount(); ++c) {
                if (model_->item(r,c)->text().contains(s, Qt::CaseInsensitive)) { hit = true; break; }
            }
            vis = hit;
        }
        table_->setRowHidden(r, !vis);
    }
}

void MainWindow::issueSelected() {
    auto idx = table_->currentIndex(); if (!idx.isValid()) return;
    const QString isbn = model_->item(idx.row(), 2)->text();
    const QString rid  = QInputDialog::getText(this, "Issue Book", "Reader ID (e.g. U001):");
    if (rid.isEmpty()) return;
    if (!lib_->issueBook(isbn.toStdString(), rid.toStdString()))
        QMessageBox::warning(this, "Issue", "Failed to issue: missing book/reader/unavailable.");
    refreshView();
}

void MainWindow::returnSelected() {
    auto idx = table_->currentIndex(); if (!idx.isValid()) return;
    const QString isbn = model_->item(idx.row(), 2)->text();
    const QString rid  = QInputDialog::getText(this, "Return Book", "Reader ID (e.g. U001):");
    if (rid.isEmpty()) return;
    if (!lib_->returnBook(isbn.toStdString(), rid.toStdString()))
        QMessageBox::warning(this, "Return", "Failed to return: missing book/reader/book not issued.");
    refreshView();
}

void MainWindow::showReaders() {
    const auto& readers = lib_->getReaders();
    if (readers.empty()) {
        QMessageBox::information(this, "Readers", "The list is empty. Please load readers.txt first.");
        return;
    }

    QDialog dlg(this);
    dlg.setWindowTitle("Readers List");
    dlg.resize(560, 420);

    QVBoxLayout layout(&dlg);
    QTableWidget table(&dlg);
    table.setColumnCount(3);
    table.setHorizontalHeaderLabels({"Name", "ID", "Email"});
    table.horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    table.setRowCount(static_cast<int>(readers.size()));
    for (int i = 0; i < static_cast<int>(readers.size()); ++i) {
        table.setItem(i, 0, new QTableWidgetItem(QString::fromStdString(readers[i].getName())));
        table.setItem(i, 1, new QTableWidgetItem(QString::fromStdString(readers[i].getId())));
        table.setItem(i, 2, new QTableWidgetItem(QString::fromStdString(readers[i].getEmail())));
    }

    layout.addWidget(&table);
    dlg.exec();
}
