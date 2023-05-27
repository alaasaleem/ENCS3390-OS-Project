#########################################
#  Project#3: CPU Scheduling Simulator  #
# Ebaa Taleeb, Raha Zabade, Alaa Saleem #
#########################################

# Define a class "Process" to represent a process in the system
class Process:
    # Define constructor that initializes the attributes of the process object
    def __init__(self, name, burst_time, priority):
        self.name = name                       # assign the name of the process
        self.burst_time = burst_time           # assign the burst_time of the process
        self.priority = priority               # assign the priority of the process


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
processes = [
    Process("P1", 10, 3),
    Process("P2", 1, 1),
    Process("P3", 2, 4),
    Process("P4", 1, 5),
    Process("P5", 5, 2)
]

print("\n\033[91mPriority Scheduling:\033[0m")
PriorityScheduling(processes)
