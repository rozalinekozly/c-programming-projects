#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>
#include <omp.h>

int main()
{
	struct timespec t1, t2;
	unsigned int number = 0;
	unsigned int sum = 0;
	unsigned int i = 0;

	printf("Enter a 10-12 digit number: ");
	scanf("%lu", &number);

	clock_gettime(CLOCK_MONOTONIC, &t1);

	#pragma omp parallel for reduction(+:sum)
	for (i = 1; i <= number; ++i)
	{
		if (0 == number % i)
		{
			sum += i;
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &t2);

	printf("Sum of divisors: %lu\n", sum);
	printf("Time: %.4f seconds\n",
		(t2.tv_sec - t1.tv_sec) + (t2.tv_nsec - t1.tv_nsec) / 1e9);

	return 0;
}
