#include <stdio.h>
#include <stdlib.h>

void Swap(int*, int*);
int TestSwap(int*, int*);

void CpyArr(int*, int*, int);
int TestCpy(int*, int*, int);

void SwapSizeT(size_t*, size_t*);
int TestSwapSizeT(size_t*, size_t*);

void SwapSizeTPtr(size_t**, size_t**);
int TestSwapSizeTPtr(size_t**, size_t**);

void Swap(int* a, int* b)
{
	  int tmp;
	  tmp = *a;
	  *a = *b;
	  *b = tmp;

}

int TestSwap(int* a, int* b)
{
  int old_a_val = *a;
  int old_b_val = *b;
  
	printf("Before: a = %d, b = %d - ", *a, *b);
	
	Swap(a, b);
	printf("After: a = %d, b = %d - ", *a, *b);

	if ((*a == old_b_val) && (*b == old_a_val))
	{
		printf("TEST PASSED\n\n");
		return 1;
	}
	else
	{
		printf("TEST FAILED\n\n");
		return 0;
	}

}

void CpyArr(int* src, int* dest, int size)
{
	int i;
	printf("Copying the array: ");
	for(i = 0; i < size ; i++)
	{
	        printf("%d ",i);
		dest[i] = src[i];
	}


}

int TestCpy(int* src, int* dest, int size)
{
	int i = 0;
        CpyArr(src, dest, size);
	for(i = 0; i < size ; i++)
	{
		if(src[i] != dest[i]) 
		{
			printf("- TEST FAILED\n\n");
			return 0;
		}
       }
       
       	printf("- TEST PASSED\n\n");
	return 1;

}

void SwapSizeT(size_t* swap1, size_t* swap2)
{
   size_t temp;
   temp = *swap1;
   *swap1 = *swap2;
   *swap2 = temp;
}

int TestSwapSizeT(size_t* a, size_t* b)
{
  size_t old_a_val = *a;
  size_t old_b_val = *b;
  SwapSizeT(a,b);
  
	printf("Before: a = %lu, b = %lu - ", old_a_val, old_b_val);
	printf("After: a = %lu, b = %lu - ", *a, *b);

	if ((*a == old_b_val) && (*b == old_a_val))
	{
		printf("TEST PASSED\n\n");
		return 1;
	}
	else
	{
		printf("TEST FAILED\n\n");
		return 0;
	}
}
/*
void SwapSizeTPtr(size_t** swap1, size_t** swap2)
{
  size_t* modified_swap1 = &swap1;
  size_t* modified_swap2 = &swap2;
  SwapSizeT(modified_swap1, modified_swap2);
}

int TestSwapSizeTPtr(size_t** swap1, size_t** swap2)
{ 
   if(swap1 != swap2)
   {
    printf("TEST FAILED\n");
    return 0;
   }
   printf("TEST PASSED\n");
   return 1;

}

*/

int main()
{
int swap1 = 55;
int swap2 = 66;

int src[] = {1,2,3,4};
int size = (sizeof(src)/sizeof(int));
int* dest = (int*)malloc(size*sizeof(int));

int successed = 0;

size_t a = 1024;
size_t b = 999999999;

printf("\n1 - Swap function test: \n\n"); 
successed += TestSwap(&swap1, &swap2);

printf("2 - copy array test: \n\n");
successed += TestCpy(src, dest, size);

printf("3 - swipe size_t test: \n\n");
successed += TestSwapSizeT(&a, &b);

printf("Successed in %d tests out of 4\n\n", successed);

return 0;
}
