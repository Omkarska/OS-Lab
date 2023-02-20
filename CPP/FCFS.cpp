#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm> // for sort function
#include <numeric>   // for accumulate function

using namespace std;

// Process structure to store process information
struct Process
{
    int id;          // process id
    int burstTime;   // burst time of the process
    int arrivalTime; // arrival time of the process
};

int main()
{
    int n; // number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    // input burst time and arrival time for each process
    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i + 1 << endl;
        processes[i].id = i + 1;
        cout << "Enter burst time: ";
        cin >> processes[i].burstTime;
        cout << "Enter arrival time: ";
        cin >> processes[i].arrivalTime;
    }

    // sort processes in increasing order of arrival time
    sort(processes.begin(), processes.end(), [](const Process &p1, const Process &p2)
         { return p1.arrivalTime < p2.arrivalTime; });

    // calculate completion time, waiting time, and turnaround time for each process
    int currentTime = processes[0].arrivalTime; // start from the first process arrival time
    vector<int> completionTimes(n);
    vector<int> waitingTimes(n);
    vector<int> turnaroundTimes(n);
    for (int i = 0; i < n; i++)
    {
        // calculate completion time for the current process
        currentTime += processes[i].burstTime;
        completionTimes[i] = currentTime;

        // calculate waiting time and turnaround time for the current process
        waitingTimes[i] = completionTimes[i] - processes[i].burstTime - processes[i].arrivalTime;
        turnaroundTimes[i] = completionTimes[i] - processes[i].arrivalTime;
    }

    // print Gantt chart and process table
    cout << endl
         << "Gantt Chart:" << endl;
    cout << "-----------" << endl;
    currentTime = processes[0].arrivalTime; // start from the first process arrival time
    cout << "| "
         << "P" << processes[0].id << " ";
    for (int i = 1; i < n; i++)
    {
        currentTime += processes[i - 1].burstTime;
        while (currentTime < processes[i].arrivalTime)
        {
            cout << "| "
                 << " "
                 << " ";
            currentTime++;
        }
        cout << "| "
             << "P" << processes[i].id << " ";
    }
    currentTime += processes[n - 1].burstTime;
    cout << "|";
    cout << endl
         << setw(2) << processes[0].arrivalTime << "      ";
    for (int i = 1; i < n; i++)
    {
        cout << setw(2) << currentTime << "      ";
        currentTime += processes[i].burstTime;
    }
    cout << endl;

    cout << endl
         << "Process Table:" << endl;
    cout << "--------------" << endl;
    cout << "| Process | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time |" << endl;
    cout << "|---------|--------------|------------|----------------|--------------|-----------------|" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "| " << setw(7) << "P" << processes[i].id << " | " << setw(12) << processes[i].arrivalTime << " | "
             << setw(10) << processes[i].burstTime << " | "
             << setw(15) << completionTimes[i] << " | "
             << setw(12) << waitingTimes[i] << " | "
             << setw(15) << turnaroundTimes[i] << " |" << endl;
    }
    cout << endl;

    // calculate and print average waiting time and turnaround time
    double avgWaitingTime = accumulate(waitingTimes.begin(), waitingTimes.end(), 0.0) / n;
    double avgTurnaroundTime = accumulate(turnaroundTimes.begin(), turnaroundTimes.end(), 0.0) / n;
    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;

    return 0;
}