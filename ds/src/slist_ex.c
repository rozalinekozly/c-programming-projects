/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : ?
worksheet : 15 (ds - slist exercise)
version   : 1
date      : 14 Dec 2025
stage     : intial
----------------------------------------------------------------------------*/
#include <assert.h>							/* assert() */
#include "../include/slist_ex.h"


#define TRUE    1
#define FALSE   0

node_ty* Flip(node_ty* head)
{
	node_ty* next_node = head -> next;
	node_ty* prev_node = head;
	assert(NULL != head);
	
	while(NULL != next_node)
	{
		next_node -> next = prev_node;
		prev_node = next_node;
		next_node ->= next;
	}
	head = prev_node;
	return head;
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
