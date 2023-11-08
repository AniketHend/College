#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#include "./debug.h"
#else
#define debug(...) "(0_0)"
#endif

#define int long long

void fcfs(int se, vector<int> &disks)
{
    int tm = 0;
    int p = se;

    cout << "Sequence :: ";
    for (int i = 0; i < disks.size(); i++)
    {
        cout << disks[i] << " ";
        tm += abs(p - disks[i]);
        p = disks[i];
    }
    cout << endl;
    cout << "Total Time required :: " << tm << endl;
}

void sstf(int se, vector<int> &disks)
{
    vector<int> a = disks;

    int tm = 0;
    int p = se;
    int n = disks.size();
    vector<int> vis(n, 0);
    int com = 0;
    cout << "Sequence :: ";
    while (com < n)
    {
        int j = -1;
        int t = 1e9;
        for (int i = 0; i < n; i++)
        {
            if (vis[i] == 0)
            {
                if (abs(a[i] - p) < t)
                {
                    t = abs(a[i] - p);
                    j = i;
                }
            }
        }
        cout << a[j] << " ";
        vis[j] = 1;
        tm += abs(a[j] - p);
        p = a[j];
        com++;
    }
    cout << endl;
    cout << "Total Time required :: " << tm << endl;
}

void scan(int sp, vector<int> a, int fe, int se)
{
    int n = a.size();
    sort(a.begin(), a.end());
    debug(a);
    if (sp - fe < se - sp)
    {
        int index = -1;
        for (int i = 0; i < n; i++)
        {
            if (a[i] <= sp)
                index = i;
        }
        debug(a);
        debug(index);
        if (index == -1)
        {
            int tm = 0;
            cout << "Sequence :: ";
            int p = sp;
            for (int i = 0; i < n; i++)
            {
                tm += a[i] - p;
                cout << a[i] << " ";
                p = a[i];
            }
            cout << endl;
        }
        else
        {
            int tm = 0;
            cout << "Sequence :: ";
            int p = sp;
            for (int i = index; i >= 0; i--)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            tm += p;
            p = 0;
            for (int i = index + 1; i < n; i++)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            cout << endl;
            cout << "Total Time required :: " << tm << endl;
        }
    }
    else
    {
        int index = -1;
        for (int i = 0; i < n; i++)
        {
            if (a[i] < sp)
                index = i;
        }
        debug(a);
        debug(index);
        if (index == n - 1)
        {
            int tm = 0;
            cout << "Sequence :: ";
            int p = sp;
            for (int i = n - 1; i >= 0; i--)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            cout << endl;
        }
        else
        {
            index++;
            int tm = 0;
            cout << "Sequence :: ";
            int p = sp;
            for (int i = index; i < n; i++)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            tm += se - p;
            p = se;
            for (int i = index - 1; i >= 0; i--)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            cout << endl;
            cout << "Total Time required :: " << tm << endl;
        }
    }
}

void cscan(int sp, vector<int> a, int fe, int se)
{
    int n = a.size();
    sort(a.begin(), a.end());

    if (sp - fe < se - sp)
    {
        int index = -1;
        for (int i = 0; i < n; i++)
        {
            if (a[i] <= sp)
                index = i;
        }
        debug(a);
        debug(index);
        if (index == -1)
        {
            int tm = 0;
            cout << "Sequence :: ";
            int p = sp;
            for (int i = 0; i < n; i++)
            {
                tm += a[i] - p;
                cout << a[i] << " ";
                p = a[i];
            }
            cout << endl;
        }
        else
        {
            int tm = 0;
            cout << "Sequence :: " << sp << " ";
            int p = sp;
            for (int i = index; i >= 0; i--)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            tm += p - fe;
            // tm += se - fe;
            cout << fe << " ";
            cout << se << " ";
            p = se;
            for (int i = n - 1; i > index; i--)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            cout << endl;
            cout << "Total Time required :: " << tm << endl;
        }
    }
    else
    {
        int index = -1;
        for (int i = 0; i < n; i++)
        {
            if (a[i] < sp)
                index = i;
        }
        debug(a);
        debug(index);
        if (index == n - 1)
        {
            int tm = 0;
            cout << "Sequence :: ";
            int p = sp;
            for (int i = n - 1; i >= 0; i--)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            cout << endl;
        }
        else
        {
            index++;
            int tm = 0;
            cout << "Sequence :: " << sp << " ";
            int p = sp;
            for (int i = index; i < n; i++)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            tm += se - p;
            cout << se << " ";
            cout << fe << " ";
            p = fe;
            for (int i = 0; i < index; i++)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            cout << endl;
            cout << "Total Time required :: " << tm << endl;
        }
    }
}
void clook(int sp, vector<int> a)
{
    int n = a.size();
    sort(a.begin(), a.end());
    int fe = a[0];
    int se = a[n - 1];
    if (sp - fe < se - sp)
    {
        int index = -1;
        for (int i = 0; i < n; i++)
        {
            if (a[i] < sp)
                index = i;
        }
        debug(a);
        debug(index);
        if (index == -1)
        {
            int tm = 0;
            cout << "Sequence :: ";
            int p = sp;
            for (int i = 0; i < n; i++)
            {
                tm += a[i] - p;
                cout << a[i] << " ";
                p = a[i];
            }
            cout << endl;
        }
        else
        {
            int tm = 0;
            cout << "Sequence :: " << sp << " ";
            int p = sp;
            for (int i = index; i >= 0; i--)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            tm += p - fe;
            // tm += se - fe;
            cout << fe << " ";
            cout << se << " ";
            p = se;
            for (int i = n - 1; i > index; i--)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            cout << endl;
            cout << "Total Time required :: " << tm << endl;
        }
    }
    else
    {
        int index = -1;
        for (int i = 0; i < n; i++)
        {
            if (a[i] < sp)
                index = i;
        }
        debug(a);
        debug(index);
        if (index == n - 1)
        {
            int tm = 0;
            cout << "Sequence :: ";
            int p = sp;
            for (int i = n - 1; i >= 0; i--)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            cout << endl;
        }
        else
        {
            index++;
            int tm = 0;
            cout << "Sequence :: " << sp << " ";
            int p = sp;
            for (int i = index; i < n; i++)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            tm += se - p;
            cout << se << " ";
            cout << fe << " ";
            p = fe;
            for (int i = 0; i < index; i++)
            {
                tm += abs(a[i] - p);
                cout << a[i] << " ";
                p = a[i];
            }
            cout << endl;
            cout << "Total Time required :: " << tm << endl;
        }
    }
}

void _solve()
{
    int N;
    cin >> N;
    vector<int> d(N);
    for (auto &i : d)
        cin >> i;
    fcfs(50, d);
    sstf(50, d);
    scan(50, d, 0, 199);
    scan(144, d, 0, 199);
    cscan(50, d, 0, 199);
    cscan(144, d, 0, 199);
    clook(50, d);
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1; //  cin >> T;
    while (T--)
        _solve();
}
