/* Problem:
 *   Write code to remove duplicates from an unsorted linked list.
 *
 * Solution:
 *   Use a hash map to determine if some node is a duplicate. The map's 'key' 
 *   is going to be the element in the list. The map's 'value' is going to be
 *   true or false.
 *   Loop thorugh the linked list and at each node, add the value to the hash 
 *   map. If there is already a value mapped at that index then we know that
 *   node is a duplicate.
 * 
 * Big O:
 *   Time: O(n)
 *   Memory: O(n)
 * 
 * Source:
 *   Cracking the Coding Interview by Gayle Laackman McDowell
 *     Question: 2.1
*/
#include <list>
#include <unordered_map>

/// @brief Uses a map to keep track of duplicate elements
/// @param link_list a pointer to the list
void removeDups(std::list<int>* link_list )
{
    std::unordered_map<int, bool> map;

    // loop through the list
    std::list<int>::iterator it = link_list->begin();
    while (it != link_list->end())
    {
        // if the element hasn't been found before, set
        // the map value to true
        if(map[*it] == false)
        {
            map[*it] = true;
            ++it;
        }
        else
        {
            it = link_list->erase(it);
        }
    }
}