/*contains spawn*/
#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>		/*exit*/

static int g_was_recieved = 0;

void handler(int sig)
{
    (void)sig;
    g_was_recieved = 1;
}

int main(void)
{
    pid_t pid = 0;
    struct sigaction sa = {0};

    sa.sa_handler = handler;

    if (0 != sigaction(SIGUSR2, &sa, NULL))
    {
        perror("sigaction failed");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        char *argv[] = {"./ping", NULL};
        execvp(argv[0], argv);

        perror("exec failed");
        exit(1);
    }

	/*parent code*/
    while (1)
    {
        while (!g_was_recieved)
        {
            sleep(1);
        }

        g_was_recieved = 0;

        printf("parent: pong\n");

        kill(pid, SIGUSR1);
    }

    return 0;
}
