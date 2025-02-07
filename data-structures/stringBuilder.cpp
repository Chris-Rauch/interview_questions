#include <iostream>
#include "stringBuilder.h"

using namespace CustomStructs;

/// @brief Constructs a mutable char array from the given string
/// @param str The contents of the array
StringBuilder::StringBuilder(const std::string &str) 
{
    std::string::const_iterator it;
    for(it = str.begin(); it != str.end(); ++it)
    {
        _arr.push_back(*it);
    }
}


std::string StringBuilder::toString()
{
    return std::string(&_arr[0]); // does this work??
}


