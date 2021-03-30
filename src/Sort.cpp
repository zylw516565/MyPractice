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
		int j = i - 1;  //�������������β��ͷ,���Ҳ���λ��
		for (; j >= 0; --j)
		{
			if (array[j] > value){
				array[j + 1] = array[j];  //�ƶ�Ԫ��
			}
			else {
				break;
			}
		}

		array[j + 1] = value;
	}
}