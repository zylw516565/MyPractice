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

void mergeV2(int* array, int left, int right)
{
	int len = right - left;
	int mid = (left + right) / 2;
	int i = left; int j = mid + 1; int k = 0;

	int* tmp = new int[len + 1];

	while (i <= mid && j <= right)
	{
		if (array[i] <= array[j])
		{
			tmp[k++] = array[i++];
		}
		else {
			tmp[k++] = array[j++];
		}
	}

	//如果i区间还有剩余数据,则把剩余全部放入tmp数组中
	while (i <= mid)
	{
		tmp[k++] = array[i++];
	}

	//如果j区间还有剩余数据,则把剩余全部放入tmp数组中
	while (j <= right)
	{
		tmp[k++] = array[j++];
	}

	//最后把tmp中排序后的数据拷贝到源数据中
	i = left, k = 0;
	while (i <= right)
	{
		array[i++] = tmp[k++];
	}
}

void merger_sortV2(int* array, int left, int right)
{
	if (left >= right || nullptr == array) return;

	int mid = (left + right) / 2;

	merger_sortV2(array, left, mid);
	merger_sortV2(array, mid + 1, right);
	mergeV2(array, left, right);
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

	//如果i区间还有剩余数据,则把剩余全部放入tmp数组中
	while (i <= mid)
	{
		tmp[k++] = array[i++];
	}

	//如果j区间还有剩余数据,则把剩余全部放入tmp数组中
	while (j <= rigth)
	{
		tmp[k++] = array[j++];
	}

	//最后把tmp中排序后的数据拷贝到源数据中
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

int partition(vector<int>& array, int left, int right)
{
	int& pivot = array[right];

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
	array[i] = pivot;
	pivot = tmp;

	//int tmp = array[i];
	//array[i] = array[right];
	//array[right] = tmp;

	return i;
}

void quickSort(vector<int>& array, int left, int right)
{
	if (left >= right || array.empty())
		return;

	int mid = partition(array, left, right);
	quickSort(array, left, mid - 1);
	quickSort(array, mid + 1, right);
}