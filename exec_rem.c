#include "test.h"
void exec_remain_commands(char **token3,char *tempdir,char tempdir2[],char dir[],int count,int *bg_arr_size, int bg_array[],node **head,char* var14,char *var15, int check1, int check2, int count2, int *fildes, int *fd_in)
{
	int check = 0;
	if(token3[count-1][strlen(token3[count-1])-1]=='&')
	{
		check = 1;
		token3[count-1][strlen(token3[count-1])-1]='\0';
	}
	token3[count]=NULL;
	int pid = fork();
	int var9 = 0;
	int fd1,fd2;
	if(check == 1)
	{
		bg_array[*bg_arr_size] = pid;
		(*bg_arr_size)++;
	}
	if(pid<0)
	{
		fprintf(stderr,"Fork failed\n");
		exit(1);
	}
	else if(pid == 0)
	{
		dup2(*fd_in,0);
		if(count2>0)
		{
			if(dup2(fildes[1],1)==-1)
				perror("1 dup2 fail");
		}
		close(fildes[0]);
		if(check1 == 1)
		{
			fd1 = open(var14,O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if(dup2(fd1,1)==-1)
			{
				perror("2 dup2 fail\n");
			}
		}
		if(check1 == 2)
		{
			fd1 = open(var14,O_RDONLY | O_CREAT, 0644);
			if(dup2(fd1,0)== -1)
			{
				perror("3 dup2 fail\n");
			}
		}
		if(check1 == 3)
		{
			fd1 = open(var14,O_WRONLY | O_CREAT | O_APPEND, 0644);
			if(dup2(fd1,1)==-1)
			{
				perror("4 dup2 fail\n");
			}
		}
		if(check2 == 1)
		{
			fd2 = open(var15,O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if(dup2(fd2,1)==-1)
			{
				perror("5 dup2 fail\n");
			}
		}
		if(check2 == 2)
		{
			fd2 = open(var15,O_WRONLY | O_TRUNC | O_CREAT | O_APPEND, 0644);
			if(dup2(fd2,1)==-1)
			{
				perror("6 dup2 fail\n");
			}
		}
		var9 = execvp(token3[0],token3);
		if(var9!=0)
		{
			fprintf(stderr,"execution failed %d\n",var9);
			exit(1);
		}
		close(fd1);
		close(fd2);
	}
	else
	{
		if (check==1)
		{
			node *temp;
			temp = (node *)malloc(sizeof(node));
			temp->pid_of_bg=pid;
			if(token3[count-1]=='\0')
				temp->pid_str=token3[count-2];
			else
				temp->pid_str=token3[count-1];
			temp->next=NULL;
			node *temp1=*head;
			if(*head==NULL)
				*head=temp;
			else
			{
				node *temp1=*head;
				while(temp1->next!=NULL)
				{
					temp1=temp1->next;
				}
				temp1->next=temp;
			}
		}
		if(check == 1)
			return;
		else
		{
			int status;
			waitpid(pid,&status,WUNTRACED);
			kill(pid,SIGCONT);
			close(fildes[1]);
			*fd_in = fildes[0];
		}
	}
}
