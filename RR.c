#########################################
#  Project#3: CPU Scheduling Simulator  #
# Ebaa Taleeb, Raha Zabade, Alaa Saleem #
#########################################
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

void roundRobinScheduling(struct Process processes[], int numProcesses, int timeQuantum) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < numProcesses) {
        for (int i = 0; i < numProcesses; i++) {
            struct Process *process = &processes[i];
            
            if (process->remainingTime > 0) {
                int executionTime = (process->remainingTime > timeQuantum) ? timeQuantum : process->remainingTime;
                
                process->remainingTime -= executionTime;
                currentTime += executionTime;
                
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

void printProcessTable(struct Process processes[], int numProcesses) {
    printf("\nProcess Table:\n");
    printf("+----+------------+-----------+\n");
    printf("| ID | Burst Time | Arrival   |\n");
    printf("|    |            | Time      |\n");
    printf("+----+------------+-----------+\n");
    for (int i = 0; i < numProcesses; i++) {
        struct Process *process = &processes[i];
        printf("| %-2s | %-10d | %-9d |\n", process->name, process->burstTime, process->arrivalTime);
    }
    printf("+----+------------+-----------+\n");
}

void printMetricsTable(struct Process processes[], int numProcesses) {
    printf("\nMetrics Table:\n");
    printf("+----+-------------+-----------------+--------------+\n");
    printf("| ID | Completion  | Turnaround Time | Waiting Time |\n");
    printf("|    | Time        |                 |              |\n");
    printf("+----+-------------+-----------------+--------------+\n");
    for (int i = 0; i < numProcesses; i++) {
        struct Process *process = &processes[i];
        printf("| %-2s | %-11d | %-15d | %-12d |\n", process->name, process->completionTime, process->turnaroundTime, process->waitingTime);
    }
    printf("+----+-------------+-----------------+--------------+\n");
}

int main() {
    int numProcesses, timeQuantum;
    struct Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);

    printf("Enter the time quantum for Round Robin: ");
    scanf("%d", &timeQuantum);

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
    roundRobinScheduling(processes, numProcesses, timeQuantum);

    printProcessTable(processes, numProcesses);
    printMetricsTable(processes, numProcesses);

    return 0;
}
