#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <strings.h>

void main()
{
    int arr[100], n, i, choice;
    pid_t newpid, child;
    char buffer[25];

    // The main process starts
    printf("\n This is the main process - ");
    printf("\n Process Id -> %d", getpid());
    printf("\n Parent Id -> %d", getppid());
    printf("\n --------- MENU ---------");
    printf("\n 1. Normal Execution ");
    printf("\n 2. Zombie ");
    printf("\n 3. Orphan ");
    printf("\n Enter your choice - ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        // Fork System call
        printf("\n Forking the process - ");
        newpid = fork();

        if (newpid == -1)
        {
            printf("\n Unfortunately the child was not born");
        }
        else if (newpid == 0)
        {
            // Inside child process
            printf("\nHello from the child process !\n");
            snprintf(buffer, 25, "ps -elf | grep %d", getpid());
            system(buffer);
            printf("child executed successfully\n");
        }
        else
        {
            // Inside parent process
            int status;
            child = wait(&status);
            if (child != -1)
            {
                printf("\nWaited for child with pid %d\n", child);
            }
            printf("\n Hello from the parent process !");
            snprintf(buffer, 25, "ps -elf | grep %d", getpid());
            system(buffer);
            printf("parent executed successfully\n");
        }
        break;
    case 2:
        // Fork System call
        printf("Forking the process - \n");
        newpid = fork();

        if (newpid == -1)
            printf("Unfortunately the child was not born\n");
        else if (newpid == 0)
        {
            // Inside child process
            printf("Hello from the child process !\n");
            snprintf(buffer, 25, "ps -elf | grep %d", getpid());
            system(buffer);
            printf("Child executed successfully\n");
            printf("child is now in zombie state\n");
        }
        else
        {
            // Inside parent process
            sleep(10);
            printf("Hello from the parent process !\n");
            snprintf(buffer, 25, "ps -elf | grep %d", newpid);
            system(buffer);
            printf("Parent executed successfully \n");
            wait(NULL);
            exit(0);
        }
        break;
    case 3:
        // Fork System call
        printf("\n Forking the process - ");
        newpid = fork();
        if (newpid == -1)
            printf("\n Unfortunately the child was not born");
        else if (newpid == 0)
        {
            // Inside child process
            printf("Hello from the child process : %d\n", getpid());
            sleep(10);
            snprintf(buffer, 25, "ps -l | grep %d", getpid());
            system(buffer);
            printf("\nchild executed successfully\n");
        }
        else
        {
            // Inside parent process
            printf("Hello from the parent process !\n");
            printf("parent executeed successfully\n");
            snprintf(buffer, 25, "ps -l | grep %d", getpid());
            system(buffer);
            printf("parent died , child is now orphan\n");
            exit(0);
        }
        break;
    default:
        printf("\n OOPS! INVALID INPUT");
    }
}
