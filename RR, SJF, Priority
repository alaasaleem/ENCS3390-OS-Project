#########################################
#  Project#3: CPU Scheduling Simulator  #
# Ebaa Taleeb, Raha Zabade, Alaa Saleem #
#########################################

# Define a class "Process" to represent a process in the system
class Process:
    # Define constructor that initializes the attributes of the process object
    def __init__(self, name, arrival_time, burst_time, priority): 
        self.name = name                       # assign the name of the process
        self.arrival_time = arrival_time       # assign the arrival_time of the process
        self.burst_time = burst_time           # assign the burst_time of the process
        self.remaining_time = burst_time       # initialize the remaining time with the burst time
        self.priority = priority               # assign the priority of the process


# Round Robin (RR) Scheduling algorithm
def RR(processes, time_quantum):
    # Create a queue of processes 
    queue = processes.copy()         # Create a copy of the list of processes 
    total_execution_time = 0         # Variable "total_execution_time" to keep track of the total execution time (time for executing all processes in the queue)
    waiting_times = {}               # Dictionary to store the waiting times for each process
    gantt_chart = []                 # List to store the Gantt chart entries
    
    # Loop until the queue of processes is empty
    while queue:
        # Get the process to be executed from the front of the queue 
        current_process = queue.pop(0) 
        
        # If process execution completed within the time quantum
        if current_process.remaining_time <= time_quantum:
            execution_time = current_process.remaining_time
            total_execution_time += execution_time  # Update the total execution time 
            waiting_time = total_execution_time - current_process.burst_time
            waiting_times[current_process.name] = waiting_time
            
            gantt_chart.append((current_process.name, execution_time))
            
            if current_process.remaining_time == 0:
                print(f"Process {current_process.name} is completed with completion time = {total_execution_time}, Turnaround Time = {total_execution_time} = {total_execution_time} - {current_process.arrival_time}, Waiting Time = {waiting_time} = {total_execution_time} - {current_process.arrival_time} - {current_process.burst_time}")
        else:
            execution_time = time_quantum
            total_execution_time += execution_time  # Update the total execution time 
            current_process.remaining_time -= execution_time  # Update the remaining time for the process
            queue.append(current_process)
            
            gantt_chart.append((current_process.name, execution_time))
    
    print("\n\033[91mProcess Table:\033[0m")
    # Print the process table
    print("Process ID\tArrival Time\tBurst Time")
    for process in processes:
        completion_time = process.arrival_time + waiting_times[process.name] + process.burst_time
        turnaround_time = completion_time - process.arrival_time
        print(f"{process.name.center(12)}\t{str(process.arrival_time).center(14)}\t{str(process.burst_time).center(11)}")

    print("\n\033[91mGantt Chart:\033[0m")
    # Print the Gantt chart
    print("---------------------------------------------------------------------------------")
    print("|", end="")
    for process, time in gantt_chart:
        print(f"   {process}    |", end="")
    print()
    print("---------------------------------------------------------------------------------")
    print(0, end="")
    cumulative_time = 0
    for process, time in gantt_chart:
        cumulative_time += time
        print(f"--------{cumulative_time}", end="")
    print()

    print("\n\033[91mSummary Table:\033[0m")
    # Print the waiting times, completion times, turnaround times in a table format
    print("Process ID\tCompletion Time\t\tTurnaround Time\t\tWaiting Time")
    for process in processes:
        completion_time = process.arrival_time + waiting_times[process.name] + process.burst_time
        turnaround_time = completion_time - process.arrival_time
        print(f"{process.name.center(12)}\t{str(completion_time).center(16)}\t{str(turnaround_time).center(18)}\t{str(waiting_times[process.name]).center(16)}")

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

# Priority Scheduling algorithm
def PriorityScheduling(processes):
    total_execution_time = 0                 # Variable "total_execution_time" to keep track of the total execution time (time for executing all processes)
    waiting_times = {}                       # Dictionary to store the waiting times for each process
    gantt_chart = []                         # List to store the Gantt chart entries
    
    # Sort the processes based on their priority (lower priority number indicates higher priority)
    sorted_processes = sorted(processes, key=lambda x: x.priority)
    
    # Loop through the sorted processes
    while sorted_processes:
        process = sorted_processes[0]        # Get the process with the highest priority
        
        # Update the waiting time for the process
        waiting_times[process.name] = total_execution_time
        
        # Update the total execution time and Gantt chart
        total_execution_time += process.burst_time
        gantt_chart.append((process.name, total_execution_time))
        
        sorted_processes.pop(0)              # Remove the process from the list
        
    print("\n\033[91mGantt Chart:\033[0m")
    print_gantt_chart(gantt_chart)          # Print the Gantt chart
    print("\n\033[91mProcess Table:\033[0m")
    print_process_table(processes)          # Print the process table
    print("\n\033[91mSummary Table:\033[0m")
    print_summary_table(processes, waiting_times)  # Print the summary table


# Function to print the Gantt chart
def print_gantt_chart(gantt_chart):
    print('-' * 60)
    print('|', end='')
    for entry in gantt_chart:
        process_name, execution_time = entry
        print(f'   {process_name}   |', end='')
    print('\n', '-' * 60)
    print(0, end='')
    for entry in gantt_chart:
        process_name, execution_time = entry
        print(f'------{execution_time}', end='')
    print()


# Function to print the process table
def print_process_table(processes):
    print("Process ID\tBurst Time\tPriority")
    for process in processes:
        print(f"{process.name}\t\t{str(process.burst_time)}\t\t{str(process.priority)}")


# Function to print the summary table
def print_summary_table(processes, waiting_times):
    print("Process ID\tCompletion Time\tTurnaround Time\tWaiting Time")
    for process in processes:
        completion_time = waiting_times[process.name] + process.burst_time
        turnaround_time = completion_time
        waiting_time = waiting_times[process.name]
        print(f"{process.name}\t\t{str(completion_time)}\t\t{str(turnaround_time)}\t\t{str(waiting_time)}")


# Example usage
processes_PRIORITY = [
    Process("P1",0, 10, 3),
    Process("P2",0, 1, 1),
    Process("P3",0, 2, 4),
    Process("P4",0, 1, 5),
    Process("P5",0, 5, 2)
]

print("\n\033[91mPriority Scheduling:\033[0m")
PriorityScheduling(processes_PRIORITY)


processes_SJF = [
    Process("P1", 0, 6, 0),
    Process("P2", 0, 8, 0),
    Process("P3", 0, 7, 0),
    Process("P4", 0, 3, 0)
]

print("\n\033[91mShortest Job First (SJF) Scheduling:\033[0m")
SJF(processes_SJF)


processes_RR = [
    Process("P1", 0, 24, 1),
    Process("P2", 0, 3, 1),
    Process("P3", 0, 3, 1)
]

time_quantum = 4

print("\n\033[91mRound Robin Scheduling:\033[0m")
RR(processes_RR, time_quantum)
