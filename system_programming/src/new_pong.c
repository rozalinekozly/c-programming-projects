#define _POSIX_C_SOURCE 200809L

#include <signal.h>     /* sigaction(), kill(), SIGUSR1 */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* getppid(), sleep() */
#include <stdio.h>      /* printf(), perror() */
#include <stdlib.h>		/*atpi()*/
#include <assert.h> 
static int g_was_recieved = 0;


void handler(int sig)
{
    (void)sig;
    g_was_recieved = 1;
}

int main(int argc, char* argv[])
{
    struct sigaction sa = {0};
	pid_t another_target = 0;
    sa.sa_handler = handler;
	
	assert(2 == argc);
	
	another_target = (pid_t)(atoi(argv[1]));
	
    if (0 != sigaction(SIGUSR2, &sa, NULL))
    {
        perror("sigaction failed");
        return 1;
    }

	kill(another_target, SIGUSR1);
    while (1)
    {
        while (!g_was_recieved)
        {
            sleep(1);
        }

        g_was_recieved = 0;

        printf("pong\n");

        kill(another_target, SIGUSR1);
    }

    return 0;
}
