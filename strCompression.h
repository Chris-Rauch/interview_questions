/* Problem:
 *   Implement a method to perform basic string compression using the counts of
 *   repeated characters. For example, the string "aabcccccaaa" would become 
 *   a2b1c5a3. If the compressed string would not become smaller than the 
 *   original string, your method should return the original string. You can
 *   assume the string only has upper and lowercase letters.
 *
 * Solution:
 *   Loop through the given string and look to the char in front of the current
 *   one. If they're different, append the char and charCount as a string. If
 *   they are the same, increment charCount. 
 *
 * Big O:
 *   O(n)
 * 
 * Source: 
 *   Cracking the Coding Interview by Gayle Laackman McDowell
 *     Question: 1.6
 */
#include <string>
#include <iostream>

std::string compressStringV2(const std::string& str)
{
    int length = str.length();
    int charCount = 1;
    std::string compressedStr = "";

    if(length == 0) 
    {
        return str;
    }

    for(int i = 0; i < length; ++i)
    {
        // if at end of string opr next char is different
        if((i+1==length) || (str[i] != str[i+1]))
        {
            std::string number = std::to_string(charCount);
            compressedStr.push_back(str[i]);
            compressedStr.append(number);
            charCount = 1;
        }
        else
        {
            ++charCount;
        }
    }

    if(compressedStr.length() >= str.length())
    {
        return str;
    }

    return compressedStr;
}

std::string compressString(const std::string& str)
{
    char lastChar = '\0';
    int count = 1;
    std::string returnStr = "";

    for(std::string::const_iterator it = str.cbegin(); it != str.cend(); ++it)
    {
        if(it == str.cbegin())
        {
            returnStr.push_back(*it);
            lastChar = (*it);
        }
        else if(it == (str.cend() - 1))
        {
            if(lastChar == (*it))
            {
                ++count;
            }
            std::string num = std::to_string(count);
            returnStr.append(num);
        }
        else if(lastChar == (*it))
        {
            ++count;
        }
        else
        {
            std::string num = std::to_string(count);
            returnStr.append(num);
            returnStr.push_back(*it);
            count = 1; // reset count
            lastChar = (*it);
        }
    }

    if(returnStr.length() >= str.length())
    {
        return str;
    }

    return returnStr;
}