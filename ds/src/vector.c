/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : steve 
worksheet : 13 (ds - vector)
version   : 1
date      : 10 Dec 2025
stage     : intial
----------------------------------------------------------------------------*/

#include "../include/vector.h" 

#define GROWTH_FACTOR		2
#define FREE(x)			(free(x), x = NULL)
struct vector
{
	size_t element_size;
	size_t current_size;
	size_t capacity;
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
	vector_p -> current_size = 0;
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
	
	free(vec -> data);
	vec -> data = NULL;
	free(vec);


}


int VectorPushBack(vector_ty* vec, void* data)
{



}







