#pragma once
#include <string>
#include <list>
#include <vector>

using namespace std;

template <typename Key, typename Value>
class Hashing {
private:
    struct KeyValuePair {
        Key key;
        Value value;
        
        KeyValuePair( Key& k,  Value& v) : key(k), value(v) {}
    };

    vector<list<KeyValuePair>> table; 
    int elementCount;
    int tableSize;
    double loadFactorThreshold;
    int hashFunction( Key& key)  {
        int hashValue = 0;
        for (char ch : key) {
            hashValue = (hashValue * 31 + ch) % tableSize;
        }
        return hashValue;
    }
    void resizeTable() {
        int newSize = tableSize * 2;
        vector<list<KeyValuePair>> newTable(newSize);

        for (auto& bucket : table) {
            for (auto& pair : bucket) {
                int newIndex = hashFunction(pair.key) % newSize;
                newTable[newIndex].emplace_back(pair.key, pair.value);
            }
        }

        table = std::move(newTable);
        tableSize = newSize;
    }

public:
    Hashing(int initialSize = 100, double loadFactor = 0.6)
        : tableSize(initialSize), loadFactorThreshold(loadFactor), elementCount(0) {
        table.resize(tableSize);
    }
    void insert(Key & key,Value &value) {
        if (((double)elementCount / tableSize) >= loadFactorThreshold) {
            resizeTable();
        }

        int index = hashFunction(key);
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                pair.value = value;  
                return;
            }
        }

        table[index].emplace_back(key, value);  
        ++elementCount;
    }

 
    Value* search( Key& key)  {
        int index = hashFunction(key);
        for (const auto& pair : table[index]) {
            if (pair.key == key) {
                return const_cast<Value*>(&pair.value);  
            }
        }
        return nullptr;  
    }

    
    void remove( Key& key) {
        int index = hashFunction(key);
        auto& pairs = table[index];
        for (auto it = pairs.begin(); it != pairs.end(); ++it) {
            if (it->key == key) {
                pairs.erase(it);
                --elementCount;
                return;
            }
        }
    }
};
