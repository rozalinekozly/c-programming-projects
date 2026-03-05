#define _GNU_SOURCE  /*defined before any include to expose GNU/Linux extensions*/
#include <limits.h>  /* HOST_NAME_MAX, PATH_MAX */
#include <stdio.h>   /* printf(), perror() */
#include <unistd.h>  /* getuid(), gethostname(), getcwd(), fork(), execvp() */
#include <pwd.h>     /* getpwuid() */
#include <string.h>  /* strtok(), strcmp() */
#include <sys/wait.h>/* waitpid() */
#include <stdlib.h>  /* exit() */
#include <assert.h>  /* assert() */

enum
{
	SHELL_MAX_ARGS = 16,
	SHELL_MAX_INPUT = 256
};

typedef enum
{
	NOT_INTERNAL_CMD = 0,
	EXIT = 1
} internal_cmd_ty;

/* return value : 0 = not an internal command
				  other value = relevant internal command number*/
static int IsInternalCmdIMP(char* cmd_);
static void RunInternalIMP(int internal_cmd_);
static void PrintPrefixIMP(void);
static void PrintFailure(const char* msg_);

int ShellRun(void)
{
	int internal_cmd = NOT_INTERNAL_CMD;
	char input[SHELL_MAX_INPUT] = {0};
	char* token = NULL;
	char* args[SHELL_MAX_ARGS] = {NULL};
	int i = 0;
	pid_t pid = 0;
	int status = 0;

    /* while 1 */
    while(1)
	{
    	/* print prefix <username>@<machine_name>:<current_dir>$ */
    	PrintPrefixIMP();

        /* read input*/
        if(NULL == fgets(input, SHELL_MAX_INPUT, stdin))
        {
        	printf("\n");
        	break;
        }

        input[strcspn(input, "\n")] = '\0';
        
        /* split it into words (tokens)*/
        i = 0;
        token = strtok(input, " ");
        while(NULL != token && i < SHELL_MAX_ARGS - 1)
        {
        	args[i] = token;
        	token = strtok(NULL, " ");
        	++i;
        }
        args[i] = NULL;
		
		/* if command is enter continue */
		if(NULL == args[0])
		{
   			continue;
		}

        /* if input is an internal command*/
        internal_cmd = IsInternalCmdIMP(args[0]);
        if(internal_cmd)
        {
        	/* call relevant function */
        	RunInternalIMP(internal_cmd);
        	continue;
        }

		/* fork */
		pid = fork();

		/* if fork failed */
		if(-1 == pid)
	   	{
	   		PrintFailure("fork failed");
	   		continue;
	   	}
		/* if child (pid == 0) */
		else if(0 == pid)
	  	{
	  		/* execvp(args[0], args) */
	  		execvp(args[0], args);

	  		/* if we reach here execvp failed */
			PrintFailure("execvp failed");
			exit(1); /* child exits only */
	  	}
   		/* if parent (pid > 0) */
   		else
   		{
   		 	/* wait and save status */
	    	if(-1 == waitpid(pid, &status, 0))
	        {
	        	PrintFailure("waitpid failed");
	        	continue;
	        }

	        /* if child exited normally */
	        if (WIFEXITED(status))
	        {
	        	int code = WEXITSTATUS(status);

	        	/* if exit code != 0 */
	        	if (0 != code)
	        	{
	        		printf("command exited with status %d\n", code);
	        	}
	        }
	        /* if child was killed by signal */
	        else if (WIFSIGNALED(status))
	        {
	        	printf("command killed by signal %d\n", WTERMSIG(status));
	        }
   		}
    }

    return 0;
}

int main(void)
{
	return ShellRun();
}

static void PrintPrefixIMP(void)
{
	/* declare prefix's paths */
	char machine_name[HOST_NAME_MAX] = {0};
    char curr_dir[PATH_MAX] = {0};
	struct passwd* pw = NULL;
	
	/* extract them using proper sys calls */
	pw = getpwuid(getuid());
	if(NULL == pw)
	{
		PrintFailure("getpwuid failed");
		return;
	}

    if(-1 == gethostname(machine_name, sizeof(machine_name)))
    {
    	PrintFailure("gethostname failed");
    	return;
    }

    if(NULL == getcwd(curr_dir, sizeof(curr_dir)))
    {
    	PrintFailure("getcwd failed");
    	return;
    }
    
    /* print prefix username@machine_name:current_dir$ */
    printf("%s@%s:%s$ ", pw->pw_name, machine_name, curr_dir);
}

static int IsInternalCmdIMP(char* cmd_)
{
	assert(cmd_);

	/* if command is exit */
	if(0 == strcmp(cmd_, "exit"))
	{
		return EXIT;
	}

	/* else */
	return NOT_INTERNAL_CMD;
}

static void RunInternalIMP(int internal_cmd_)
{
	/* run internal command according to the passed code */
	if(EXIT == internal_cmd_)
	{
		exit(0);
	}
}

static void PrintFailure(const char* msg_)
{
	assert(msg_);
	perror(msg_);
}
