#ifndef GRAPH_HPP
#define GRAHP_HPP

#include <iostream>
#include <vector>
#include <stack>
#include <queue>

class Graph{
    public:
        Graph();

        void addEdge(int from, int to, int weight);

        bool bfs(const std::vector<std::vector<int>> &residualGraph, int source,
                    int sink, std::vector<int> &parent) const;

    private:
        struct Edges{
            int to;
            int weight;
        };

        std::vector<std::vector<Edges>> adjList;
        int numVertices;
};


#endif //GRAPH_HPP