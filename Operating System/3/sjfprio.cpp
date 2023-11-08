#include <bits/stdc++.h>
using namespace std;

struct process
{
    int id;
    int aT;
    int bT;
    int rT;
    int cT;
    int P;

    bool operator<(process &oth)
    {
        if (oth.aT == aT)
        {
            return P > oth.P;
        }
        return aT < oth.aT;
    }
};

int getIndex(int ct, vector<process> &pro)
{
    int j = -1, mt = 1e9;
    for (int i = 0; i < pro.size(); i++)
    {
        if (pro[i].aT <= ct && pro[i].rT > 0 && pro[i].P < mt)
        {
            mt = pro[i].P;
            j = i;
        }
    }
    return j;
}

void sjf_priority()
{
    int n;
    cin >> n;

    vector<process> pro(n);
    for (int i = 0; i < n; i++)
    {
        pro[i].id = i + 1;
        // cout << "Enter Arrival time & burst time & priority for process " << i + 1 << endl;
        cin >> pro[i].aT >> pro[i].P >> pro[i].bT;
        pro[i].rT = pro[i].bT;
    }

    int completed = 0;
    int ctime = 0;
    vector<pair<int, int> > gnT;

    while (completed < n)
    {
        int si = getIndex(ctime, pro);
        if (si == -1)
        {
            ctime++;
            if (gnT.size() > 0 && gnT.back().first == -1)
            {
                gnT.back().second += 1;
            }
            else
            {
                gnT.push_back({-1, 1});
            }
        }
        else
        {
            pro[si].rT--;
            ctime++;
            if (pro[si].rT == 0)
            {
                completed++;
            }
            if (gnT.size() > 0 && gnT.back().first == pro[si].id)
            {
                gnT.back().second += 1;
            }
            else
            {
                gnT.push_back({pro[si].id, 1});
            }
        }
    }
    cout << "Gantt Chart :: ";
    cout << "|";
    for (int i = 0; i < gnT.size(); i++)
    {
        for (int j = 0; j <= gnT[i].second / 2; j++)
        {
            cout << " ";
        }
        cout << " P" << gnT[i].first << "(" << gnT[i].second << ")";
        for (int j = 0; j <= gnT[i].second / 2; j++)
        {
            cout << " ";
        }
        cout << "|";
    }
    cout << endl;
}

int main()
{
    sjf_priority();
    return 0;
}
/*
5
0 3 3
1 2 4
2 4 6
3 6 4
5 10 2
*/
