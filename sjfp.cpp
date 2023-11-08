#include <bits/stdc++.h>
using namespace std;

struct process
{
    int id; // process id
    int aT; // arrival time
    int bT; // burst time
    int cT; // completion time
    int rT; // remaining time

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

void sjfp(int n, vector<process> pro)
{
    // // int n;
    // // // cout << "Enter number of processes :: ";
    // // cin >> n;

    // // vector<process> pro(n);

    // for (int i = 0; i < n; i++)
    // {
    //     pro[i].id = i + 1;
    //     // cout << "Enter Arrival time & burst time for process " << i + 1 << endl;
    //     cin >> pro[i].aT >> pro[i].bT;
    //     pro[i].rT = pro[i].bT;
    // }

    sort(pro.begin(), pro.end());

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
            if (gnT.size() && gnT.back().first == -1)
            {
                gnT.back().second++;
            }
            else
            {
                gnT.push_back({-1, 1});
            }
        }
        else
        {
            pro[sindex].rT--;
            ct++;
            if (gnT.size() && gnT.back().first == pro[sindex].id)
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

void rr(int n, vector<process> pro, int timeQ)
{
    // std::cout << "Enter number of processes :: ";
    // int n;
    // std::cin >> n;

    // vector<process> pro(n);

    // for (int i = 0; i < n; i++)
    // {
    //     pro[i].id = i + 1;
    //     std::cout << "Enter Arrival time & burst time for process " << i + 1 << endl;
    //     cin >> pro[i].aT >> pro[i].bT;
    //     pro[i].rT = pro[i].bT;
    // }

    sort(pro.begin(), pro.end());
    // for (int i = 0; i < n; i++)
    // {
    //     std::cout << pro[i].id << " ";
    // }
    // cout << endl;
    // int timeQ;
    // std::cout << ("Enter time Quantum :: ");
    // std::cin >> timeQ;
    // cout << endl;
    int cT = 0;
    // int j = 0;
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
        cout << "Ready Queue at time " << t << " :: [";
        while (!q1.empty())
        {
            process tp = q1.front();
            cout << tp.id;
            if (q1.size() > 1)
            {
                cout << ",";
            }
            q1.pop();
        }
        cout << "]" << endl;
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
        if (q.empty())
        {
            cT++;

            if (gnT.size() > 0 && gnT.back().first == -1)
            {
                gnT.back().second += 1;
            }
            else
            {
                gnT.push_back({-1, 1});
            }
            for (int i = 0; i < n; i++)
            {
                if (!inq[i] && pro[i].aT <= cT)
                {
                    q.push(pro[i]);
                    inq[i] = 1;
                }
            }
            continue;
        }
        process top = q.front();
        q.pop();
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
        cout << "|";
    }
    cout << endl;
}

void sjfnp(int N, vector<process> pro)
{
    // int N;
    // cin >> N;
    // vector<process> pro(N);

    for (int i = 0; i < N; i++)
    {
        cin >> pro[i].aT >> pro[i].bT;
        pro[i].cT = pro[i].bT;
        pro[i].rT = pro[i].bT;
        pro[i].id = i + 1;
    }

    sort(pro.begin(), pro.end());
    vector<int> comOn(N), wt(N), tt(N);
    vector<pair<int, int> > gnT;

    int currentTime = 0;
    for (int i = 0; i < N; i++)
    {
        if (pro[i].aT > currentTime)
        {
            currentTime = pro[i].aT;
        }
        int shortestIndex = i;

        for (int j = i; j < N; j++)
        {
            if (pro[j].aT <= currentTime && pro[shortestIndex].bT > pro[j].bT)
            {
                shortestIndex = j;
            }
        }

        process tmp = pro[i];
        pro[i] = pro[shortestIndex];
        pro[shortestIndex] = tmp;
        gnT.push_back({pro[i].id, pro[i].bT});
        currentTime += pro[i].bT;
        comOn[pro[i].id - 1] = currentTime;
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
    int timeQ;
    cin >> timeQ;

    // while (1)
    // {
    //     cout << "1) SJF P\n2) SJF NP\n3)RR\n";
    //     cout << "choice ::";
    //     int c;
    //     cin >> c;
    //     if (c == 1)
    //     {
    //         sjfp(n, pro);
    //     }
    //     if (c == 2)
    //     {
    //         sjfnp(n, pro);
    //     }
    //     if (c == 3)
    //     {
    rr(n, pro, timeQ);
    //     }
    // }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1; //  cin >> T;
    while (T--)
        _solve();
    return 0;
}
