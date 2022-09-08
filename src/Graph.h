#pragma once

#include <iostream>
#include <unordered_set>
#include <unordered_map>

using std::cout;

class Graph
{
private:
    int count_;  //¶¥µã¸öÊı
    unordered_map<int, int> adjMap_;

public:
    Graph(const int count)
    :count_(count)
    {
        adjMap_.reserve(count);
    }

    ~Graph() = default;

    void addEdge(const int i, const int j)
    {
        adjMap_[i] = j;
        adjMap_[j] = i;
    }

};
