#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to store process details
struct process
{
    int pid;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
};

int main()
{
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> quantum;

    vector<process> processes(n);
    queue<process> readyQueue;

    // Get the burst time for each process from the user
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        cout << "Enter the burst time for process " << processes[i].pid << ": ";
        cin >> processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
        readyQueue.push(processes[i]);
    }

    int currentTime = 0;

    while (!readyQueue.empty())
    {
        process currentProcess = readyQueue.front();
        readyQueue.pop();

        // If burst time is less than or equal to time quantum
        if (currentProcess.burstTime <= quantum)
        {
            currentTime += currentProcess.burstTime;
            currentProcess.burstTime = 0;
        }
        // If burst time is greater than time quantum
        else
        {
            currentTime += quantum;
            currentProcess.burstTime -= quantum;
        }

        // Update waiting time and turnaround time for each process
        for (int i = 0; i < n; i++)
        {
            if (processes[i].pid != currentProcess.pid && processes[i].burstTime > 0)
            {
                processes[i].waitingTime += currentTime - max(currentTime, currentTime - quantum - processes[i].waitingTime);
            }
            if (processes[i].burstTime == 0 && processes[i].turnaroundTime == 0)
            {
                processes[i].turnaroundTime = currentTime;
            }
        }

        if (currentProcess.burstTime > 0)
        {
            readyQueue.push(currentProcess);
        }
    }

    // Output the details of each process
    cout << "Process_Number\tBurst_Time\tWaiting_Time\tTurnaround_Time\n\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << processes[i].pid << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
    }

    // Calculate the average waiting time and turnaround time
    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++)
    {
        avgWaitingTime += processes[i].waitingTime;
        avgTurnaroundTime += processes[i].turnaroundTime;
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;
    cout << "Average waiting time: " << avgWaitingTime << endl;
    cout << "Average turnaround time: " << avgTurnaroundTime << endl;

    return 0;
}
