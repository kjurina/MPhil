#include <iostream>
#include <vector>


void calcNextRow(const int* prevRow, int* nextRow, int rowNo);

int main()
{
    int N;
    std::cout << "Please enter a number of rows you want in a Pascal triangle";
    std::cin >> N;
    //std::cout << std::endl;

    int* row1 = new int[N];
    int* row2 = new int[N];

    for(int i=1 ; i < N+1 ; i++)
    {
        calcNextRow(row1, row2, i);

        for(int j=0 ; j < i ; j++)
        {
            std::cout << row2[j] << " ";
        }

        std::cout << std::endl;

        int* tmp = row1;
        row1 = row2;
        row2 = tmp;
    }

    delete[] row1;
    delete[] row2;

    return 0;
}



void calcNextRow(const int* prevRow, int* nextRow, int rowNo)
{
    // First element in the row
    nextRow[0] = 1;

    for(int i = 1; i < rowNo-1; i++)
    {
        nextRow[i] = prevRow[i] + prevRow[i - 1];
    }
    nextRow[rowNo-1] = 1;

}


