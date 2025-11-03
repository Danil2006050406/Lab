#include "Library.h"


void Library::addReader(const std::string& name, const std::string& id, const std::string& email) {
    readers.emplace_back(name, id, email);   
}


Book* Library::findBookByISBN(const std::string& isbn) {
    for (auto& b : books) if (b.getISBN() == isbn) return &b;
    return nullptr;
}
const Book* Library::findBookByISBN(const std::string& isbn) const {
    for (const auto& b : books) if (b.getISBN() == isbn) return &b;
    return nullptr;
}
Reader* Library::findReaderById(const std::string& id) {
    for (auto& r : readers) if (r.getId() == id) return &r;
    return nullptr;
}
const Reader* Library::findReaderById(const std::string& id) const {
    for (const auto& r : readers) if (r.getId() == id) return &r;
    return nullptr;
}


bool Library::issueBook(const std::string& isbn, const std::string& readerId) {
    Book* b = findBookByISBN(isbn);
    if (!b || !b->isAvailable()) return false;
    if (!b) return false;
    Reader* r = findReaderById(readerId);
    if (!r) return false;

    if (!b->isAvailable()) return false;
    if (!b->checkout())    return false;
    
    auto hasReader = [&]{ for (const auto& r : readers) if (r.getId() == readerId) return true; return false; }();
    if (!hasReader) return false;

    
    if (!b->checkout()) return false;

    

    return true;
}

bool Library::returnBook(const std::string& isbn, const std::string& readerId) {
    (void)readerId; 
    Book* b = findBookByISBN(isbn);
    if (!b) return false;
    b->checkin();
    return true;
}
