/* Problem: 
 *   Given a linked list which might contain a loop, implement an algorithm
 *   that returns the nodevat the beginning of the loop (if it exists).
 *
 * Solution:
 *   Iterate through the list and use a hash map to determine if a node has
 *   been seen before.
 *
 * Big O:
 *   Time: O(n)
 *   Space: O(n)
*/

#include <cstddef>
#include <unordered_set>

struct lNode 
{
    char data;
    lNode* next;
    lNode(char rData) : data(rData), next(nullptr) {}
};

lNode* findLoop(lNode* head)
{
    std::unordered_set<lNode*, bool> set;

    while(head != nullptr)
    {
        // check to see if the node is in the map
        if(set.find(head) != set.end())
        {
            return head; // Loop detected, return the start of the loop
        }

        // if not, add it
        set.emplace(head, true);
        head = head->next;
    }

    return nullptr;
}