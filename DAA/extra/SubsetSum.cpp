#include <bits/stdc++.h>
using namespace std;
void solve(int i, vector<int> &arr, vector<int> temp, vector<vector<int>> &ans, int target)
{
    if (target == 0)
    {
        ans.push_back(temp);
        return;
    }
    if (i == 0)
    {
        if (target == arr[0])
        {
            temp.push_back(arr[0]);
            ans.push_back(temp);
        }
        return;
    }
    if (target >= arr[i])
    {
        temp.push_back(arr[i]);
        solve(i - 1, arr, temp, ans, target - arr[i]);
        temp.pop_back();
    }
    solve(i - 1, arr, temp, ans, target);
    return;
}
int main()
{
    int n;
    cout << "Enter the no. of elements" << endl;
    cin >> n;
    vector<int> arr(n);
    vector<int> temp;
    vector<vector<int>> ans;
    int target = 30;
    cout << "Enter the elements" << endl;
    for (int i = 0; i < arr.size(); i++)
    {
        cin >> arr[i];
    }
    cout << "Enter the target" << endl;
    cin >> target;
    solve(n - 1, arr, temp, ans, target);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << "Solution No: " << i + 1 << endl;
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}
