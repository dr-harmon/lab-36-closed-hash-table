#pragma once

#include <functional>
#include <memory>
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

    std::unique_ptr<HashtableEntry[]> hashtable;

    int computeHash(K key) const {
        std::hash<K> keyHash;
        return keyHash(key) % tableSize;
    }

public:

    class KeyNotFoundException {};
    class HashtableFullException {};

    ClosedHashMap(int tableSize) {
        this->size = 0;
        this->tableSize = tableSize;
        hashtable = std::make_unique<HashtableEntry[]>(tableSize);
        for (int i = 0; i < tableSize; i++) {
            hashtable[i].state = UNUSED;
        }
    }

    bool exists(K key) const {
        int i = computeHash(key);
        int probes = 0;
        do {
            HashtableEntry& entry = hashtable[i];
            if (entry.state == UNUSED) {
                return false;
            } else if (entry.key == key && entry.state == USED) {
                return true;
            } else {
                i = (i + 1) % tableSize;
                probes++;
            }
        } while (probes < tableSize);

        return false;
    }

    const V& find(K key) const {
        int i = computeHash(key);
        int probes = 0;
        do {
            HashtableEntry& entry = hashtable[i];
            if (entry.key == key && entry.state == USED) {
                return entry.value;
            }
            i = (i + 1) % tableSize;
            probes++;
        } while (probes < tableSize);

        throw KeyNotFoundException();
    }

    void put(K key, V value) {
        if (size == tableSize) {
            throw HashtableFullException();
        }

        bool found = exists(key);
        int i = computeHash(key);
        int probes = 0;
        do {
            HashtableEntry& entry = hashtable[i];
            if (found) {
                if (entry.key == key && entry.state == USED) {
                    entry.value = value;
                    return;
                }
            } else {
                if (entry.state == UNUSED || entry.state == AVAILABLE) {
                    entry.key = key;
                    entry.value = value;
                    entry.state = USED;
                    size++;
                    return;
                }
            }
            i = (i + 1) % tableSize;
            probes++;
        } while (probes < tableSize);
    }

    void erase(K key) {
        if (!exists(key)) {
            throw KeyNotFoundException();
        }

        int i = computeHash(key);
        int probes = 0;
        do {
            HashtableEntry& entry = hashtable[i];
            if (entry.key == key && entry.state == USED) {
                entry.state = AVAILABLE;
                size--;
                return;
            }
            i = (i + 1) % tableSize;
            probes++;
        } while (probes < tableSize);
    }

    int getSize() const {
        return size;
    }
};
