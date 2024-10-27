#include <iostream>
#include <iomanip> 
#include <cstring> 
using namespace std;

struct Process {
    char process_id[10];
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process proc[100];

    cout << "Input Process ID, Arrival Time, and Burst Time (separated by spaces):\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << (i + 1) << ": ";
        cin >> proc[i].process_id >> proc[i].arrival_time >> proc[i].burst_time;
    }

    int completed = 0, current_time = 0;
    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    bool is_completed[100] = {false};

    while (completed < n) {
        int shortest_job_index = -1;
        int min_burst_time = 100000;

        for (int i = 0; i < n; i++) {
            if (!is_completed[i] && proc[i].arrival_time <= current_time && proc[i].burst_time < min_burst_time) {
                min_burst_time = proc[i].burst_time;
                shortest_job_index = i;
            }
        }

        if (shortest_job_index != -1) {
            current_time += proc[shortest_job_index].burst_time;
            proc[shortest_job_index].completion_time = current_time;
            proc[shortest_job_index].turnaround_time = proc[shortest_job_index].completion_time - proc[shortest_job_index].arrival_time;
            proc[shortest_job_index].waiting_time = proc[shortest_job_index].turnaround_time - proc[shortest_job_index].burst_time;

            total_waiting_time += proc[shortest_job_index].waiting_time;
            total_turnaround_time += proc[shortest_job_index].turnaround_time;

            is_completed[shortest_job_index] = true;
            completed++;
        } else {
            current_time++;
        }
    }

    
    cout << "\nFinal Results of Processes:\n";
    cout << left << setw(12) << "ProcessID"
         << setw(13) << "ArrivalTime"
         << setw(11) << "BurstTime"
         << setw(16) << "CompletionTime"
         << setw(16) << "TurnaroundTime"
         << setw(12) << "WaitingTime" << endl;

    for (int i = 0; i < n; i++) {
        cout << left << setw(12) << proc[i].process_id
             << setw(13) << proc[i].arrival_time
             << setw(11) << proc[i].burst_time
             << setw(16) << proc[i].completion_time
             << setw(16) << proc[i].turnaround_time
             << setw(12) << proc[i].waiting_time << endl;
    }

    
    float avg_waiting_time = total_waiting_time / n;
    float avg_turnaround_time = total_turnaround_time / n;
    cout << "\nAverage Times:\n";
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;

    return 0;
}
