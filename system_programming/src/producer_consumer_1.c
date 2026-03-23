/*ex 1 : 1 producer, 1 consumer using spinlock and busywait */

#include <stdio.h>
#include <pthread.h>	/**/

/*lock status*/
enum
{
	LOCKED = 1,
	NOT_LOCKED = 0
};

typedef int spinlock_ty;

spinlock_ty g_is_locked = NOT_LOCKED;

int shared_resource = 0;

/*acquire lock*/
void SpinLock()
{
    while (__atomic_exchange_n(&g_is_locked, LOCKED, __ATOMIC_ACQUIRE) == LOCKED)
    {
    	/*do nothing (busy wait))*/
    }
}

/*release lock*/
void SpinUnlock()
{
    __atomic_store_n(&g_is_locked, NOT_LOCKED, __ATOMIC_RELEASE);
}

void* Routine(void* arg)
{
    int i;

    for(i = 0; i < 100000; ++i)
    {
        SpinLock();

        shared_resource++;

        SpinUnlock();
    }

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, Routine, NULL);
    pthread_create(&t2, NULL, Routine, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final value: %d\n", shared_resource);

    return 0;
}
