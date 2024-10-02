/* Problem:
 *   Given an image represented by an M x N matrix, where each pixel in the 
 *   image is represented by an integer, write a method to rotate the image by
 *   90 degrees. Can you do this in place? (In place means without allocating
 *   more memory)
 * 
 * Ex:
 *   Input
 *       1 2 3
 *       4 5 6
 *       7 8 9
 *   Output
 *       7 4 1
 *       8 5 2
 *       9 6 3
 * Solution:
 *   - 90 degree (clockwise) rotation
 *       1) Transpose the matrix
 *       2) Reverse the rows
 *   - 90 degrees (counter-clockwise) rotation
 *       1) tranpose the matrix
 *       2) reverse the columns
 *   - 180 degrees
 *       1) transpose the matrix
 *       2) reverse the rows
 *       3) transpose the matrix
 * 
 *   In order to rotate a matrix in place, it must be a square (for data
 *   structures using contiguous memory allocation). To achieve this, use a 
 *   swap function. And if you want to be badass, use a swap function that
 *   doesn't allocate a temp variable (arithmitic only)
 *   There is a kind-of in place method that would transpose a square subset 
 *   of the matrix in place. Then copy over the extra columns or rows 
 * 
 * Big O:
 *   O(n^2)
 */
#include <iostream>
#include <vector>
#include <algorithm>
void swap(int& x, int& y);
void printMatrix(int** matrix, const int& len);
void printMatrix( const std::vector<std::vector<int>>& matrix);


/// @brief Rotate matrix 90 degrees. If matrix is an int** then it must be a 
///   square matrix where len is the number of rows and columns. This rotates
///   the matrix in place
/// @param matrix pointer to an array of int pointers
/// @param len number of rows and columns
void rotateMatrix(int** matrix, const int& len)
{
    if(len <= 1) return;

    // transpose the matrix
    // total number of swap is going to equal (n)(n-1) / 2
    for(int i = 0; i < len; ++i)
    {
        for(int j = i+1; j < len; ++j)
        {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    // reverse each row
    for(int i = 0; i < len; ++i)
    {
        for(int j = 0; j < (len/2); ++j)
        {
            swap(matrix[i][j], matrix[i][(len-1) - j]);
        }
    }

}

/// @brief Rotates the matrix 90 degrees. This is not in palce. A matrix of 
///   equal size is created, copied over and then reassigned to the input var
/// @param matrix matrix represented with vectors. Upon completion, will have
///   rotated 90 degrees
void rotateMatrix(std::vector<std::vector<int>>& matrix)
{
    int rows = matrix.size();
    int columns = matrix.front().size();
    std::vector<std::vector<int>> transposeMatrix(columns, std::vector<int>(rows));

    // transpose matrix
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < columns; ++j)
        {
            //std::cout << '(' << i << ',' << j << ')' << std::endl;
            transposeMatrix[j][i] = matrix[i][j];
        }
    }

    // reverse the columns
    for(int i = 0; i < columns; ++i)
    {
        for(int j = 0; j < rows/2; ++j)
        {
            swap(transposeMatrix[i][j], transposeMatrix[i][(rows-1)-j]);
        }
    }

    // avoid making a deep copy and just change the pointers
    matrix = std::move(transposeMatrix);
}


/// @brief In order to rotate the matrix in place, this swap function will not
///   allocate a temp variable. Rather, use arithmitic to swap the values
/// @param ptr1 
/// @param ptr2 
void swap(int& ptr1, int& ptr2)
{
    ptr1 = ptr1 + ptr2;
    ptr2 = ptr1 - ptr2;
    ptr1 = ptr1 - ptr2;
}

void printMatrix(int** matrix, const int& len)
{
    for(int i = 0; i < len; ++i)
    {
        for(int j = 0; j < len; ++j)
        {
            std::cout << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void printMatrix(const std::vector<std::vector<int>>& matrix)
{
    std::vector<std::vector<int>>::const_iterator it;
    for(it = matrix.cbegin(); it != matrix.cend(); ++it)
    {
        std::vector<int>::const_iterator v_it;
        for(v_it = it->cbegin(); v_it != it->cend(); ++v_it)
        {
            std::cout << *v_it << "    ";
        }
        std::cout << std::endl;
    }
}