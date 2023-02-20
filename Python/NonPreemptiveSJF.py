n = int(input("Enter the number of processes: "))

arrival_time = []
burst_time = []
for i in range(n):
    arrival_time.append(int(input("Enter arrival time for process {}: ".format(i+1))))
    burst_time.append(int(input("Enter burst time for process {}: ".format(i+1))))

process = list(zip(arrival_time, burst_time))
process.sort(key = lambda x: x[1])

completion_time = [0] * n
waiting_time = [0] * n
turnaround_time = [0] * n
completion_time[0] = process[0][0] + process[0][1]
waiting_time[0] = 0
turnaround_time[0] = completion_time[0] - process[0][0]
for i in range(1, n):
    completion_time[i] = completion_time[i-1] + process[i][1]
    waiting_time[i] = completion_time[i] - process[i][0] - process[i][1]
    turnaround_time[i] = completion_time[i] - process[i][0]

avg_waiting_time = sum(waiting_time) / n
print("Average waiting time: ", avg_waiting_time)

avg_turnaround_time = sum(turnaround_time) / n
print("Average turnaround time: ", avg_turnaround_time)

print("Process    Burst Time    Waiting Time    Completion Time    Turnaround Time")
for i in range(n):
    print("P{}\t\t {}\t\t {}\t\t {}\t\t {}".format(i+1, burst_time[i], waiting_time[i], completion_time[i], turnaround_time[i]))

