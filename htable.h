#ifndef HTABLE_H
#define HTABLE_H

#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#define capacity 100


template<typename K, typename V>
class HTable
{
public:
    struct HashNode {
        K key;
        V value;

        HashNode(K k, V v) {
            key = k;
            value = v;
        }
    };

    HTable();
    HTable(const HTable& other);
    ~HTable();

    void clear();
    void insert(K key, V value);
    void remove(K key);

    int getSize() const;
    int getSum() const;

    HashNode* find(K key);
    K getKey(int number);
    V getValue(K key);
    bool isKey(K key);

    void writeToFile(const std::string& path) const;
    void loadFromFile(const std::string& path);

    bool operator==(const HTable& other) const;
    V& operator[](K key);

    void display();

private:
    std::vector<std::list<HashNode*>*> table;

    int hashFunction(K key);
};

#endif // HTABLE_H
