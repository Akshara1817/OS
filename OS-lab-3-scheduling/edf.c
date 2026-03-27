#include <stdio.h>

struct Task {
    int pid;
    int burst;
    int deadline;
    int period;
    int rem;
    int abs_dl;
};

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Task tks[n];
    int hyperperiod = 1;

    for (int i = 0; i < n; i++) {
        printf("Enter PID, Burst, Deadline, and Period for process %d: ", i + 1);
        scanf("%d %d %d %d", &tks[i].pid, &tks[i].burst, &tks[i].deadline, &tks[i].period);
        tks[i].rem = 0;
        tks[i].abs_dl = 0;
        hyperperiod = lcm(hyperperiod, tks[i].period);
    }

    printf("\nPID\tBurst\tDeadline\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\n", tks[i].pid, tks[i].burst, tks[i].deadline, tks[i].period);
    }
    printf("Scheduling occurs for %d ms\n\n", hyperperiod);

    int prev_selected = -2; // Track previous state to only print context switches

    for (int time = 0; time < hyperperiod; time++) {
        for (int i = 0; i < n; i++) {
            if (time % tks[i].period == 0) {
                tks[i].rem = tks[i].burst;
                tks[i].abs_dl = time + tks[i].deadline;
            }
        }
        
        int min_dl = 999999;
        int selected = -1;
        
        for (int i = 0; i < n; i++) {
            if (tks[i].rem > 0 && tks[i].abs_dl < min_dl) {
                min_dl = tks[i].abs_dl;
                selected = i;
            }
        }
        
        // Print only if there is a context switch or CPU state change
        if (selected != prev_selected) {
            if (selected != -1) {
                printf("%dms onwards: Process %d running\n", time, tks[selected].pid);
            } else {
                printf("%dms onwards: CPU is idle\n", time);
            }
            prev_selected = selected;
        }
        
        // Execute the chosen process for 1ms
        if (selected != -1) {
            tks[selected].rem--;
        }
    }
    printf("\n1BM24CS028");

    return 0;
}