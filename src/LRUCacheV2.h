#pragma once

#include <map>
#include <list>

using std::list;
using std::map;


//********************
//**Filename:LRUCache.h
//**Discribe: LRUCache实现文件：双向链表+map
//**Date: 2018.7.26
//**@author: Mr.xiong
//*****
#include<iostream>
#include<map>  
using namespace std;


//** 链表节点结构体

struct ListNode
{
	int m_key;                //key,value 形式方便map存储。
	int m_value;
	ListNode* pPre;
	ListNode* pNext;

	ListNode(int key, int value)
	{
		m_key = key;
		m_value = value;
		pPre = NULL;
		pNext = NULL;
	}
};

//*  LRU缓存实现类  双向链表。
class LRUCacheV2
{
public:
	//** 构造函数初始化缓存大小
	LRUCacheV2(int size)
	{
		m_capacity = size;
		pHead = NULL;
		pTail = NULL;
	}

	~LRUCacheV2()
	{
		//**  一定要注意，map释放内存时，先释放内部new的内存，在释放map的内存
		map<int, ListNode*>::iterator it = mp.begin();
		for (; it != mp.end();)
		{
			delete it->second;
			it->second = NULL;
			mp.erase(it++);    //** 注意：一定要这样写，it++ 放在其他任何一个地方都会导致其迭代器失效。
		}
		delete pHead;
		pHead = NULL;
		delete pTail;
		pTail = NULL;

	}
	//** 这里只是移除，并不删除节点
	void Remove(ListNode* pNode)
	{
		// 如果是头节点
		if (pNode->pPre == NULL)
		{
			pHead = pNode->pNext;
			pHead->pPre = NULL;
		}

		// 如果是尾节点
		if (pNode->pNext == NULL)
		{
			pTail = pNode->pPre;
			pTail->pNext = NULL;
		}

		else
		{
			pNode->pPre->pNext = pNode->pNext;
			pNode->pNext->pPre = pNode->pPre;
		}

	}
	//  将节点放到头部，最近用过的数据要放在队头。
	void SetHead(ListNode* pNode)
	{
		pNode->pNext = pHead;
		pNode->pPre = NULL;
		if (pHead == NULL)
		{
			pHead = pNode;
		}
		else
		{
			pHead->pPre = pNode;
			pHead = pNode;

		}
		if (pTail == NULL)
		{
			pTail = pHead;
		}
	}
	// * 插入数据，如果存在就只更新数据
	int Set(int key, int value)
	{
		map<int, ListNode*>::iterator it = mp.find(key);
		if (it != mp.end())
		{
			ListNode* Node = it->second;
			Node->m_value = value;
			Remove(Node);
			SetHead(Node);
		}
		else
		{
			ListNode* NewNode = new ListNode(key, value);
			if (mp.size() >= m_capacity)
			{
				map<int, ListNode*>::iterator it = mp.find(pTail->m_key);
				//从链表移除
				Remove(pTail);
				//删除指针指向的内存
				delete it->second;
				//删除map元素
				mp.erase(it);
			}
			//放到头部
			SetHead(NewNode);
			mp[key] = NewNode;

		}

		return 0;
	}



	//获取缓存里的数据
	int Get(int key)
	{
		map<int, ListNode*>::iterator it = mp.find(key);
		if (it != mp.end())
		{
			ListNode* Node = it->second;
			Remove(Node);
			SetHead(Node);
			return Node->m_value;
		}
		else
		{
			return -1;       //这里不太好，有可能取得值也为-1
		}
	}

	int GetSize()
	{
		return mp.size();
	}

private:
	int m_capacity;    //缓存容量
	ListNode* pHead;   //头节点
	ListNode* pTail;   //尾节点
	map<int, ListNode*>  mp;   //mp用来存数据，达到find为o(1)级别。
};