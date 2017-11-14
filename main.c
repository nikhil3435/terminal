#include "test.h"
char tempdir[1024];
char tempdir2[1024];
char dir[1024];
void handle_stp(int sig)
{
	signal(sig,SIG_IGN);
}
void my_handler(int sig)
{
	printf("\n");
	print_prompt(tempdir,tempdir2,dir);
	fflush(stdout);
}
int main(int argc,char** argv)
{
	int exit_status = 0,count=0,bg_arr_size=0;
	int bg_array[2000];
	int pid;
	uid_t uid;
	node *head=NULL;
	char machname[1024];
	getcwd(dir,sizeof(dir));
	getcwd(tempdir,sizeof(tempdir));
	int var1 = gethostname(machname,sizeof(machname));
	strcpy(tempdir2,tempdir);
  signal(SIGINT,my_handler);
  signal(SIGTSTP,handle_stp);
	while(1)
	{
		char full_dir_path[1024];
		full_dir_path[0]='~';
		int i,j;
		for(j=1; j<1024; j++)
			full_dir_path[j]=0;
		int var3 = max(strlen(tempdir),strlen(dir));
		print_prompt(tempdir,tempdir2,dir);
		int status,count3=0;
		bg_check(bg_array,&bg_arr_size,&head);
		separating_commands(tempdir,tempdir2,dir,&exit_status,&bg_arr_size,bg_array,&head);
		if(exit_status == 1)
		{
			printf("terminated\n");
			break;
		}
	}
	return 0;
}
