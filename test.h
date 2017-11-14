#define _BUILT_IN_COMMANDS_H
#define PROMPT_H
#define _EXEC_REM_COMMANDS_H
#define _SEPARATE_COMMANDS_H
#define _NODE_H
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<pwd.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>
typedef struct node
{
	int pid_of_bg;
	char *pid_str;
	struct node *next;
}node;
int max(int a, int b);
void print_prompt(char *tempdir,char *tempdir2,char *dir);
void bg_check(int* bg_array,int *bg_arr_size,node **head);
void execute_cd(char **token, int count,char tempdir[],char tempdir2[],char dir[]);
int compare_exit(char *token,char tempdir[],char tempdir2[],char dir[],int *exit_status);
void exec_echo(char *token,char **token1,int count,char tempdir[],char tempdir2[],char dir[]);
void exec_jobs(node **head,int check1,int count2);
void exec_kjobs(node **head, char **token3,int *bg_arr_size,int *bg_array);
void exec_fg(node **head, char **token3);
void exec_bg(node **head, char **token3);
void exec_killallbg(node **head,int *bg_arr_size,int *bg_array);
void pinfo_bonus(char **token3, int count1, char tempdir2[]);
void check_symbol(char **token1,int var10);
void separating_commands(char tempdir[],char tempdir2[],char dir[],int *exit_status,int *bg_arr_size,int bg_array[],node **head);
void exec_remain_commands(char **token3,char *tempdir,char tempdir2[],char dir[],int count,int *bg_arr_size, int bg_array[],node **head,char* var14,char *var15, int check1, int check2, int count2, int *fildes, int *fd_in);
void var_env(int argc, char *argv[]);

