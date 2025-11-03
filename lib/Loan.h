#pragma once
#include <string>
#include <ctime>

class Loan {
private:
    std::string loanId, bookIsbn, userId;
    time_t loanDate, dueDate;
    bool returned;
public:
    Loan(const std::string& lid, const std::string& isbn, const std::string& uid,
        time_t loanD, time_t dueD);

    void markReturned();
    bool isReturned() const;
    bool isOverdue() const;
    int daysLeft() const;

    const std::string& getISBN() const;
    const std::string& getUserId() const;
    const std::string& getLoanId() const;
};