#pragma once
#include <vector>
#include <string>
#include "Book.h"
#include "User.h"   // Reader
#include "Loan.h"

class Library {
private:
    std::vector<Book>   books;
    std::vector<Reader> readers;
    std::vector<Loan>   loans;

public:
    // --- добавление данных ---
    void addBook(const Book& b)   { books.push_back(b); }
    void addBook(Book&& b)        { books.emplace_back(std::move(b)); }
    void addReader(const Reader& r) { readers.push_back(r); }
    void addReader(const std::string& name, const std::string& id, const std::string& email);

    // --- операции (оставь свои реализации в .cpp) ---
    bool issueBook(const std::string& isbn, const std::string& readerId);
    bool returnBook(const std::string& isbn, const std::string& readerId);

    // --- поиск ---
    Book*       findBookByISBN(const std::string& isbn);
    const Book* findBookByISBN(const std::string& isbn) const;
    Reader*       findReaderById(const std::string& id);
    const Reader* findReaderById(const std::string& id) const;
    // --- представления для GUI ---
    const std::vector<Book>&   getBooks()   const { return books; }
    const std::vector<Reader>& getReaders() const { return readers; }

    // (если есть listBooks/listReaders/listLoans — оставь)
};
