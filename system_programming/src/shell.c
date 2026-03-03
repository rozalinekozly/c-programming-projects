#include <limits.h>	   /*macros: HOST_NAME_MAX, PATH_MAX*/
#include <stdio.h>	   /*printf()*/
#include <unistd.h>    /*getuid(), gethostname(), getcwd()*/
#include <pwd.h>  	   /*getpwuid()*/

typedef enum
{
	NOT_INTERNAL_CMD = 0,
	EXIT = 1
}internal_cmd_ty;

/* return value : 0 = not an internal command
				  other value = relevant internal command number*/
static int IsInternalCmdIMP(command_);

static void RunInternalIMP(internal_cmd_);

static void PrintPrefixIMP(void);
int main()
{
	int internal_cmd = NOT_INTERNAL_CMD;
    /* while 1 */
    while(1)
    {
    	 /* print prefix <username>@<machine_name>:<current_dir>$ */
    	 PrintPrefixIMP();
        /* read input and split it into words */
        /* if input is an internal command*/
        internal_cmd = IsInternalCmdIMP(command);
        if(internal_cmd)
        {
        	/*call relevant function*/
        	RunInternalIMP(internal_cmd);
        }
        /*else */
			/* hand the command to the OS to run and save return status*/
			/*if running command failed*/
				/*print to stderr proper error massage*/
    }
    return 0;
}

static void PrintPrefixIMP()
{
	/*declare prefix's paths'*/
	char machine_name[HOST_NAME_MAX] = {0};
    char curr_dir[PATH_MAX] = {0};
    char* username = NULL;
	
	/*extract them using proper sys calls*/
    username = getpwuid(getuid())->pw_name;
    gethostname(machine_name, sizeof(machine_name));
    getcwd(curr_dir, sizeof(curr_dir));
    
    /*print prefix with the order username@machine name:current_dir$*/
    printf("%s@%s:%s$ ", username, machine_name, curr_dir);
}

static int IsInternalCmdIMP(command_)
{
	/*if command is one of internal_cmd_ty*/
		/*return command's code*/
	/*else*/
		/*return NOT_INTERNAL_CMD */
}

static void RunInternalIMP(internal_cmd_)
{
	/*run internal command according to the passed code*/
}

