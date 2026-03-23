/* unnamed_threads.c */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
sem_t empty;
sem_t full;

int buffer = 0;

void* Producer(void* arg)
{
    int i;

    (void)arg;

    for(i = 1; i <= 5; i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer = i;
        printf("Produced %d\n", buffer);

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }

    return NULL;
}

void* Consumer(void* arg)
{
    int i;

    (void)arg;

    for(i = 1; i <= 5; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        printf("Consumed %d\n", buffer);

        sem_post(&mutex);
        sem_post(&empty);

        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t p;
    pthread_t c;

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);

    pthread_create(&p, NULL, Producer, NULL);
    pthread_create(&c, NULL, Consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
