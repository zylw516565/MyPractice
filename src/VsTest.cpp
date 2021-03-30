#include "VsTest.h"
#include <iostream>
#include <vector>

#include "LRUCache.h"
#include "LRUCacheV2.h"
#include "Sort.h"

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

void Output(int* data, int len)
{
	for (int i = 0; i < len; ++i)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

int main()
{
	cout << "Before bubbleSort, Data[]: ";
	Output(Data, sizeof(Data) / sizeof(int));
	bubbleSort(Data, sizeof(Data)/sizeof(int));
	cout << "After bubbleSort, Data[]: ";
	Output(Data, sizeof(Data) / sizeof(int));

	cout << "Before insertSort, Data[]: ";
	Output(DataV2, sizeof(DataV2) / sizeof(int));
	insertSort(DataV2, sizeof(DataV2)/sizeof(int));
	cout << "After insertSort, Data[]: ";
	Output(DataV2, sizeof(DataV2) / sizeof(int));

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