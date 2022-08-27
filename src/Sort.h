#pragma once

#include <vector>
#include <iostream>

using std::vector;
using std::cout;

void bubbleSort(int* array, int len);

void insertSort(int* array, int len);

void merge_sort(vector<int>& array, int left, int rigth);

void merger_sortV2(int* array, int left, int right);

void quickSort(vector<int>& array, int left, int right);

void f(const char* s);

int binarySearch(const vector<int>& array, int key);

int findFirstEqual(const vector<int>& array, int key);

int findLastEqual(const vector<int>& array, int key);

int findFirstGreaterThan(const vector<int>& array, int key);

int findLastLessThan(const vector<int>& array, int key);

class QuickSortSolution 
{
private:
    int res = -1;
    int pos;

public:

    int findKthLargest(vector<int>& array, int k)
    {
        int length = array.size();
        pos = length - k;
        quickSort(array, 0, length - 1);

        return res;
    }

    void clear()
    {
        res = -1;
    }

    void quickSort(vector<int>& array, int left, int right)
    {
        if (left >= right || array.empty())
            return;

        int mid = partition(array, left, right);
        if (pos == mid)
        {
            res = array[mid];
        }
        else if (pos > mid)
        {
            quickSort(array, mid + 1, right);
        }
        else
        {
            quickSort(array, left, mid - 1);
        }
    }

    int partition(vector<int>& array, int left, int right)
    {
        int pivot = array[right];

        int i = left;
        for (int j = left; j < right; ++j)
        {
            if (array[j] < pivot)
            {
                int tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
                i++;
            }
        }

        int tmp = array[i];
        array[i] = array[right];
        array[right] = tmp;

        return i;
    }


};