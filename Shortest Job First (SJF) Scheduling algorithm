#########################################
#  Project#3: CPU Scheduling Simulator  #
# Ebaa Taleeb, Raha Zabade, Alaa Saleem #
#########################################

# Define a class "Process" to represent a process in the system
class Process:
    # Define constructor that initializes the attributes of the process object
    def __init__(self, name, arrival_time, burst_time): 
        self.name = name                       # assign the name of the process
        self.arrival_time = arrival_time       # assign the arrival_time of the process
        self.burst_time = burst_time           # assign the burst_time of the process


# Shortest Job First (SJF) Scheduling algorithm
def SJF(processes):
    # Sort the processes based on burst time (shortest job first)
    sorted_processes = sorted(processes, key=lambda x: x.burst_time)
    
    # Variables to keep track of total execution time, waiting times, and completion times
    total_execution_time = 0
    waiting_times = {}
    completion_times = {}
    gantt_chart = []
    
    print("\n\033[91mProcess Table:\033[0m")
    # Print the process table
    print("Process ID\tArrival Time\tBurst Time")
    for process in sorted_processes:
        print(f"{process.name}\t\t{process.arrival_time}\t\t{process.burst_time}")
    
    print("\n\033[91mGantt Chart:\033[0m")
    # Execute the processes in the sorted order
    for process in sorted_processes:
        waiting_time = total_execution_time - process.arrival_time
        completion_time = total_execution_time + process.burst_time
        turnaround_time = completion_time - process.arrival_time
        waiting_times[process.name] = waiting_time
        completion_times[process.name] = completion_time
        gantt_chart.append((process.name, total_execution_time, completion_time))
        
        total_execution_time += process.burst_time

    # Sort the Gantt chart entries based on the completion time
    sorted_gantt_chart = sorted(gantt_chart, key=lambda x: x[1])
    
    print("---------" * (len(sorted_gantt_chart) + 1))
    print("|", end="")
    for entry in sorted_gantt_chart:
        print(f"   {entry[0]}    |", end="")
    print()
    print("---------" * (len(sorted_gantt_chart) + 1))
    print(0, end="")
    cumulative_time = 0
    for entry in sorted_gantt_chart:
        cumulative_time = entry[2]
        print(f"--------{cumulative_time}", end="")
    print()

    print("\n\033[91mSummary Table:\033[0m")
    # Print the waiting times, completion times, and turnaround times in a table format
    print("Process ID\tCompletion Time\tTurnaround Time\tWaiting Time")
    for process in sorted_processes:
        print(f"{process.name}\t\t{completion_times[process.name]}\t\t{completion_times[process.name] - process.arrival_time}\t\t{waiting_times[process.name]}")


# Example usage
processes = [
    Process("P1", 0, 6),
    Process("P2", 0, 8),
    Process("P3", 0, 7),
    Process("P4", 0, 3)
]

print("\n\033[91mShortest Job First (SJF) Scheduling:\033[0m")
SJF(processes)
