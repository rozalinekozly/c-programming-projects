/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : steve 
worksheet : 13 (ds - vector)
version   : 1
date      : 14 Dec 2025
stage     : peer- review
----------------------------------------------------------------------------*/
#include <assert.h>				/* assert()  */
#include <string.h>				/* memcpy() */
#include <stdlib.h>				/* malloc(), realloc() */
#include "../include/vector.h" 

#define GROWTH_FACTOR			2
#define SUCCESS				0
#define FAILURE				1

#define FREE(x)			(free(x), x = NULL)

struct vector
{
	/*element size within the vector*/
	size_t element_size;
	/*current size of the vector*/
	size_t size;
	/*capacity of elements the vector can hold*/
	size_t capacity;
	/*the actual vector*/
	char* data;
};

vector_ty* VectorCreate(size_t capacity, size_t element_size)
{
	vector_ty* vector_p = (vector_ty*)malloc(sizeof(vector_ty));
	
	if (NULL == vector_p)
	{
		return NULL;
	}
	
	vector_p -> element_size = element_size;
	vector_p -> size = 0;
	vector_p -> capacity = capacity;
	vector_p -> data = (char*)malloc(capacity * element_size);
	
	if (NULL == vector_p->data)
	{
		free(vector_p);
		vector_p = NULL;
	}
	
	return vector_p;
}

void VectorDestroy(vector_ty* vec)
{
	if(NULL != vec)
	{
		free(vec -> data);
		vec -> data = NULL;
		free(vec);
	}
}

int VectorPushBack(vector_ty* vec, void* data)
{
	size_t placement_to_insert = 0;
	
	assert(NULL != vec);
	assert(NULL != data);
	
	/* reached full capacity */
	if (vec -> size == vec -> capacity)
	{
		/* perform resizing */
		if (FAILURE == VectorReserve(vec, GROWTH_FACTOR * (vec -> capacity)))
		{
			return FAILURE;
		}
	}
	
	/* the placement to insert is where size "points" at*/
	placement_to_insert = (vec -> size) * (vec -> element_size);
	memcpy((vec -> data) + placement_to_insert, data, vec -> element_size);
	/*memmove(vec -> data + placement_to_insert, data, vec -> element_size);*/
	++(vec -> size);
	
	return SUCCESS;
}

void VectorPopBack(vector_ty* vec)
{
	assert(NULL != vec);
	
	--(vec -> size);
}

void* VectorGetAccessToElement(const vector_ty* vec, size_t idx)
{
	assert(NULL != vec);
	assert(idx < (vec -> size)); 
	
	return ((vec -> data) + idx * (vec -> element_size));
}

size_t VectorSize(const vector_ty* vec)
{
	assert(NULL != vec);
	
	return (vec -> size);
}

size_t VectorCapacity(const vector_ty* vec)
{
	assert(NULL != vec);
	
	return (vec -> capacity);
}

int VectorShrinkToFit(vector_ty* vec)
{
	assert(NULL != vec);
	
	return VectorReserve(vec, (vec -> size));
}

int VectorReserve(vector_ty* vec, size_t new_capacity)
{
	assert(NULL != vec);
	
	/*"new capcity represents number of new elements within the vector
         so in order to calculate the actual new capacity we multiply it's value
         with element_size of the vector this operation takes O(n)*/
	vec -> data = (char*)realloc(vec -> data, (vec -> element_size) * new_capacity);
	if (NULL == vec -> data)
	{
		return FAILURE;
	}
		
	vec -> capacity = new_capacity;
	
	return SUCCESS;
}







