#include<stdio.h>
struct node
{
  int pno, freq;
}frames[20];
int n;
int page_found(int pno)
{
  int fno;
  for(fno=0;fno<n;fno++)
  {
    if(frames[fno].pno==pno)
	   return fno;
  }
  return -1;
}
int get_free_frame()
{  int fno;
  for (fno=0; fno<=n; fno++)
  {
    if (frames[fno].pno==-1)
      return(fno);
  }
   return(-1);
}
int get_lfu_frame()
{
  int fno;
  int selfno=0;
  for (fno=1; fno<n; fno++)
  {
    if(frames[fno].freq<frames[selfno].freq)
	selfno=fno;
  }
  return selfno;
}
void main()
{
   int p_request[]={5,8,10,14,10,9,5,10,8,5,1,10,9,12,10};
   int size=15;
   int page_falts=0,i,j,fno;
   
   printf("\nHow many frames:");  scanf("%d",&n);
   for (i=0; i<n; i++)
   { frames[i].pno=-1;
     frames[i].freq=0;
   }
   printf("\nPageNo     Page Frames          	Page Fault");
   printf("\n---------------------------------------------------");
   for(i=0;i<size;i++)
   {
	 j=page_found(p_request[i]);
	 if(j==-1)  
	 {
	   j=get_free_frame();
	   if (j==-1) 
		 j=get_lfu_frame();
	   page_falts++;
	   frames[j].pno=p_request[i];
	   frames[j].freq=1;
	   printf("\n%4d\t ",p_request[i]);
	   for (fno=0; fno<n; fno++)
		 printf("%4d:%2d",frames[fno].pno,frames[fno].freq);
	   printf(" : YES");
	 }
	else 
	{
	   frames[j].freq++;
	   printf("\n%4d\t ",p_request[i]);
	   for (fno=0; fno<n; fno++)
		 printf("%4d:%2d",frames[fno].pno,frames[fno].freq);
	   printf(" : NO");
	}
   }
  printf("\n-------------------------------------------------------");
  printf("\n Number of Page_Falts=%d\n",page_falts);
  
}


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

