#include "htable.h"


template<typename K, typename V>
HTable<K, V>::HTable() {
    table.resize(capacity);

    for (size_t i = 0; i < capacity; i++) {
        table[i] = NULL;
    }
}

template<typename K, typename V>
HTable<K, V>::HTable(const HTable& other) {
    table.resize(capacity);

    for (int i = 0; i < capacity; i++) {
        table[i] = NULL;
        if (other.table[i]) {
            for (auto it = other.table[i]->begin(); it != other.table[i]->end(); it++) {
                this->insert((*it)->key, (*it)->value);
            }
        }
    }
}

template<typename K, typename V>
HTable<K, V>::~HTable() {
    this->clear();
}


template<typename K, typename V>
int HTable<K, V>::hashFunction(K key) {
    int hash = 0;
    for (int j = 0; key[j]; j++) {
        hash += key[j];
    }
    return hash % capacity;
}

template<typename K, typename V>
void HTable<K, V>::clear() {
    for (int i = 0; i < capacity; i++) {
        if (table[i]) {
            table[i]->clear();
            table[i] = NULL;
        }
    }
    table.clear();
}

template<typename K, typename V>
void HTable<K, V>::insert(K key, V value) {
    int index = hashFunction(key);

    if (!table[index]) {
        table[index] = new std::list<HashNode*>;
        table[index]->push_back(new HashNode(key, value));
    }
    else {
        for (auto it = table[index]->begin(); it != table[index]->end(); it++) {
            if ((*it)->key == key) {
                if ((*it)->value < value) {
                    (*it)->value = value;
                    return;
                }
                else {
                    return;
                }
            }
        }
        table[index]->push_back(new HashNode(key, value));
    }

}

template<typename K, typename V>
void HTable<K, V>::remove(K key) {
    int index = hashFunction(key);
    HashNode *search = this->find(key);

    if (!table[index] || !search) {
        std::cout << "Element with key: " << key << " not found" << std::endl;
        return;
    }

    table[index]->remove(search);
    if (table[index]->empty()) {
        table[index] = NULL;
    }
}

template<typename K, typename V>
int HTable<K, V>::getSize() const {
    int size = 0;

    for (int i = 0; i < capacity; i++) {
        if (table[i]) {
            size += table[i]->size();
        }
    }
    return size;
}

template<typename K, typename V>
int HTable<K, V>::getSum() const {
    int sum = 0;

    for (int i = 0; i < capacity; i++) {
        if (table[i]) {
            auto it = table[i]->begin();
            for (it; it != table[i]->end(); it++) {
                sum += (*it)->value;
            }
        }
    }
    return sum;
}

template<typename K, typename V>
typename HTable<K, V>::HashNode* HTable<K, V>::find(K key) {
    int index = hashFunction(key);

    if (!table[index]) {
        std::cout << "Element with key: " << key << " not found" << std::endl;
        return nullptr;
    }

    auto it = table[index]->begin();

    while(it != table[index]->end()) {
        if ((*it)->key == key)
            return *it;
        it++;
    }
    std::cout << "Element with key: " << key << " not found" << std::endl;
    return nullptr;
}

template<typename K, typename V>
K HTable<K, V>::getKey(int number) {
    int count = 0;
    for (int i = 0; i < capacity; i++) {
        if (table[i]) {
            for (auto it = table[i]->begin(); it != table[i]->end(); it++) {
                count++;
                if (count == number) {
                    return (*it)->key;
                }
            }
        }
    }
}

template<typename K, typename V>
V HTable<K, V>::getValue(K key) {
    HashNode *search = this->find(key);
    return search->value;
}

template<typename K, typename V>
bool HTable<K, V>::isKey(K key) {
    if (this->find(key)) {
        return true;
    }
    return false;
}

template<typename K, typename V>
void HTable<K, V>::writeToFile(const std::string& path) const {
    std::ofstream file;

    file.open(path);

    if (!file.is_open()) {
        std::cout << "Can't open the file " << path << std::endl;
        return;
    }

    file << "KEY, VALUE" << std::endl;
    file << "==========" << std::endl;
    for (int i = 0; i < capacity; i++) {
        if (table[i]) {
            for (auto it = table[i]->begin(); it != table[i]->end(); it++) {
                file << (*it)->key << ", " << std::to_string((*it)->value) << std::endl;
            }
        }
    }

    file.close();
}

template<typename K, typename V>
void HTable<K, V>::loadFromFile(const std::string& path) {
    std::string tmp;
    std::ifstream file;

    file.open(path);

    if (!file.is_open()) {
        std::cout << "Can't open the file " << path << std::endl;
        return;
    }

    this->clear();

    K key;
    V value;
    int count = 0;
    while (!file.eof()) {
        count++;
        std::getline(file, tmp);
        if (!tmp.empty() && count > 2) {
            int s = tmp.find(", ");
            key = tmp.substr(0, s);
            value = std::stoi(tmp.substr(s + 2, tmp.length()));
            this->insert(key, value);
        }
    }

    file.close();
}

template<typename K, typename V>
bool HTable<K, V>::operator==(const HTable& other) const {
    for (int i = 0; i < capacity; i++) {
        if (table[i] && other.table[i]) {
            auto it1 = table[i]->begin();
            auto it2 = other.table[i]->begin();
            while (it1 != table[i]->end() && it2 != other.table[i]->end()) {
                if ((*it1)->key != (*it2)->key || (*it1)->value != (*it2)->value) {
                    return false;
                }
                it1++;
                it2++;
            }
        }
    }
    return true;
}

template<typename K, typename V>
V& HTable<K, V>::operator[](K key) {
    return this->find(key)->value;
}

template<typename K, typename V>
void HTable<K, V>::display() {
    for (int i = 0; i < capacity; i++) {
        if (table[i]) {
            std::cout << "Hash index: " << std::to_string(i) << std::endl;
            for (auto it = table[i]->begin(); it != table[i]->end(); it++) {
                std::cout << "              |Key: " << (*it)->key << " -->" << " Value: " << (*it)->value << std::endl;
            }
        }
      }
}
