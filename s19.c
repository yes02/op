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
