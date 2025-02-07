#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>

/* 10,000     insertions -> .068893s 
 * 100,000    insertions -> 13.00s
 * 1,000,000  insertions -> 175.92s
 * 10,000,000 insertions ->
*/

namespace CustomStructs {

template <typename T>
class LinkedList
{
    struct node
    {
        node(const T &rVal) : val(rVal), next(nullptr){}
        node *next;
        T val;
    };

public:
    LinkedList() : _head(nullptr), _tail(nullptr), _size(0){}
    ~LinkedList();
    T& front();
    T& back();
    T& get_index(const size_t &index);
    void pop_front();
    void pop_back();
    void pop_index(const size_t &index);
    bool push_front(const T &rVal);
    bool push_back(const T &rVal);
    bool push_index(const T &rVal, const size_t &index);
    bool contains(const T &rVal) const;
    size_t size() const { return _size; }
    void clear();

    LinkedList& operator=(const LinkedList &rVal);
    const T& operator[](const size_t &index) const;

private:
    bool is_empty() const {return _head == nullptr;}
    node* get_node(const size_t &index) const;

private:
    node *_head;
    node *_tail;
    size_t _size;
};

/// @brief Destructor
template <typename T>
LinkedList<T>::~LinkedList()
{
    while (_head != nullptr)
    {
        node *temp = _head;
        _head = _head->next;
        delete temp;
    }
}

/// @brief Retrieves the value of the first element in the list.
/// @return A reference to the value of the first element.
/// @throws std::out_of_range if the list is empty.
template <typename T>
T& LinkedList<T>::front()
{
    if(is_empty())
    {
        throw std::out_of_range("List is empty");
    }

    return _head->val;
}

/// @brief Retrieves the value of the last element in the list.
/// @return A reference to the value of the last element.
/// @throws std::out_of_range if the list is empty.
template <typename T>
T& LinkedList<T>::back()
{
    if(is_empty())
    {
        throw std::out_of_range("List is empty");
    }
    return _tail->val;
}

/// @brief Removes the first item in the list.
/// @return The first value in the list.
/// @throws std::out_of_range if the list is empty
template <typename T>
void LinkedList<T>::pop_front()
{
    // retrieve the first item
    T value = front();

    // remove the item from the list
    node *temp = _head;
    _head = _head->next;
    delete temp;
    --_size;
    if(_size == 0) 
    {
        _tail = nullptr;
    }
}

/// @brief Removes the last item in the list
/// @return The last value in the list
/// @throws std::out_of_range if the list is empty
template <typename T>
void LinkedList<T>::pop_back()
{
    // retrieve the last item
    T value = back();

    // retrieve the second to last item
    node* temp = get_node(_size-2);

    // remove the tail and set the pointers
    _tail = temp;
    delete _tail->next;
    _tail->next = nullptr;
    --_size;
}

/// @brief
/// @tparam T
/// @param index
/// @return
template <typename T>
void LinkedList<T>::pop_index(const size_t &index)
{
    if (index == 0)
    {
        pop_front();
    }
    else if (index == (_size-1))
    {
        pop_back();
    }
    else
    {
        // find the target node and the one to the left
        node* leftNode = get_node(index-1);
        node* targetNode = leftNode->next;
        T value = targetNode->val;

        // set the pointers and delete the node
        leftNode->next = targetNode->next;
        delete targetNode;
        --_size;
        return value;
    }
}

/// @brief
/// @tparam T
/// @param rVal
/// @return
template <typename T>
bool LinkedList<T>::push_front(const T &rVal)
{
    // create the new node
    node* newNode = nullptr;
    try 
    {
        newNode = new node(rVal);
    } 
    catch(std::bad_alloc) 
    {
        return false;
    }

    // update the head
    node* temp = _head;
    _head = newNode;
    _head->next = temp;
    ++_size;
    
    // update the tail if neccessary
    if(_size == 1) 
    {
        _tail = _head;
    }
    return true;
}

/// @brief Adds an element to the end of the LinkedList.
/// @param rVal The value to be inserted at the end of the LinkedList.
/// @return True if the insertion was successful, false if memory allocation 
///   failed.
template <typename T>
bool LinkedList<T>::push_back(const T &rVal)
{
    // create the new node
    node* newNode = nullptr;
    try 
    {
        newNode = new node(rVal);
    }
    catch(std::bad_alloc) 
    {
        return false;
    }

    // handle empty list
    if (_size == 0)
    {
        _head = _tail = newNode;
    }
    else
    {
        _tail->next = newNode;
        _tail = newNode;
    }
    ++_size;
    return true;
}

/// @brief Inserts an element at a specified index in the LinkedList, shifting
///   subsequent elements to the right.
/// @param rVal The value to be inserted at the specified index.
/// @param index The position at which to insert the new element. Must be
///   between 0 and the current size of the list.
/// @return True if the insertion was successful, false if memory allocation
///   failed or the index is out of range.
template <typename T>
bool LinkedList<T>::push_index(const T &rVal, const size_t &index)
{
    if (index == 0)
    {
        return push_front(rVal);
    }
    else if (index == _size)
    {
        return push_back(rVal);
    }
    else
    {
        // create the new node & return false on bad memory allocation
        node* newNode = nullptr;
        try
        {
            newNode = new node(rVal);
        }
        catch(const std::bad_alloc& e)
        {
            return false;
        }

        // find the node to the left of the insertion
        node *temp = get_node(index-1);

        // update pointers
        newNode->next = temp->next;
        temp->next = newNode;
        ++_size;

        return true;
    }
}

/// @brief Checks if the list contains a specific value.
/// @param rVal The value to search for in the list.
/// @return True if the value is found, otherwise false.
template <typename T>
bool LinkedList<T>::contains(const T &rVal) const 
{
    const node *temp = _head;

    while(temp != nullptr)
    {
        if(temp->val == rVal) 
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

/// @brief Clears the entire list, deleting all nodes.
template <typename T>
void LinkedList<T>::clear()
{
    while(_head != nullptr)
    {
        node *temp = _head;
        _head = _head->next;
        delete temp;
    }
    _tail = nullptr;
    _size = 0;
}

/// @brief Assignment operator for copying another LinkedList.
/// @param rVal The LinkedList to copy from.
/// @return A reference to this LinkedList.
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &rVal) 
{
    // check for self assignment
    if(this == &rVal)
    {
        return *this;
    }

    // clear the list
    this->clear();

    // copy values over
    for(std::size_t x = 0; x < rVal.size(); ++x)
    {
        this->push_back(rVal.get_index(x));
    }
}

/// @brief Retrieves the value at a specified position in the list.
/// @param index The position in the list where the value is to be retrieved.
///   Must be within the bounds of the list.
/// @return The value at the specified position.
/// @throws std::out_of_range if index is out of bounds
template <typename T>
T& LinkedList<T>::get_index(const size_t &index) //can't be const. TODO
{
    node* temp = get_node(index);
    
    // check for out of bounds
    if(temp == nullptr)
    {
        throw std::out_of_range("Index out of range");
    }

    return temp->val;
}

/// @brief Finds and returns the node at a specified index in the list.
/// @param index The position of the node to be retrieved. Must be within the 
///   bounds of the list.
/// @return A pointer to the node at the specified index. nullptr if not found
template <typename T>
typename LinkedList<T>::node* LinkedList<T>::get_node(const size_t &index) const
{
    node* temp = _head;

    if(is_empty()) 
    {
        return nullptr;
    }

    // traverse list
    for (size_t x = 0; temp != nullptr; ++x)
    {
        if(x == index) 
        {
            return temp; // return if found
        }
        temp = temp->next;
    }

    return nullptr;
}

/// @brief Accesses the element at the specified index in the linked list.
///   This operator provides read-only access to the element.
/// @tparam T The type of the elements stored in the linked list.
/// @param index The index of the element to access, starting from 0.
/// @return A constant reference to the element at the specified index.
template<typename T>
const T& LinkedList<T>::operator[](const size_t &index) const {
    node* elem = get_node(index);
    return elem->val;
}

} // namespace MyDataStructures

#endif // LINKEDLIST_H