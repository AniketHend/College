#include <bits/stdc++.h>
using namespace std;

class Node {
public :
    int Vertex;
    int Cost;
    int Level;
    vector<vector<int>> Matrix;
    vector<pair<int, int>> Path;
};
Node* newNode(vector<vector<int>>&parent, vector<pair<int, int>>&path, int level, int par, int child) {
    Node* tmp = new Node;
    tmp->Path = path;
    if (level != 0) {
        tmp->Path.push_back({par, child});
    }
    tmp->Matrix = parent;
    for (int k = 0; k < parent.size() && level != 0; k++) {
        tmp->Matrix[par][k] = INT_MAX;
        tmp->Matrix[k][child] = INT_MAX;
    }
    tmp->Matrix[child][0] = INT_MAX;

    tmp->Level = level;
    tmp->Vertex = child;
    return tmp;
}

void Reduce_Row(vector<vector<int>>&matrix, vector<int>&row) {
    int n = matrix.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            row[i] = min(row[i], matrix[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (row[i] != INT_MAX) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= row[i];
                }
            }
        }
    }
}
void Reduce_Col(vector<vector<int>>&matrix, vector<int>&col) {
    int n = matrix.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (col[j] > matrix[i][j]) {
                col[j] = matrix[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (col[j] != INT_MAX) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= col[j];
                }
            }
        }
    }
}

int cost_calculation(vector<vector<int>>&matrix) {
    int n = matrix.size();

    vector<int> row(n, INT_MAX), col(n, INT_MAX);
    Reduce_Row(matrix, row);
    Reduce_Col(matrix, col);
    int cost = 0;
    for (int i = 0; i < col.size(); i++) {
        if (row[i] != INT_MAX) cost += row[i];
        if (col[i] != INT_MAX) cost += col[i];
    }
    return cost;
}

class cmp {
public:
    bool operator()(const Node* x, const Node* y) {
        return x->Cost > y->Cost;
    }
};

void TSP(vector<vector<int>>&adj) {
    int n = adj.size();
    vector<pair<int, int>>path;

    Node* root = newNode(adj, path, 0, -1, 0);
    root->Cost = cost_calculation(adj);

    priority_queue<Node*, vector<Node*>, cmp>pq;
    pq.push(root);

    while (!pq.empty()) {
        Node* cur = pq.top();
        pq.pop();
        int ver = cur->Vertex;
        cout << ver << endl;
        if (cur->Level == n - 1) {
            cur->Path.push_back({ver, 0});
            cout << "Path\n";
            // printPath(cur->Path);
            cout << "Cost :" << cur->Cost << endl;
            return;
        }

        for (int i = 0; i < n; i++) {
            if (cur->Matrix[ver][i] != INT_MAX) {
                Node * child = newNode(cur->Matrix, cur->Path, cur->Level + 1, ver, i);
                child->Cost = cur->Cost +  cur->Matrix[ver][i] + cost_calculation(cur->Matrix);
                cout << child->Cost << " " << i << endl;
                pq.push(child);
            }
        }
        cout << endl;
        delete cur;
    }
}
int INF = INT_MAX;
int main() {
    vector<vector<int>> adj = {
        { INF, 20, 30, 10, 11 },
        { 15,  INF, 16,  4,  2 },
        { 3,   5,  INF, 2,  4 },
        { 19,   6,   18,   INF, 3 },
        { 16,   4,   7,   16, INF }
    };
    TSP(adj);
}
