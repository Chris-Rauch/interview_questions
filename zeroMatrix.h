/* Problem:
 *   Write an algorithm such that iif an element in an M x N matrix is 0, its
 *   entire row and column are set to zero.
 * 
 * Source:
 *   Cracking the Coding Interview by Gayle Laackman McDowell
 *     Question: 1.8
*/

#include <vector>

void zeroRow(std::vector<std::vector<int>>& matrix, const int& row);
void zeroColumn(std::vector<std::vector<int>>& matrix, const int& column);


void zeroMatrix(std::vector<std::vector<int>>& matrix)
{
    // check for size == 0
    if(matrix.size() < 1) return;

    // loop thorugh the matrix and find all occurences of 0
    int rows = matrix.size();
    int columns = matrix.front().size();
    std::vector<std::pair<int,int>> zeroList;
    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < columns; ++j)
        {
            if(matrix[i][j] == 0)
            {
                zeroList.push_back(std::pair<int,int>(i,j));
            }
        }
    }

    // once found, zero out the applicable rows and columns
    std::vector<std::pair<int,int>>::const_iterator it;
    for(it = zeroList.cbegin(); it != zeroList.cend(); ++it)
    {
        int row = it->first;
        int col = it->second;
        zeroColumn(matrix, col);
        zeroRow(matrix, row);
    }

}

void zeroRow(std::vector<std::vector<int>>& matrix, const int& row)
{
    int columns = matrix.front().size();
    for(int i = 0; i < columns; ++i)
    {
        matrix[row][i] = 0;
    }
}

void zeroColumn(std::vector<std::vector<int>>& matrix, const int& column)
{
    int rows = matrix.size();
    for(int i = 0; i < rows; ++i)
    {
        matrix[i][column] = 0;
    }

}