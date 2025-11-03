#pragma once
#include <QString>


struct Item {
    int id{};
    QString name;
    int quantity{};
    double price{};
    bool active{true};
};
