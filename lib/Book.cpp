#include "Book.h"
#include <iostream>
#include <algorithm>
#include <cctype>

Book::Book(const std::string& t, const std::string& a, const std::string& i, int y, int copies)
    : title(t), author(a), isbn(i), year(y), totalCopies(copies) {
}

void Book::displayInfo() const {
    std::cout << "Book: '" << title << "' by " << author
        << " (" << year << ") ISBN:" << isbn
        << " copies:" << totalCopies
        << " available:" << isAvailable() << "\n";
}

bool Book::matchesTitle(const std::string& q) const {
    std::string t = title, qq = q;
    std::transform(t.begin(), t.end(), t.begin(),
        [](char c) { return std::tolower(static_cast<unsigned char>(c)); });
    std::transform(qq.begin(), qq.end(), qq.begin(),
        [](char c) { return std::tolower(static_cast<unsigned char>(c)); });
    return t.find(qq) != std::string::npos;
}

bool Book::checkout() {
    if (!isAvailable()) return false;
    totalCopies--;
    return true;
}

void Book::checkin() {
    totalCopies++;
}

bool Book::isOldEdition(int thresholdYear) const {
    return year < thresholdYear;
}

bool Book::isAvailable() const {
    return totalCopies > 0;
}

const std::string& Book::getISBN() const {
    return isbn;
}

// EBook

EBook::EBook(const std::string& t, const std::string& a, const std::string& i, int y,
    const std::string& url, double size)
    : Book(t, a, i, y, 1), downloadUrl(url), fileSizeMB(size) {
}

void EBook::getDownloadInfo() const {
    std::cout << "EBook download: " << downloadUrl << " (" << fileSizeMB << " MB)\n";
}
