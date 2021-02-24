#include "LRUCache.h"

void LRUCache::put(int key, int value)
{
	auto iter = nodesMap_.find(key);
	if (iter != nodesMap_.end())
	{
		//缓存中key已经存在
		iter->second->value = value;      //更新此key对应的value
		LRUNode* tempNode = iter->second;
		removeNode(tempNode);
		setHead(tempNode);    //访问过的放入头部
	}
	else
	{
		//新添加
		LRUNode* newNode = new LRUNode ( key, value );
		if (nodesMap_.size() >= static_cast<unsigned int>(cacheSize_))
		{
			removeNode(listTail_);
			auto iter = nodesMap_.find(listTail_->key);
			if (iter != nodesMap_.end())
			{
				nodesMap_.erase(iter);
			}
		}

		nodesMap_.insert(NodesType::value_type(key, newNode));
		setHead(newNode);    //放入头部
	}
}

int LRUCache::get(int key)
{
	auto iter = nodesMap_.find(key);
	if (iter != nodesMap_.end())
	{
		removeNode(iter->second);
		setHead(iter->second);
		return iter->second->value;
	}
	else
	{
		return -1;
	}
}

int LRUCache::getSize()
{
	return nodesMap_.size();
}

void LRUCache::removeNode(LRUNode* node)
{
	if (NULL == node)
		return;

	//如果是头指针
	if (node->prev == NULL)
	{
		listHead_ = node->next;
		listHead_->prev = NULL;
	}	
	
	if (node->next == NULL)
	{//如果是尾指针
		listTail_ = node->prev;
		listTail_->next = NULL;
	}
	else
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}
}

void LRUCache::setHead(LRUNode* node)
{
	if (NULL == node)
		return;

	node->next = listHead_;
	node->prev = NULL;
	if (NULL == listHead_)
	{
		listHead_ = node;
	}
	else
	{
		listHead_->prev = node;
		listHead_ = node;
	}

	if (NULL == listTail_)
	{
		listTail_ = listHead_;
	}
}