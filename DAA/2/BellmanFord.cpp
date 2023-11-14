#include <bits/stdc++.h>
using namespace std;
struct edge
{
    int source, destination, weight;
};
vector<edge> edges;

void printPath(int destination, vector<int> &parent)
{
    vector<int> path;
    int cur = destination;

    while (cur != -1)
    {
        path.push_back(cur);
        cur = parent[cur];
    }

    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i] << "-  "[i == path.size() - 1];
    }
    cout << endl;
}

void BellmanFord(int src, int n)
{
    vector<int> distance(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);
    distance[src] = 0;
    parent[src] = -1;
    cout << "Source Vertex     :" << src << endl;

    for (int i = 1; i < n; i++)
    {
        bool changed = false;
        for (auto j : edges)
        {
            if (distance[j.destination] > j.weight + distance[j.source])
            {
                changed = true;
                distance[j.destination] = distance[j.source] + j.weight;
                parent[j.destination] = j.source;
            }
        }
        if (!changed)
        {
            cout << "got final answer in " << i + 1 << " iterations" << endl;
            break;
        }
    }

    for (auto j : edges)
    {
        if (distance[j.destination] > j.weight + distance[j.source])
        {
            cout << "Negetive edge Cycle is present in the graph\n";
            exit(0);
        }
    }
    cout << "--------------------------------\n";
    for (int dest = 2; dest < n + 1; dest++)
    {
        cout << "Vertex            :" << dest << endl;
        cout << "distance          :" << distance[dest] << endl;
        cout << "shortest path     :";
        printPath(dest, parent);
        cout << "--------------------------------\n";
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, weight;
        cin >> u >> v >> weight;
        edges.push_back({u, v, weight});
    }
    BellmanFord(1, n);
    return 0;
}

7 10
1 2 6
2 5 -1
5 7 3
1 3 2
1 4 5
3 5 1
4 6 -1
6 7 3
4 3 -2
3 2 -2


4 5
1 2 2
2 3 2
2 4 -2
3 4 1
4 1 -1
