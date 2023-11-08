#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
};

struct queue
{
    struct Process arr[1000];
    int front = -1;
    int rear = -1;

    void push(struct Process num)
    {
        if (front == -1)
        {
            front++;
            rear++;
            arr[front] = num;
            rear++;
        }
        else
        {
            arr[rear++] = num;
        }
    }

    struct Process pop()
    {
        if (front == -1)
        {
            struct Process p;
            p.burstTime = -1;
            return p;
        }
        else if (front == rear)
        {
            struct Process tm = arr[front];
            front = -1;
            rear = -1;
            return tm;
        }
        else
        {
            return arr[front++];
        }
    }
};

void sortByArrivalTime(struct Process processes[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime)
            {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// process with less burst time cha index return karnyasathi
int findShortestJob(struct Process processes[], int n, int currentTime)
{
    int shortestJobIndex = -1;
    int shortestBurst = 99999;
    for (int i = 0; i < n; i++)
    {
        // 3 condition arrival current peksha kami kiva equal, remaining time zero peksha jast
        // ani remaining time shortest burst time peksha kami
        if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && processes[i].remainingTime < shortestBurst)
        {
            shortestJobIndex = i;
            shortestBurst = processes[i].remainingTime;
        }
    }
    return shortestJobIndex;
}

int sjfp()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].id);
        // nehmi scanf vapartana address patvaycha
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        // startingla remaining time = burst time saglya process sathi
        processes[i].remainingTime = processes[i].burstTime;
    }

    sortByArrivalTime(processes, n);

    int currentTime = 0;
    int completedProcesses = 0;
    int shortestJobIndex = -1;

    int completionTime[n];
    int turnaroundTime[n];
    int waitingTime[n];

    struct GanttEntry
    {
        struct Process process;
        int startTime;
    };
    struct GanttEntry ganttChart[n * 2]; // Max size (twice the number of processes)

    int ganttIndex = 0;
    ganttChart[ganttIndex].process = processes[0];
    ganttChart[ganttIndex].startTime = 0;
    ganttIndex++;

    while (completedProcesses < n)
    {
        //  Index kadaycha sj process cha
        shortestJobIndex = findShortestJob(processes, n, currentTime);
        // jr sj bhetlach nhi tr
        if (shortestJobIndex == -1)
        {
            currentTime++; // current time nehmi vadhvaycha
        }
        else
        {
            // shortestjob process ji bhetli tyach remaining timee kami karaycha
            processes[shortestJobIndex].remainingTime--;
            currentTime++; // ++ 
            // ekda process cha execution sampla ki completed process la increment ani completion time note thevaycha
            if (processes[shortestJobIndex].remainingTime == 0)
            {
                completedProcesses++;
                completionTime[shortestJobIndex] = currentTime;
            }
            if (ganttIndex == 0 || ganttChart[ganttIndex - 1].process.id != processes[shortestJobIndex].id)
            {
                ganttChart[ganttIndex].process = processes[shortestJobIndex];
                ganttChart[ganttIndex].startTime = currentTime - 1;
                ganttIndex++;
            }
        }
    }
    // tt=ct-at   and wt= tt-bt
    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;
    for (int i = 0; i < n; i++)
    {
        turnaroundTime[i] = completionTime[i] - processes[i].arrivalTime;
        waitingTime[i] = turnaroundTime[i] - processes[i].burstTime;
        totalTurnaroundTime += turnaroundTime[i];
        totalWaitingTime += waitingTime[i];
    }

    printf("\nGantt Chart:\n");
    for (int i = 0; i < ganttIndex; i++)
    {
        printf("P%d-%d ", ganttChart[i].process.id, ganttChart[i].startTime);
    }
    printf("\n");

    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, completionTime[i], turnaroundTime[i], waitingTime[i]);
    }

    double averageTurnaroundTime = (double)totalTurnaroundTime / n;
    double averageWaitingTime = (double)totalWaitingTime / n;

    printf("\nAverage Turnaround Time: %.2f\n", averageTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", averageWaitingTime);

    return 0;
};

int sjfnp()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].id);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        // startingla saglya processes cha completion time 0
        processes[i].completionTime = 0;
    }

    sortByArrivalTime(processes, n);

    int currentTime = 0;
    // current time = arrival time if arrival is greater than it
    for (int i = 0; i < n; i++)
    {
        if (processes[i].arrivalTime > currentTime)
        {
            currentTime = processes[i].arrivalTime;
        }

        int shortestJob = i;
        for (int j = i; j < n; j++)
        {
            // je processes current time chya aadhi aalet ani jya process cha bt kami it will
            // be selected as shortestjob
            if (processes[j].arrivalTime <= currentTime && processes[j].burstTime < processes[shortestJob].burstTime)
            {
                shortestJob = j;
            }
        }

        struct Process temp = processes[i];
        processes[i] = processes[shortestJob];
        processes[shortestJob] = temp;
        // ct = current time + bt
        // currenttime= new ct
        processes[i].completionTime = currentTime + processes[i].burstTime;
        currentTime = processes[i].completionTime;
    }

    int totalTurnaroundTime = 0;
    int totalWaitingTime = 0;

    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        int turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        int waitingTime = turnaroundTime - processes[i].burstTime;
        totalTurnaroundTime += turnaroundTime;
        totalWaitingTime += waitingTime;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, turnaroundTime, waitingTime);
    }

    double averageTurnaroundTime = (double)totalTurnaroundTime / n;
    double averageWaitingTime = (double)totalWaitingTime / n;

    printf("\nAverage Turnaround Time: %.2f\n", averageTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", averageWaitingTime);

    return 0;
};

int timeQ;
int n;
struct Process processes[100];
int ganT[1000];
void rr()
{
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].arrivalTime);
        scanf("%d", &processes[i].burstTime);
        processes[i].completionTime = 0;
    }

    printf("Enter time Quantum :: ");
    scanf("%d", &timeQ);

    sortByArrivalTime(processes, n);
    int cT = 0;
    int j = 0;
    int completed = 0;
    int comOn[100];

    queue q;

    for (int i = 0; i < n; i++)
    {
        if (processes[i].arrivalTime <= cT)
        {
            q.push(processes[i]);
        }
    }
    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].burstTime - timeQ >= 0)
            {
                processes[i].burstTime -= timeQ;
                for (int k = 0; k < timeQ; k++)
                {
                    ganT[j++] = processes[i].id;
                }
                cT += timeQ;

                if (processes[i].burstTime == 0)
                {
                    completed++;
                    comOn[processes[i].id] = cT;
                }
            }
            else if (processes[i].burstTime != 0)
            {
                cT += processes[i].burstTime;
                completed++;
                for (int k = 0; k < processes[i].burstTime; k++)
                {
                    ganT[j++] = processes[i].id;
                }
                processes[i].burstTime = 0;
                comOn[processes[i].id] = cT;
            }
        }

        if (completed == n)
        {
            break;
        }
    }
    printf("IDLE | ");
    for (int i = 0; i < cT; i++)
    {
        printf(" P%d  ", ganT[i]);
        if (i != cT - 1)
        {
            printf("|");
        }
    }
    printf("\n");
}

int main()
{
    while (1)
    {
        int choice;
        printf("Menu:\n");
        printf("1. SJF NonPreemptive\n");
        printf("2. SJF preemptive \n");
        printf("3. Round Robin\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            sjfnp();
            break;

        case 2:
            sjfp();
            break;

        case 3:
            rr();
            break;
        case 4:
            // Code for Exit
            printf("Exiting the program\n");
            // Add any cleanup code if needed
            return 0;
            break;

        default:
            printf("Invalid choice\n");
        }
        break;
    }
    return 0;
}
