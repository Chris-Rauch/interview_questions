/* Problem:
 *   Given two strings, write a method to decide if one is a permutation
 *   of the other.
 *  
 * Solution:
 *   Find the frequency of each character in the two strings. Frequency of each
 *   char should exactly match. We can add a freq when a char is detected in 
 *   str1 and subtract a freq when a char is detected in str2. If the two str's
 *   are permutations, then the freq[] should be all 0's.
 *   Throw an error if non-printable ascii char is detected
 *   
 * Big O:
 *   O(n)
 * 
 * Source:
 *   Cracking the Coding Interview by Gayle Laackman McDowell
 *     Question: 1.2
 */
#include <cstring>
#include <stdexcept>

bool checkPermutations(const char* str1, const char* str2)
{
    // 94 print-able ASCII characters 32...126
    unsigned short freq[94] = {0};

    // find length of each string
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    // if lengths are not equal, return false
    if(len1 != len2)
    {
        return false;
    }

    // loop through each string and count the freq of each char
    for(size_t i = 0; i < len1; ++i)
    {
        // if the string contains a non printable char, throw an error
        if(str1[i] < 32 || str2[i] < 32 || str1[i] > 126 || str2[i] > 126)
        {
            throw std::invalid_argument("Non-printable ASCII char detected");
        }
        unsigned char index1 = static_cast<unsigned char>(str1[i] - 32);
        unsigned char index2 = static_cast<unsigned char>(str2[i] - 32);
        freq[index1]++;
        freq[index2]--;
    }

    // if str1 and str2 are permutations, then freq[] should be all 0's
    for(unsigned short i = 0; i < 94; ++i)
    {
        if(freq[i] != 0)
        {
            return false;
        }
    }

    return true;
}