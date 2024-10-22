/* Problem:
 *   Implement an algorithm to delete a node in the middle (i.e., any node but
 *   the first and last node, not necessarily the exact middle) of a singly 
 *   linked list, give only access to that node.
 * 
 * Solution:
 *   Given node and nextNode, set node equal to nextNode. Then delete next node
 * 
 * Big O:
 *   O(1) Time
 *   O(1) Memory
 *
 * Source:
 *   Cracking the Coding Interview by Gayle Laackman McDowell
 *     Question: 2.3
 */

#include <list>

struct node 
{
    int val;
    node* next;
};

/// @brief Deletes a node from the list
/// @param n The desired node to be deleted
void deleteMiddleNode(node* n)
{
    // make sure this node or next node isn't null
    if(n == nullptr || n->next == nullptr) return;

    // set node equal to the next node
    node* nextNode = n->next;
    n->val = nextNode->val;
    n->next = nextNode->next;

    delete nextNode;
}