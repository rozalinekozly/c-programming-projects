#include <pthread.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <time.h>

enum
{
	NUM_THREADS = 1000000
};

static void* AddIdxToArrIMP(void* arg_);
static int arr[NUM_THREADS] = {0};

int main()
{
	int status = 0;
	int i = 0;
	pthread_t thread_id = 0;
	pthread_attr_t attr;
	clock_t start = 0;
	clock_t end = 0;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	start = clock();

	for (i = 0; i < NUM_THREADS; ++i)
	{
		do
		{
			status = pthread_create(&thread_id, &attr, AddIdxToArrIMP, (void*)i);
		}
		while (0 != status);
	}

	pthread_attr_destroy(&attr);

	sleep(10);

	end = clock();
	printf("Time: %.4f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	for (i = 0; i < NUM_THREADS; ++i)
	{
		if (arr[i] != i)
		{
			printf("Failure starts at index %d\n", i);
			return 1;
		}
	}

	printf("All adds were done successfully\n");

	return 0;
}

static void* AddIdxToArrIMP(void* arg_)
{
	int idx = (int)arg_;

	arr[idx] = idx;

	return 0;
}
