/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : steve 
worksheet : 13 (ds - vector)
version   : 1
date      : 10 Dec 2025
stage     : peer-review
----------------------------------------------------------------------------*/
#include <stdio.h>				/* printf() */
#include "../include/vector.h" 
#include <math.h>		/* pow()   */
#include <stdlib.h>	/* rand() */
#include  <limits.h>		/*INT_MAX*/


#define CAPACITY				10
#define SIZEOF_ARR(ARR)                  (sizeof(ARR)/sizeof(*ARR))
static void TestVectorCreateAndDestroy();
static void TestVectorPushPopAccess();
static void TestVectorSize();
static void TestVectorCapacity();
static void TestVectorReserve();
static void TestVectorShrink();


int main()
{
	TestVectorCreateAndDestroy();
	TestVectorPushPopAccess();
	TestVectorSize();
	TestVectorCapacity();
	TestVectorReserve();
	TestVectorShrink();
	
	return 0;
}
static void TestVectorCreateAndDestroy()
{
	vector_ty* vec = VectorCreate(CAPACITY, sizeof(int));
	
	printf("create\t\t");
	if(NULL == vec)
	{
		printf("failed at creation");
		return;	
	}
	
	if(CAPACITY != VectorCapacity(vec))
	{
		printf("failed at creation in updating capacity\n");
		return;
	}
	printf("PASSED\n");
	printf("destroy\t\t");
	VectorDestroy(vec);
      printf("PASSED\n");
}

static void TestVectorPushPopAccess()
{
	vector_ty* vec = VectorCreate(CAPACITY, sizeof(int));
	int val = 0;
	int arr[] = {12, 100, 87, 99, 48, 70};
	size_t arr_size = SIZEOF_ARR(arr);
	/* array iterator */
	size_t i = 0;

	 printf("push-pop-access\t");
	 for(i = 0 ; i < arr_size ; i++)
	 {
	 	VectorPushBack(vec, &arr[i]);
	 }
	 /* get access*/
	 for(i = 0 ; i < arr_size ; i++)
	 {
	 	val = *(int*)VectorGetAccessToElement(vec,i);
	 	if(val != arr[i])
	 	{
	 		printf("failed at accessing element at index %lu, expected is %d, got %d\n", i, arr[i], val);
	 	}
	 
	 }
	 for(i = 0 ; i < arr_size ; i++)
	 {
	 	VectorPopBack(vec);
	 	val = *(int*)VectorGetAccessToElement(vec,arr_size - 1 - i);
	 	if(val != arr[arr_size - 1 - i])
	 	{
	 		printf("failed at accessing element at index %lu, expected is %d, got %d\n", arr_size - 1 - i, arr[arr_size - 1 - i], val);
	 	}
	 
	 }
	 printf("PASSED\n");
	 VectorDestroy(vec);
}

static void TestVectorSize()
{
	vector_ty* vec = VectorCreate(CAPACITY, sizeof(int));
	size_t i = 0;
	size_t expected_size = 0;
	size_t vec_size = 0;
	int val =  pow(-1,rand()%2)*(rand()%INT_MAX);
	
	printf("size\t\t");
	for(i = 0 ; i <  CAPACITY ; i++)
	{
		VectorPushBack(vec, &val);
		++expected_size;
		vec_size = VectorSize(vec);
		if(vec_size != expected_size)
		{
			printf("failed at size\n");
		}
		
	}
	for(i = 0 ; i <  CAPACITY ; i++)
	{
		VectorPopBack(vec);
		--expected_size;
		vec_size = VectorSize(vec);
		if(vec_size != expected_size)
		{
			printf("failed at size2\n");
		}
		
	}
	
	printf("PASSED\n");
	VectorDestroy(vec);

}

static void TestVectorCapacity()
{
	vector_ty* vec = VectorCreate(CAPACITY, sizeof(int));
	size_t vec_capacity = VectorCapacity(vec);
	
	VectorDestroy(vec);
	printf("capacity\t");
	if(CAPACITY != vec_capacity)
	{
		printf("failed at capacity!\n");
		return;
	}
	printf("PASSED\n");
}

static void TestVectorReserve()
{
      vector_ty* vec = VectorCreate(CAPACITY, sizeof(int));
	int val =  pow(-1,rand()%2)*(rand()%INT_MAX);
	size_t expected_capacity = 2*CAPACITY ;
	size_t vec_capacity = 0;
	size_t i = 0;
	
	printf("push-reserve\t");
	
	for(i = 0 ; i < 2*CAPACITY ; i++)
	{
	
	     VectorPushBack(vec, &val);
	
	}
	
	vec_capacity =  VectorCapacity(vec);
	VectorDestroy(vec);
	
	if(vec_capacity != expected_capacity)
	{
		printf("failed at reserving \n");
		return;
	
	}
	printf("PASSED\n");

}

static void TestVectorShrink()
{
      vector_ty* vec = VectorCreate(CAPACITY, sizeof(int));
	size_t expected_capacity =0;
	size_t vec_capacity = 0;
	size_t i = 0;
	int val =  pow(-1,rand()%2)*(rand()%INT_MAX);
	
	for(i = 0 ; i < CAPACITY/2 ; i++)
	{
	     VectorPushBack(vec, &val);
	}
	
	VectorShrinkToFit(vec);
	expected_capacity = CAPACITY/2;
	vec_capacity = VectorCapacity(vec);
	VectorDestroy(vec);
	
	printf("shrink\t\t");
	if(expected_capacity != vec_capacity)
	{
		printf("failed at shrinking\n");
		return;
	}
	printf("PASSED\n");
	

}







