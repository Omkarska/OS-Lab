n = int(input("Enter the number of processes: "))

arrival_time = []
burst_time = []
for i in range(n):
    arrival_time.append(int(input("Enter arrival time for process {}: ".format(i+1))))
    burst_time.append(int(input("Enter burst time for process {}: ".format(i+1))))

quantum = int(input("Enter the time quantum: "))

remaining_time = list(burst_time)

completion_time = [0] * n
waiting_time = [0] * n
turnaround_time = [0] * n

time = 0

completed = False

while not completed:
    completed = True
    for i in range(n):
        if arrival_time[i] <= time and remaining_time[i] > 0:
            completed = False
            if remaining_time[i] > quantum:
                time += quantum
                remaining_time[i] -= quantum
            else:
                time += remaining_time[i]
                completion_time[i] = time
                remaining_time[i] = 0
                waiting_time[i] = completion_time[i] - arrival_time[i] - burst_time[i]
                turnaround_time[i] = completion_time[i] - arrival_time[i]

avg_waiting_time = sum(waiting_time) / n
print("Average waiting time: ", avg_waiting_time)

avg_turnaround_time = sum(turnaround_time) / n
print("Average turnaround time: ", avg_turnaround_time)

print("Process    Burst Time    Waiting Time    Completion Time    Turnaround Time")
for i in range(n):
    print("P{}\t\t {}\t\t {}\t\t {}\t\t {}".format(i+1, burst_time[i], waiting_time[i], completion_time[i], turnaround_time[i]))
