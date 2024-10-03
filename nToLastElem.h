/* Problem:
 *   Implement an algorithm to find the n-th to last element in a singly-linked
 *   list.
 * 
 * Solution:
 *   c++ implements a double linked list std::list. I am going to use this but 
 *   limit the list traversal to be uni-directional (left to right)
 * 
 * 
*/

#include <iostream>
#include <list>

/// @brief Finds the n-th to last element in the array
/// @param link_list pointer to the list
/// @param n how far the desired element is to the end of the list
/// @return the value of the desired element. -1 if the value isn't found
int nToLastElem(const std::list<int>* link_list, const int& n)
{
    int listSize = link_list->size(); // size() is O(1)
    int index = listSize - n - 1;

    if(n < 0 || n >= listSize) return -1;

    std::list<int>::const_iterator it = link_list->cbegin();
    for(int i = 0; it != link_list->cend(); ++i)
    {
        if(i == index)
        {
            return *it;
        }

        ++it;
    }
    return -1;
}