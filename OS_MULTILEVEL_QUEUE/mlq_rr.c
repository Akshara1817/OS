#include <stdio.h>

struct Process {
    int id;         
    int at;         
    int bt;         
    int ct;         
    int tat;        
    int wt;         
    int type;       
    int completed;  
    int rt;         
};

int main() {
    int n, i;
    int completed_count = 0;
    int current_time = 0;
    float total_wt = 0, total_tat = 0;
    int time_quantum;

    printf("Enter the total number of processes: ");
    scanf("%d", &n);

    printf("Enter Time Quantum for System Processes: ");
    scanf("%d", &time_quantum);

    struct Process p[n];

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d\n", p[i].id);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Enter Process Type (1 for System, 2 for User): ");
        scanf("%d", &p[i].type);
        p[i].completed = 0; 
        p[i].rt = p[i].bt; 
    }

    int rr_queue[1000]; 
    int front = 0, rear = 0;
    int running_sys = -1;
    int current_quantum = 0;

    for (i = 0; i < n; i++) {
        if (p[i].at == current_time && p[i].type == 1) {
            rr_queue[rear++] = i;
        }
    }

    while (completed_count < n) {
        int active_idx = -1;

        if (running_sys != -1) {
            active_idx = running_sys;
        } else if (front < rear) {
            running_sys = rr_queue[front++];
            current_quantum = 0;
            active_idx = running_sys;
        } else {
            int earliest_arrival = 999999;
            for (i = 0; i < n; i++) {
                if (p[i].type == 2 && p[i].completed == 0 && p[i].at <= current_time) {
                    if (p[i].at < earliest_arrival) {
                        earliest_arrival = p[i].at;
                        active_idx = i;
                    }
                }
            }
        }

        if (active_idx != -1) {
            p[active_idx].rt--;
            current_time++;
            
            if (p[active_idx].type == 1) {
                current_quantum++;
            }
        } else {
            current_time++;
        }

        for (i = 0; i < n; i++) {
            if (p[i].type == 1 && p[i].at == current_time && p[i].completed == 0) {
                rr_queue[rear++] = i;
            }
        }

        if (active_idx != -1) {
            if (p[active_idx].rt == 0) {
                p[active_idx].completed = 1;
                p[active_idx].ct = current_time;
                p[active_idx].tat = p[active_idx].ct - p[active_idx].at;
                p[active_idx].wt = p[active_idx].tat - p[active_idx].bt;
                
                total_tat += p[active_idx].tat;
                total_wt += p[active_idx].wt;
                
                completed_count++;

                if (p[active_idx].type == 1) {
                    running_sys = -1;
                }
            } else if (p[active_idx].type == 1 && current_quantum == time_quantum) {
                rr_queue[rear++] = active_idx;
                running_sys = -1; 
            }
        }
    }

    printf("\n--- Scheduling Results ---\n");
    printf("PID\tType\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].id, 
               (p[i].type == 1 ? "SYS" : "USR"), 
               p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    return 0;
}