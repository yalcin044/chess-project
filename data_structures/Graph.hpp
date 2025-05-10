#ifndef GRAPH_HPP
#define GRAHP_HPP

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

template<class ItemType>
class Graph{
    public:
        Graph();

        void addEdge(int from, int to, ItemType weight);

        bool bfs(const std::vector<std::vector<ItemType>> &residualGraph, int source,
                    int sink, std::vector<int> &parent) const;

    private:
        struct Edges{
            int to;
            ItemType weight;
        };

        std::vector<std::vector<Edge>> adjList;
        int numVertices;
};


#endif //GRAPH_HPP