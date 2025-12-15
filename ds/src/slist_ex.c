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
#include "../include/slist_ex.h"


#define TRUE    1
#define FALSE   0

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
	node_ty* slow = head;
	node_ty* fast = head;
	
	while(NULL != fast && NULL != fast -> next)
	{
		if(slow == fast)
		{
			/*found a loop*/
			return TRUE;
		}
		fast = fast -> next -> next;
		slow = slow -> next;
	}
	
	return FALSE;
}

node_ty* FindIntersection(node_ty* head_1, node_ty* head_2)
{


}
