#include "test.h"
void execute_cd(char **token, int count,char tempdir[],char tempdir2[],char dir[])
{
	count--;
	char *token1;
	char vardir[1024];
	char vardir1[1024];
	if(count>0)
	{
		if(token[1][0] == '-')
		{
			token1 = tempdir2;
		}
		else if(token[1][0] == '~')
		{
			strcpy(vardir1,dir);
			strcat(vardir1,token[1]+1);
			token1 = vardir1;
		}
		else
		{
			token1 = token[1];
		}
		int var6 = chdir(token1);
		getcwd(vardir,sizeof(vardir));
		strcpy(tempdir2,tempdir);
		if(var6 != 0 )
			fprintf(stderr,"No such directory exists\n");
		else
			strcpy(tempdir,vardir);
	}
	else
	{
		token1 = dir;
		int var6 = chdir(token1);
		getcwd(vardir,sizeof(vardir));
		strcpy(tempdir2,tempdir);
		if(var6 != 0 )
			fprintf(stderr,"No such directory exists\n");
		else
			strcpy(tempdir,vardir);
	}
	return;
}
int compare_exit(char *token,char tempdir[],char tempdir2[],char dir[],int *exit_status)
{
	char exitvar[5] = "quit";
	int i;
	for (i=0; i<strlen(exitvar); i++)
	{
		if(token[i] != exitvar[i])
			break;
	}
	if(i==strlen(exitvar))
	{
		*exit_status = 1;
		return 1;
	}
	return 0;
}
void exec_echo(char *token,char **token1,int count,char tempdir[],char tempdir2[],char dir[])
{
	int check = 0;
	count--;
	int i;
	if(token1[1]!=NULL)
	{
		if(token1[1][0]!='"' && token1[1][0]!='\'')
		{
			int p =1;
			while(count>1)
			{
				printf("%s ",token1[p]);
				count--;
				p++;
			}
			printf("%s\n",token1[p]);
		}
		else
		{
			for(i=5; i<strlen(token); i++)
			{
				if(token[i]!='"' && token[i]!='\'')
					printf("%c",token[i]);
			}
			printf("\n");
		}
	}
	else
		printf("\n");
	return;
}
void exec_jobs(node **head,int check1,int count2)
{
	node *temp1=*head;
	while(temp1!=NULL)
	{
		printf("%d %s\n",temp1->pid_of_bg,temp1->pid_str);
		temp1=temp1->next;
	}
}
void exec_kjobs(node **head, char **token3,int *bg_arr_size,int *bg_array)
{
	int count=0;
	if(*head!=NULL)
	{
		node *temp1=*head,*temp2=*head;
		while(temp1->next!=NULL)
		{
			count++;
			if(count==token3[1][0]-48)
				break;
			temp2=temp1;
			temp1=temp1->next;
		}
		int i;
		for(i=0; i<*bg_arr_size; i++)
		{
			if(bg_array[i]==temp1->pid_of_bg)
			{
				bg_array[i]=-1;
			}
		}
		int ret = kill(temp1->pid_of_bg,token3[2][0]-48);
		if(count==0 && token3[1][0]-48 == 1)
		{
			*head=(*head)->next;
			free(temp1);
		}
		else
		{
			temp2->next=temp1->next;
			free(temp1);
		}
	}
	else
	{
		printf("No jobs yet!!\n");
	}
}
void exec_fg(node **head, char **token3)
{
	node *temp=*head;
	int count=0;
	if(*head!=NULL)
	{
		while(temp->next!=NULL)
		{
			count++;
			if(count==token3[1][0]-48)
				break;
			temp=temp->next;
		}
		int status;
		waitpid(temp->pid_of_bg,&status,WUNTRACED);
		kill(temp->pid_of_bg,SIGCONT);
	}
	else
	{
		printf("No such background process exists\n");
	}
}

void exec_bg(node **head, char **token3)
{
	node *temp=*head;
	int count=0;
	if(*head!=NULL)
	{
		while(temp->next!=NULL)
		{
			count++;
			if(count==token3[1][0]-48)
				break;
			temp=temp->next;
		}
		int status;
		kill(temp->pid_of_bg,SIGCONT);
	}
	else
	{
		printf("No such background process exists\n");
	}
}

void exec_killallbg(node **head,int *bg_arr_size,int *bg_array)
{
	node *temp=*head,*temp1;
	int i;
	while(temp!=NULL)
	{
		bg_array[i]=-1;
		int ret = kill(temp->pid_of_bg,9);
		if(ret == -1)
		{
			printf("No process to kill\n");
		}
		temp1=temp;
		temp=temp->next;
		free(temp1);
	}
	*head=NULL;
}

void pinfo_bonus(char **token3, int count1, char tempdir2[])
{
	FILE *filepointer;
	char var14[1024],state;
	char var12[1024],var13[1024];
	int pid2;
	long unsigned int memsize;
	if(count1==1)
	{
		sprintf(var12,"/proc/%d/stat",getpid());
		sprintf(var13,"/proc/%d/exe",getpid());
	}
	else
	{
		sprintf(var12,"/proc/%s/stat",(token3[1]));
		sprintf(var13,"/proc/%s/exe",(token3[1]));
	}
	if((filepointer=fopen(var12,"r"))!=NULL)
	{
		fscanf(filepointer,"%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&pid2,&state,&memsize);
		fclose(filepointer);
		printf("pid -- %d\nProcess Status -- %c\nmemory -- %lu\n",pid2,state,memsize);
		readlink(var13,var14,1024);
		if(strstr(var14,tempdir2))
		{
			char var15[1000]="~";
			strcat(var15,var14+strlen(tempdir2));
			printf("Executable Path -- %s\n",var15);                                                                                               }
		else
			printf("Executable Path -- %s\n",var14);
	}
	else
		fprintf(stderr,"No such process\n");
}

void check_symbol(char **token1,int var10)
{
	int h=0,po=0;
	char token4[100];
	for(h=0; h<=strlen(token1[var10]); h++)
	{
		if(token1[var10][h] == '>' && token1[var10][h+1] == '>')
		{
			h++;
			token4[po++] = ' ';
			token4[po++] = '>';
			token4[po++] = '>';
			token4[po++] = ' ';
		}
		else if(token1[var10][h] == '>')
		{
			token4[po++] = ' ';
			token4[po++] = '>';
			token4[po++] = ' ';
		}
		else if(token1[var10][h] == '<')
		{
			token4[po++] = ' ';
			token4[po++] = '<';
			token4[po++] = ' ';
		}
		else if (token1[var10][h] == '"')
			token4[po++]=' ';
		else
			token4[po++] = token1[var10][h];
	}
	strcpy(token1[var10],token4);
}
