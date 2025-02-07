#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

/* 10,000      insertions -> .037813s
 * 100,000     insertions -> 5.55s
 * 1,000,000   insertions -> 728s
 * 10,000,000  insertions ->
*/

#include <iostream>

namespace CustomStructs {

template <typename T>
class ArrayList
{
public:
    ArrayList() : _size(0), _capacity(64) { _arr = new T[_capacity]; }
    ArrayList(const int& capacity) : _size(0), _capacity(capacity) { _arr = new T[_capacity]; }
    ~ArrayList() { delete[] _arr; };
    void push_front(const T &rVal);
    void push_back(const T &rVal);
    void push_index(const size_t &index, const T &rVal);
    void pop_front();
    void pop_back() { --_size; }
    bool contains(const T &rVal) const;
    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }

    T& operator[](std::size_t index) ;

private:
    void resize();

private:
    T* _arr;
    size_t _size;
    size_t _capacity;
};

/// @brief Inserts an element at the front of the ArrayList, shifting all existing elements to the right.
/// @param rVal The value to be inserted at the front of the ArrayList.
template<typename T>
void ArrayList<T>::push_front(const T &rVal) {
    // resize if necessary
    if(_size == _capacity) {
        resize();
    }

    // shift all elements to the right. O(n)
    for(size_t x = size; x > 0; --x) {
        _arr[x] = _arr[x-1];
    }
    _arr[0] = rVal;
    ++_size;
}

/// @brief Adds an element to the end of the ArrayList.
/// @param rVal The value to be inserted at the end of the ArrayList.
template <typename T>
void ArrayList<T>::push_back(const T &rVal)
{
    // resize if necessary
    if(_size == _capacity) {
        resize();
    }
    _arr[_size] = rVal;
    ++_size;
}

/// @brief Inserts an element at a specified index in the ArrayList, shifting
///   subsequent elements to the right.
/// @param index The position at which to insert the new element. Must be 
///   within the current size of the ArrayList.
/// @param rVal The value to be inserted at the specified index.
/// @throws std::out_of_range if the index is greater than the current size of 
///   the ArrayList.
template <typename T>
void ArrayList<T>::push_index(const size_t &index, const T &rVal) 
{
    if(_size < index) 
    {
        throw std::out_of_range("Index out of range");
    }

    // resize if necessary
    if(_size == _capacity) 
    {
        resize();
    }

    for(size_t x = _size; x > index; --x) 
    {
        _arr[x] = _arr[x-1]; // shift arr to the right
    }
    _arr[index] = rVal;
    ++_size;
}

/// @brief Removes and returns the first element of the ArrayList, shifting 
///   subsequent elements to the left.
/// @return The first element of the ArrayList before removal.
/// @throws std::out_of_range if the ArrayList is empty.
template <typename T>
void ArrayList<T>::pop_front()
{
    T value = _arr[0];

    //shift all elements to the left
    for(size_t x = 0; x < _size; ++x)
    {
        _arr[x] = _arr[x+1];
    }
    --_size;
}

template <typename T>
bool ArrayList<T>::contains(const T &rVal) const {
    for(std::size_t x = 0; x < _size; ++x) 
    {
        if(_arr[x] == rVal) 
        {
            return true;
        }
    }
    return false;
}

/// @brief 
/// @tparam T 
template <typename T>
void ArrayList<T>::resize() 
{
    T* temp;
    size_t newCap = _capacity * 2;

    try 
    {
        temp = new T[_capacity];
    }
    catch(const std::bad_alloc&)
    {
        throw std::runtime_error("Memory allocation failed during resize");
    }

    for(size_t x = 0; x < _size; ++x)
    {
        temp[x] = _arr[x];
    }

    delete[] _arr;
    _arr = temp;
    _capacity = newCap;
}

/// @brief Accesses the element at the specified index.
/// @param index The index of the element to access. Must be within the current
///   size of the ArrayList.
/// @return A reference to the element at the specified index.
/// @throws std::out_of_range if the index is out of the valid range 
template <typename T>
T& ArrayList<T>::operator[](std::size_t index) 
{
    /* 
    // normal implementation
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    */

    // hash map implementation
    if(index >= _capacity) 
    {
        throw std::out_of_range("Index out of range");
    }
    return _arr[index];
}
} // namespace MyDataStructures
#endif // ARRAY_LIST_H