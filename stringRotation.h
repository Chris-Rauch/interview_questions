/* Problem:
 *   Assume you have a method isSubstring which checls if one word is a 
 *   substring of another. Given two strings, s1 and s2, write code to check 
 *   if s2 is a rotation of s1 using only one call to isSubstring.
 * 
 * Ex.
 *   "waterbottle" is a rotation of "erbottlewat"
 * 
 * Hint:
 *   Step 1 is to concatenate two strings...
 * 
 * Solution:
 *   I implemented my own isSubtring method which is a brute force check 
 *   yielding O(n^2) time complexity. To improve efficiency, implement a substr
 *   method that uses KMP, Rabin-Karp or Boyer-Moore algorithms. 
 * 
 * Source:
 *   Cracking the Coding Interview by Gayle Laackman McDowell
 *     Question: 1.9
*/

#include <iostream>
#include <cstring>

bool isSubstring(const char* s1, const char* s2);
void rotateString(char* str, const int& shift);

/// @brief Concatenates s1 to s1 yielding a third string, s3. Then checks if s2
///   is a substring of s3. If s1 and s2 are rotations of the other, then the 
///   substring method will return true. Making this functions time complexity
///   limited to the efficiency of the substring method. My brute force 
///   implementaion of isSubstring is O(n^2) time. O(2n) space because of the
///   concatenation of the two strings.
/// @param s1 C-String 
/// @param s2 C-String
/// @return true if s1 and s2 are rotations of the other
bool isRotation(const char* s1, const char* s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if(len1 != len2) return false;

    char* s3 = new char[2*len1+1];

    // concatenate s1 to s1
    strcpy(s3, s1);
    strcat(s3, s1);

    // if s2 is a substring of the concatenated string, then it is a rotation
    bool result = isSubstring(s3, s2);

    // clean up
    delete[] s3;

    return result;
}

/// @brief Brute force method in place. Searches all possible substrings making
///   it O(n^2) time and O(1) space.
/// @param s1 C-String
/// @param s2 C-String
/// @return true if s1 and s2 are rotations of the other
bool isRotationBruteForceV2(const char* s1, const char* s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if(len1 != len2) return false;

    for(int i = 0; i < len1; ++i)
    {
        int j;
        for(j = 0; j < len1; ++j)
        {
            //int index = (j + len1) % len1;
            int otherIndex = (i + j + len1) % len1;
            if(s2[j] != s1[otherIndex])
            {
                break;
            }
        }

        if(j == len1)
        {
            return true;
        }
    }
    return false;
}

/// @brief Worst method. My for loop is O(n), rotateString is O(n), and strcmp
///   is O(n) yielding O(n^2n) or O(n^2) time complexity for the whole function
/// @param s1 C-String
/// @param s2 C-String
/// @return true if s1 and s2 are rotations of the other
bool isRotationBruteForce(const char* s1, const char* s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if(len1 != len2) return false;

    // create a temp variable
    char* temp = new char[len1+1];
    strcpy(temp, s2);
    temp[len1] = '\0';

    // try a brute force check
    for(int i = 0; i < len1; ++i)
    {
        // rotate the string and then compare
        rotateString(temp, i);
        if(strcmp(s1,temp) == 0)
        {
            return true;
        }
    }
    return false;
}

/// @brief Checks to see if s2 is a substring of s1
/// @param s1 C-String that is the main string
/// @param s2 C-String that is the (potential) substring
/// @return true if s2 is a substring of s1
bool isSubstring(const char* s1, const char* s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if(len1 < len2) return false;

    for(int i = 0; i <= len1 - len2; ++i)
    {
        int j;
        for(j = 0; j < len2; ++j)
        {
            //std::cout << s1[i+j] << ':' << s2[j] << std::endl;
            if(s1[i+j] != s2[j])
            {
                break;
            }
        }
        if(j == len2)
        {
            return true;
        }
    }
    return false;
}

void rotateString(char* str, const int& shift)
{
    int size = strlen(str);
    char* otherStr = new char[size + 1];

    for(int i = 0; i < size; ++i)
    {
        otherStr[(i+shift+size) % size] = str[i];
    }
    otherStr[size] = '\0';

    // copy it over
    strcpy(str, otherStr);

    // clean up
    delete[] otherStr;
}