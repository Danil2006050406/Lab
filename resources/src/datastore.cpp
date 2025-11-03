#include "datastore.h"
#include <QtWidgets>


DataStore& DataStore::instance() {
    static DataStore ds; return ds;
}


int DataStore::nextId() const {
    int maxId = 0; for (const auto& i : items_) maxId = std::max(maxId, i.id);
    return maxId + 1;
}


void DataStore::seed() {
    if (!items_.empty()) return;
    items_.push_back({1, "Notebook", 10, 199.99, true});
    items_.push_back({2, "Mouse", 25, 15.49, true});
    items_.push_back({3, "Keyboard", 12, 39.99, true});
    items_.push_back({4, "Monitor", 7, 159.00, false});
}


std::optional<Item> DataStore::get(int id) const {
    for (const auto& it : items_) if (it.id == id) return it;
    return std::nullopt;
}


void DataStore::upsert(const Item& it) {
    for (auto& e : items_) if (e.id == it.id) { e = it; return; }
    items_.push_back(it);
}


void DataStore::remove(int id) {
    items_.erase(std::remove_if(items_.begin(), items_.end(), [=](const Item& i){return i.id==id;}), items_.end());
}
