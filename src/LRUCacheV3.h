#pragma once

#include <map>
#include <list>
#include<iostream>
#include <unordered_map>

using std::list;
using std::map;
using std::unordered_map;


class LRUCacheV3
{
public:
	LRUCacheV3() = default;
	~LRUCacheV3() = default;

	LRUCacheV3(const int nMaxSize)
		:maxSize_(nMaxSize)
	{
	}

	void get(int x)
	{
		//x在链表中
		auto iter = list_.begin();
		for ( ; iter != list_.end(); iter++)
		{
			if (x == *iter)
			{
				iter = list_.erase(iter);
				list_.emplace_front(x);
				return;
			}
		}

		//x不在链表中
		if (list_.size() != maxSize_)
		{//链表未满
			list_.emplace_front(x);
		}
		//链表已满
		else
		{
			list_.pop_back();     //移除尾部
			list_.emplace_front(x);  //在头部插入
		}

		return;
	}

    size_t maxSize() const
    {
        return list_.max_size();
    }

    size_t size() const
    {
        return list_.size();
    }

	void print()
	{
		for (auto n : list_)
		{
			cout << n << " ";
		}
		cout << endl;
	}

private:
	const int maxSize_;
	list<int> list_;

};



class LRUCacheV4
{
public:
    typedef list<pair<int, int>> ListIntType;
    typedef unordered_map<int, ListIntType::iterator> HashIntType;

private:
    const int   maxSize_;
    ListIntType cacheList_;    //存储key,value
    HashIntType cacheHashMap_;

public:
    LRUCacheV4() = default;
    ~LRUCacheV4() = default;

    LRUCacheV4(const int nMaxSize)
        :maxSize_(nMaxSize)
    {
    }

    int get(int key)
    {
        auto iter = cacheHashMap_.find(key);
        if (iter == cacheHashMap_.end())
        {//key不在链表中
            return -1;
        }

        //key在链表中, 找到key在链表中的位置,并将其移到链表头部
        cacheList_.splice(cacheList_.begin(), cacheList_, cacheHashMap_[key]);
        return cacheList_.front().second;
    }

    void put(const int key, const int value)
    {
        //key存在链表中, get函数已经将其移到头部
        if (get(key) != -1)
        {
            cacheList_.front().second = value;
        }
        // key不存在
        else
        {
            if (maxSize_ == cacheList_.size())
            {//链表已满
                int delKey = cacheList_.back().second;
                cacheList_.pop_back();     //移除尾部
                cacheHashMap_.erase(delKey);
            }

            //链表未满
            cacheList_.emplace_front(key, value);   //在头部插入
            cacheHashMap_[key] = cacheList_.begin();
        }
    }

    size_t maxSize() const
    {
        return cacheList_.max_size();
    }

    size_t size() const
    {
        return cacheList_.size();
    }

    void print()
    {
        for (auto n : cacheList_)
        {
            cout << n.first << " " << n.second << endl;
        }
        cout << "-----------" << endl;
    }

};
