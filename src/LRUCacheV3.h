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
		//x��������
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

		//x����������
		if (list_.size() != maxSize_)
		{//����δ��
			list_.emplace_front(x);
		}
		//��������
		else
		{
			list_.pop_back();     //�Ƴ�β��
			list_.emplace_front(x);  //��ͷ������
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
    ListIntType cacheList_;    //�洢key,value
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
        {//key����������
            return -1;
        }

        //key��������, �ҵ�key�������е�λ��,�������Ƶ�����ͷ��
        cacheList_.splice(cacheList_.begin(), cacheList_, cacheHashMap_[key]);
        return cacheList_.front().second;
    }

    void put(const int key, const int value)
    {
        //key����������, get�����Ѿ������Ƶ�ͷ��
        if (get(key) != -1)
        {
            cacheList_.front().second = value;
        }
        // key������
        else
        {
            if (maxSize_ == cacheList_.size())
            {//��������
                int delKey = cacheList_.back().second;
                cacheList_.pop_back();     //�Ƴ�β��
                cacheHashMap_.erase(delKey);
            }

            //����δ��
            cacheList_.emplace_front(key, value);   //��ͷ������
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
