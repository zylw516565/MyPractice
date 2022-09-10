#pragma once

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using std::cout;

class Graph
{
private:
    int count_;  //¶¥µã¸öÊý
    vector<list<int>> adjList_;

public:
    Graph(const int count)
    :count_(count)
    {
        adjList_.resize(count_);
    }

    ~Graph() = default;

    void addEdge(const int i, const int j)
    {
        adjList_[i].push_back(j);
        adjList_[j].push_back(i);
    }

    void bfs(const int start, const int target)
    {
        if (start == target) return;

        vector<bool> vecVisited;
        vecVisited.resize(count_);
        vecVisited[start] = true;

        queue<int> queQueue;
        queQueue.push(start);

        vector<int> vecPrev;
        vecPrev.resize(count_);

        while (!queQueue.empty()) {
            int w = queQueue.front(); queQueue.pop();

            for (auto elment : adjList_[w]){
                if (!vecVisited[elment]) {
                    vecPrev[elment] = w;

                    if (elment == target)
                    {
                        print(vecPrev, start, target); cout << endl;
                        return;
                    }

                    vecVisited[elment] = true;
                    queQueue.push(elment);
                }
            }
        }
    }

private:

    void print(const vector<int>& p_vecPrev, const int start, int target)
    {
        if (p_vecPrev[target] != -1 && start != target) {
            print(p_vecPrev, start, p_vecPrev[target]);
        }

        cout << target << " ";
    }
};
