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

int main()
{
    /* int** 3x3
    int len = 3;
    int dist = 4;
    int* matrix[3] = {nullptr};
    for(int i = 0; i < len; ++i)
    {
        matrix[i] = new int[len];
    }  
    for(int i = 0; i < len; ++i)
    {
        for(int j = 0; j < len; ++j)
        {
            matrix[i][j] = ((i*len) + j);
        }
    }
    */
    vector<vector<int>> matrix(3,vector<int>(4));
    for(int i = 0; i < matrix.size(); ++i)
    {
        for(int j = 0; j < matrix.front().size(); ++j)
        {
            matrix[i][j] = ((i*4) + j);
        }
    }
    cout << "Initial matrix\n";
    printMatrix(matrix);
    rotateMatrixInPlace(matrix);
    cout << "After Rotate\n";
    printMatrix(matrix);


    return 0;
}
