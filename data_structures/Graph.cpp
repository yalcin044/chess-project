#include "Graph.hpp"

Graph::Graph(){ }
 
bool Graph::bfs(const std::vector<std::vector<int>> &residualGraph, int source,
                   int sink, std::vector<int> &parent) const {
  
    std::vector<bool> visited(numVertices, false);
    std::queue<int> queue;

    queue.push(source);   
    visited[source] = true;
    parent[source] = -1;

    while (!queue.empty()) {
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
 
void Graph::addEdge(int from, int to, int weight) {
    adjList[from].push_back({to, weight});
}