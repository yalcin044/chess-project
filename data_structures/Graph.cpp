#include "Graph.hpp"


template<class ItemType>
Graph<class ItemType>::Graph(){ }
 

template <typename T>
bool Graph<T>::bfs(const std::vector<std::vector<T>> &residualGraph, int source,
                   int sink, std::vector<int> &parent) const {
  
    std::vector<bool> visited(numVertices, false);
    std::queue<int> queue;

    queue.push(source);   
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = queue.front();
        queue.pop();

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
            queue.push(v);
            parent[v] = u;
            visited[v] = true;
            }
        }
    }

    return visited[sink];
}


template<class ItemType> 
void Graph<ItemType>::addEdge(int from, int to, ItemType weight) {
    adjList[from].push_back({to, weight});
}