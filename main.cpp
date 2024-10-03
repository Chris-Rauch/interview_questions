#include <iostream>
#include <string>
using namespace std;

#include "isUnique.h"
#include "checkPermutations.h"
#include "URLify.h"
#include "palindromePermutation.h"
#include "levenshtein.h"
#include "strCompression.h"
#include "rotateMatrix.h"
#include "zeroMatrix.h"
#include "stringRotation.h"

int main()
{
    const char* s1 = "waterbottle";
    const char* s2 = "erbottlewat";

    bool isTrue = isRotationBruteForceV2(s1,s2);

    if(isTrue){
        cout << "true" << endl;
    }
    else cout << "false" << endl;


    return 0;
}
