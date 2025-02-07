#ifndef STRING_BUILDER
#define STRING_BUILDER

#include <string>
#include <vector>
#include "stringBuilder.h"

namespace CustomStructs {

class StringBuilder 
{
public:
    StringBuilder(const std::string &str);
    ~StringBuilder() {_arr = std::vector<char>();}

    std::string toString();
    void clear() { _arr.clear(); }
    std::size_t size() { return _arr.size(); }

private:
    std::vector<char> _arr; 
};


} // namespace MyDataStructures

#endif // STRING_BUILDER