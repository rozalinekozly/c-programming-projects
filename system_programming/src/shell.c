#include <limits.h>	   /*macros: HOST_NAME_MAX, PATH_MAX*/
#include <stdio.h>	   /*printf()*/
#include <unistd.h>    /*getuid(), gethostname(), getcwd()*/
#include <pwd.h>  	   /*getpwuid()*/
#include <string.h>	   /*strtok()*/

enum
{
	MAX_ARGS = 16,
	MAX_INPUT = 256
};

typedef enum
{
	NOT_INTERNAL_CMD = 0,
	EXIT = 1
}internal_cmd_ty;

enum
{

	FAILED_TO_READ_INPUT = 1
};

/* return value : 0 = not an internal command
				  other value = relevant internal command number*/
static int IsInternalCmdIMP(command_);

static void RunInternalIMP(internal_cmd_);

static void PrintPrefixIMP(void);

static void PrintFailure(failure_status_);

int main()
{
	int internal_cmd = NOT_INTERNAL_CMD;
	char input[MAX_INPUT] = {0};
	char* token = NULL;
	char* args[MAX_ARGS] = {NULL};
	int i = 0;
	
    /* while 1 */
    while(1)
    {
    	 /* print prefix <username>@<machine_name>:<current_dir>$ */
    	 PrintPrefixIMP();
        /* read input*/
        if(NULL == fgets(input, MAX_INPUT, stdin))
        {
         	PrintFailure(FAILED_TO_READ_INPUT);
        }
        input[strcspn(input, "\n")] = '\0';
        
        /*split it into words (tokens)*/
        i = 0;
        token = strtok(input, " ");
        while(NULL != token)
        {
        	args[i] = token;
        	token = strtok(NULL, " ");
        	++i;
        }
        args[i] = NULL;
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

static void PrintFailure(failure_status_)
{
    if(FAILED_TO_READ_INPUT == failure_status_)
    {
        perror("failed to read input");
        exit(1);
    }
}

