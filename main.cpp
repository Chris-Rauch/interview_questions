#include <iostream>
using namespace std;

#include "isUnique.h"
#include "checkPermutations.h"
#include "URLify.h"
#include "palindromePermutation.h"
#include "levenshtein.h"

int main()
{
    const char* str1 = "kitten";
    const char* str2 = "sitting";
    levenshteinDist(str1,str2);

    return 0;
}
