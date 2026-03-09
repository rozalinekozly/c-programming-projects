/* 100k thread ex2*/
#include <pthread.h>		/*pthread_create*/
#include <stdio.h>			/*printf()*/

enum
{
	SIZE = 1000000
};

int arr[SIZE] = {0};

static void* AssignIndexIMP(void* idx_);

int main()
{
	pthread_t thread;
	int i = 0;

	for(i = 0 ; i < SIZE ; i++)
	{
		while(0 != pthread_create(&thread, NULL, AssignIndexIMP, (void*)i));
	}
	
	for(i = 0 ; i < SIZE ; i++)
	{
		if(i != arr[i])
		{
			printf("detected first failure at index %d\n", i);
			return 1;
		}
	}
	
	return 0;
}

static void* AssignIndexIMP(void* idx_)
{
	int idx = (int)idx_;
	
	arr[idx] = idx;
	return NULL;
}
