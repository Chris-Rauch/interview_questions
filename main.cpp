#include <iostream>
#include <string>
using namespace std;

#include "isUnique.h"
#include "checkPermutations.h"
#include "URLify.h"
#include "palindromePermutation.h"
#include "levenshtein.h"
#include "strCompression.h"

int main()
{
    string str = "aabcccccaaa";
    string otherStr = compressStringV2(str);

    cout << "Other String: " << otherStr << endl;

    return 0;
}
