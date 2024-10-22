/* Problem: 
 *   Given two linked lists, determine if the two lists intersect. Return the
 *   intersecting node. Note that the intersecting node is based on reference,
 *   not value.
 * 
 * Solution:
 *   Every element after the intersection point will be equal by reference.
 *   Recursively find the end of each list, then in the call stack compare 
 *   each node by reference. Once we come across two node's that are not
 *   equal then we know node->next is the intersection point.
 *
 * Big O:
 *   Time: O(n+m)
 *   Space: O(1)
 */

struct listNode 
{
    int data;
    listNode* next;
    listNode(const int& rval) : data(rval), next(nullptr) {}
};

listNode* findIntersection(listNode* head1, listNode* head2)
{
    // empty list means no intersection
    if(head1 == nullptr || head2 == nullptr) return nullptr;

    listNode* t1 = head1;
    listNode* t2 = head2;
    int len1 = 0;
    int len2 = 0;

    // Count the lengths of both lists
    while (t1 != nullptr) 
    {
        t1 = t1->next;
        ++len1;
    }
    while (t2 != nullptr) 
    {
        t2 = t2->next;
        ++len2;
    }

    // if the last nodes aren't equal then there is no intersection
    if(t1 != t2) return nullptr;

    // restart the iteration
    t1 = head1;
    t2 = head2;

    // start iterating the lists at the maximum yet equal distance from the end
    for(int x = 0; x < (len1-len2); ++x)
    {
        t1 = t1->next;
    }
    for(int y = 0; y < (len2-len1); ++y)
    {
        t2 = t2->next;
    }

    // now t1 and t2 are equal distance form the end
    while(t1 != nullptr && t2 != nullptr)
    {
        if(t1 == t2)
        {
            return t1;
        }
        t1 = t1->next;
        t2 = t2->next;
    }

    // no intersection
    return nullptr;
}


