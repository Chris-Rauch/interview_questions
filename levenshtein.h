/* Problem:
 *   There are three types of edits that can be performed on strings: insert,
 *   remove, and replace.Given two strings, write a function to check if they
 *   are one edit (or zero edits) away
 *
 * Example:
 *   pale, ple -> true
 *   pales, pale -> true
 *   pale, bale -> true
 *   pale, bake -> false
 * 
 * Solution:
 *   Levenshtein's Algorithm. Used to compute how many edits it would take to
 *   get from str1 to str2.
 *   This solution is going to be a modified form of this algorithm since we 
 *   can as soon as we know is is more than 1 edit away.
 * 
 * Big O:
 *   O(n^2)
 * 
 * Source:
 *   Cracking the Coding Interview by Gayle Laackman McDowell
 *     Question: 1.5
*/
#include <iostream>
#include <cstring>

#define MIN(x,y) ((x>y) ? y:x)

// function declarations
std::size_t levenshteinDist(const char* str1, const char* str2);
bool oneAway(const char* str1, const char* str2);
void printArr(std::size_t** arr, const char* str1, const char* str2);

/// @brief Levenshtein's algorithm, also known as the Levenshtein distance,
///   is a dynamic programming algorithm used to measure the difference between
///   two strings. It calculates the minimum number of single-character edits
///   required to change one string into another.
/// @param str1 C-String
/// @param str2 C-String
/// @return The number of edits it would require to change str1 into str2
std::size_t levenshteinDist(const char* str1, const char* str2)
{
    std::size_t columns = strlen(str1)+1;
    std::size_t rows = strlen(str2)+1;
    std::size_t dist;

    // allocate memory for the 2D array
    std::size_t** dp = new std::size_t*[rows]; 
    for(std::size_t i = 0; i < rows; ++i)
    {
        dp[i] = new std::size_t[columns];
    }

    // initialize array
    for(std::size_t i = 0; i < rows; ++i)
    {
        for(std::size_t j = 0; j < columns; ++j)
        {
            if(i == 0)
            {
                dp[0][j] = j;
            }
            else if(j == 0)
            {
                dp[i][0] = i; 
            }
            else
            {
                // check if the chars are similar
                if(str1[j-1] == str2[i-1])
                {
                    dp[i][j] = dp[i-1][j-1]; // no cost, assign it to it's diagonal
                }
                else
                {
                    // cost function
                    dp[i][j] = 1 + MIN(dp[i-1][j],               // deletion
                                          MIN(dp[i][j-1],        // insertion
                                                 dp[i-1][j-1])); // substitution
                }
            }
        }
    }
    dist = dp[rows-1][columns-1];

    //printArr(dp, str1,str2);

    // release dp from memory
    for(std::size_t i = 0; i < rows; ++i)
    {
        delete[] dp[i];
    }
    delete[] dp;

    return dist;
}

/// @brief Using levenstein's distance algorithm, find the number of edits to
///   to get from str1 to str2. If the distance is 1 or 0, return true. If it's
///   greater than 1, return false
/// @param str1 C-String to be compared
/// @param str2 C-String to be compared
/// @return true if distance is less than or equal to one. Otherwise, false
bool oneAway(const char* str1, const char* str2)
{
    std::size_t distance = levenshteinDist(str1,str2);
    return (distance <= 1 ? true : false);
}

// used for testing. Prints the array used in levensteins alg. Breaks after
// double digit columns/rows
void printArr(std::size_t** arr, const char* str1, const char* str2)
{
    std::size_t columns = strlen(str1)+1;
    std::size_t rows = strlen(str2)+1;

    bool printStr1 = true;

    for(std::size_t i = 0; i < rows; ++i)
    {
        if(printStr1 == true)
        {
            for(std::size_t x = 0; x < columns; ++x)
            {
                if(x == 0)
                {
                    std::cout << "    ";
                }
                else
                {
                    std::cout << str1[x-1] << ' ';
                }
            }
            std::cout << std::endl;
            printStr1 = false;
        }


        for(std::size_t j = 0; j < columns; ++j)
        {
            if(i == 0 && j == 0)
            {
                std::cout << "  ";
            }
            else if(j == 0)
            {
                std::cout << str2[i-1] << ' ';
            }
            std::cout << arr[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}