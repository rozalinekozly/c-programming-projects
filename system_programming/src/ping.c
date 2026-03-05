/*child code*/
#define _POSIX_C_SOURCE 200809L

#include <signal.h>     /* sigaction(), kill(), SIGUSR1 */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* getppid(), sleep() */
#include <stdio.h>      /* printf(), perror() */

static int g_was_recieved = 0;

void handler(int sig)
{
    (void)sig;
    g_was_recieved = 1;
}

int main(void)
{
    struct sigaction sa = {0};

    sa.sa_handler = handler;

    if (0 != sigaction(SIGUSR1, &sa, NULL))
    {
        perror("sigaction failed");
        return 1;
    }

	kill(getppid(), SIGUSR2);
    while (1)
    {
        while (!g_was_recieved)
        {
            sleep(1);
        }

        g_was_recieved = 0;

        printf("child: ping\n");

        kill(getppid(), SIGUSR2);
    }

    return 0;
}
