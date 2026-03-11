#define _POSIX_C_SOURCE 199309L
#include <pthread.h>
#include <stdio.h>
#include <time.h>

enum
{
	NUM_THREADS = 4
};

typedef struct
{
	unsigned long start;
	unsigned long end;
	unsigned long result;
} Args;

static unsigned long number = 0;
static Args args[NUM_THREADS];

static void* SumDivisorsIMP(void* arg_)
{
	Args *a = (Args*)arg_;
	unsigned long i = 0;

	a->result = 0;
	for (i = a->start; i <= a->end; ++i)
	{
		if (0 == number % i)
		{
			a->result += i;
		}
	}

	return 0;
}

int main()
{
	pthread_t threads[NUM_THREADS];
	struct timespec t1, t2;
	unsigned long total = 0;
	unsigned long chunk = 0;
	int i = 0;

	printf("Enter a 10-12 digit number: ");
	scanf("%lu", &number);

	chunk = number / NUM_THREADS;

	clock_gettime(CLOCK_MONOTONIC, &t1);

	for (i = 0; i < NUM_THREADS; ++i)
	{
		args[i].start = i * chunk + 1;
		args[i].end = (i == NUM_THREADS - 1) ? number : (i + 1) * chunk;
		args[i].result = 0;
		pthread_create(&threads[i], NULL, SumDivisorsIMP, &args[i]);
	}

	for (i = 0; i < NUM_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
		total += args[i].result;
	}

	clock_gettime(CLOCK_MONOTONIC, &t2);

	printf("Sum of divisors: %lu\n", total);
	printf("Time: %.4f seconds\n",
		(t2.tv_sec - t1.tv_sec) + (t2.tv_nsec - t1.tv_nsec) / 1e9);

	return 0;
}
