/* Problem:
 *   Implement an algorithm to determine if a string has all unique characters.
 *   What if you cannot use additional data structures?
 * 
 * Solution:
 *   Use a boolean array. As you traverse the string, use the array to keep 
 *   track of char's that have already been seen
 * 
 * Big O:
 *   O(n)
 * 
 * Source:
 *   Cracking the Coding Interview by Gayle Laackman McDowell
 *     Question: 1.1
*/
#include <iostream>
#include <string>

/// @brief Checks if all characters in a given C-string are unique, considering
///   printable ASCII characters.
/// @param str - C-string (null-terminated) that contains characters in the 
///   printable ASCII range (32...126).
/// @return true if all characters are unique, false if any character appears
///   more than once.

bool isUnique(const char* str)
{
    // ranges from ASCII values 32...126
    // 94 is the range of printable ASCII characters
    bool found[94] = {false};

    // traverse c-string
    for(std::size_t i = 0; str[i] != '\0'; ++i)
    {
        // convert to ASCII
        unsigned char currentChar = static_cast<unsigned char>(str[i]);

        // check if char has been seen before
        if(found[currentChar - 32])
        {
            return false;
        }

        // if not found, mark it as as found
        found[currentChar - 32] = true;
        
    }
    return true;
}