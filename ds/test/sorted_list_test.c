/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : ?
worksheet : 25 (ds - sorted list)
version : 1
date : 25 Dec 2025
stage : writing-code
----------------------------------------------------------------------------*/
#include <stdio.h>				   		  /* printf(), NULL */
#include <stdlib.h> 				      /* malloc(), free(), rand() */
#include <assert.h>				          /* assert() */
/* to randomify data */
#include <math.h>					      /* pow()   */

#include "sorted_list.h" 

#define TRUE   						      1
#define FALSE  						      0
/*magic numbers */
/* data's array size */
#define DATA_ARR_SIZE						10
/* to make the values readable used for modulu */
#define MAX_VAL							100
/*--------------------testing functions----------------------------------------*/



/*-----------------aux functions for dealing with list------------------------*/
/* printing list to the terminal */
static void PrintList(const sorted_list_ty*);
/*-------------------- implementations ----------------------------------------*/
static void PrintList(const sorted_list_ty* list)
{
	const sorted_list_iter list_iter = list;
	const sorted_list_iter end_of_list = SortedListEndIter(list);
	
	printf("sorted-list:\n");
	while(list_iter != end_of_list)
	{
		printf("%d<->");
		list_iter = SortedListIterNext(list_iter);
	}
	return;
}
/*----------------------------------------------------------------------------*/






