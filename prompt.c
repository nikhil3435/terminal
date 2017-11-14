#include "test.h"
int max(int a, int b)
{
	if (a>b)
		return a;
	else
		return b;
}
void print_prompt(char *tempdir,char *tempdir2,char *dir)
{
	int i,j;
	struct passwd *password;
	char machname[1024];
	int var1 = gethostname(machname,sizeof(machname));
	password = getpwuid(getuid());
	char full_dir_path[1024];
	full_dir_path[0]='~';
	for(j=1; j<1024; j++)
		full_dir_path[j]=0;
	int var3 = max(strlen(tempdir),strlen(dir));
	for(i = 0; i<var3; i++)
	{
		if(tempdir[i]!=dir[i])
			break;
	}
	if (i<strlen(dir))
	{
		printf("\x1B[32m" "%s@%s:%s$ " "\x1B[0m",password->pw_name,machname,tempdir);
	}
	else
	{
		int p = 1;
		for(j=i; j<strlen(tempdir); j++)
		{
			full_dir_path[p++] = tempdir[j];
		}
		printf("\x1B[32m" "%s@%s:%s$ " "\x1B[0m",password->pw_name,machname,full_dir_path);
	}
}
void bg_check(int* bg_array,int *bg_arr_size,node **head)
{
	int i,status;
	for(i=0; i<*bg_arr_size; i++)
	{
		if(bg_array[i]!=-1)
			if(waitpid(bg_array[i],&status,WNOHANG))
			{
				if(WIFEXITED(status))
				{
					fprintf(stderr,"process with pid %d exited normally\n",bg_array[i]);
					node *temp2=*head,*temp3=*head;
					while(temp2->pid_of_bg!=bg_array[i])
					{
						temp3=temp2;
						temp2=temp2->next;
					}
					if(temp2==*head)
					{
						*head=(*head)->next;
					}
					bg_array[i] =-1;
					temp3->next=temp2->next;
					free(temp2);
				}
			}
	}
}
