#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == 0) {
      
        printf("Child process with PID %d created.\n", getpid());
        printf("Parent process ID (PPID): %d\n", getppid());

     
        for (int i = 1; i <= 5; i++) {
            printf("Child working... (%d seconds)\n", i);
            sleep(1);
        }

        printf("Child process finished.\n");
    } else if (child_pid > 0) {
        
        printf("Parent process with PID %d created.\n", getpid());
        printf("Child process ID (PID): %d\n", child_pid);

        printf("Parent process terminating.\n");
    } else {
        perror("fork");
    }

    return 0;
}


//First in First Out
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

