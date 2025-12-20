/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : Itay
worksheet : 15 (ds - slist exercise)
version   : 1
date      : 16 Dec 2025
stage     : mimir
----------------------------------------------------------------------------*/
#include <assert.h>				/* assert() */
#include <stddef.h>			      /* NULL */
#include "slist_ex.h"

#define TRUE   					    1
#define FALSE  					    0
/*---------------------- aux functions ---------------------------------------*/
/*
	GoToNode(start-of-list, index-of-node-to-go-to)
	purpose: to traverse over the list and return the node index 
	with index-of-node-to-go-to.
	return values: a pointer to the node with index.
	if number of nodes of list < index-to-go-to then it returns
	NULL .
*/
static node_ty* GoToNode(node_ty* head, size_t idx);
/*
	CountNodes(start-of-list)
	purpose: to count number of nodes in a given list.
	return values:size_t type, in case of NULL it returns zero.
*/
static size_t CountNodes(node_ty* head);

/*---------------------- implementation ---------------------------------------*/
node_ty* Flip(node_ty* head)
{
	node_ty* next_node = NULL;
	node_ty* prev_node = NULL;
	node_ty* curr_node = head;
	
	assert(NULL != head);
	
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
	
	while(NULL != fast && NULL != fast -> next)
	{
		fast = fast -> next -> next;
		slow = slow -> next;
		if (slow == fast)
		{
			return TRUE;
		}
	}
	
	return FALSE;
} 

node_ty* FindIntersection(node_ty* head_1, node_ty* head_2)
{
	node_ty* list_1_itr = head_1;
	node_ty* list_2_itr = head_2;
      size_t count_1 = 0;
      size_t count_2 = 0;
      
      count_1 = CountNodes(head_1);
      count_2 = CountNodes(head_2);
      
      if(count_1 > count_2)
      {
      	list_1_itr = GoToNode(head_1, count_1 - count_2);
      }
      else
      {
      	list_2_itr = GoToNode(head_2, count_2 - count_1);        
      }
      
      while(list_1_itr != list_2_itr)
      {
		list_1_itr = list_1_itr->next;
		list_2_itr = list_2_itr->next;		   
      }
      return list_1_itr;
}
/*---------------------- aux implementation ----------------------------------*/
static node_ty* GoToNode(node_ty* head, size_t idx)
{
	node_ty* itr = head;
	
	while(idx > 0 && NULL != head)
	{
		itr = itr -> next;
		--idx;
	}
	return itr;
}

static size_t CountNodes(node_ty* head)
{
	size_t count = 0;
	node_ty* itr = head;
	
	while(NULL != itr)
	{
		++count;
		itr = itr -> next;
	}
	return count;
}

