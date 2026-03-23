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
int g_shared_counter = 0;
/*-------------------------- forward declarations ----------------------------*/
static void* ProducerThreadIMP(void* arg);
static void* ConsumerThreadIMP(void* arg);

static int ProduceIMP(void);
static void ConsumeIMP(void);

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
static void SpinLockIMP()
{
    while (__atomic_exchange_n(&g_is_locked, LOCKED, __ATOMIC_ACQUIRE) == LOCKED)
    {
    	/*do nothing (busy wait))*/
    }
}
/*----------------------------------------------------------------------------*/
/*release lock*/
static void SpinUnlockIMP()
{
    __atomic_store_n(&g_is_locked, NOT_LOCKED, __ATOMIC_RELEASE);
}
/*----------------------------------------------------------------------------*/
static void* ProducerThreadIMP(void* arg)
{
	UNUSED(arg);
	
	while(1)
	{
		/*aquire lock*/
		SpinLockIMP();
		/*perform critical section*/
		ProduceIMP();
		/*free lock*/
		SpinUnlockIMP();
	}
}
/*----------------------------------------------------------------------------*/
static void* ConsumerThreadIMP(void* arg)
{
	UNUSED(arg);
	
	while(1)
	{
		/*aquire lock*/
		SpinLockIMP();
		/*perform critical section*/
		ConsumeIMP();
		/*free lock*/
		SpinUnlockIMP();
	}
}
/*----------------------------------------------------------------------------*/
static int ProduceIMP(void)
{
	/*increment g_shared_counter (atomic increment)*/
	__atomic_fetch_add(&g_shared_counter,1, __ATOMIC_SEQ_CST);
}
/*----------------------------------------------------------------------------*/
static void ConsumeIMP(void)
{
	/*print g_shared_counter value*/
	int val = __atomic_load_n(&g_shared_counter, __ATOMIC_SEQ_CST);
	printf("consumer read %d\n", val);
}
/*----------------------------------------------------------------------------*/

