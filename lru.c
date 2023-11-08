#include <stdio.h>

void fifo(int a[], int n, int no)
{
    printf("FIFO\n");

    int i, j, frame[10], k, avail, count = 0;

    for (i = 0; i < no; i++)
    {
        frame[i] = -1;
    }
    char f1[10][50];
    int u = 0;
    char hits[50];

    j = 0;
    for (i = 1; i <= n; i++)
    {
        avail = 0;
        for (k = 0; k < no; k++)
        {
            if (frame[k] == a[i])
            {
                avail = 1;
            }
        }
        if (avail == 0)
        {
            frame[j] = a[i];
            j = (j + 1) % no;
            count++;
            hits[u] = 'M';
        }
        else
        {
            hits[u] = 'H';
        }
        for (k = 0; k < no; k++)
        {
            f1[u][k] = (char)(frame[k] + '0');
        }
        u++;
    }
    for (int j = 0; j < no; j++)
    {
        printf("frame %d :: ", j);
        for (int i = 0; i < n; i++)
        {
            printf("%c | ", f1[i][j]);
        }
        printf("\n");
    }
    printf("\t   ");
    for (int i = 0; i < n; i++)
    {
        printf("%c | ", hits[i]);
    }
    printf("\n");
    printf("Page Fault is %d:", count);
}

void optimal(int a[], int n, int no)
{
    printf("OPTIMAL\n");

    int i, j, frame[10], k, avail, count = 0;

    for (i = 0; i < no; i++)
    {
        frame[i] = -1;
    }
    j = 0;
    char f1[10][50];
    int u = 0;
    char hits[50];
    for (i = 1; i <= n; i++)
    {
        avail = 0;
        for (k = 0; k < no; k++)
        {
            if (frame[k] == a[i])
            {
                avail = 1;
                break;
            }
        }
        if (avail == 0)
        {
            int tm[no];
            for (int x = 0; x < no; x++)
            {
                tm[x] = n + 1;
            }

            for (int j = i + 1; j <= n; j++)
            {
                for (int x = 0; x < no; x++)
                {
                    if (a[j] == frame[x])
                    {
                        if (tm[x] > j)
                        {
                            tm[x] = j;
                        }
                    }
                }
            }
            int y = -1, z = 0;
            for (int x = 0; x < no; x++)
            {
                if (tm[x] > z)
                {
                    z = tm[x];
                    y = x;
                }
            }

            frame[y] = a[i];
            count++;
            for (k = 0; k < no; k++)
            {
                f1[u][k] = (char)(frame[k] + '0');
            }
            hits[u] = 'M';
        }
        else
        {
            for (k = 0; k < no; k++)
            {
                f1[u][k] = (char)(frame[k] + '0');
            }
            hits[u] = 'H';
        }
        u++;
    }
    for (int j = 0; j < no; j++)
    {
        printf("frame %d :: ", j);
        for (int i = 0; i < n; i++)
        {
            printf("%c | ", f1[i][j]);
        }
        printf("\n");
    }
    printf("\t   ");
    for (int i = 0; i < n; i++)
    {
        printf("%c | ", hits[i]);
    }
    printf("\n");
    printf("Page Fault is : %d", count);
}
void lru(int a[], int n, int no)
{
    printf("LRU\n");
    int i, j, frame[10], k, avail, count = 0;

    for (i = 0; i < no; i++)
    {
        frame[i] = -1;
    }
    int time[10];
    for (int i = 0; i < 10; i++)
    {
        time[i] = 1000;
    }
    j = 0;
    char f1[10][50];
    int u = 0;
    char hits[50];
    for (i = 1; i <= n; i++)
    {
        avail = 0;
        int lru = -1, mt = 0;
        for (k = 0; k < no; k++)
        {
            if (frame[k] == a[i])
            {
                avail = k + 1;
                time[k] = 1;
                break;
            }
            if (time[k] > mt)
            {
                mt = time[k];
                lru = k;
            }
        }
        if (avail == 0)
        {
            frame[lru] = a[i];
            time[lru] = 1;
            j = (j + 1) % no;
            count++;
            for (k = 0; k < no; k++)
            {
                f1[u][k] = (char)(frame[k] + '0');
            }
            for (k = 0; k < no; k++)
            {
                if (k != lru)
                {
                    time[k]++;
                }
            }
            hits[u] = 'M';
        }
        else
        {
            hits[u] = 'H';
            for (k = 0; k < no; k++)
            {
                if (k != avail - 1)
                {
                    time[k]++;
                }
            }
            for (k = 0; k < no; k++)
            {
                f1[u][k] = (char)(frame[k] + '0');
            }
        }
        u++;
    }
    for (int j = 0; j < no; j++)
    {
        printf("frame %d :: ", j);
        for (int i = 0; i < n; i++)
        {
            printf("%c | ", f1[i][j]);
        }
        printf("\n");
    }
    printf("\t   ");
    for (int i = 0; i < n; i++)
    {
        printf("%c | ", hits[i]);
    }
    printf("\n");
    printf("Page Fault is : %d", count);
}

int main()
{
    int n, i, a[50], no;
    printf("\n ENTER THE NUMBER OF PAGES:\n");
    scanf("%d", &n);
    printf("\n ENTER THE PAGE NUMBER :\n");
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("\n ENTER THE NUMBER OF FRAMES :\n");
    scanf("%d", &no);

    int ch;
    scanf("%d", &ch);
    if (ch == 1)
    {
        fifo(a, n, no);
    }
    else if (ch == 2)
    {
        lru(a, n, no);
    }
    else
    {

        optimal(a, n, no);
    }
    return 0;
}