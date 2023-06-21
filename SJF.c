#include <stdio.h>

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
};

void sjfScheduling(struct Process processes[], int numProcesses) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < numProcesses) {
        int shortestJobIndex = -1;
        int shortestJobBurstTime = __INT_MAX__;

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
        } else {
            currentTime++;
        }
    }
}

void printProcessTable(struct Process processes[], int numProcesses) {
    printf("\nProcess Table:\n");
    printf("+----+------------+--------------+\n");
    printf("| ID | Burst Time | Arrival Time |\n");
    printf("|    |            |              |\n");
    printf("+----+------------+--------------+\n");
    for (int i = 0; i < numProcesses; i++) {
        struct Process *process = &processes[i];
        printf(" %-7s  %-10d  %-9d \n", process->name, process->burstTime, process->arrivalTime);
    }
    printf("+----+------------+--------------+\n");
}

void printMetricsTable(struct Process processes[], int numProcesses) {
    printf("\nMetrics Table:\n");
    printf("+----+-----------------+-----------------+--------------+\n");
    printf("| ID | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("|    |                 |                 |              |\n");
    printf("+----+-----------------+-----------------+--------------+\n");
    for (int i = 0; i < numProcesses; i++) {
        struct Process *process = &processes[i];
        printf(" %-7s  %-15d  %-18d  %-12d \n", process->name, process->completionTime, process->turnaroundTime, process->waitingTime);
    }
    printf("+----+-----------------+-----------------+--------------+\n");
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

        process->remainingTime = process->burstTime;
    }

    printf("\nProcess scheduling started...\n");
    sjfScheduling(processes, numProcesses);

    printProcessTable(processes, numProcesses);
    printMetricsTable(processes, numProcesses);

    return 0;
}
