#include <bits/stdc++.h>
using namespace std;

#define N 5
#define INF INT_MAX

class Node
{
public:
    vector<pair<int, int>> path;
    vector<vector<int>> b;
    int cost;
    int vertex;
    int lvl;
};

Node* newNode(vector<vector<int>>&par, vector<pair<int, int>> const &path, int lvl, int i, int j) {
    Node* node = new Node;
    node->path = path;
    if (lvl != 0) {
        node->path.push_back({i, j});
    }
    node->b = par;
    for (int k = 0; lvl != 0 && k < N; k++) {
        node->b[i][k] = INF;
        node->b[k][j] = INF;
    }

    node->b[j][0] = INF;
    node->lvl = lvl;
    node->vertex = j;
    return node;
}

void red_row(vector<vector<int>>&b, vector<int>&row) {
    row.assign(N, INF);

    for (int i = 0; i < N; i++) {
        row[i] = *min_element(b[i].begin(), b[i].end());
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (b[i][j] != INF && row[i] != INF) {
                b[i][j] -= row[i];
            }
        }
    }
}

void red_col(vector<vector<int>>&b, vector<int>&col) {
    col.assign(N, INF);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (b[i][j] < col[j]) {
                col[j] = b[i][j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (b[i][j] != INF && col[j] != INF) {
                b[i][j] -= col[j];
            }
        }
    }
}

int cost_cal(vector<vector<int>>&b) {
    int cost = 0;
    vector<int> row, col;
    red_row(b, row);
    red_col(b, col);

    for (int i = 0; i < N; i++) {
        cost += (row[i] != INT_MAX) ? row[i] : 0;
        cost += (col[i] != INT_MAX) ? col[i] : 0;
    }

    return cost;
}

void printPath(vector<pair<int, int>> const &list) {
    for (int i = 0; i < list.size(); i++) {
        cout << list[i].first + 1 << " -> " << list[i].second + 1 << endl;
    }
}

class comp {
public:
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->cost > rhs->cost;
    }
};

int solve(vector<vector<int>>&adj) {
    priority_queue<Node*, std::vector<Node*>, comp> pq;
    vector<pair<int, int>> v;
    Node* root = newNode(adj, v, 0, -1, 0);
    root->cost = cost_cal(root->b);

    pq.push(root);
    while (!pq.empty()) {
        Node* cur = pq.top();
        pq.pop();
        int i = cur->vertex;

        if (cur->lvl == N - 1) {
            cur->path.push_back(make_pair(i, 0));
            printPath(cur->path);
            return cur->cost;
        }

        for (int j = 0; j < N; j++) {
            if (cur->b[i][j] != INF) {
                Node* child = newNode(cur->b, cur->path, cur->lvl + 1, i, j);
                child->cost = cur->cost + cur->b[i][j] + cost_cal(child->b);
                pq.push(child);
            }
        }

        delete cur;
    }
}

int main() {
    vector<vector<int>> adj = {
        { INF, 20, 30, 10, 11 },
        { 15,  INF, 16,  4,  2 },
        { 3,   5,  INF, 2,  4 },
        { 19,   6,   18,   INF, 3 },
        { 16,   4,   7,   16, INF }
    };
    cout << "\nCost is " << solve(adj);
    return 0;
}
