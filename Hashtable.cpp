#include <iostream>
#include <vector>
#include <list>

// Define the hash table class
template<typename KeyType, typename ValueType, typename Hash = std::hash<KeyType>>
class HashTable {
private:
    // Define the hash table entry
    struct Entry {
        KeyType key;
        ValueType value;
    };

    // Define the array of buckets (each bucket is a linked list)
    std::vector<std::list<Entry>> table;
    Hash hashFunction;

public:
    // Constructor
    HashTable(size_t size) : table(size) {}

    // Function to insert a key-value pair into the hash table
    void insert(const KeyType& key, const ValueType& value) {
        size_t index = hashFunction(key) % table.size();
        for (auto& entry : table[index]) {
            if (entry.key == key) {
                entry.value = value; // Update value if key already exists
                return;
            }
        }
        table[index].push_back({key, value});
    }

    // Function to retrieve the value associated with a key
    bool find(const KeyType& key, ValueType& value) const {
        size_t index = hashFunction(key) % table.size();
        for (const auto& entry : table[index]) {
            if (entry.key == key) {
                value = entry.value;
                return true; // Found the key
            }
        }
        return false; // Key not found
    }

    // Function to remove a key-value pair from the hash table
    void remove(const KeyType& key) {
        size_t index = hashFunction(key) % table.size();
        table[index].remove_if([key](const Entry& entry) { return entry.key == key; });
    }
};

int main() {
    // Example usage
    HashTable<std::string, int> myHashTable(10);

    // Insert key-value pairs
    myHashTable.insert("apple", 5);
    myHashTable.insert("banana", 10);
    myHashTable.insert("orange", 15);

    // Retrieve values
    int value;
    if (myHashTable.find("banana", value)) {
        std::cout << "Value associated with banana: " << value << std::endl;
    } else {
        std::cout << "banana not found" << std::endl;
    }

    // Remove a key-value pair
    myHashTable.remove("banana");

    // Try to retrieve the value again (should fail)
    if (myHashTable.find("banana", value)) {
        std::cout << "Value associated with banana: " << value << std::endl;
    } else {
        std::cout << "banana not found" << std::endl;
    }

    return 0;
}
