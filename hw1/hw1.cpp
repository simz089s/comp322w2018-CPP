#include <iostream>
#include <cstdlib>

// using namespace std;

/**
 * Question 1
 * Yes. Sort of. Using the basic array[] operator without "new" will limit to the
 * scope to the function, but dynamically allocating blocks of memory allows us
 * to return a pointer to the first element which acts like an array. It must be
 * deallocated at some point to avoid memory leaks.
 */

/**
 * Question 8
 * Yes. When we think of it, if we flatten a 2D array into a single array, then
 * an element's position can still be seen as a "row" and "column". Every row
 * have the same length. So the column stays the same, but we multiply by the
 * numbers of row before to "get to" the row and then just add the column as the
 * extra indices inside the row.
 */

const int rows = 5;
const int cols = 5;

/**
 * The fillMatrix functions will use mod 10 so they all have the same size and
 * are easy to look at and compute
 */

// Q2 With static arrays
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

// Q7 With double pointers
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

// Q8 With single array
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

// Q3 With static array
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

// Q7 With double pointers
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

// Q8 With single array
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

// Q4 With static array
void transposeMatrix(int matrix[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = i; j < cols; j++)
        {
            // Swap (transpose is like a flip with the diagonal as axis)
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
    }
}

// Q7 With double pointers
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

// Q5 With static arrays and iteration but returns double pointer (dynamically allocated)
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

// Q6 With recursion
int** multiplyMatricesRec(int matrix1[rows][cols], int matrix2[rows][cols],
                          int** matrix3, int i, int j)
{
    if (j == cols)
    {
        j = 0;
        i++;
    }
    if (i == rows) { return matrix3; }
    else
    {
        int sum = 0;
        for (int k = 0; k < cols; k++)
        {
            sum += matrix1[i][k] * matrix2[k][j];
        }
        matrix3[i][j] = sum;
        return multiplyMatricesRec(matrix1, matrix2, matrix3, i, j+1);
    }
}

int main(void)
{
    // Q2 and Q3
    int matrix0[rows][cols] = {{0,}};
    fillMatrix(matrix0);
    PrintMatrix(matrix0);
    std::cout << std::endl;

    // Q4
    transposeMatrix(matrix0);
    PrintMatrix(matrix0);
    std::cout << std::endl;

    // Q5
    int matrix1[rows][cols] = {{0,}};
    fillMatrix(matrix1);
    int** matrix0x1 = multiplyMatrices(matrix0, matrix1);
    PrintMatrix(matrix0x1);
    std::cout << std::endl;

    // Q6
    fillMatrix(matrix0x1); // Reuse this, fill it with junk to prove the following works
    // PrintMatrix(matrix0x1);
    matrix0x1 = multiplyMatricesRec(matrix0, matrix1, matrix0x1, 0, 0);
    PrintMatrix(matrix0x1);
    // Cleanup
    for (int i = 0; i < rows; delete[] matrix0x1[i], i++);
    delete[] matrix0x1;
    std::cout << std::endl;

    // Q7
    // Could've reused matrix0x1 but oh well this is cleaner
    int** matrix2 = new int*[rows];
    fillMatrix(matrix2);
    PrintMatrix(matrix2);
    transposeMatrix(matrix2);
    PrintMatrix(matrix2);
    for (int i = 0; i < rows; delete[] matrix2[i], i++);
    delete[] matrix2;
    std::cout << std::endl;

    // Q8
    int* matrix3 = new int[rows*cols];
    fillMatrix(matrix3);
    PrintMatrix(matrix3);
    delete[] matrix3;
    std::cout << std::endl;

    return EXIT_SUCCESS;
}
