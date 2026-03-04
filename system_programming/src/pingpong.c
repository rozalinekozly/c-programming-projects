#define _POSIX_C_SOURCE 200809L

#include <signal.h>	/*sigaction(), kill(), SIGUSR1, SIGUSR2*/
#include <sys/types.h>	/*pid_t*/
#include <unistd.h>	/*fork(), getppid(), pause()*/
#include <stdio.h>	/*printf(), perror()*/

/*set a global semaphore (flag) to signal to process if it is it's
  turn to send a signal back*/
static int g_flag = 0;

/* declare on a handler to turn-on the global flag */
void handler(int sig)
{
    (void)sig;
    g_flag = 1;
}

int main(void)
{
    pid_t pid = 0;
    struct sigaction sa = {0};
	
    /*set handler to be sigactions's field*/
    sa.sa_handler = handler;

    if(0 != (sigaction(SIGUSR1, &sa, NULL) || sigaction(SIGUSR2, &sa, NULL)))
    {
    	perror("failed at setting new action to signal SIGUSR1\n");
    	return 1;
    }
	
	/*fork a child*/
    pid = fork();
	/*handle failure*/
    if (pid < 0) 
    {
        perror("fork failed");
        return 1;
    }

	/*if process is child*/
    if (0 == pid)
    {
    	/*intiate a signal from child */
        printf("child: Sending initial Ping\n");
        kill(getppid(), SIGUSR2);
		
		/*run an infinite loop (child's main body)*/
        while (1)
        {
            /* wait for signal */
            while (!g_flag) 
            {
                pause();
            }
            /*turn flag off*/
            g_flag = 0;
            printf("child: ping\n");
            /*send back signal*/
            kill(getppid(), SIGUSR2);
        }
    }
    /*parent process*/
    else
    {
    	/*parent body*/
        while (1)
        {
            /*wait for signal */
            while (!g_flag) 
            {
                pause();
            }
			/*turn off flag*/
            g_flag = 0;
            printf("parent: pong\n");
            /*send back signal*/
            kill(pid, SIGUSR1);
        }
    }

    return 0;
}
