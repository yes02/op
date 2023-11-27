
#include<stdio.h>
struct frmnode
{
  int pno;
}
frames[20];
int n;
int page_found(int pno)
{
 int fno;
 for(fno=0;fno<n;fno++)
 { if(frames[fno].pno==pno)
     return fno;
 }
 return -1;
}
int get_free_frame()
{ int fno;
 for (fno=0; fno<n; fno++)
 {
  if (frames[fno].pno==-1)
   return(fno);
 }
return(-1);
}
int get_fifo_frame()
{
 static int fno=-1;
 fno=(fno+1)%n;
 return(fno);
}
void main()
{
 int p_request[]={5,8,10,14,10,9,5,10,8,5,1,10,9,12,10};
 int size=15;
 int page_falts=0,i,j,fno;
 printf("\nHow many frames:");  scanf("%d",&n);
 for (i=0; i<n; i++)
 { frames[i].pno=-1;
 }
 printf("\nPageNo     Page Frames        Page Fault");
 printf("\n---------------------------------------------------");
 for(i=0;i<size;i++)
 {
  j=page_found(p_request[i]);
  if(j==-1)  
  {
   page_falts++;
   j=get_free_frame();
   if (j==-1) 
    j=get_fifo_frame();

   frames[j].pno=p_request[i];

   printf("\n%4d\t ",p_request[i]);
   for (fno=0; fno<n; fno++)
    printf("%4d",frames[fno].pno);
   printf(" : YES");
  }
  else 
  {
   printf("\n%4d\t ",p_request[i]);
   for (fno=0; fno<n; fno++)
    printf("%4d",frames[fno].pno);
   printf(" : NO");
  }
 }
 printf("\n-------------------------------------------------------");
 printf("\n Number of Page_Falts=%d\n",page_falts);
}




#include <stdio.h>

void fcfs(int num_processes, int arrival_time[], int burst_time[]) {
    int completion_time[num_processes];
    int waiting_time[num_processes];
    int turnaround_time[num_processes];
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    completion_time[0] = burst_time[0];

    for (int i = 1; i < num_processes; i++) {
        completion_time[i] = completion_time[i-1] + burst_time[i];
    }

    for (int i = 0; i < num_processes; i++) {
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, arrival_time[i], burst_time[i], completion_time[i], turnaround_time[i], waiting_time[i]);
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

    for (int i = 0; i < num_processes; i++) {
        printf("Enter arrival time for Process %d: ", i+1);
        scanf("%d", &arrival_time[i]);

        printf("Enter burst time for Process %d: ", i+1);
        scanf("%d", &burst_time[i]);
    }

    fcfs(num_processes, arrival_time, burst_time);

    return 0;
}
