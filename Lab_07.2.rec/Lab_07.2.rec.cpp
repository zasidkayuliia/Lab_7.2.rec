#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

void CreateRow(int** a, const int rowNo, const int cols, const int Low, const int High, int colNo);
void CreateRows(int** a, const int rows, const int cols, const int Low, const int High, int rowNo);
void PrintRow(int** a, const int rowNo, const int cols, int colNo);
void PrintRows(int** a, const int rows, const int cols, int rowNo);
void FindMaxInColumn(int** a, const int rows, int colNo, int& maxElement, int rowNo);
int SumMaxOddColumns(int** a, const int rows, const int cols, int colNo);

int main()
{
    srand((unsigned)time(NULL));
    int Low = 1;
    int High = 100;
    int rows, cols;

    cout << "k: ";
    cin >> rows;
    cout << "n: ";
    cin >> cols;

    int** a = new int* [rows];
    for (int i = 0; i < rows; i++)
        a[i] = new int[cols];

    CreateRows(a, rows, cols, Low, High, 0);
    PrintRows(a, rows, cols, 0);

    int sum = SumMaxOddColumns(a, rows, cols, 1);
    cout << "Сума максимальних елементів по непарних стовпцях матриці = " << sum << endl;

    for (int i = 0; i < rows; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void CreateRow(int** a, const int rowNo, const int cols, const int Low, const int High, int colNo)
{
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < cols - 1)
        CreateRow(a, rowNo, cols, Low, High, colNo + 1);
}

void CreateRows(int** a, const int rows, const int cols, const int Low, const int High, int rowNo)
{
    CreateRow(a, rowNo, cols, Low, High, 0);
    if (rowNo < rows - 1)
        CreateRows(a, rows, cols, Low, High, rowNo + 1);
}

void PrintRow(int** a, const int rowNo, const int cols, int colNo)
{
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < cols - 1)
        PrintRow(a, rowNo, cols, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int rows, const int cols, int rowNo)
{
    PrintRow(a, rowNo, cols, 0);
    if (rowNo < rows - 1)
        PrintRows(a, rows, cols, rowNo + 1);
    else
        cout << endl;
}

void FindMaxInColumn(int** a, const int rows, int colNo, int& maxElement, int rowNo)
{
    if (a[rowNo][colNo] > maxElement)
        maxElement = a[rowNo][colNo];
    if (rowNo < rows - 1)
        FindMaxInColumn(a, rows, colNo, maxElement, rowNo + 1);
}

int SumMaxOddColumns(int** a, const int rows, const int cols, int colNo)
{
    if (colNo >= cols)
        return 0;

    int maxElement = a[0][colNo];
    FindMaxInColumn(a, rows, colNo, maxElement, 1);

    return maxElement + SumMaxOddColumns(a, rows, cols, colNo + 2);
}