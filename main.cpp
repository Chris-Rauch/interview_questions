#include <iostream>
using namespace std;

#include "isUnique.h"
#include "checkPermutations.h"
#include "URLify.h"
#include "palindromePermutation.h"

int main()
{
    const char* str = "tact coa";
    if(isPalinPerm(str)) 
    {
        cout << "true\n";
    }

    return 0;
}
