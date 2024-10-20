/* Problem:
 *   You have two numbers represented by a linked list, where each node 
 *   contains a single digit. The digits are stored in reverse order, such that
 *   the 1's digit is at the head of the list. Write a function that adds the
 *   two numbers and returns the sum as a linked list.
 *
 * Example:
 *   Input (7 -> 1 -> 6) + (5 -> 9 -> 2). That is 617 + 295
 *   Output (2 -> 1 -> 9). That is 912
 *
 * Solution:
 *   Synchronously traverse the lists and add the two numbers together. If
 *   their sum is greater than 10, add 1 to the right node. If one list is
 *   bigger than the other, treat null nodes as 0
 *
 * Source:
 *   Cracking the Coding Interview by Gayle Laackmann McDowell
 *     Question: 2.4
*/

#include <cstddef>
#include <iostream>

struct node 
{
    int val;
    node* next;
    node(int rVal) : val(rVal), next(nullptr) {}
};

/// @brief Adds the lists together and returns a pointer to the new list
/// @param list1 A linked list representing some whole number
/// @param list2 A linked list representing some whole number
/// @return Returns a pointer to the new list. Memory management is handed off
/// to the user
node* sumList(const node* list1, const node* list2)
{
    int carryDigit = 0;
    node* head = nullptr;
    node* temp = nullptr;

    // traverse the lists
    while(list1 != nullptr || list2 != nullptr)
    {
        // grab the value from the list. Treat end of list as 0
        int val1 = (list1) ? list1->val : 0;
        int val2 = (list2) ? list2->val : 0;
        int sum = val1 + val2 + carryDigit;

        // set carry over digit
        carryDigit = (sum >= 10) ? 1 : 0;

        // if it's the first elem, set the head
        node* t = new node(sum%10);
        if(head == nullptr)
        {
            head = temp = t;
        }
        else 
        {
            temp->next = t;
            temp = temp->next;
        }

        // increment the lists
        list1 = (list1) ? list1->next : nullptr;
        list2 = (list2) ? list2->next : nullptr;
    }

    if(carryDigit > 0)
    {
        temp->next = new node(carryDigit);
    }

    return  head;
}

void printSum(const node* list)
{
    while(list != nullptr)
    {

        std::cout << list->val;
        if(list->next != nullptr)
        {
            std::cout << "->";
        }
        list = list->next;
    }
}