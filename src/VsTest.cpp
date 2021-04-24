#include "VsTest.h"
#include <iostream>
#include <vector>

#include "LRUCache.h"
#include "LRUCacheV2.h"
#include "Sort.h"
#include "../StringValueConvert.h"
#include "../SharedPtr.h"

using  std::cout;
using  std::endl;
using  std::vector;

//class noncopyable
//{
//
//protected:
//	noncopyable() {};
//	~noncopyable() {};
//
//private:
//	noncopyable(const noncopyable&) = delete;
//	noncopyable& operator= (const noncopyable&) = delete;
//};
//
//class B : public noncopyable
//{ };

class BitMap
{
public:
	BitMap(size_t range)
		:maxRange_(range)
	{
		bitTable_.resize((range >> 5) + 1);
	};
	~BitMap() {};

	void setBit(size_t num)
	{
		if (num > maxRange_) 
			return;

		size_t index = num >> 5;
		size_t mod = num % 32;
		bitTable_[index]  |=  (1 << mod);
	}

	void resetBit(size_t num)
	{
		if (num > maxRange_)
			return;

		size_t index = num >> 5;
		size_t mod = num % 32;
		bitTable_[index] &= ~(1 << mod);
	}

	bool getBit(size_t num)
	{
		if (num > maxRange_) 
			return false;

		size_t index = num >> 5;
		size_t mod = num % 32;
		 return ((bitTable_[index] >> mod) & 1) ? true : false;
	}

private:

	size_t maxRange_ = 0;
	vector<int> bitTable_;
};

int Data[] = { 4,5,6,1,3,2 };

int DataV2[] = { 4,5,6,1,3,2 };

vector<int> mergeData = {11,8,3,9,7,1,2,5};
int mergeDataV2[] = {11,8,3,9,7,1,2,5 };

vector<int> quickData = { 11,8,3,9,7,1,2,5 };

void Output(int* data, int len)
{
	for (int i = 0; i < len; ++i)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

void OutputV2(const vector<int>& data)
{
	for (int i = 0; i < data.size(); ++i)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

char comment[] = "abc...   //zhushi\n876996997/abcd,,,,*//*ijihi**/end";

#include "ProducerConsumer.h"

int main()
{

	//SharedPtr::test()
	SharedPtr::test();

	//StringValueConvert
	StringValueConvert::begin();

	startProduceConsume();
	f(comment);

	cout << "Before bubbleSort, Data[]: ";
	Output(Data, sizeof(Data) / sizeof(int));
	bubbleSort(Data, sizeof(Data)/sizeof(int));
	cout << "After bubbleSort, Data[]: ";
	Output(Data, sizeof(Data) / sizeof(int));
	cout << endl;

	cout << "Before insertSort, Data[]: ";
	Output(DataV2, sizeof(DataV2) / sizeof(int));
	insertSort(DataV2, sizeof(DataV2)/sizeof(int));
	cout << "After insertSort, Data[]: ";
	Output(DataV2, sizeof(DataV2) / sizeof(int));
	cout << endl;

	cout << "Before merge_sort, mergeData[]: ";
	OutputV2(mergeData);
	merge_sort(mergeData, 0, mergeData.size()-1);
	cout << "After merge_sort, mergeData[]: ";
	OutputV2(mergeData);
	cout << endl;

	cout << "Before merge_sortV2, mergeDataV2[]: ";
	Output(mergeDataV2, sizeof(mergeDataV2) / sizeof(int));
	merger_sortV2(mergeDataV2, 0, sizeof(mergeDataV2)/sizeof(int) - 1);
	cout << "After merge_sortV2, mergeDataV2[]: ";
	Output(mergeDataV2, sizeof(mergeDataV2) / sizeof(int));
	cout << endl;

	cout << "Before quickSort, quickData[]: ";
	OutputV2(quickData);
	quickSort(quickData, 0, quickData.size() - 1);
	cout << "After quickSort, quickData[]: ";
	OutputV2(quickData);
	cout << endl;


	LRUCache* lruCache = new LRUCache(3);
	lruCache->put(1, 1);
	lruCache->put(2, 3);
	cout << lruCache->getSize() << endl;
	lruCache->put(3, 5);
	cout << lruCache->getSize() << endl;
	cout << lruCache->get(1) << endl;
	lruCache->put(6, 3);
	cout << lruCache->getSize() << endl;
	cout << lruCache->get(3) << endl;
	cout << lruCache->get(1) << endl;
	cout << lruCache->get(2) << endl;

	LRUCacheV2* lruCacheV2 = new LRUCacheV2(3);
	lruCacheV2->Set(1, 1);
	lruCacheV2->Set(2, 3);
	cout << lruCacheV2->GetSize() << endl;
	lruCacheV2->Set(3, 5);
	cout << lruCacheV2->GetSize() << endl;
	cout << lruCacheV2->Get(1) << endl;
	lruCacheV2->Set(6, 3);
	cout << lruCacheV2->GetSize() << endl;
	cout << lruCacheV2->Get(3) << endl;
	cout << lruCacheV2->Get(1) << endl;
	cout << lruCacheV2->Get(2) << endl;


	//B b;
	//B b1(b);
	//B b2 = b;
	//b2 = b;
	//cout
	//	<< "(1 << 0) = "		<< (1 << 0)		<< "\n"
	//	<< "(4 >> 1) = "		<< (4 >> 1)		<< "\n"
	//	<< "((1 << 10)  >> 5) = "		<< ((1 << 10)  >> 5)		<< "\n"
	//	<< "(1 << 31) = "	<< (1 << 31)	<< "\n"
	//	<< "(uint)(1 << 31) = "	<< (uint32_t)(1 << 31)	<< "\n"
	//	<< "(1 << 32) = "	<< (1 << 32)	<< "\n"
	//	<< "(uint)(1 << 32 - 1) = "	<< (uint32_t)(1 << 32) - 1	<< "\n"
	//	<<
	//endl;

	//BitMap bitMap(127);
	//bitMap.setBit(100);
	//bitMap.setBit(101);
	//bitMap.setBit(127);
	//bitMap.setBit(128);

	//cout 
	//	<< "bitMap.getBit(99) = "	<< bitMap.getBit(99)	<< "\n"
	//	<< "bitMap.getBit(100) = " << bitMap.getBit(100) << "\n"
	//	<< "bitMap.getBit(101) = " << bitMap.getBit(101) << "\n"
	//	<< "bitMap.getBit(102) = " << bitMap.getBit(102) << "\n"
	//	<< "bitMap.getBit(128) = " << bitMap.getBit(128) << "\n"		
	//	<< 
	//endl;

	//bitMap.resetBit(100);
	//cout
	//	<< "bitMap.getBit(100) = " << bitMap.getBit(100) << "\n"
	//	<< 
	//endl;

	cout << "hello world!!!" << endl;
	return 0;
}