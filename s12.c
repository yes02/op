#include<stdio.h>
struct frmnode
{
 int pno,counter;//new
}
frames[20];
int n;
int page_found(int pno)
{
 int fno;
 for(fno=0;fno<n;fno++)
 {if(frames[fno].pno==pno)
    return fno;
  }
 return -1;
}
int get_free_frame()
{int fno;
 for (fno=0; fno<n; fno++)
 {
  if (frames[fno].pno==-1)
   return(fno);
  }
 return(-1);
}
int get_lru_Frame()
{
 int lrufno=0,fno;
 for (fno=1; fno<n; fno++)
 {
  if(frames[fno].counter<frames[lrufno].counter)
   lrufno=fno;
 }
 return lrufno;
}
void main()
{
 int p_request[]={5,8,10,14,10,9,5,10,8,5,1,10,9,12,10};
 int size=15,currtime;
 int page_falts=0,i,j,fno;
 printf("\nHow many frames:");  scanf("%d",&n);
 for (i=0; i<n; i++)
 { frames[i].pno=-1;
 }
 printf("\nPageNo     Page Frames     Page Fault");
 printf("\n---------------------------------------------------");
 currtime=0;
 for(i=0;i<size;i++)
 {
  j=page_found(p_request[i]);
  if(j==-1)  
  {
   j=get_free_frame();
   if (j==-1)
    j=get_lru_Frame();
   page_falts++;
   frames[j].pno=p_request[i];
   frames[j].counter=currtime;
   printf("\n%4d\t ",p_request[i]);
   for (fno=0; fno<n; fno++)
    printf("%4d:%2d",frames[fno].pno,frames[fno].counter);
   printf(" : YES");
  }
  else
  {frames[j].counter=currtime; 
   printf("\n%4d\t ",p_request[i]);
   for (fno=0; fno<n; fno++)
    printf("%4d:%2d",frames[fno].pno,frames[fno].counter);
   printf(" : NO");
  }
  currtime++;
 }
 printf("\n------------------------------------------");
 printf("\n Number of Page_Falts=%d\n",page_falts);
}





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
