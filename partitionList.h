/* Problem:
 *   Write code to aprtition a linked list arounda  value x, such that all
 *   nodes less than x come before all nodes greater than or equal to x. (Note:
 *   The partition element can appear anywhere on the right side of the 
 *   partition; it does not need to appear in between the left and right
 *   partitions)
 * 
 * Ex:
 *   Input:  3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition is 5]
 *   Output: 3 -> 1 -> 2    ->    10 -> 5 -> 5 -> 8
 *   This is one of many output  
 * 
 * Solution:
 *   I can think of two solutions.
 *     1) Merging lists. Create two temp lists, one for elements less than
 *        the partition and the other for elems greater than or equal to. As
 *        traverse the list, add elements to the tmp lists accordingly. Then
 *        merge the two list
 *     2) In place. Modify the list dynamically while traversing. As you come
 *        across an element, push it to the front or back of the list.
 *   Solution 1 is esier to read and probably less prone to bugs.
 *   Solution 2 uses memory more efficiently which could be usefull for large
 *     lists
 * 
 * Big O:
 *   Solution 1:
 *      O(n) Time
 *      O(n) Memory (allocating the two temp lists)
 *   Solution 2:
 *      O(n) Time
 *      O(1) Memory (only ever allocate one node at a time)
 * 
 * Source:
 *   Cracking the Coding Interview by Gayle Laackman McDowell
 *     Question: 2.4
*/
#include <list>

/// @brief Rearranges list such that all values less partition come before all
///   values greater than or equal to partition. This is sort of an in place
///   implementation. There will only ever be at most (n + 1) elems in the list
///   at any given time. 
///   Traverse the list. If the elem is is less than the partition, move it to
///   the front of the list. If it is greater or equal, move it to the back.
/// @param list The list to be rearranged
/// @param partition partitioning element
void partitionListInPlace(std::list<int>* list, const int& partition)
{
    int size = list->size();
    std::list<int>::iterator it = list->begin();

    // traverse the list
    for(int i = 0; i < size; ++i)
    {
        if(*it < partition)
        {
            list->push_front(*it);
        }
        else
        {
            list->push_back(*it);
        }
        it = list->erase(it);
    }
}


void partitionList(std::list<int>* list, const int& partition)
{
    std::list<int> lesser = {};
    std::list<int> upper = {};

    std::list<int>::iterator it;
    for(it = list->begin(); it != list->end(); ++it)
    {
        if(*it < partition)
        {
            lesser.push_front(*it); 
        }
        else
        {
            upper.push_front(*it);
        }
        // you could delete it here to save memory
    }
    list->clear();
    list->splice(list->end(), lesser);
    list->splice(list->end(), upper);
}