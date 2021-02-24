#pragma once

#include <map>
#include <list>

using std::list;
using std::map;

class LRUCache
{
public:

	struct LRUNode
	{
		LRUNode*  prev  = NULL;
		LRUNode*  next   = NULL;
		int                 key    =  0;
		int                 value = 0;

		LRUNode(int key, int value)
		:prev( NULL)
		,next(NULL)
		,key(key)
		,value(value)
		{}
	};

	typedef map<int, LRUNode*>  NodesType;

	LRUCache(int size) 
	:cacheSize_(size)
	,listHead_(nullptr)
	,listTail_(nullptr)
	{
	}

public:

	void put(int key, int value);
	int get(int key);
	int getSize();

private:

	void removeNode(LRUNode* node);
	void setHead(LRUNode* node);

private:

	LRUNode*    listHead_;
	LRUNode*    listTail_;

	int    cacheSize_;
	NodesType    nodesMap_;
};

class CPPLRUCache
{

public:
	//typedef map<int, LRUNode*>  NodesType;

private:
	int    cacheSize_;

	//map<>   nodesMap_;
};