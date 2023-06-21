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
        printf("| %-2s | %-10d | %-9d | %-7d |\n", process->name, process->burstTime, process->arrivalTime, process->priority);
    }
    printf("+----+------------+--------------+---------+\n");
}

void printMetricsTable(struct Process processes[], int numProcesses) {
    printf("\nMetrics Table:\n");
    printf("+----+-----------------+------------------+--------------+\n");
    printf("| ID | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("|    |                 |                  |              |\n");
    printf("+----+-----------------+------------------+--------------+\n");
    for (int i = 0; i < numProcesses; i++) {
        struct Process *process = &processes[i];
        printf("| %-2s | %-15d | %-16d | %-12d |\n", process->name, process->completionTime, process->turnaroundTime, process->waitingTime);
    }
    printf("+----+-----------------+------------------+--------------+\n");
}

int main() {
    int numProcesses;
    struct Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter process details:\n");
    for (int i = 0; i < numProcesses; i++) {
        struct Process *process = &processes[i];
        printf("Process %d:\n", i + 1);

        printf("Enter process name: ");
        scanf("%s", process->name);

        printf("Enter arrival time: ");
        scanf("%d", &process->arrivalTime);

        printf("Enter burst time: ");
        scanf("%d", &process->burstTime);

        printf("Enter priority: ");
        scanf("%d", &process->priority);

        process->remainingTime = process->burstTime;
    }

    printf("\nProcess scheduling started...\n");
    priorityScheduling(processes, numProcesses);

    printProcessTable(processes, numProcesses);
    printMetricsTable(processes, numProcesses);

    return 0;
}