#include <iostream>
#include <cstdlib>

/**
 * Question 1
 * Yes. Sort of. Using the basic array[] operator without "new" will limit to the
 * scope to the function, but dynamically allocating blocks of memory allows us
 * to return a pointer to the first element which acts like an array. It must be
 * deallocated at some point to avoid memory leaks.
 */

const int rows = 5;
const int cols = 5;

void fillMatrix(int matrix[rows][cols])
{
    srand(time(NULL));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = rand() % 10;
        }
    }
}

void PrintMatrix(int matrix[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void transposeMatrix(int matrix[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = i; j < cols; j++)
        {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
    }
}

int* multiplyMatrices(int matrix1[rows][cols], int matrix2[rows][cols])
{
    int matrix3[rows][cols];
    for (int i = 0; i < rows; i++)
    {
        for (int j = i; j < cols; j++)
        {
            matrix3[i][j] = matrix1[i][j] * matrix2[j][i];
        }
    }
}

int main(int argc, char** argv)
{
    int matrix[rows][cols];
    fillMatrix(matrix);
    PrintMatrix(matrix);
    transposeMatrix(matrix);
    PrintMatrix(matrix);
    return EXIT_SUCCESS;
}
