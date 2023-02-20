#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

// define a struct for each process
struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
};

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    // initialize a vector of processes
    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        cout << "Process " << i + 1 << endl;
        cout << "Enter burst time: ";
        cin >> processes[i].burstTime;
        cout << "Enter arrival time: ";
        cin >> processes[i].arrivalTime;
    }

    // sort processes by arrival time
    sort(processes.begin(), processes.end(),
         [](const Process &p1, const Process &p2)
         { return p1.arrivalTime < p2.arrivalTime; });

    vector<int> completionTimes(n); // to store completion times of each process
    vector<int> waitingTimes(n);    // to store waiting times of each process
    vector<int> turnaroundTimes(n); // to store turnaround times of each process

    // calculate completion times of each process
    int currentTime = 0;
    for (int i = 0; i < n; i++)
    {
        int shortestBurstTime = processes[i].burstTime;
        int shortestIndex = i;
        for (int j = i + 1; j < n && processes[j].arrivalTime <= currentTime; j++)
        {
            if (processes[j].burstTime < shortestBurstTime)
            {
                shortestBurstTime = processes[j].burstTime;
                shortestIndex = j;
            }
        }
        swap(processes[i], processes[shortestIndex]); // move shortest process to front
        currentTime += processes[i].burstTime;
        completionTimes[i] = currentTime;
    }

    // calculate waiting and turnaround times of each process
    for (int i = 0; i < n; i++)
    {
        waitingTimes[i] = completionTimes[i] - processes[i].burstTime - processes[i].arrivalTime;
        turnaroundTimes[i] = completionTimes[i] - processes[i].arrivalTime;
    }

    // print Gantt chart
    cout << endl
         << "Gantt Chart:" << endl
         << "-----------" << endl;
    int prevTime = processes[0].arrivalTime;
    for (int i = 0; i < n; i++)
    {
        cout << "|  P" << processes[i].pid << "  ";
        if (i == n - 1)
        {
            cout << "|";
            prevTime = completionTimes[i];
        }
        else
        {
            int nextTime = min(completionTimes[i], processes[i + 1].arrivalTime);
            for (int j = prevTime + 1; j < nextTime; j++)
            {
                cout << " ";
            }
            cout << "|";
            prevTime = nextTime;
        }
    }
    cout << endl;
    prevTime = processes[0].arrivalTime;
    for (int i = 0; i < n; i++)
    {
        cout << prevTime << setw(7);
        if (i == n - 1)
        {
            cout << completionTimes[i] << endl;
            break;
        }
        int nextTime = min(completionTimes[i], processes[i + 1].arrivalTime);
        cout << nextTime << setw(7);
        prevTime = nextTime;
    }
    // print process table
    double avgWaitingTime = accumulate(waitingTimes.begin(), waitingTimes.end(), 0.0) / n;
    double avgTurnaroundTime = accumulate(turnaroundTimes.begin(), turnaroundTimes.end(), 0.0) / n;
    cout << endl
         << "Process Table:" << endl
         << "-------------" << endl;
    cout << "P   Arrival Time   Burst Time   Completion Time   Waiting Time   Turnaround Time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i].pid << setw(10) << processes[i].arrivalTime << setw(13)
             << processes[i].burstTime << setw(14) << completionTimes[i] << setw(16)
             << waitingTimes[i] << setw(18) << turnaroundTimes[i] << endl;
    }
    cout << endl
         << "Average waiting time: " << avgWaitingTime << endl;
    cout << "Average turnaround time: " << avgTurnaroundTime << endl;

    return 0;
}
