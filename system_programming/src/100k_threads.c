/* 100k thread */
#include <pthread.h>		/*pthread_create*/
#include <stdio.h>			/*printf()*/

enum
{
	SIZE = 500000
};

int arr[SIZE] = {0};

void* AssignIndexIMP(void* idx_);
/*void InitIdxArrIMP(int idx[]);*/

int main()
{
	pthread_t threads[SIZE];
	int i = 0;
	
	/*int idx[SIZE] ={0};
	InitIdxArrIMP(idx);*/

	for(i = 0 ; i < SIZE ; i++)
	{
		pthread_create(&threads[i], NULL, AssignIndexIMP, (void*)&i);
	}
	
	for(i = 0 ; i < SIZE ; i++)
	{
		if(i != arr[i])
		{
			printf("detected first failure at index %d\n", i);
			return 1;
		}
		else
		{
			printf("success %d\n", i);
		}
	}
	
	return 0;
}

void* AssignIndexIMP(void* idx_)
{
	int idx = *(int*)idx_;
	
	arr[idx] = (int)idx;
	return NULL;
}

void InitIdxArrIMP(int idx[])
{
	int i = 0;
	for(i = 0 ; i < SIZE ; i++)
	{
		idx[i] = i;
	}
}



