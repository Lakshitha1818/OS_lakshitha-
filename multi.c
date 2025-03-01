#include <stdio.h>

void sort(int proc_id[], int at[], int bt[], int n) {
    int min, temp;
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(at[j] < at[i]) {
                // Swap arrival time
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                // Swap burst time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                // Swap process ID
                temp = proc_id[i];
                proc_id[i] = proc_id[j];
                proc_id[j] = temp;
            }
        }
    }
}

void simulateFCFS(int proc_id[], int at[], int bt[], int n, int start_time) {
    int c = start_time, ct[n], tat[n], wt[n];
    double ttat = 0.0, twt = 0.0;

    // Completion time
    for(int i=0; i<n; i++) {
        if(c >= at[i])
            c += bt[i];
        else
            c = at[i] + bt[i];
        ct[i] = c;
    }

    // Turnaround time
    for(int i=0; i<n; i++)
        tat[i] = ct[i] - at[i];

    // Waiting time
    for(int i=0; i<n; i++)
        wt[i] = tat[i] - bt[i];

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc_id[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        ttat += tat[i];
        twt += wt[i];
    }

    printf("Average Turnaround Time: %.2lf ms\n", ttat/n);
    printf("Average Waiting Time: %.2lf ms\n", twt/n);
}

void main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int proc_id[n], at[n], bt[n], type[n];
    int sys_proc_id[n], sys_at[n], sys_bt[n], user_proc_id[n], user_at[n], user_bt[n];
    int sys_count = 0, user_count = 0;

    for(int i=0; i<n; i++) {
        proc_id[i] = i + 1;
        printf("Enter arrival time, burst time and type (0 for system, 1 for user) for process %d: ", i+1);
        scanf("%d %d %d", &at[i], &bt[i], &type[i]);

        if(type[i] == 0) {
            sys_proc_id[sys_count] = proc_id[i];
            sys_at[sys_count] = at[i];
            sys_bt[sys_count] = bt[i];
            sys_count++;
        } else {
            user_proc_id[user_count] = proc_id[i];
            user_at[user_count] = at[i];
            user_bt[user_count] = bt[i];
            user_count++;
        }
    }

    // Sort both queues by arrival time
    sort(sys_proc_id, sys_at, sys_bt, sys_count);
    sort(user_proc_id, user_at, user_bt, user_count);

    // Scheduling
    printf("System Processes Scheduling:\n");
    simulateFCFS(sys_proc_id, sys_at, sys_bt, sys_count, 0);

    // Find the time when system processes finish
    int system_end_time = 0; // Initialize system_end_time to 0. This variable will hold the time at which the last system process finishes.
    if (sys_count > 0) {    // Check if there are any system processes. If there are no system processes (sys_count == 0), there's no need to calculate system_end_time.
        system_end_time = sys_at[sys_count - 1] + sys_bt[sys_count - 1];   // Set system_end_time to the sum of the arrival time and burst time of the last system process in the sorted list. This is a rough initial estimate, assuming that all previous processes have completed before the last one starts.
        for (int i = 0; i < sys_count - 1; i++) {        // Loop over all system processes
            if (sys_at[i + 1] > system_end_time) {        // Check if the arrival time of the next process is greater than the current system_end_time.
                system_end_time = sys_at[i + 1];          // If it is, update system_end_time to this process's arrival time. This handles any idle time (gaps) between processes.
            }
            system_end_time += sys_bt[i];   // Add the burst time of the current process to system_end_time. This updates the end time to include the time taken by the current process.
        }
    }

    printf("\nUser Processes Scheduling:\n");
    simulateFCFS(user_proc_id, user_at, user_bt, user_count, system_end_time);
}
