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

// Q2
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

// Q7
void fillMatrix(int** matrix)
{
    srand(time(NULL));
    for (int i = 0; i < rows; i++)
    {
        *(matrix+i) = new int[cols];
        for (int j = 0; j < cols; j++)
        {
            *(*(matrix+i)+j) = rand() % 10;
        }
    }
}

// Q8
void fillMatrix(int matrix[rows*cols])
{
    srand(time(NULL));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i*cols + j] = rand() % 10;
        }
    }
}

// Q3
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

// Q7
void PrintMatrix(int** matrix)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << *(*(matrix+i)+j) << " ";
        }
        std::cout << std::endl;
    }
}

// Q8
void PrintMatrix(int matrix[rows*cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << matrix[i*cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

// Q4
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

// Q7
void transposeMatrix(int** matrix)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = i; j < cols; j++)
        {
            int tmp = *(*(matrix+i)+j);
            *(*(matrix+i)+j) = *(*(matrix+j)+i);
            *(*(matrix+j)+i) = tmp;
        }
    }
}

// Q5
int** multiplyMatrices(int matrix1[rows][cols], int matrix2[rows][cols])
{
    int** matrix3 = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix3[i] = new int[cols];
        for (int j = 0; j < cols; j++)
        {
            int sum = 0;
            for (int k = 0; k < cols; k++)
            {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            matrix3[i][j] = sum;
        }
    }
    return matrix3;
}

int main(int argc, char** argv)
{
    int* matrix = new int[rows*cols];
    fillMatrix(matrix);
    PrintMatrix(matrix);
    return EXIT_SUCCESS;
}
