/* Problem:
 *   Given a string, write a function to check if it is a permutation of a
 *   palindrome. A palindrom is a word or phrase that is the same forwards and
 *   backwords. A permutation is a rearrangement of letters. The palindrome 
 *   does not need to be limited to just dictionary words. You can ignore
 *   casing and non-letter characters
 * 
 * Example:
 *   Input: Tact Coa
 *   Output: True (permutations: "taco cat", "atco cta", etc.)
 *
 * Hints:
 *   every char frequency in a palindrome is (n % 2 = 0) except maybe 1  
 * 
 * Big O:
 *   O(n)
 * 
 * Source:
 *   Cracking the Coding Interview by Gayle Laackman McDowell
 *     Question: 1.4
*/
#include <cstring>
#include <cctype>
#include <stdexcept>

bool isPalinPerm(const char* str)
{
    int freq[26] = {0};
    int len = strlen(str);

    // get the frequency of each char (assume all lowercase)
    for(int i = 0; i < len; ++i)
    {
        // check for alphabetic input
        if(!isalpha(str[i]))
        {
            throw std::invalid_argument("Only alphabetic chars are allowed");
        }

        int index = tolower(str[i]) - 97;
        ++freq[index];
    }

    // Check how many characters have odd frequencies
    short numUneven = 0;
    for(int i = 0; i < 26; ++i)
    {
        if( (freq[i] % 2) !=  0)
        {
            ++numUneven;
        }

        // If more than one character has an odd count, it's not a palindrome
        // permutation
        if(numUneven > 1)
        {
            return false;
        }
    }
    return true;
}