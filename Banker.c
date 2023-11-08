#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define mp 10
#define mr 10

int allocation[mp][mr];
int maxneed[mp][mr];
int remneed[mp][mr];

int p, r;
int tot[mr];
int cur_available[mr];
int ca[mr];
int safe[mp];
int vis[mp];

void inp(int a[][mr])
{
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
}

int ind = 0;

void printSafe()
{
    printf("Safe Sequence : ");
    for (int i = 0; i < p; i++)
    {
        printf("P%d", safe[i]);
        if (i != p - 1)
        {
            printf("->");
        }
    }
    printf("\n");
}

void Banker()
{
    printf("Enter number of processes :");
    scanf("%d", &p);
    printf("Enter number of resources :");
    scanf("%d", &r);

    printf("Enter process details\n");
    printf("Enter allocation\n");
    inp(allocation);
    printf("Enter maxneed\n");
    inp(maxneed);

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < r; j++)
        {
            remneed[i][j] = maxneed[i][j] - allocation[i][j];
        }
    }

    // printf("Enter total available resources\n");
    for (int i = 0; i < r; i++)
    {
        scanf("%d", &tot[i]);
    }

    for (int i = 0; i < r; i++)
    {
        int z = 0;
        for (int j = 0; j < p; j++)
        {
            z += allocation[j][i];
        }
        if (tot[i] < z)
        {
            printf("System is not in Safe mode\n");
            return;
        }
        cur_available[i] = tot[i] - z;
        ca[i] = cur_available[i];
    }

    while (true)
    {
        bool changed = false;
        for (int i = 0; i < p; i++)
        {
            if (vis[i] == true)
            {
                continue;
            }
            bool found = true;
            for (int j = 0; j < r; j++)
            {
                if (cur_available[j] < remneed[i][j])
                {
                    found = false;
                    break;
                }
            }

            if (found == true)
            {
                vis[i] = true;
                safe[ind++] = i;
                for (int j = 0; j < r; j++)
                {
                    cur_available[j] += allocation[i][j];
                }
                changed = true;
            }
        }

        if (changed == false)
        {
            printf("System is not in Safe mode\n");
            return;
        }
        if (ind == p)
        {
            printf("System is in Safe mode\n");
            break;
        }
    }

    printSafe();
}

void request(int pro_id, int req[mr])
{
    for (int i = 0; i < mp; i++)
    {
        safe[i] = -1;
        vis[i] = 0;
    }
    int NewCurentA[mr];
    for (int i = 0; i < mr; i++)
    {
        NewCurentA[i] = ca[i];
    }

    ind = 0;
    for (int i = 0; i < r; i++)
    {
        if (ca[i] < req[i])
        {
            printf("System is not in Safe mode\n");
            return;
        }
        NewCurentA[i] += allocation[pro_id][i];
    }
    safe[ind++] = pro_id;
    vis[pro_id] = 1;

    while (true)
    {
        bool changed = false;
        for (int i = 0; i < p; i++)
        {
            if (vis[i] == true)
            {
                continue;
            }
            bool found = true;
            for (int j = 0; j < r; j++)
            {
                if (NewCurentA[j] < remneed[i][j])
                {
                    found = false;
                    break;
                }
            }

            if (found == true)
            {
                vis[i] = true;
                safe[ind++] = i;
                for (int j = 0; j < r; j++)
                {
                    NewCurentA[j] += allocation[i][j];
                }
                changed = true;
            }
        }

        if (changed == false)
        {
            printf("System is not in Safe mode\n");
            return;
        }
        if (ind == p)
        {
            printf("System is in Safe mode\n");
            break;
        }
    }

    printSafe();
}

int main()
{
    Banker();
    // int px;
    // scanf("%d", &px);
    // int req[mr];
    // for (int i = 0; i < r; i++)
    // {
    //     scanf("%d", &req[i]);
    // }
    // request(px, req);
    return 0;
}
/*
5 3

0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

10 5 7

*/