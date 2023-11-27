#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char comm[80];
char *args[10];
int tot_arg,i,j;
void getcomm();
void sep_arg();
void take_action();
void typeline();
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
  if(strcmp(args[0],"typeline")==0)
   typeline();
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

void typeline()
{
  int fd,ret,n,cnt=0,totlines;
  char ch;
  if(tot_arg<2) return;
  fd=open(args[2],0);
  if (fd==-1)
  { printf("File not found..\n");
    return;
  }
  if(strcmp(args[1],"a")==0)
  { ret=read(fd,&ch,1);
    while(ret!=0)
    { printf("%c",ch);
      ret=read(fd,&ch,1);
    }
  }
  else
  if(*args[1]=='+')
  { n=atoi(args[1]+1);
    ret=read(fd,&ch,1);
   cnt=0;
    while(ret!=0)  
    { if(ch=='\n') cnt++;
      printf("%c",ch);
      if(cnt==n) break;
      ret=read(fd,&ch,1);
    }
  } 
  else
  if(*args[1]=='-')
  { n=atoi(args[1]+1);
    totlines=0;
    ret=read(fd,&ch,1);
    while(ret!=0) 
    { if(ch=='\n') totlines++;
      ret=read(fd,&ch,1);
    }
    cnt=0;
    lseek(fd,0,SEEK_SET);
    ret=read(fd,&ch,1);
    while(ret!=0)
    { if (ch=='\n') cnt++;
      if(cnt>=totlines-n)
        printf("%c",ch);
      ret=read(fd,&ch,1);
    } 
   }  
  else
   printf("Invalid option\n");
  close(fd);
 } 
 
 
 
 #include <stdio.h>

void sjf(int num_processes, int arrival_time[], int burst_time[]) {
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
            }
        }
    }

    completion_time[0] = arrival_time[0] + burst_time[0];
    turnaround_time[0] = completion_time[0] - arrival_time[0];
    waiting_time[0] = turnaround_time[0] - burst_time[0];
    total_waiting_time += waiting_time[0];
    total_turnaround_time += turnaround_time[0];

    for (int i = 1; i < num_processes; i++) {
        int shortest = i;

        for (int j = i+1; j < num_processes; j++) {
            if (completion_time[i-1] >= arrival_time[j] && burst_time[j] < burst_time[shortest]) {
                shortest = j;
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

        completion_time[i] = completion_time[i-1] + burst_time[i];
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

    sjf(num_processes, arrival_time, burst_time);

    return 0;
}
