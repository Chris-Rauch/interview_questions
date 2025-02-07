#ifndef PAIR_H
#define PAIR_H

namespace CustomStructs {

template <typename T1, typename T2>
struct pair {
    // cosntructor
    pair(const T1 &first, const T2 &second) : first(first), second(second) {}

    // overload 
    bool operator==(const pair<T1,T2>& rVal) const;
    friend std::ostream& operator<<(std::ostream& os, const pair<T1,T2>& p) 
    {
        os << "{" << p.first << ":" << p.second << "}";
        return os;
    }
    
    T1 first;
    T2 second;
};

template <typename T1, typename T2>
bool pair<T1,T2>::operator==(const pair<T1,T2>& rVal) const 
{
    return first == rVal.first && second == rVal.second;
}

}

#endif // PAIR_H