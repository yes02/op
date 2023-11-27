#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
    int child_pid;
    int priority;

    child_pid = fork();

    if (child_pid == 0) {
        printf("Child Process ID: %d\n", getpid());
        priority = nice(10);

        if (priority == -1) {
            perror("nice");
        } else {
            printf("Increased priority for child process. New priority level: %d\n", priority);
        }
    } else if (child_pid > 0) {
        printf("Parent Process ID: %d\n", getpid());
        printf("Child Process ID: %d\n", child_pid);
    } else {
        perror("fork");
    }

    return 0;
}




#include <stdio.h>

void nonPreemptivePriority(int num_processes, int arrival_time[], int burst_time[], int priority[]) {
    int completion_time[num_processes];
    int waiting_time[num_processes];
    int turnaround_time[num_processes];
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (int i = 0; i < num_processes; i++) {
        for (int j = i+1; j < num_processes; j++) {
            if (arrival_time[i] > arrival_time[j]) {
                int temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;

                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;
            }
        }
    }

    completion_time[0] = arrival_time[0] + burst_time[0];
    turnaround_time[0] = completion_time[0] - arrival_time[0];
    waiting_time[0] = turnaround_time[0] - burst_time[0];
    total_waiting_time += waiting_time[0];
    total_turnaround_time += turnaround_time[0];

    for (int i = 1; i < num_processes; i++) {
        int highest_priority = priority[i];
        int shortest = i;

        for (int j = i+1; j < num_processes; j++) {
            if (arrival_time[j] <= completion_time[i-1] && priority[j] < highest_priority) {
                shortest = j;
                highest_priority = priority[j];
            }
        }

        int temp = completion_time[i-1];
        completion_time[i-1] = completion_time[shortest];
        completion_time[shortest] = temp;

        temp = arrival_time[i];
        arrival_time[i] = arrival_time[shortest];
        arrival_time[shortest] = temp;

        temp = burst_time[i];
        burst_time[i] = burst_time[shortest];
        burst_time[shortest] = temp;

        temp = priority[i];
        priority[i] = priority[shortest];
        priority[shortest] = temp;

        completion_time[i] = completion_time[i-1] + burst_time[i];
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, arrival_time[i], burst_time[i], priority[i], completion_time[i], turnaround_time[i], waiting_time[i]);
    }

    double avg_waiting_time = (double)total_waiting_time / num_processes;
    double avg_turnaround_time = (double)total_turnaround_time / num_processes;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int num_processes;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    int arrival_time[num_processes];
    int burst_time[num_processes];
    int priority[num_processes];

    for (int i = 0; i < num_processes; i++) {
        printf("Enter arrival time for Process %d: ", i+1);
        scanf("%d", &arrival_time[i]);

        printf("Enter burst time for Process %d: ", i+1);
        scanf("%d", &burst_time[i]);

        printf("Enter priority for Process %d: ", i+1);
        scanf("%d", &priority[i]);
    }

    nonPreemptivePriority(num_processes, arrival_time, burst_time, priority);

    return 0;
}
