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