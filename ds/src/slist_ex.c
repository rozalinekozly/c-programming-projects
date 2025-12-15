/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : Itay
worksheet : 15 (ds - slist exercise)
version   : 1
date      : 15 Dec 2025
stage     : intial
----------------------------------------------------------------------------*/
#include <assert.h>							/* assert() */
#include <stddef.h>						     /* NULL */
#include <stdio.h> /*delete later*/
#include "../include/slist_ex.h"


#define TRUE   					    1
#define FALSE  					    0

#define UNUSED(x)					(void)(x)

node_ty* Flip(node_ty* head)
{
	node_ty* next_node = NULL;
	node_ty* prev_node = NULL;
	node_ty* curr_node = head;
	
	assert(NULL != head);
	
	curr_node = head;
	next_node = head -> next;
	
	while(NULL != curr_node)
	{
		 next_node = curr_node -> next;
      	 curr_node -> next = prev_node;
      	 /* moving forward */
       	 prev_node = curr_node;
        	 curr_node = next_node;
      }
    
    return prev_node;
}


int HasLoop(const node_ty* head)
{
	node_ty* slow = (node_ty*)head;
	node_ty* fast = (node_ty*)head;
	
	while(NULL != slow && NULL != fast && NULL != fast -> next)
	{
		fast = fast -> next -> next;
		slow = slow -> next;
		if (slow == fast)
		{
			/*found a loop*/
			return TRUE;
		}
	}
	
	return FALSE;
} 

node_ty* FindIntersection(node_ty* head_1, node_ty* head_2)
{
	node_ty* list_1_itr = head_1;
	node_ty* list_2_itr = head_2;

	
	/* for each node in head_2 check if all the nodes in head_2 equal to it */
	while (list_2_itr != NULL) 
	{
	  list_1_itr = head_1;
        while (list_1_itr != NULL) 
        {

            if (list_1_itr == list_2_itr)
                return list_2_itr;
            list_1_itr = list_1_itr -> next;
        }
        list_2_itr = list_2_itr -> next;
    }
	return NULL;
}
