#define _POSIX_C_SOURCE 200809L

#include <signal.h>     /* sigaction(), kill(), SIGUSR1 */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* getppid(), sleep() */
#include <stdio.h>      /* printf(), perror() */

static int g_was_recieved = 0;

static pid_t target;

void handler(int sig, siginfo_t* sg, void* param)
{
	(void)param;
	(void)sig;
    g_was_recieved = 1;
    target = sg->si_pid;
}

/*
void handler(int sig)
{
    (void)sig;
    g_was_recieved = 1;
}*/

int main(void)
{
    struct sigaction sa = {0};

    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;

    if (0 != sigaction(SIGUSR1, &sa, NULL))
    {
        perror("sigaction failed");
        return 1;
    }
	
	printf("ping pid is %d\n", getpid());
    while (1)
    {
        while (!g_was_recieved)
        {
            sleep(1);
        }

        g_was_recieved = 0;

        printf("ping\n");

        kill(target, SIGUSR2);
    }

    return 0;
}
