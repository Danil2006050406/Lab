#include "Loan.h"
#include <cmath>    
#include <ctime>     

Loan::Loan(const std::string& lid, const std::string& isbn, const std::string& uid,
    time_t loanD, time_t dueD)
    : loanId(lid), bookIsbn(isbn), userId(uid), loanDate(loanD), dueDate(dueD), returned(false) {
}

void Loan::markReturned() {
    returned = true;
}

bool Loan::isReturned() const {
    return returned;
}

bool Loan::isOverdue() const {
    return !returned && time(nullptr) > dueDate;
}

int Loan::daysLeft() const {
    double diff = difftime(dueDate, time(nullptr));
    return diff < 0 ? 0 : static_cast<int>(ceil(diff / (60 * 60 * 24)));
}

const std::string& Loan::getISBN() const {
    return bookIsbn;
}

const std::string& Loan::getUserId() const {
    return userId;
}

const std::string& Loan::getLoanId() const {
    return loanId;
}