import operator

# Function to find the waiting time for all processes
def findWaitingTime(processes, n, bt, at, wt, quantum):
    rem_bt = [0] * n
    for i in range(n):
        rem_bt[i] = bt[i]
    t = 0
    while(1):
        done = True
        for i in range (n):
            if (rem_bt[i] > 0) :
                done = False
                if (rem_bt[i] > quantum) :
                    t += quantum
                    rem_bt[i] -= quantum
                else:
                    t = t + rem_bt[i]
                    wt[i] = t - bt[i] - at[i]
                    rem_bt[i] = 0
        if (done == True):
            break

# Function to find the turn around time for all processes
def findTurnAroundTime(processes, n, bt, wt, tat):
    for i in range(n):
        tat[i] = bt[i] + wt[i]

# Function to find the average time
def findavgTime(processes, n, bt, at, wt, tat):
    total_wt = 0
    total_tat = 0
    for i in range(n):
        total_wt = total_wt + wt[i]
        total_tat = total_tat + tat[i]
    print("\nAverage waiting time = %.5f "%(total_wt /n) )
    print("Average turn around time = %.5f "% (total_tat / n))

# Function for sorting the process according to priority
def priorityScheduling(processes, n, bt, at, priority):
    processes = [[i+1,bt[i],at[i],priority[i]] for i in range(n)]
    processes = sorted(processes, key = lambda x: x[3])
    wt=[0]*n
    tat=[0]*n
    for i in range(n):
        for j in range(i):
            wt[i]+=bt[j]
        wt[i]-=at[i]
    for i in range(n):
        tat[i]=wt[i]+bt[i]
    findavgTime(processes, n, bt, at, wt, tat)
    print("Processes  Burst Time  Arrival Time Priority Waiting Time  Turn Around Time")
    for i in range(n):
        print(" ", i + 1, "\t\t", bt[i], "\t\t", at[i], "\t\t", priority[i],"\t\t", wt[i], "\t\t", tat[i])

if __name__ =="__main__":
    n = int(input("Enter the number of processes: "))
    processes = list(range(1, n+1))
    burst_time = list(map(int, input("Enter the burst time of the processes separated by space: ").strip().split()))[:n]
    arrival_time = list(map(int, input("Enter the arrival time of the processes separated by space: ").strip().split()))[:n]
    priority = list(map(int, input("Enter the priority of the processes separated by space: ").strip().split()))[:n]
    priorityScheduling(processes, n, burst_time, arrival_time, priority)
