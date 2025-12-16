/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : Itay
worksheet : 15 (ds - slist exercise)
version   : 1
date      : 15 Dec 2025
stage     : intial
----------------------------------------------------------------------------*/
#include <stdio.h>				     /* printf(), NULL */
#include <stdlib.h> 				     /* malloc(), free(), rand() */
#include <assert.h>				     /* assert() */
/* to randomify data */
#include <math.h>					      /* pow()   */

#include "slist_ex.h" 

#define TRUE   						      1
#define FALSE  						      0
/*magic numbers */
/* data's array size */
#define DATA_ARR_SIZE						10
/* to make the values readable used for modulu */
#define MAX_VAL						100
/*--------------------testing functions----------------------------------------*/
static void TestFlip();
static void TestHasLoop();
static void TestFindIntersection();
/*-----------------aux functions for dealing with list------------------------*/
/* printing list to the terminal */
static void PrintList(node_ty*); 
/* push to list (pushes to head)*/
static void Push(node_ty**, int*);
/* function to generate random data */
static void GenereateData(int* arr, size_t arr_size);
/* function to generate a list from given array */
static node_ty* GenerateListFrmArr(node_ty* head, int* arr, size_t arr_size);
/* free list*/
static void FreeList(node_ty* head);
/* getter for tail node */
static node_ty* GetTailNode(node_ty* head);
/* get random node from list */
static node_ty* GetRandomNodeFromList(node_ty* head, size_t list_size);
/*-------------------- implementations ----------------------------------------*/
int main() 
{
	TestFlip();
	TestHasLoop();
	TestFindIntersection();
    	return 0;
}
/*---------------------- aux functions ----------------------------------------*/
static void PrintList(node_ty* head) 
{
    node_ty* tmp = head;
    while (NULL != tmp) {
        printf("%d -> ",*(int*) tmp->data);
        tmp = tmp->next;
    }
    printf("NULL\n");
}

static void Push(node_ty** head_ref, int* new_data)
 {
    node_ty* new_node = (node_ty*)malloc(sizeof(node_ty));
    new_node -> data = new_data;
    new_node -> next = (*head_ref);
    (*head_ref) = new_node;
}

static void GenereateData(int* arr, size_t arr_size)
{
    size_t i = 0;
     
    /* intialize data's array */
    for(i = 0 ; i < arr_size ; ++i)
    {
    	arr[i] = pow(-1,i)*(rand()%MAX_VAL);
    
    }
}

static node_ty* GenerateListFrmArr(node_ty* head, int* arr, size_t arr_size)
{
 	 size_t i = 0;
 	 
  	for(i = 0 ; i < arr_size ; ++i)
  	{
		Push(&head, &arr[i]);
  	}
   	return head;
}

static void FreeList(node_ty* head)
{
	node_ty* tmp = head;
	while(NULL != head)
	{
		tmp = head -> next;
		free(head);
		head = tmp;
	}
}

static node_ty* GetTailNode(node_ty* head)
{
	/* in order not to lose the head*/
	node_ty* tail = head;
	
	while(NULL != tail -> next)
	{
		tail = tail -> next;
	}
	return tail;
}

static node_ty* GetRandomNodeFromList(node_ty* head, size_t list_size)
{
	size_t random = rand() % list_size;
	node_ty* itr = head;
	
	while(random > 0)
	{
		itr = itr -> next;
		--random;
	}
	
	return itr;
}
/*-------------------- testing functions --------------------------------------*/
static void TestFlip()
{
	node_ty* head = NULL;
	int arr[DATA_ARR_SIZE] = {0};

	GenereateData(arr, DATA_ARR_SIZE);
	head = GenerateListFrmArr(head, arr, DATA_ARR_SIZE);
	printf("flip:\n");
	printf("Original list: ");
	PrintList(head);
	head = Flip(head);
	printf("Flipped list: ");
	PrintList(head);
	FreeList(head);
}

static void TestHasLoop()
{
	node_ty* head = NULL;
	node_ty* tail = NULL;
	node_ty* knot = NULL;
	int arr[DATA_ARR_SIZE] = {0};
	int has_loop = FALSE;

	GenereateData(arr, DATA_ARR_SIZE);
	head = GenerateListFrmArr(head, arr, DATA_ARR_SIZE);	
	tail = GetTailNode(head);
	knot = GetRandomNodeFromList(head, DATA_ARR_SIZE);
	tail -> next = knot;
	has_loop = HasLoop(head);
	
	printf("has loop (with loop)\t\t");
	if(TRUE == has_loop)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("failed at detecting the loop!\n");
	}
	
	/* fix loop */
	tail -> next = NULL;
	has_loop = HasLoop(head);
	printf("has loop (w/out loop)\t\t");
	if(FALSE == has_loop)
	{
		printf("PASSED\n");
	}
	else
	{
		printf("failed at detecting the loop!\n");
	}
	
	FreeList(head);
}


static void TestFindIntersection()
{
	node_ty* head_1 = NULL;
	node_ty* head_2 = NULL;
	node_ty* tail_2 = NULL;
	node_ty* intersection_node = NULL;
	int arr_1[DATA_ARR_SIZE] = {0};
	int arr_2[DATA_ARR_SIZE] = {0};
	node_ty* ret_node = NULL;

	/* create random data*/
	GenereateData(arr_1, DATA_ARR_SIZE);
	GenereateData(arr_2, DATA_ARR_SIZE);
	/* create list from given data's array */
	head_1 = GenerateListFrmArr(head_1, arr_1, DATA_ARR_SIZE);	
	head_2 = GenerateListFrmArr(head_2, arr_2, DATA_ARR_SIZE);
			
	tail_2 = GetTailNode(head_2);
	intersection_node = GetRandomNodeFromList(head_1, DATA_ARR_SIZE);
	tail_2 -> next = intersection_node;		
	
	ret_node = FindIntersection(head_1, head_2);
	
	printf("find intersection \t\t");
	if(ret_node != intersection_node)
	{
		printf("FAILED\n");
	}
	else
	{
		printf("PASSED\n");
	}
	/* fix the intersection node */
	tail_2 -> next = NULL;
	FreeList(head_1);
	FreeList(head_2);
}


