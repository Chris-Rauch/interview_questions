/* MergeSort 
 *
*/
#include <iostream>
void mergeSort(int* arr, const int& left, const int& right);
void merge(int* arr1, const int& left, const int& mid, const int& right);

void mergeSort(int* arr, const int& left, const int& right)
{
    if(arr == nullptr || left >= right) return;

    int mid = left + ((right - left) / 2);

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void merge(int* arr, const int& left, const int& mid, const int& right)
{
    // create temp variable
    int size1 = mid-left+1;
    int size2 = right-mid;
    int* t1 = new int[size1];
    int* t2 = new int[size2];

    // copy data over into temp vars
    int arrIndex = left;
    for(int i = 0; i < size1; ++i)
    {
        t1[i] = arr[arrIndex];
        ++arrIndex;
    }
    for(int i = 0; i < (right - mid); ++i)
    {
        t2[i] = arr[arrIndex];
        ++arrIndex;
    }

    // traverse the two temp arrays, comparing their values and then merge back
    // into arr
    int i = 0, j = 0, k = left;
    while(i < size1 && j < size2)
    {
        if(t1[i] < t2[j])
        {
            arr[k] = t1[i];
            ++i;
        }
        else
        {
            arr[k] = t2[j];
            ++j;
        }
        ++k;
    }

    // copy over remaining elems, if any
    while(i < size1)
    {
        arr[k] = t1[i];
        ++k;
        ++i;
    }
    while(j < size2)
    {
        arr[k] = t2[j];
        ++k;
        ++j;
    }

    delete[] t1;
    delete[] t2;
}