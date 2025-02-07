#ifndef HASH_MAP
#define HASH_MAP
#include <iostream>
#include <functional>
#include "arrayList.h"
#include "linkedList.h"
#include "pair.h"

using namespace CustomStructs;

template<typename KeyType, class ValueType> 
class HashMap 
{
public:
    //HashMap();
    bool insert(const KeyType& key, const ValueType& val);
    bool remove(const KeyType& key);
    void printMap();

private:
    std::size_t hashFunction(const KeyType &key) const;

private:
    ArrayList<LinkedList<pair<KeyType,ValueType>*>*> _hashMap;
};
#endif // HASH_MAP

/// @brief Inserts a new key-value pair into the hash map. If the key already
///   exists, insertion fails.
/// @param key The key to be inserted into the hash map.
/// @param val The value associated with the key to be inserted.
/// @return Returns true if the key-value pair was successfully inserted, false
///   if the key already exists.
template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::insert(const KeyType &key, const ValueType &val)
{
    // get the index for the new key/val pair
    std::size_t hashKey = hashFunction(key);
    //std::cout << "hash key: " << hashKey << std::endl;
    std::size_t index = hashKey % _hashMap.capacity();
    //std::cout << "index: " << index << std::endl;

    // create the new pair object
    pair<KeyType, ValueType> *p = new pair<KeyType, ValueType>(key, val);

    //std::cout << "p->first: " << p->first << std::endl;
    //std::cout << "p->second: " << p->second << std::endl;

    // check to see if key already exists
    LinkedList<pair<KeyType,ValueType>*> *list = _hashMap[index]; 
    if(list == nullptr) 
    {
        list = new LinkedList<pair<KeyType,ValueType>*>();
        _hashMap[index] = list;
    } 
    else
    {
        for(std::size_t x = 0; x < list->size(); ++x) 
        {

            if(list->get_index(x)->first == key)
            {
                return false;
            }
        }
    }

    // at this index, add the key/value pair to the map
    _hashMap[index]->push_back(p);
    return true;
}

/// @brief Searches for the given key in the hash map and removes the 
///   corresponding key-value pair if found.
/// @param key The key to be removed from the hash map.
/// @return Returns true if the key was found and successfully removed, false
///   if the key does not exist.
template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::remove(const KeyType &key)
{
    // get the hash key
    std::size_t hashKey = hashFunction(key);
    std::size_t index = hashKey % _hashMap.size();

    // search the linked list for the key
    for(std::size_t x = 0; x < _hashMap[index].size(); ++x)
    {
        // if found, remove and return true
        if(key == _hashMap[index].get_index(x).first)
        {
            _hashMap[index].pop_index(x);
            return true;
        }
    }

    return false;
}

/// @brief Computes the hash value for a given key using the standard hash 
///   function.
/// @tparam KeyType The type of the key used in the HashMap.
/// @param key The key for which the hash value is computed.
/// @return The computed hash value as a size_t.
template <typename KeyType, typename ValueType>
std::size_t HashMap<KeyType, ValueType>::hashFunction(const KeyType &key) const
{
    return std::hash<KeyType>()(key);  
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType,ValueType>::printMap()
{
    std::cout << "hash map size: " << _hashMap.size() << std::endl;
    for(std::size_t x = 0; x < _hashMap.size(); ++x)
    {
        LinkedList<pair<KeyType,ValueType>*> *list = _hashMap[x];
        if(list == nullptr) 
        {
            std::cout << "\n";
        }
        else
        {
            for(std::size_t x = 0; x < list->size(); ++x) 
            {
                pair<KeyType,ValueType>* p = list->get_index(x);
                std::cout << &p;

                if(x == (list->size()-1))
                {
                    std::cout << "\n";
                }
            }
        }
    }
}