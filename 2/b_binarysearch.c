#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int v;
void bs(long int a[], int n)
{
    printf("enter element to be search :: ");
    scanf("%d", &v);
    int ok = 0;
    int ng = n - 1, mid;

    while (ok <= ng)
    {
        mid = (ok + ng) / 2;
        if (a[mid] == v)
        {
            printf("element found at index %d\n", mid);
            return;
        }
        else if (a[mid] > v)
        {
            ng = mid - 1;
        }
        else
        {
            ok = mid + 1;
        }
    }
    printf("element is not present in the array\n");
}

void main(int argc, char *argv[])
{
    int i, n = 0, v;
    long ret[10];
    n = 0;
    for (i = 1; argv[i] != NULL; i++)
    {
        ret[i - 1] = strtol(argv[i], NULL, 10);
        n++;
    }
    n--;
    printf("bs : In second child process. My process-id is %d.\n", getpid());
    printf("bs : My parent's process-id is %d.\n", getppid());

    for (int i = 0; i < n; i++)
    {
        printf("%ld ", ret[i]);
    }
    printf("\n");
    bs(ret, n);
}
