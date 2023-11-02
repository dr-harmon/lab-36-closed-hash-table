#pragma once

#include <functional>
#include <utility>

template <typename K, typename V>
class ClosedHashMap {
private:

    enum State {
        UNUSED, USED, AVAILABLE
    };

    struct HashtableEntry {
        K key;
        V value;
        State state;
    };

    int size;
    int tableSize;

public:

    ClosedHashMap(int tableSize) {
        this->size = 0;
        this->tableSize = tableSize;
    }

    bool exists(K key) const {
        // TODO
    }

    const V& find(K key) const {
        // TODO
    }

    void put(K key, V value) {
        // TODO
    }

    void erase(K key) {
        // TODO
    }

    int getSize() const {
        return size;
    }
};
