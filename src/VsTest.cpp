#include "VsTest.h"
#include <iostream>
#include <vector>

#include "LRUCache.h"
#include "LRUCacheV2.h"
#include "LRUCacheV3.h"
#include "Sort.h"
#include "../StringValueConvert.h"
#include "../SharedPtr.h"
#include "Graph.h"
#include "StringMatch.h"
#include "DevPractice/Practice.h"


#include <fstream>      // std::filebuf
#include <sstream>      // std::stringstream 

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

vector<int> binarySearchData = { 1,2,3,4,5,6,7,8,9,10 };
vector<int> findFirstEqualData = { 1,2,3,4,5,5,5,8,9,10,11 };

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

int fabnacci(int n)
{
	if (1 == n) return 1;
	if (2 == n) return 2;
	return fabnacci(n - 1) + fabnacci(n - 2);
}

#include <algorithm>

int compareFunc(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

int main()
{

//     const char* strArray = "hello world";
//     char strArray[] = "hello world";
//     cout << "sizeof(strArray): " << sizeof(strArray) << endl;
//     cout << "pos: " << find(strArray, strlen(strArray), 'a') << endl;
//     cout << "pos: " << find(strArray, strlen(strArray), 'b') << endl;
//     cout << "pos: " << find(strArray, strlen(strArray), 'l') << endl;
//     cout << "pos: " << find(strArray, strlen(strArray), 'd') << endl;

	//const vector<int> vecHeapData = {0,33,17,21,16,13,15,9,5,6,7,8,1,2};
	//Heap objHeap(30);
	//objHeap.setData(vecHeapData);
	//OutputV2(objHeap.data());
	//objHeap.insert(22);
	//OutputV2(objHeap.data());

	//const vector<int> vecHeapDataV2 = { 33,17,21,16,13,15,9,5,6,7,8,1,2 };
 //   Heap objHeapV2(30);
 //   OutputV2(objHeapV2.data());
	//for (auto i: vecHeapDataV2)
	//{
	//	objHeapV2.insert(i);
	//}
 //   OutputV2(objHeapV2.data());
	//objHeapV2.insert(22);
 //   OutputV2(objHeapV2.data());

	//const vector<int> vecHeapDataV3 = { 33,27,21,16,13,15,19,5,6,7,8,1,2,12};
	//Heap objHeapV3(30);
	//OutputV2(objHeapV3.data());
	//for (auto i : vecHeapDataV3)
	//{
	//	objHeapV3.insert(i);
	//}
	//OutputV2(objHeapV3.data());
	//objHeapV3.removeMax();
	//OutputV2(objHeapV3.data());

	//vector<int> vecHeapDataV4 = { 0,7,5,19,8,4,1,20,13,16};
	//HeapV2 objHeapV4;
	//objHeapV4.buildHeap(vecHeapDataV4);
	//OutputV2(vecHeapDataV4);

	Graph objGraph(8);
	objGraph.addEdge(0, 1);
	objGraph.addEdge(0, 3);
	objGraph.addEdge(1, 2);
	objGraph.addEdge(1, 4);
	objGraph.addEdge(3, 4);
	objGraph.addEdge(2, 5);
	objGraph.addEdge(4, 5);
	objGraph.addEdge(4, 6);
	objGraph.addEdge(5, 7);
	objGraph.addEdge(6, 7);
	//广度优先
	objGraph.bfs(0, 6);

	Graph objGraphV2(9);
	objGraphV2.addEdge(1, 2);
	objGraphV2.addEdge(1, 4);
	objGraphV2.addEdge(2, 3);
	objGraphV2.addEdge(2, 5);
	objGraphV2.addEdge(3, 6);
	objGraphV2.addEdge(4, 5);
	objGraphV2.addEdge(5, 6);
	objGraphV2.addEdge(5, 7);
	objGraphV2.addEdge(6, 8);
	objGraphV2.addEdge(7, 8);
	//深度优先
	objGraphV2.dfs(1, 7);

	string strMainString("aabcaaaba");
	string strTarget("aa");
	StringMatch objStringMatch;
	objStringMatch.match(strMainString, strTarget);

	//错误,待修改
	//int start = 0;
	//while (start <= strMainString.size() - 1)
	//{
	//	int index = strMainString.find(strTarget, start);
	//	if (index != string::npos)
	//	{
	//		cout << "Equal string start index: " << index << endl;
	//		start = index;
	//	}
	//	else {
	//		break;
	//	}
	//}

	call_StructuredBinding();
	//call_Emplace();
	call_UniquePtr();
	call_BMMatch();
	call_SharedPtr();
	call_testRetValue();
	call_KMPMatch();

	vector<int> vecHeapDataV5 = { 0,7,5,19,8,4,1,20,13,16 };
	vector<int> vecHeapDataV6 = vecHeapDataV5;
	NiceHeap objHeapV5;
	objHeapV5.buildHeap(vecHeapDataV5);
	OutputV2(vecHeapDataV5);
	objHeapV5.sort(vecHeapDataV6);
	OutputV2(vecHeapDataV6);

    cout << "findLastLessThan(findFirstEqualData, 5) = " << findLastLessThan(findFirstEqualData, 5) << endl;
    cout << "findLastLessThan(findFirstEqualData, 2) = " << findLastLessThan(findFirstEqualData, 2) << endl;
    cout << "findLastLessThan(findFirstEqualData, 3) = " << findLastLessThan(findFirstEqualData, 3) << endl;

    cout << "findFirstGreaterThan(findFirstEqualData, 5) = " << findFirstGreaterThan(findFirstEqualData, 5) << endl;
    cout << "findFirstGreaterThan(findFirstEqualData, 2) = " << findFirstGreaterThan(findFirstEqualData, 2) << endl;
    cout << "findFirstGreaterThan(findFirstEqualData, 3) = " << findFirstGreaterThan(findFirstEqualData, 3) << endl;

    cout << "findLastEqual(findFirstEqualData, 5) = " << findLastEqual(findFirstEqualData, 5) << endl;
    cout << "findLastEqual(findFirstEqualData, 2) = " << findLastEqual(findFirstEqualData, 2) << endl;
    cout << "findLastEqual(findFirstEqualData, 3) = " << findLastEqual(findFirstEqualData, 3) << endl;

	cout << "findFirstEqual(findFirstEqualData, 5) = " <<  findFirstEqual(findFirstEqualData, 5) << endl;
	cout << "findFirstEqual(findFirstEqualData, 2) = " << findFirstEqual(findFirstEqualData, 2) << endl;
	cout << "findFirstEqual(findFirstEqualData, 3) = " << findFirstEqual(findFirstEqualData, 3) << endl;

	cout << binarySearch(binarySearchData, 3) << endl;
	cout << binarySearch(binarySearchData, 9) << endl;
	cout << binarySearch(binarySearchData, 11) << endl;

	Output(Data, sizeof(Data) / sizeof(int));
	qsort(Data, sizeof(Data)/sizeof(int), sizeof(int), compareFunc);
	Output(Data, sizeof(Data) / sizeof(int));
/*	std::sort(quickData.begin(), quickData.end());*/
	std::stable_sort(quickData.begin(), quickData.end());

	for (auto data : quickData)
	{
		cout << data << " ";
	}
	cout << endl;

	int result = -1;
	QuickSortSolution objQSort;
	cout << objQSort.findKthLargest(quickData, 0) << endl; objQSort.clear();
	cout << objQSort.findKthLargest(quickData, 3) << endl; objQSort.clear();
	cout << objQSort.findKthLargest(quickData, 1) << endl; objQSort.clear();
	cout << objQSort.findKthLargest(quickData, 9) << endl; objQSort.clear();
	
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

	double       g_fDistributeInterval = 0.0;
	int nDistributeInterval;
	nDistributeInterval = 3;
	g_fDistributeInterval = (double) nDistributeInterval / 1000;
	cout << "g_fDistributeInterval " << g_fDistributeInterval << endl;
	printf("g_fDistributeInterval [%f]", g_fDistributeInterval);

    nDistributeInterval = 30;
    g_fDistributeInterval = (double) nDistributeInterval / 1000;
    cout << "g_fDistributeInterval " << g_fDistributeInterval << endl;


	LRUCacheV3 objLRUCacheV3(3);
	objLRUCacheV3.print(); cout << "maxSize: " << objLRUCacheV3.maxSize() << endl;
	cout << "size: " << objLRUCacheV3.size() << endl;
	objLRUCacheV3.get(1);
	objLRUCacheV3.print();
	objLRUCacheV3.get(2);
	objLRUCacheV3.print();
	objLRUCacheV3.get(3);
	objLRUCacheV3.print();
	objLRUCacheV3.get(1);
	objLRUCacheV3.print();
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