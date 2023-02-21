#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process
{
    int id;
    int burst_time;
    int priority;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    bool operator<(const Process &other) const
    {
        return arrival_time < other.arrival_time;
    }
};

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter burst time for P" << i + 1 << ": ";
        cin >> processes[i].burst_time;
        cout << "Enter priority for P" << i + 1 << ": ";
        cin >> processes[i].priority;
        cout << "Enter arrival time for P" << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        processes[i].id = i + 1;
    }

    sort(processes.begin(), processes.end());

    int CPU = processes[0].arrival_time; // CPU Current time
    int allTime = 0;                     // Time needed to finish all processes
    int NoP = n;                         // number of Processes

    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);

    cout << "\nGantt chart:\n";
    cout << "---------------------------\n";
    while (NoP > 0 && CPU <= 1000)
    {
        int highest_priority = -1;
        int selected_process = -1;
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= CPU)
            {
                if (processes[i].priority > highest_priority)
                {
                    highest_priority = processes[i].priority;
                    selected_process = i;
                }
            }
            else
            {
                break;
            }
        }

        if (selected_process == -1)
        {
            CPU = CPU + 1;
            continue;
        }
        else
        {
            waitingTime[selected_process] = CPU - processes[selected_process].arrival_time;
            CPU = CPU + processes[selected_process].burst_time;
            turnaroundTime[selected_process] = CPU - processes[selected_process].arrival_time;
            processes[selected_process].priority = -1; // mark as completed
            NoP = NoP - 1;

            cout << "|  P" << processes[selected_process].id << "  ";
        }
    }
    cout << "|\n";
    cout << "---------------------------\n\n";

    cout << "Process_Number\tBurst_Time\tPriority\tArrival_Time\tWaiting_Time\tTurnaround_Time\n\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << processes[i].id << "\t\t" << processes[i].burst_time << "\t\t" << processes[i].priority << "\t\t" << processes[i].arrival_time << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime[i] << endl;
    }

    float AvgWT = 0;  // Average waiting time
    float AVGTaT = 0; // Average Turn around time
    for (int i = 0; i < n; i++)
    {
        AvgWT = waitingTime[i] + AvgWT;
        AVGTaT = turnaroundTime[i] + AVGTaT;
    }

    cout << "Average waiting time = " << AvgWT / n << endl;
    cout << "Average turnaround time = " << AVGTaT / n << endl;
}