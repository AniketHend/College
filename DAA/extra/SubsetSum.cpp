void solve(int i, int target, vector<int>&a, std::vector<int>arr, std::vector<vector<int>> &ans) {
    if (!target) {
        ans.push_back(arr);
        return;
    }
    if (i >= a.size()) {
        return;
    }
    arr.push_back(a[i]);
    solve(i + 1, target - a[i], a, arr, ans);
    arr.pop_back();
    solve(i + 1, target, a, arr, ans);
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a) {
        cin >> i;
    }

    int target;
    cin >> target;

    vector<vector<int>> ans;
    vector<int> temp;
    solve(0, target, a, temp, ans);
    if (ans.size() == 0) {
        cout << "No Subset found\n";
        return;
    }
    for (auto i : ans) {
        cout << "[";
        for (auto j : i) {
            cout << j << " ";
        }
        cout << "]\n";
    }
}
