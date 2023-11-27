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
void count();
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
  if(strcmp(args[0],"count")==0)
   count();
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
void count()
{
  int fd,ret,ccnt,wcnt,lcnt,wflag;
  char ch;
  fd=open(args[2],0);
  if (fd==-1)
  { printf("File not found..\n");
    return;
  }
  ccnt =wcnt = lcnt = 0;
  wflag=0;
  ret=read(fd,&ch,1);
  while(ret!=0)
  {
   ccnt++;
   if( ch ==' ' || ch== '\t') 
   {
     if( wflag == 0 )
     { wcnt++;
       wflag = 1;
     }
   }
   else
   if( ch == '\n') 
   { lcnt++;
     if(wflag == 0 )
     { wcnt++;
       wflag = 1;
     }
   }
   else
     wflag = 0;
   ret=read(fd,&ch,1);
  }
  if( wflag == 0 )
  { wcnt++;
    lcnt++;
   }
  close(fd);
  if(strcmp(args[1],"c")==0)
  printf("\nNo.of Chars:%d\n",ccnt);
  else
  if(strcmp(args[1],"w")==0)
  printf("\nNo.of Word:%d\n",wcnt);
  else
  if(strcmp(args[1],"l")==0)
  printf("\nNo.of Lines:%d\n",lcnt);
  else
  printf("\nInvalid Option\n");
}




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to perform bubble sort
void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Function to perform insertion sort
void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}

int main() {
    int n;
    printf("Enter the number of integers to sort: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter the %d integers to sort:\n", n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(-1);
    } else if (pid == 0) {
        // Child process (perform insertion sort)
        insertionSort(arr, n);
        printf("Child process (Insertion sort) completed sorting.\n");
    } else {
        // Parent process (perform bubble sort)
        bubbleSort(arr, n);
        printf("Parent process (Bubble sort) completed sorting.\n");

        // Wait for child process to complete
        wait(NULL);

        // Print sorted array
        printf("\nSorted array: ");
        for(int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}
