#include "LibraryUtils.h"
#include "Book.h"
#include "User.h"    
#include <iostream>

bool issueBookToReader(Book& book, const Reader& reader) {
    if (!book.isAvailable()) {
        std::cout << "The book is not available for borrowing.\n";
        return false;
    }
    if (!book.checkout()) {
        std::cout << "Failed to issue the book (no copies left).\n";
        return false;
    }
    std::cout << "The book has been successfully issued to reader "
        << reader.getName() << " [ID: " << reader.getId() << "]\n";
    return true;
}

bool returnBookFromReader(Book& book, const Reader& reader) {
    (void)reader;
    book.checkin();
    std::cout << "The book has been successfully returned.\n";
    return true;
}

void printBookInfo(const Book& book) {
    std::cout << "Book: " << book.getTitle()
        << " (" << book.getYear() << ")"
        << ", ISBN: " << book.getISBN()
        << ", Available: " << (book.isAvailable() ? "Yes" : "No")
        << "\n";
}

void printReaderInfo(const Reader& reader) {
    std::cout << "Reader: " << reader.getName()
        << " [ID: " << reader.getId()
        << "], email: " << reader.getEmail()
        << "\n";
}

