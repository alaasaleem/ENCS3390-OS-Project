#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 10
#define MAX_PROCESSES 100

struct Process {
    char name[MAX_NAME_LENGTH];
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int priority;
};

void sjfScheduling(struct Process processes[], int numProcesses) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < numProcesses) {
        int shortestJobIndex = -1;
        int shortestJobBurstTime = __INT_MAX__;
        int start = currentTime;
        char* currentProcess = NULL;

        for (int i = 0; i < numProcesses; i++) {
            struct Process *process = &processes[i];

            if (process->remainingTime > 0 && process->arrivalTime <= currentTime) {
                if (process->burstTime < shortestJobBurstTime) {
                    shortestJobIndex = i;
                    shortestJobBurstTime = process->burstTime;
                }
            }
        }

        if (shortestJobIndex != -1) {
            struct Process *process = &processes[shortestJobIndex];
            process->remainingTime = 0;
            process->completionTime = currentTime + process->burstTime;
            process->turnaroundTime = process->completionTime - process->arrivalTime;
            process->waitingTime = process->turnaroundTime - process->burstTime;
            completedProcesses++;
            currentTime = process->completionTime;
            currentProcess = process->name;
        } else {
            currentTime++;
        }

        if (currentProcess != NULL) {
            printf("From %d to %d: %s\n", start, currentTime, currentProcess);
        }
    }
}

void roundRobinScheduling(struct Process processes[], int numProcesses, int timeQuantum) {
    int currentTime = 0;
    int completedProcesses = 0;
    int start = 0;
    while (completedProcesses < numProcesses) {
        for (int i = 0; i < numProcesses; i++) {
            struct Process *process = &processes[i];

            if (process->remainingTime > 0) {
                start = currentTime;
                int executionTime = (process->remainingTime > timeQuantum) ? timeQuantum : process->remainingTime;

                process->remainingTime -= executionTime;
                currentTime += executionTime;

                printf("From %d to %d: %s\n", start, currentTime, process->name);

                if (process->remainingTime == 0) {
                    process->completionTime = currentTime;
                    process->turnaroundTime = process->completionTime - process->arrivalTime;
                    process->waitingTime = process->turnaroundTime - process->burstTime;
                    completedProcesses++;
                }
            }
        }
    }
}

void priorityScheduling(struct Process processes[], int numProcesses) {
    int currentTime = 0;
    int completedProcesses = 0;
    char currentProcess[MAX_NAME_LENGTH] = "";
    int start = 0; // Added declaration of 'start' variable

    while (completedProcesses < numProcesses) {
        int highestPriority = -1;
        int highestPriorityIndex = -1;

        for (int i = 0; i < numProcesses; i++) {
            struct Process *process = &processes[i];

            if (process->arrivalTime <= currentTime && process->remainingTime > 0) {
                if (highestPriority == -1 || process->priority < highestPriority) {
                    highestPriority = process->priority;
                    highestPriorityIndex = i;
                }
            }
        }

        if (highestPriorityIndex == -1) {
            currentTime++;
            continue;
        }

        struct Process *process = &processes[highestPriorityIndex];
        if (strcmp(process->name, currentProcess) != 0) {
            if (strlen(currentProcess) > 0) {
                printf("From %d to %d: %s\n", start, currentTime, currentProcess);
            }
            start = currentTime;
            strcpy(currentProcess, process->name);
        }
        currentTime++;
        process->remainingTime--;

        if (process->remainingTime == 0) {
            printf("From %d to %d: %s\n", start, currentTime, currentProcess);
            process->completionTime = currentTime;
            process->turnaroundTime = process->completionTime - process->arrivalTime;
            process->waitingTime = process->turnaroundTime - process->burstTime;
            completedProcesses++;
            strcpy(currentProcess, "");
        }
    }
}

void printProcessTable(struct Process processes[], int numProcesses) {
    printf("\nProcess Table:\n");
    printf("+----+------------+--------------+---------+\n");
    printf("| ID | Burst Time | Arrival Time | Priority|\n");
    printf("|    |            |              |         |\n");
    printf("+----+------------+--------------+---------+\n");
    for (int i = 0; i < numProcesses; i++) {
        struct Process *process = &processes[i];
        printf("%-7s  %-12d  %-11d  %-7d \n", process->name, process->burstTime, process->arrivalTime, process->priority);
    }
    printf("+----+------------+--------------+---------+\n");
}

void printMetricsTable(struct Process processes[], int numProcesses) {
    printf("\nMetrics Table:\n");
    printf("+----+-----------------+------------------+--------------+\n");
    printf("| ID | Completion Time | Turnaround Time  | Waiting Time |\n");
    printf("|    |                 |                  |              |\n");
    printf("+----+-----------------+------------------+--------------+\n");

    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (int i = 0; i < numProcesses; i++) {
        struct Process *process = &processes[i];
        printf("%-7s  %-18d  %-17d  %-12d \n", process->name, process->completionTime, process->turnaroundTime, process->waitingTime);

        totalWaitingTime += process->waitingTime;
        totalTurnaroundTime += process->turnaroundTime;
    }

    double avgWaitingTime = (double)totalWaitingTime / numProcesses;
    double avgTurnaroundTime = (double)totalTurnaroundTime / numProcesses;

    printf("+----+-----------------+------------------+--------------+\n");
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}


int main() {
    int numProcesses;
    int timeQuantum;
    int algorithmChoice;

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    struct Process processes[MAX_PROCESSES];

    for (int i = 0; i < numProcesses; i++) {
        printf("\nProcess %d\n", i + 1);

        printf("Enter process name (up to %d characters): ", MAX_NAME_LENGTH - 1);
        scanf("%s", processes[i].name);

        printf("Enter arrival time: ");
        scanf("%d", &processes[i].arrivalTime);

        printf("Enter burst time: ");
        scanf("%d", &processes[i].burstTime);

        processes[i].remainingTime = processes[i].burstTime;

        printf("Enter priority: ");
        scanf("%d", &processes[i].priority);
    }

    printf("\nSelect scheduling algorithm:\n");
    printf("1. Shortest Job First (SJF)\n");
    printf("2. Round Robin (RR)\n");
    printf("3. Priority Scheduling (PS)\n");
    printf("Enter your choice: ");
    scanf("%d", &algorithmChoice);

    switch (algorithmChoice) {
        case 1:
            printProcessTable(processes, numProcesses);
            printf("\nThe order in which processes or threads are selected for execution:\n");
            sjfScheduling(processes, numProcesses);
            printMetricsTable(processes, numProcesses);
            break;
        case 2:
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &timeQuantum);
            printProcessTable(processes, numProcesses);
            printf("\nThe order in which processes or threads are selected for execution:\n");
            roundRobinScheduling(processes, numProcesses, timeQuantum);
            printMetricsTable(processes, numProcesses);
            break;
        case 3:
            printProcessTable(processes, numProcesses);
            printf("\nThe order in which processes or threads are selected for execution:\n");
            priorityScheduling(processes, numProcesses);
            printMetricsTable(processes, numProcesses);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }


    return 0;
}
