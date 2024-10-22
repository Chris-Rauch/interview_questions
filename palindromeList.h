/* Problem: 
 *   Implement a function to see if the linked list is a palindrome.
 *
 * Solution:
 *   1) Create a copy and reverse the linked list.
 *   2) Iterate through the list. Push the first half into a stack. Compare
 *      the stack to the back half
 *   3) Recursively, given the length. In this approach, we need to return a
 *      pair<node*,bool>. This is to keep track of the result of the palindrome
 *      and the node on the right side of the call stack
 *   
 * 
*/

#include <cstddef>
#include <stack>
#include <system_error>
#include <utility>

namespace PalindromeList {
struct node
{
    char c;
    node* next;
    node(char letter) : c(letter), next(nullptr){}
    ~node() {}
};
}

/**
 * @brief Checks if list is a palindrome
 * 
 * @param list A linked list containing char's
 * @return true if it is a palindrome
 * @return false if not
 */
bool palindromeListCloneAndReverse(PalindromeList::node* list)
{
    bool isPalindrome = true;;
    
    // check empty list
    if(list == nullptr) return true;

    // create a copy in the reverse order
    PalindromeList::node* newList = nullptr;
    PalindromeList::node* temp = list;
    int count = 0;
    while(temp != nullptr)
    {
        PalindromeList::node* t = new PalindromeList::node(temp->c);
        t->next = newList;
        newList = t;

        temp = temp->next;
        ++count;
    }

    // compare the two lists
    PalindromeList::node* t1 = list;
    PalindromeList::node* t2 = newList;
    for(int x = 0; x < (count/2); ++x)
    {
        if(t1->c != t2->c) 
        {
            isPalindrome = false;
            break;
        }
        t1 = t1->next;
        t2 = t2->next;
    }

    while(newList != nullptr)
    {
        PalindromeList::node* t = newList->next;
        delete newList;
        newList = t;
    }

    return isPalindrome;
}

bool palindromeListIterate(PalindromeList::node* head) 
{
    std::stack<char> stack;
    PalindromeList::node* slow = head;
    PalindromeList::node* fast = head;

    // iterate through the first half of the list and add it to the stack
    while(fast != nullptr && fast->next != nullptr)
    {
        stack.push(slow->c);
        slow = slow->next;
        fast = fast->next->next;
    }

    // skip the middle elem if the tot len is un-even
    if(fast != nullptr)
    {
        slow = slow->next;
    }

    // iterate through the rest of the list
    // pop the stack an compare
    while(slow != nullptr)
    {
        char c = stack.top();
        if(c != slow->c)
        {
            return false;
        }
        stack.pop();
    }

    return true;
}

std::pair<PalindromeList::node*, bool> solve(PalindromeList::node* head, const int& len);



bool palindromeListRecursive(PalindromeList::node* head, const int& len)
{
    return solve(head,len).second;
}

std::pair<PalindromeList::node*, bool> solve(PalindromeList::node* head, const int& len)
{
    // len of list is odd. Return head->next
    if(len == 1)
    {
        return std::pair<PalindromeList::node*, bool>(head->next, true);
    } 
    // len of list is even. Return head
    else if (len == 0) 
    {
        return std::pair<PalindromeList::node*, bool>(head, true);
    }

    std::pair<PalindromeList::node*, bool> rVal = solve(head->next, len - 2);

    if(rVal.first == nullptr || rVal.second == false) return rVal;

    if(rVal.first->c != head->c)
    {
        rVal.second = false;
    }

    rVal.first = rVal.first->next;
    return rVal;
}
