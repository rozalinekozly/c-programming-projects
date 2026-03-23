/*spinlock template */
/*
	notes:
	- __atomic_* are GCC builtins
	- not part of POSIX/libc
	- implemented by computer, not OS
	* so no man page for ti
*/
/*
	atomic functions:
	1) type __atomic_load_n(type* ptr, int memorder)
	 e.g: val = __atomic_load_n(&x, __ATOMIC_SEQ_CST);
	 	gurantees you read a real, consistent value.
	 	load = safe read + visibility control.
	 	visibility control = when one thread's changes become seen by another
	 	threas.
	 	visibility control -> safe handoff.
	 	- memorder: rules that control when other threads see your change
	 	1- __ATOMIC_RELAXED
	 		only gurantees operation is atomic, no ordering and no visibility
	 		 gurantees
	 		 "everything i did before is now visible""
	 	2- __ATOMIC_ACQUIRE
	 		used when reading (lock), gurantees everything after this line sees
	 		fresh data.
	 		(lock -> then read data)
	 		"if i see your signal, then i see your past"
	 	3- __ATOMIC_RELEASE
	 		used when writing(unlock)
	 		gurantees everything before this line is visible to others
	 		(write data -> then unlock)
	 	4- __ATOMIC_SEQ_CST
	 		gurantees global order across all threads
	 		"everything happens in a single agreed order"
	 		
	2) void __atomic_store_n(type* ptr, type val, int memorder)
		purpose: atomatically write a value to a shared variable with 
		controlled visibility.
		it gurantees no partial write (atomic) and visibility control based
		on memorder.
		
	3) type __atomic_exchange_n(type* ptr, type val, int memorder)
    	purpose: atomically replace *ptr with val (unconditional swap).
    	return:
        old value that was in *ptr
        notes: always writes, wheras CAS writes only if needed
*/
#include <stdio.h>
#include <pthread.h>	/*multi-threaded program (elaborate more)*/

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
