#pragma once
#include <string>

// Базовый пользователь (абстрактный)
class User {
protected:
    std::string name;
    std::string id;
    std::string email;

public:
    User(const std::string& n, const std::string& i, const std::string& e);
    virtual ~User() = default;

    // абстрактные методы — обязательны к реализации в наследнике
    virtual void displayInfo() const = 0;
    virtual void notify(const std::string& message) = 0;

    // Геттеры (inline, чтобы не было дублирования в .cpp)
    const std::string& getId()    const { return id; }
    const std::string& getName()  const { return name; }
    const std::string& getEmail() const { return email; }
};

// Конкретный читатель библиотеки
class Reader : public User {
public:
    using User::User;  // Наследуем конструктор User(n, id, email)

    void displayInfo() const override;
    void notify(const std::string& message) override;
};
