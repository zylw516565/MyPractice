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

void quickSort(vector<int>& array, int left, int right)
{
	if (left >= right || array.empty())
		return;

	int mid = partition(array, left, right);
	quickSort(array, left, mid - 1);
	quickSort(array, mid + 1, right);
}

//数组,[3,2,5,1,4] 这些面值的卡片,只能头移到尾部,或者尾部移到头部,
//只有当头部的卡片最小时才能删除,每次移动一次耗费的能量值为卡片面值
//问:把所有卡片删除,需要耗费的最小能量值是多少?

int moveDelete(vector<int>& array, int left, int right)
{
	int sumLeft = 0, sumRight = 0, min;
	int begin = left, end = right;
	while (left <= right)
	{
		if (array[left] <= array[right])
		{
			min = array[left];
			sumLeft += array[right--];
		}else{
			min = array[right];
			sumRight = array[left++];
		}
	}

	//TODO: 每次移除一个元素
	if (sumLeft <= sumRight)
	{
		while (begin <= left)
		{
			//array.begin();
			//array.insert();
		}

	}
	else
	{
	}


	return (sumLeft < sumRight)?sumLeft:sumRight;
}

void moveCard(vector<int>& array, int left, int right, int& sum)
{
	if (left >= right) return;

	sum += moveDelete(array, left, right);

	moveCard(array, left, right-1, sum);
}

typedef struct ListNode{
	ListNode* next;
	int       value;
}Node;

bool hasLoop(Node* head)
{
	if (NULL == head)
		return false;

	Node* slow = head;
	Node* fast = head;

	while (slow->next != nullptr 
		   && fast->next->next != nullptr)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			return true;
	}

	return false;
}

/* 实现一个函数 void f(const char* s), 把s字符串中除了注释部分打印出来 */

void f(const char* s)
{
	if (nullptr == s) return;

	while (*s)
	{
		if (*s == '/')
		{
			s++;

			if (*s == '/')
			{
				//row comment
				s++;
				while (*s != '\n')
				{
					s++;
				}
				s++; continue;
			}
			else if (*s == '*')
			{
				//block comment
				s++;
				while (*s != '*')
				{
					s++;
				}

				if (*s++ == '/')
				{
					s++; continue;
				}
			}
		}

		cout << *s;
		s++;
	}

}

const int key = 3;

void binarySearchRecursive(const vector<int>& array, int begin, int end)
{
	if (begin >= end) return;
	
	int mid = (begin + end) / 2;
	if (array[mid] == key)
	{
		//indexBS = mid;
		return;
	}
	else if (array[mid] < key)
	{
		binarySearchRecursive(array, begin, mid - 1);
	}
	else
	{
		binarySearchRecursive(array, mid + 1, end);
	}
}

int binarySearch(const vector<int>& array, int key)
{
	int mid;
	int begin = 0; int end = array.size() - 1;
	while (begin <= end)
    {
		mid = begin + ((end - begin) >> 1);

        if (key == array[mid])
        {
            return mid;
        }
		else if (key < array[mid])
		{
			end = mid - 1;
		}
		else
		{
			begin = mid + 1;
		}
	}

	return -1;
}

int findFirstEqual(const vector<int>& array, int key)
{
    int mid;
    int low = 0; int hight = array.size() - 1;
    while (low <= hight)
    {
        mid = low + ((hight - low) >> 1);

        if (key == array[mid])
        {
			if (0 == mid || key != array[mid - 1]) 
				return mid;
			else
				hight = mid - 1;
        }
        else if (key < array[mid])
		{
			hight = mid - 1;
        }
        else
		{
			low = mid + 1;
        }
    }

    return -1;
}

int findLastEqual(const vector<int>& array, int key)
{
    int mid;
	int low = 0; int hight = array.size() - 1; int tail = hight;
    while (low <= hight)
    {
        mid = low + ((hight - low) >> 1);

        if (key == array[mid])
        {
            if (mid == tail || key != array[mid + 1])
                return mid;
            else
                low = mid + 1;
        }
        else if (key < array[mid])
        {
            hight = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return -1;
}

int findFirstGreaterThan(const vector<int>& array, int key)
{
    int mid;
    int low = 0; int hight = array.size() - 1; int tail = hight;
    while (low <= hight)
    {
        mid = low + ((hight - low) >> 1);

        if (key == array[mid])
        {
            if (mid < tail && key < array[mid + 1])
                return mid + 1;
            else
                low = mid + 1;
        }
        else if (key < array[mid])
        {
            hight = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return -1;
}

int findLastLessThan(const vector<int>& array, int key)
{
    int mid;
    int low = 0; int hight = array.size() - 1; int tail = hight;
    while (low <= hight)
    {
        mid = low + ((hight - low) >> 1);

        if (key == array[mid])
        {
            if (mid > 0 && key > array[mid - 1])
                return mid - 1;
            else
                hight = mid - 1;
        }
        else if (key < array[mid])
        {
            hight = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return -1;
}