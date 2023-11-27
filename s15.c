
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
char comm[80];
char *args[10];
int tot_arg,i,j;
void getcomm();
void sep_arg();
void take_action();
void list();
void main()
{ int len;
  do
    {
     printf("myshell $ ");
     fgets(comm,80,stdin);
     len=strlen(comm);
     comm[len-1]='\0';
     if(strlen(comm)<=1) continue;
     sep_arg();
      take_action();        
       for(i=0;i<tot_arg;i++) args[i]=NULL; 
   } while(1);
  return;
} 
void sep_arg()
 {
  char *token,*ptr;
  tot_arg=-1;
  ptr=comm;
  while(1)
  { token=strtok(ptr," "); 
    if (token==NULL) break;
    args[++tot_arg]=(char *)malloc(strlen(token));
    strcpy(args[tot_arg],token);
    ptr=NULL;
  }
  return;
}
void take_action()
{ int pid,status;
  char str[20];
  if(strcmp(args[0],"list")==0)
   list();
  else
  {
   pid = fork();
   if(pid == 0 )
   {
    execvp(args[0],args);
    strcpy(str,"./");
    strcat(str,args[0]);
    execvp(str,args);
    printf("\n%s:command not found\n",comm);
    exit(0);
   }
   else 
    waitpid(pid,&status,0);
 }
}
void list()
{
  DIR *dp;
  struct dirent *dent;
  int cnt=0;
   dp=opendir(args[2]);
   if(dp==NULL)
    {printf("Directory not found..");
     return;
    }
    dent=readdir(dp);
    while(dent!=NULL)
    { cnt++;
      if(strcmp(args[1],"f")==0)
        printf("%s\n",dent->d_name);
      else
      if(strcmp(args[1],"i")==0)
       printf("%s\t%ld\n",dent->d_name,dent->d_ino);
      dent=readdir(dp);
    }
   if(strcasecmp(args[1],"c")==0)
    printf("No.of entries:%d\n",cnt); 
   closedir(dp); 
 }
 
 
 
 #include <stdio.h>

void sjf(int num_processes, int arrival_time[], int burst_time[]) {
    int completion_time[num_processes];
    int waiting_time[num_processes];
    int turnaround_time[num_processes];
    int processed[num_processes];
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (int i = 0; i < num_processes; i++) {
        processed[i] = 0;
    }

    int current_time = 0;
    int remaining_processes = num_processes;

    while (remaining_processes > 0) {
        int shortest_job = -1;
        int shortest_burst = 9999;

        for (int i = 0; i < num_processes; i++) {
            if (arrival_time[i] <= current_time && !processed[i] && burst_time[i] < shortest_burst) {
                shortest_job = i;
                shortest_burst = burst_time[i];
            }
        }

        if (shortest_job == -1) {
            current_time++;
        } else {
            completion_time[shortest_job] = current_time + burst_time[shortest_job];
            turnaround_time[shortest_job] = completion_time[shortest_job] - arrival_time[shortest_job];
            waiting_time[shortest_job] = turnaround_time[shortest_job] - burst_time[shortest_job];
            total_waiting_time += waiting_time[shortest_job];
            total_turnaround_time += turnaround_time[shortest_job];
            processed[shortest_job] = 1;
            current_time = completion_time[shortest_job];
            remaining_processes--;
        }
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

    sjf(num_processes, arrival_time, burst_time);

    return 0;
}
