#pragma once

#include <map>
#include <list>

using std::list;
using std::map;


//********************
//**Filename:LRUCache.h
//**Discribe: LRUCacheʵ���ļ���˫������+map
//**Date: 2018.7.26
//**@author: Mr.xiong
//*****
#include<iostream>
#include<map>  
using namespace std;


//** ����ڵ�ṹ��

struct ListNode
{
	int m_key;                //key,value ��ʽ����map�洢��
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

//*  LRU����ʵ����  ˫������
class LRUCacheV2
{
public:
	//** ���캯����ʼ�������С
	LRUCacheV2(int size)
	{
		m_capacity = size;
		pHead == NULL;
		pTail == NULL;
	}

	~LRUCacheV2()
	{
		//**  һ��Ҫע�⣬map�ͷ��ڴ�ʱ�����ͷ��ڲ�new���ڴ棬���ͷ�map���ڴ�
		map<int, ListNode*>::iterator it = mp.begin();
		for (; it != mp.end();)
		{
			delete it->second;
			it->second = NULL;
			mp.erase(it++);    //** ע�⣺һ��Ҫ����д��it++ ���������κ�һ���ط����ᵼ���������ʧЧ��
		}
		delete pHead;
		pHead == NULL;
		delete pTail;
		pTail == NULL;

	}
	//** ����ֻ���Ƴ�������ɾ���ڵ�
	void Remove(ListNode* pNode)
	{
		// �����ͷ�ڵ�
		if (pNode->pPre == NULL)
		{
			pHead = pNode->pNext;
			pHead->pPre = NULL;
		}

		// �����β�ڵ�
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
	//  ���ڵ�ŵ�ͷ��������ù�������Ҫ���ڶ�ͷ��
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
	// * �������ݣ�������ھ�ֻ��������
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
				//�������Ƴ�
				Remove(pTail);
				//ɾ��ָ��ָ����ڴ�
				delete it->second;
				//ɾ��mapԪ��
				mp.erase(it);
			}
			//�ŵ�ͷ��
			SetHead(NewNode);
			mp[key] = NewNode;

		}

		return 0;
	}



	//��ȡ�����������
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
			return -1;       //���ﲻ̫�ã��п���ȡ��ֵҲΪ-1
		}
	}

	int GetSize()
	{
		return mp.size();
	}

private:
	int m_capacity;    //��������
	ListNode* pHead;   //ͷ�ڵ�
	ListNode* pTail;   //β�ڵ�
	map<int, ListNode*>  mp;   //mp���������ݣ��ﵽfindΪo(1)����
};