#pragma once
#include <string>

class Book;
class Reader;

// Выдать книгу читателю (проверяет доступность и вызывает Book::checkout)
bool issueBookToReader(Book& book, const Reader& reader);

// Принять возврат книги от читателя (вызывает Book::checkin)
bool returnBookFromReader(Book& book, const Reader& reader);

// Утилиты печати (по желанию)
void printBookInfo(const Book& book);
void printReaderInfo(const Reader& reader);
