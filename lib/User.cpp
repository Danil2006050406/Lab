#include "User.h"
#include <iostream>

User::User(const std::string& n, const std::string& i, const std::string& e)
    : name(n), id(i), email(e) {}


void Reader::displayInfo() const {
    std::cout << "Reader: " << name << " [ID: " << id << "], email: " << email << "\n";
}

void Reader::notify(const std::string& message) {
    std::cout << "Notify " << name << " (" << email << "): " << message << "\n";
}
