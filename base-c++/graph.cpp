// Обход графа в глубину

#include <iostream>
#include <vector>
using namespace std;

vector<int> visited = { 0,0,0,0,0 };
int n = 5;
vector<vector<int>> graph = {
    {1,2,3},
    {2,3,4},
    {1,3,4},
    {0,1,4},
    {1,2,3}
};
void dfs(int vertex) {
    visited[vertex] = 1;
    cout << vertex << " ";
    for (int i = 0; i < graph[vertex].size(); i++)
        if (!visited[graph[vertex][i]]) dfs(graph[vertex][i]);
}
int main()
{
    dfs(0);
    return 0;
}