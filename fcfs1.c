#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 30

int p[MAX_PROCESS], arrTime[MAX_PROCESS], burstTime[MAX_PROCESS], compTime[MAX_PROCESS], TAT[MAX_PROCESS], waitTime[MAX_PROCESS];

// Function to sort processes based on arrival time
void sortProcess(int arrTime[], int burstTime[], int n) {
    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arrTime[j] > arrTime[j + 1]) {
                // Swap arrival times
                temp = arrTime[j];
                arrTime[j] = arrTime[j + 1];
                arrTime[j + 1] = temp;
                // Swap burst times accordingly
                temp = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = temp;
            }
        }
    }
}

// Function to calculate turnaround time
int findTurnAroundTime(int ct, int at) {
    return ct - at;
}

// Function to calculate waiting time
int waitingTime(int tat, int bt) {
    return tat - bt;
}

int main() {
    int n;
    printf("Enter total number of processes: ");
    scanf("%d", &n);

    int total_TAT = 0; // Total turnaround time
    int total_WT = 0;  // Total waiting time

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        printf("Process [%d]\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &arrTime[i]);
        printf("Burst time: ");
        scanf("%d", &burstTime[i]);
        p[i] = i + 1; // Assigning process number
    }

    // Sort processes based on arrival time
    sortProcess(arrTime, burstTime, n);

    // Calculate completion time, turnaround time, and waiting time
    for (int i = 0; i < n; i++) {
        if (i == 0 || arrTime[i] > compTime[i - 1]) {
            compTime[i] = arrTime[i] + burstTime[i];
        } else {
            compTime[i] = compTime[i - 1] + burstTime[i];
        }

        TAT[i] = findTurnAroundTime(compTime[i], arrTime[i]);
        waitTime[i] = waitingTime(TAT[i], burstTime[i]);

        // Summing up turnaround time and waiting time
        total_TAT += TAT[i];
        total_WT += waitTime[i];
    }

    // Calculate averages
    float avg_TAT = (float)total_TAT / n;
    float avg_WT = (float)total_WT / n;

    // Displaying results including averages
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i], arrTime[i], burstTime[i], compTime[i], TAT[i], waitTime[i]);
    }
    printf("\nAverage Turnaround Time: %.2f", avg_TAT);
    printf("\nAverage Waiting Time: %.2f\n", avg_WT);

    return 0;
}
