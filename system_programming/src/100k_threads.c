/* 100k thread */
#include <pthread.h>		/*pthread_create*/
#include <stdio.h>			/*printf()*/

void* AssignIndexIMP(void* idx_);

int main()
{
	int arr[500000] = {0};
}
 /*int pthread_create(pthread_t *restrict thread,
                          const pthread_attr_t *restrict attr,
                          void *(*start_routine)(void *),
                          void *restrict arg);*/



void* AssignIndexIMP(void* idx_)
{
	int idx = (int)idx_;
	
	arr[idx] = (int)idx;
	return NULL;
}
