#include "mergeSort.h"
#include <iostream>
using namespace std;

void testMergeSort(int* arr, int start, int end);
void printList(int* arr, int size);
void randomGenerateList(int* arr, int size);


const int listSize = 100;
int arr[listSize];

int main()
{
    randomGenerateList(arr,listSize);
    testMergeSort(arr,0,listSize-1);

    printList(arr,listSize);

    return 0;
}

void testMergeSort(int* arr, int start, int end)
{
    mergeSort(arr, start, end);
}

void randomGenerateList(int* arr, int size)
{
    srand(static_cast<unsigned int>(time(0)));
    for(int i = 0; i < size; ++i)
    {
        int randomNumber = rand() % 100;
        arr[i] = randomNumber;
    }
}

void printList(int* arr, int size)
{
    for(int i = 0; i < listSize; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}