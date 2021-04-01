#include "Sort.h"

#include <assert.h>


void bubbleSort(int* array, int len)
{
	if (len <= 1) return;

	for (int i = 0; i < len; ++i)
	{
		bool bFlag = false;
		for (int j = 0; j < len - i - 1; ++j)
		{
			if (array[j] > array[j + 1])
			{
				int tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
				bFlag = true;
			}
		}

		if (!bFlag) break;
	}
}

void insertSort(int* array, int len)
{
	assert(array != nullptr);
	if (len <= 1) return;

	for (int i = 0; i < len; ++i)
	{
		int value = array[i];
		int j = i - 1;  //在已排序区间从尾到头,查找插入位置
		for (; j >= 0; --j)
		{
			if (array[j] > value){
				array[j + 1] = array[j];  //移动元素
			}
			else {
				break;
			}
		}

		array[j + 1] = value;
	}
}

void merge(vector<int>& array, int left, int rigth)
{
	int mid = (left + rigth) / 2;
	int i = left; int j = mid + 1; int k = 0;
	vector<int> tmp(rigth - left +1);
	while (i <= mid && j <= rigth)
	{
		if (array[i] <= array[j]){
			tmp[k++] = array[i++];
		}
		else{
			tmp[k++] = array[j++];
		}
	}

	while (i <= mid)
	{
		tmp[k++] = array[i++];
	}

	while (j <= rigth)
	{
		tmp[k++] = array[j++];
	}

	i = left, k = 0;
	while (i <= rigth)
	{
		array[i++] = tmp[k++];
	}
}

void merge_sort(vector<int>& array, int left, int rigth)
{
	if (left >= rigth || array.empty()) return;

	int mid = (left + rigth) / 2;
	merge_sort(array, left, mid);
	merge_sort(array, mid + 1, rigth);
	merge(array, left, rigth);
}