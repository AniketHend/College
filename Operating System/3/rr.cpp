#include <bits/stdc++.h>
using namespace std;

#define int long long

struct process
{
    int id; // process id
    int aT; // arrival time
    int bT; // burst time
    int cT; // completion time
    int rT; // remaining time
    process()
    {
    }
    bool operator<(process &oth)
    {
        if (this->aT != oth.aT)
        {
            return this->aT < oth.aT;
        }
        else
        {
            return this->rT < oth.rT;
        }
    }
};

int getIndex(vector<process> &pro, int ct)
{
    int si = -1, sbt = 1e9, sat = 1e9;
    int j = 0;
    for (auto i : pro)
    {
        if (i.aT <= ct && i.rT > 0 && i.rT < sbt)
        {
            sbt = i.rT;
            sat = i.aT;
            si = j;
        }
        j++;
    }
    return si;
}

void sjfp()
{
    int n;
    // cout << "Enter number of processes :: ";
    cin >> n;

    vector<process> pro(n);

    for (int i = 0; i < n; i++)
    {
        pro[i].id = i + 1;
        // cout << "Enter Arrival time & burst time for process " << i + 1 << endl;
        cin >> pro[i].aT >> pro[i].bT;
        pro[i].rT = pro[i].bT;
    }

    sort(pro.begin(), pro.end());

    for (int i = 0; i < n; i++)
    {
        cout << pro[i].id << " " << pro[i].aT << " " << pro[i].bT << endl;
    }

    int com = 0;
    int cT[n + 1];
    int tT[n];
    int wT[n];

    int ct = 0;

    vector<pair<int, int> > gnT;
    while (com < n)
    {
        int sindex = getIndex(pro, ct);
        if (sindex == -1)
        {
            ct++;
            gnT.push_back({-1, 1});
        }
        else
        {
            pro[sindex].rT--;
            ct++;
            if (gnT.size() > 0 && gnT.back().first == pro[sindex].id)
            {
                gnT.back().second++;
            }
            else
            {
                gnT.push_back({pro[sindex].id, 1});
            }
            if (pro[sindex].rT == 0)
            {
                com++;
                cT[pro[sindex].id] = ct;
                pro[sindex].cT = ct;
            }
        }
    }
    cout << "Gantt Chart :: ";
    cout << "|";
    for (int i = 0; i < gnT.size(); i++)
    {
        cout << " P" << gnT[i].first << "(" << gnT[i].second << ")";
        for (int j = 0; j < gnT[i].second; j++)
        {
            cout << "  ";
        }
        cout << "|";
    }
    cout << endl;
}
void rr()
{
    int timeQ;
    std::cout << "Enter number of processes :: ";
    int n;
    std::cin >> n;

    vector<process> pro(n);

    for (int i = 0; i < n; i++)
    {
        pro[i].id = i + 1;
        std::cout << "Enter Arrival time & burst time for process " << i + 1 << endl;
        cin >> pro[i].aT >> pro[i].bT;
        pro[i].rT = pro[i].bT;
    }

    sort(pro.begin(), pro.end());
    for (int i = 0; i < n; i++)
    {
        std::cout << pro[i].id << " ";
    }
    cout << endl;
    std::cout << ("Enter time Quantum :: ");
    std::cin >> timeQ;
    cout << endl;
    int cT = 0;
    int j = 0;
    int completed = 0;
    int comOn[100];

    queue<process> q;

    auto display = [&](int t)
    {
        if (!q.size())
        {
            return;
        }
        queue<process> q1 = q;
        cout << "Ready Queue at time " << t << " :: ";
        while (!q1.empty())
        {
            process tp = q1.front();
            cout << tp.id << " | ";
            q1.pop();
        }
        cout << endl;
    };
    vector<int> inq(n);
    for (int i = 0; i < n; i++)
    {
        if (pro[i].aT <= cT)
        {
            q.push(pro[i]);
            inq[i] = 1;
        }
    }
    vector<pair<int, int> > gnT;

    while (completed < n)
    {
        process top = q.front();
        q.pop();
        if (top.bT == -1)
        {
            cT++;
            continue;
        }
        int e = 0;
        if (top.rT > timeQ)
        {
            top.rT -= timeQ;
            cT += timeQ;
            e += timeQ;
        }
        else
        {
            cT += top.rT;
            comOn[top.id] = cT;
            completed++;
            e += top.rT;
            top.rT = 0;
        }
        if (gnT.size() > 0 && gnT.back().first == top.id)
        {
            gnT.back().second += e;
        }
        else
        {
            gnT.push_back({top.id, e});
        }

        for (int i = 0; i < n; i++)
        {
            if (!inq[i] && pro[i].aT <= cT)
            {
                q.push(pro[i]);
                inq[i] = 1;
            }
        }
        if (top.rT > 0)
        {
            q.push(top);
        }
        display(cT);
        if (completed == n)
        {
            break;
        }
    }
    cout << "Gantt Chart :: ";
    cout << "|";
    for (int i = 0; i < gnT.size(); i++)
    {
        cout << " P" << gnT[i].first << "(" << gnT[i].second << ")";
        for (int j = 0; j < gnT[i].second; j++)
        {
            cout << "  ";
        }
        cout << "|";
    }
    cout << endl;
}

void _solve()
{
    rr();
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1; //  cin >> T;
    while (T--)
        _solve();
    return 0;
}
