/* Problem:
 *   Write a program to sort a stack such that the smallest items are on top.
 *   You can use an additional temporary stack but you may not copy the 
 *   elements into any other data structure. That stack supports push, pop,
 *   peek and isEmpty.
 *
 * Solution:
 *   1) Using two temp stacks. Pop an elemement from stack and push it into 
 *      temp. Be sure to keep temp sorted as you push each element onto it.
 *      In order to do this, you need ANOTHER temp stack to hold the values as
 *      iterate through temp searching for its correct position. This is
 *      clearer but breaks the rules of using temp stack.
 *   2) Using one temp stack. Same initial approach. Pop from stack and push
 *      into temp. Howver, use the initial stack to temporarily hold the values
 *      of the temp stack while you iterate through it. More convoluted but 
 *      follows the rules of only having one temp stack.
 *
*/

#include <stack>

void insertElemInSortedOrder(std::stack<int>& stack, const int& elem);

void sortStack(std::stack<int>& stack)
{
    std::stack<int> temp;

    while(!stack.empty())
    {
        // get the top elem
        int top = stack.top();
        stack.pop();

        // find it's correct palce in temp. This ensures temp stays sorted
        while(!temp.empty() && temp.top() > top)
        {
            stack.push(temp.top());
            temp.pop();
        }

        // push stack elem onto temp stack
        temp.push(top);
    }

    // temp is now sorted with high numbers on top
    // copy temp over to stack
    while(!temp.empty())
    {
        stack.push(temp.top());
        temp.pop();
    }
}

/**
 * @brief Sorts a stack of ints. Lowest numbers are on top. This uses two temp
 *   stacks (because insertElemInSortedOrder uses a temp stack as well)
 * 
 * @param stack The stack to be sorted
 */
void sortStackButWithTwoTempStacks(std::stack<int>& stack)
{
    std::stack<int> temp;

    while(!stack.empty())
    {
        int top = stack.top();
        stack.pop();
        insertElemInSortedOrder(temp, top);
    }

    while(!temp.empty())
    {
        int top = temp.top();
        stack.push(top);
        temp.pop();
    }
}


/**
 * @brief Insert elem into the stack. The stack should already be sorted with
 *  smallest values on the bottom
 * 
 * @param stack 
 * @param elem 
 */
void insertElemInSortedOrder(std::stack<int>& stack, const int& elem)
{
    std::stack<int> temp;

    // search for the first element in stack that is greater than elem
    while(!stack.empty())
    {
        // once you find its place, push elem into stack
        int top = stack.top();
        if(top < elem)
        {
            stack.push(elem);
            break;
        }

        // otherwise, pop and store elements in temp
        temp.push(top);
        stack.pop();
    }

    // if stack is empty that means elem is the smallest value in the stack
    if(stack.empty())
    {
        stack.push(elem);
    }

    // copy the elems back into stack
    while(!temp.empty())
    {
        int t = temp.top();
        stack.push(t);
        temp.pop();
    }
}