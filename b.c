#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int a[10], i, n;
    char *buffer[10];
    for (int i = 0; i < 10; i++)
    {
        buffer[i] = (char *)(malloc(20));
    }
    printf("enter no of elements :");
    scanf("%d", &n);
    printf("enter array elements :: ");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }

    int pid = fork();
    if (pid == 0)
    {
        printf("hello from child process %d", getpid());

        buffer[0] = "./okk";
        for (int i = 0; i < n; i++)
        {
            sprintf(buffer[i + 1], "%d", a[i]);
        }
        buffer[n + 2] = NULL;
        execv("./okk", buffer);
        printf("Error");
        printf("\nCHILD: I am dying now\n");
    }
    if (pid > 0)
    {
        sleep(5);
        system("wait");
        printf("\nparent terminated\n");
    }
}