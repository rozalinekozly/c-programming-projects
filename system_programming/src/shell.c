#define _GNU_SOURCE  /* exposes gethostname(), HOST_NAME_MAX */
#include <limits.h>  /* HOST_NAME_MAX, PATH_MAX */
#include <stdio.h>	   /*printf()*/
#include <unistd.h>    /*getuid(), gethostname(), getcwd(), pid_t, fork()*/
#include <pwd.h>  	   /*getpwuid()*/
#include <string.h>	   /*strtok()*/
#include <sys/wait.h>  /* wait() */
#include <stdlib.h>	   /*exit()*/
#include "shell.h"

enum
{
	SHELL_MAX_ARGS = 16,
	SHELL_MAX_INPUT = 256
};
typedef enum
{
	NOT_INTERNAL_CMD = 0,
	EXIT = 1
}internal_cmd_ty;
enum
{
	FAILED_TO_READ_INPUT = 1,
	FAILED_TO_FORK = 2,
	FAILED_EXECVP = 3,
	FAILED_WAIT = 4,
	FAILED_TO_GET_CURR_DIR = 5,
	FAILED_TO_GET_HOST_NAME = 6
};

/* return value : 0 = not an internal command
				  other value = relevant internal command number*/
static int IsInternalCmdIMP(char* cmd_);
static void RunInternalIMP(int internal_cmd_);
static void PrintPrefixIMP(void);
static void PrintFailure(int failure_status_);

int ShellRun(void)
{
	int internal_cmd = NOT_INTERNAL_CMD;
	char input[SHELL_MAX_INPUT] = {0};
	char* token = NULL;
	char* args[SHELL_MAX_ARGS] = {NULL};
	int i = 0;

    /* while 1 */
    while(1)
	{
    	 /* print prefix <username>@<machine_name>:<current_dir>$ */
    	 PrintPrefixIMP();

        /* read input*/
        if(NULL == fgets(input, SHELL_MAX_INPUT, stdin))
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
        internal_cmd = IsInternalCmdIMP(args[0]);
        if(internal_cmd)
        {
        	/*call relevant function*/
        	RunInternalIMP(internal_cmd);
        }
		else
		{
	  		  /* fork */
	  		  pid_t pid = fork();

			/* if fork failed */
			if(-1 == pid)
		   	{
		   		PrintFailure(FAILED_TO_FORK);
		   	}
			/* if child (pid == 0) */
			else if(0 == pid)
		  	{
		  		/* execvp(args[0], args) */
		  		execvp(args[0], args);
		  		/* if we reach here execvp failed */
				PrintFailure(FAILED_EXECVP);
		  	}
	   		/* if parent (pid > 0) (else) */
	   		else
	   		{
	   		 	/* wait and save status */
		    	/* if wait failed */
		    	if(-1 == wait(NULL))
		        {
		        	PrintFailure(FAILED_WAIT);
		        }
	   		}
		}
    }
    return 0;
}

int main()
{
	return ShellRun();
}

static void PrintPrefixIMP(void)
{
	/*declare prefix's paths'*/
	char machine_name[HOST_NAME_MAX] = {0};
    char curr_dir[PATH_MAX] = {0};
    char* username = NULL;
	
	/*extract them using proper sys calls*/
    username = getpwuid(getuid())->pw_name;
    if(-1 == gethostname(machine_name, sizeof(machine_name)))
    {
    	PrintFailure(FAILED_TO_GET_HOST_NAME);
    }
    if(NULL == getcwd(curr_dir, sizeof(curr_dir)))
    {
    	PrintFailure(FAILED_TO_GET_CURR_DIR);
    }
    
    /*print prefix with the order username@machine name:current_dir$*/
    printf("%s@%s:%s$ ", username, machine_name, curr_dir);
}

static int IsInternalCmdIMP(char* cmd_)
{
	/*if command is one of internal_cmd_ty*/
	if(0 == strcmp(cmd_, "exit"))
	{
		/*return command's code*/
		return EXIT;
	}	
	/*else*/
	else
	{
		/*return NOT_INTERNAL_CMD */
		return NOT_INTERNAL_CMD;
	}
}

static void RunInternalIMP(int internal_cmd_)
{
	/*run internal command according to the passed code*/
	if(EXIT == internal_cmd_)
	{
		exit(0);
	}
}

static void PrintFailure(int failure_status_)
{
	/*according to each failure code print appropriate msg to stderr*/
    if(FAILED_TO_READ_INPUT == failure_status_)
    {
        perror("failed to read input");
    }
    else if(FAILED_TO_FORK == failure_status_)
    {
        perror("failed to fork");
    }
    else if(FAILED_EXECVP == failure_status_)
    {
        perror("failed to execvp");
    }
    else if(FAILED_WAIT == failure_status_)
    {
        perror("failed to wait");
    }
    else if(FAILED_TO_GET_CURR_DIR == failure_status_)
    {
    	perror("getcwd failed");
    }
    else if(FAILED_TO_GET_HOST_NAME == failure_status_)
    {
    	perror("gethostname failed");
    }
    exit(1);
}
