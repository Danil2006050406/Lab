#pragma once
#include "models.h"
#include <vector>
#include <optional>


class DataStore {
public:
    static DataStore& instance();


    const std::vector<Item>& all() const { return items_; }
    std::vector<Item>& all() { return items_; }


    int nextId() const;
    void seed();


    std::optional<Item> get(int id) const;
    void upsert(const Item& it);
    void remove(int id);


private:
    DataStore() = default;
    std::vector<Item> items_;
};
