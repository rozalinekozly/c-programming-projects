/*ex 1 : 1 producer, 1 consumer using spinlock and busywait */

#include <stdio.h>
#include <pthread.h>	/**/

#include "utils.h"
/*----------------------------------------------------------------------------*/
/*lock status*/
enum
{
	LOCKED = 1,
	NOT_LOCKED = 0
};

typedef int spinlock_ty;

/*declare on a lock*/
spinlock_ty g_is_locked = NOT_LOCKED;
/*declare on a "shared" memory*/
/*producer : increments shared_resource
 cosumer reads and print the value*/
int shared_resource = 0;
/*-------------------------- forward declarations ----------------------------*/
static void* ProducerThreadIMP(void* arg);
static void* ConsumerThreadIMP(void* arg);

static int ProduceIMP(void);
static void ConsumeIMP(int product);

static void SpinLockIMP(void);
static void SpinUnlockIMP(void);
/*----------------------------------------------------------------------------*/
int main()
{
    pthread_t producer;
    pthread_t consumer;

	/*create a producer thread, to perform ProducerThreadIMP()*/
    while(0 != pthread_create(&producer, NULL, ProducerThreadIMP, NULL));
    /*create a consumer thread, to perform ConsumerThreadIMP()*/
    while(0 != pthread_create(&consumer, NULL, ConsumerThreadIMP, NULL));
	
	/*join threads before exiting*/
    EXIT_IF_BAD(0 == pthread_join(producer, NULL), 1, "failed to join producer");
    EXIT_IF_BAD(0 == pthread_join(consumer, NULL), 1, "failed to join consumer");

    return 0;
}
/*----------------------------------------------------------------------------*/
/*acquire lock*/
void SpinLock()
{
    while (__atomic_exchange_n(&g_is_locked, LOCKED, __ATOMIC_ACQUIRE) == LOCKED)
    {
    	/*do nothing (busy wait))*/
    }
}
/*----------------------------------------------------------------------------*/
/*release lock*/
void SpinUnlock()
{
    __atomic_store_n(&g_is_locked, NOT_LOCKED, __ATOMIC_RELEASE);
}
/*----------------------------------------------------------------------------*/
static void* ProducerThreadIMP(void* arg)
{
	UNUSED(arg);
}
/*----------------------------------------------------------------------------*/
static void* ConsumerThreadIMP(void* arg)
{
	UNUSED(arg);
}
/*----------------------------------------------------------------------------*/
static int ProduceIMP(void)
{

}
/*----------------------------------------------------------------------------*/
static void ConsumeIMP(int product)
{

}
/*----------------------------------------------------------------------------*/
/*rmv later*/
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


