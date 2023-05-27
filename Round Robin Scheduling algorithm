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


# Example usage
processes = [
    Process("P1", 0, 24, 1),
    Process("P2", 0, 3, 1),
    Process("P3", 0, 3, 1)
]

time_quantum = 4

print("\n\033[91mRound Robin Scheduling:\033[0m")
RR(processes, time_quantum)
