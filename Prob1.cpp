#include <bits/stdc++.h>
using namespace std;

#ifdef GENERATE_VARM
void createRandomGraph(int nodes, vector<pair<int, int>> &edgeList)
{
    srand(time(nullptr));
    int minEdges = 2 * nodes;
    int maxEdges = (nodes * (nodes - 1)) / 2;
    int totalEdges = minEdges + rand() % (maxEdges - minEdges + 1);

    set<pair<int, int>> uniqueEdges;
    while (edgeList.size() < totalEdges)
    {
        int a = rand() % nodes;
        int b = rand() % nodes;
        if (a != b && uniqueEdges.count({a, b}) == 0 && uniqueEdges.count({a, b}) == 0)
        {
            uniqueEdges.insert({a, b});
            edgeList.emplace_back(a, b);
        }
    }
}
#endif

#ifdef GENERATE_VARN
void createRandomGraph(int nodes, vector<pair<int, int>> &edgeList)
{
    srand(time(nullptr));
    int totalEdges;


#ifdef nsqrtn
    totalEdges = static_cast<int>(nodes * sqrt(nodes));
#endif
#ifdef nlogn
    totalEdges = static_cast<int>(nodes * log2(nodes));
#endif
#ifdef nc2
    totalEdges = (nodes * (nodes - 1)) / 2;
#endif

    totalEdges = 2 * nodes;

    set<pair<int, int>> uniqueEdges;
    while (edgeList.size() < totalEdges)
    {
        int a = rand() % nodes;
        int b = rand() % nodes;
        if (a != b && uniqueEdges.count({a, b}) == 0 && uniqueEdges.count({b, a}) == 0)
        {
            uniqueEdges.insert({a, b});
            edgeList.emplace_back(a, b);
        }
    }
}
#endif

#ifdef DFS
void performDFS(const vector<vector<int>> &graph)
{
    int size = graph.size();
    vector<bool> vis(size, false);
    stack<int> stk;
    stk.push(0);

    while (!stk.empty())
    {
        int currentNode = stk.top();
        stk.pop();
        if (vis[currentNode])
            continue;
        vis[currentNode] = true;

        for (int neighborNode : graph[currentNode])
        {
            if (!vis[neighborNode])
            {
                stk.push(neighborNode);
            }
        }
    }
}
#endif

#ifdef BFS
void performBFS(const vector<vector<int>> &graph)
{
    int size = graph.size();
    vector<bool> vis(size, false);
    queue<int> q;
    q.push(0);
    vis[0] = true;

    while (!q.empty())
    {
        int currentNode = q.front();
        q.pop();

        for (int neighborNode : graph[currentNode])
        {
            if (!vis[neighborNode])
            {
                vis[neighborNode] = true;
                q.push(neighborNode);
            }
        }
    }
}
#endif

#ifdef RECURSIVE_DFS
void recursiveDFS(int currentNode, vector<bool> &vis, const vector<vector<int>> &graph)
{
    vis[currentNode] = true;
    for (int neighborNode : graph[currentNode])
    {
        if (!vis[neighborNode])
        {
            recursiveDFS(neighborNode, vis, graph);
        }
    }
}
#endif

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Error: Missing number of nodes as argument!" << endl;
        return 1;
    }

    int N = atoi(argv[1]);
    vector<pair<int, int>> edges;

    // Generate graph
    createRandomGraph(N, edges);

    // Build adjacency list
    vector<vector<int>> graph(N);
    for (auto edge : edges)
    {
        int u = edge.first;
        int v = edge.second;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

// Choose and run the traversal
#ifdef RECURSIVE_DFS
    vector<bool> vis(N, false);
    recursiveDFS(0, vis, graph);
#endif
#ifdef DFS
    performDFS(graph);
#endif
#ifdef BFS
    performBFS(graph);
#endif
    return 0;
}