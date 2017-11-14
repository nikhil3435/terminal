#include "test.h"
void separating_commands(char tempdir[],char tempdir2[],char dir[],int *exit_status,int *bg_arr_size,int bg_array[],node **head)
{
	char *buffer1;
	char q[100];
	size_t bufsize = 1000;
	size_t characters;
	//char q[4];
	const char s[2] = ";";
	char *token;
	buffer1 = (char *)malloc(bufsize * sizeof(char));
	if(buffer1 == NULL)
	{
		perror("No buffer\n");
		exit(1);
	}
	else
	{
		int var6;
		getline(&buffer1,&bufsize,stdin);
		if(&buffer1[0]=="q" && &buffer1[1]=="u" && &buffer1[2]=="i" && &buffer1[3]=="t")
		{
			var6=1;
			*exit_status = 1;
			return;
		}
		int var7 = strlen(buffer1);
		char *token1[1000];
		buffer1[var7-1] = ';';
		token  = strtok(buffer1,s);
		int count=0;
		while(token!=NULL)
		{
			token1[count]=(char *)malloc(sizeof(char)*1000);
			strcpy(token1[count],token);
			token = strtok(NULL,s);
			count++;
		}
		int var10=0;
		while(count--)
		{
			int fildes[2],fd_in=0;
			char *var11;
			char *token3[100];
			char tok[1000];
			char *token_for_pipe[100];
			strcpy(tok,token1[var10]);
			int check1=-1,check2 = -1,count2=0,po = 0;
			check_symbol(token1,var10);
			char *separate_through_pipe;
			separate_through_pipe = strtok(token1[var10],"|");
			while(separate_through_pipe!=NULL)
			{
				token_for_pipe[count2++] = separate_through_pipe;
				separate_through_pipe = strtok(NULL,"|");
			}
			while(count2--)
			{
				check1=-1;
				var11 = strtok(token_for_pipe[po]," \t");
				int count1=0;
				char *var14=NULL,*var15;
				while(var11!=NULL)
				{
					var6 = compare_exit(var11,tempdir,tempdir2,dir,exit_status);
					if(var6 == 1)
						break;
					if(strcmp(var11,">") == 0)
					{
						if(check1!=2)
							check1=0;
						var11 = strtok(NULL," \t");
						if(var11!=NULL)
						{
							if(var14==NULL)
							{
								var14 = var11;
								check1=1;
							}
							else
							{
								var15 = var11;
								check2=1;
							}
							var11 = strtok(NULL," \t");
						}
						continue;
					}
					else if(strcmp(var11,"<") == 0)
					{
						check1=0;
						var11 = strtok(NULL," \t");
						if(var11 != NULL)
						{
							if(var14==NULL)
							{
								check1=2;
								var14 = var11;
							}
							else
							{
								check1 = 0;
								break;
							}
							var11 = strtok(NULL," \t");
						}
						continue;
					}
					else if(strcmp(var11,">>") == 0)
					{
						if(check1!=2)
							check1=0;
						var11 = strtok(NULL," \t");
						if(var11 != NULL)
						{
							if(var14==NULL)
							{
								check1=3;
								var14 = var11;
							}
							else
							{
								var15 = var11;
								check2=2;
							}
							var11 = strtok(NULL," \t");
						}
						continue;
					}
					token3[count1] = var11;
					var11 = strtok(NULL," \t");
					count1++;
				}
				if(var6 == 1)
					break;
				if(token3[0]!=NULL)
				{
					if(strcmp(token3[0],"cd")==0)
						execute_cd(token3,count1,tempdir,tempdir2,dir);
					else if((token3[0],"pwd")==0)
						printf("%s\n",tempdir);
					else if(strcmp(token3[0], "echo")==0)
						exec_echo(tok,token3,count1,tempdir,tempdir2,dir);
					else if(strcmp(token3[0],"jobs")==0)
						exec_jobs(head,check1,count2);
					else if(strcmp(token3[0],"kjob")==0)
						exec_kjobs(head,token3,bg_arr_size,bg_array);
					else if(strcmp(token3[0],"fg")==0)
						exec_fg(head,token3);
					else if(strcmp(token3[0],"bg")==0)
						exec_bg(head,token3);
					else if(strcmp(token3[0],"setenv")==0 || strcmp(token3[0],"unsetenv")==0)
					        var_env(count1,token3);
					else if(strcmp(token3[0],"killallbg")==0)
						exec_killallbg(head,bg_arr_size,bg_array);
					else if(strcmp(token3[0],"pinfo")==0)
						pinfo_bonus(token3,count1,tempdir);
					else if(check1 != 0)
					{
						pipe(fildes);
						exec_remain_commands(token3,tempdir,tempdir2,dir,count1,bg_arr_size,bg_array,head,var14,var15,check1,check2,count2,fildes,&fd_in);
					}
					else if (check1 == 0)
						printf("No such command\n");
				}
				else
					printf("Command not found\n");
				po++;
			}
			if(var6==1)
				break;
			var10++;
		}
	}
}
