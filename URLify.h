/* Problem: 
 *   Write a method to replace all spaces in a string with '%20'.You may assume
 *   that the string has sufficient space at the end to hold the additional
 *   characters, and that you are given the "true" length of the string. 
 *   
 *   (Note: if implementing in java please use a character array so that you
 *   can perform this operation in place)
 * 
 * Example:
 *   Input:  "Mr John Smith    ", 13
 *   Output: "Mr%20John%20Smith"
 * 
 * Solution:
 *  
 * Big O:
 *   O(n)
 * 
 * Source:
 *   Cracking the Coding Interview by Gayle Laackman McDowell
 *     Question: 1.3
*/
#include <cstring>

void URLify(char* str, const size_t& len)
{
    int numSpaces = 0;

    // count the number of spaces in the str
    for(size_t i = 0; i < len; ++i)
    {
        if(str[i] == ' ') 
        {
            ++numSpaces;
        }
    }

    // check input. make sure there is enough free space at the end
    if( (strlen(str) - len) < (numSpaces * 2) )
    {
        throw std::invalid_argument("Not enough spaces provided in URLify");
    }

    // set end of string to null
    str[len+(numSpaces*2)] = '\0';

    // traverse the string backwords
    int counter = 0;
    for(int i = (len-1); i >= 0; --i)
    {
        int shift = numSpaces * 2;

        // if there are no more spaces then we don't need to shift anymore
        if(numSpaces == 0)
        {
            break;
        }

        // if the char is not a space then shift it to the right
        if (str[i] != ' ')
        {
            str[i+shift] = str[i];
        }
        // if it is a space, shift to the right but replace ' ' with '%20'
        else 
        {
            str[i+shift] = '0';
            str[i+shift-1] = '2';
            str[i+shift-2] = '%';
            --numSpaces;
        }
    }
}