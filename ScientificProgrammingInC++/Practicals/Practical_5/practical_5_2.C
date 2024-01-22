#include <iostream>

int** allocateMatrix(int N)
{
    int* mainBlock = new int[N * N];
    int** ptrsToRows = new int*[N];

    for (int i = 0; i < N; i++)
    {
        ptrsToRows[i] = mainBlock + i*N;
    }
}

void freeMatrix(int** matrix)
{
    delete[] matrix[0];
    delete[] matrix;
}

int main()
{
    int** matrix = allocateMatrix(3);

    int m22 = matrix[2][2];

    return 0;
}

int trace(int** matrix, int N)
{
    int t = 0;
    for(int i = 0; i < N; i++)
    {
        t += matrix[i][i];
    }

    return t;
}




