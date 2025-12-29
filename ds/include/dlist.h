#ifndef __ILRD_DLIST_H_
#define __ILRD_DLIST_H_

#include <stddef.h>	/* size_t */

typedef struct dlist dlist_ty;

typedef struct dlist_node dlist_node_ty;

/* May change - do not touch or use it */
typedef dlist_node_ty* dlist_iter_ty;

/****************************************************************************** 
*   Function receives node's data ("data"), any other parameter may be
*		passed with "param".
*	Function should return 0 on success, any other value will be considered
*		failure.
******************************************************************************/
typedef int (*action_func_ty)(void* data, void* param);

/****************************************************************************** 
*   Function receives node's data ("data"), any other parameter may be
*		passed with "param".
*	Function should return 0 on success and 1 on failure.
******************************************************************************/
typedef int (*is_match_func_ty) (const void* data, void* param);
/*----------------------------------------------------------------------------*/
/*
	syntax: 	    DListCreate(void)
	purpose: 	    constructs a doubly-linked-list data structure instance.
	return values:  an iterator to the constructed list, in case it succeed.
					NULL if construction failed.
	time complexity:O(1)
 */
dlist_ty* DListCreate(void);
/*----------------------------------------------------------------------------*/
/*
	syntax: 	    DListDestroy(ptr-to-list)
	purpose: 	    destruct a doubly-linked-list instance.
	return values:  void
	time complexity:O(n)
 */
void DListDestroy(dlist_ty* dlist);
/*----------------------------------------------------------------------------*/
/*
	syntax: 	    DListCount(iter-to-dlist)
	arguments:      pointer to dlist instance.
	purpose: 	    to count number of nodes in the dlist instance.
	return values:  nodes in the instance.
	UB:				dlist is NULL.
	time complexity:O(n)
 */
size_t DListCount(const dlist_ty* dlist);
/*----------------------------------------------------------------------------*/
/*
	syntax: 	    DListIsEmpty(iter-to-dlist)
	arguments:      pointer to dlist instance.
	purpose: 	    to answer the question is dlist empty.
	return values:  TRUE = 1 = it is empty
					FALSE = 0 otherwise.
	UB:				dlist is NULL.
	time complexity:O(1)
 */
int DListIsEmpty(const dlist_ty* dlist);
/*----------------------------------------------------------------------------*/
/*
	syntax: 	    DListInsertBefore(iter-to-dlist, where-iter, new-data)
	arguments:      iter-to-dlist: pointer to dlist.
					 where-iter: iter to the placement to insert before.
					 new-data: data of the new node to insert.
	purpose: 	    insert a new node with the passed data before where-iter.
	return values:  if insertion succeed: an iterator to newly inserted node.
					if failed, NULL.
	UB:				dlist is NULL.
					where-iter is NULL.
	time complexity:O(1)
 */
dlist_iter_ty DListInsertBefore(dlist_ty* dlist, dlist_iter_ty where, 
								void* new_data);
/*----------------------------------------------------------------------------*/
/*
	syntax: 	    DListPushFront(iter-to-dlist, new-data)
	arguments:      iter-to-dlist: pointer to dlist.
					 new-data: data of the new node to insert.
	purpose: 	    insert a new node with the passed data in front of the dlist.
	return values:  if pushing succeed: an iterator to newly pushed node.
					otherwise: NULL.
	UB:				dlist is NULL.
	time complexity:O(1)
 */
dlist_iter_ty DListPushFront(dlist_ty* dlist, void* new_data);
/*----------------------------------------------------------------------------*/
/*
	syntax: 	    DListPopFront(iter-to-dlist)
	arguments:      iter-to-dlist: pointer to dlist.
	purpose: 	    removes front node in dlist.
	return values:  void.
	UB:				dlist is NULL or empty.
	time complexity:O(1)
 */
void DListPopFront(dlist_ty* dlist);
/*----------------------------------------------------------------------------*/
/*
	syntax: 	    DListPushBack(iter-to-dlist, new-data)
	arguments:      iter-to-dlist: pointer to dlist.
					 new-data: data of the new node to insert.
	purpose: 	    insert a new node with the passed data in the end of the dlist.
	return values:  if pushing succeed: an iterator to newly pushed node.
					otherwise: NULL.
	UB:				dlist is NULL.
	time complexity:O(1)
 */
dlist_iter_ty DListPushBack(dlist_ty* dlist, void* new_data);
/*----------------------------------------------------------------------------*/
/*
	syntax: 	    DListPopBack(iter-to-dlist)
	arguments:      iter-to-dlist: pointer to dlist.
	purpose: 	    removes last node in dlist.
	return values:  void.
	UB:				dlist is NULL or empty.
	time complexity:O(1)
 */
void DListPopBack(dlist_ty* dlist);
/*----------------------------------------------------------------------------*/
/*
	syntax: 	    DListPopBack(iter-to-dlist)
	arguments:      iter-to-dlist: pointer to dlist.
	purpose: 	    removes last node in dlist.
	return values:  void.
	UB:				dlist is NULL or empty.
	time complexity:O(1)
 */
dlist_iter_ty DListRemove(dlist_iter_ty iter);

/****************************************************************************** 
*   Description:
* 		Returns pointer to the node's data on which iter points
* 	Return value: 
* 		Pointer to the node's data
* 	Undefined behavior:
* 		"iter" is DListEnd
* 	O(1)
******************************************************************************/
void* DListIterGetData(const dlist_iter_ty iter);

/****************************************************************************** 
* 	Description:
* 		Sets a given data
* 	Return value: 
* 		None
* 	Undefined behavior:
* 		"iter" is DListEnd
* 	O(1)
******************************************************************************/
void DListIterSetData(dlist_iter_ty iter, void* data_to_set);

/****************************************************************************** 
*	Description:
* 		Returns iter to "dummy" node - invalid node
* 	Return value: 
* 		iterator to the "dummy" node
* 	Undefined behavior:
* 		dlist is NULL
* 	O(1)
******************************************************************************/
dlist_iter_ty DListEndIter(const dlist_ty* dlist);

/****************************************************************************** 
*   Description:
* 		Returns iter to the first node in the list
* 	Return value: 
* 		iterator to the first node
* 		In case of empty list - returns "DListEndIter()", the dummy node 
* 	Undefined behavior:
* 		dlist is NULL
* 	O(1)
******************************************************************************/
dlist_iter_ty DListBeginIter(const dlist_ty* dlist);

/******************************************************************************
*	Description:
* 		Returns iter to next node
* 	Return value: 
* 		iterator to the next node
*	Undefined behavior:
* 		"iter" is DListEnd
* 	O(1)
******************************************************************************/
dlist_iter_ty DListIterNext(const dlist_iter_ty iter);

/******************************************************************************
*	Description:
* 		Returns iter to prev node
* 	Return value: 
* 		iterator to the prev node
*	Undefined behavior:
* 		"iter" is the first node
* 	O(1)
******************************************************************************/
dlist_iter_ty DListIterPrev(const dlist_iter_ty iter);

/****************************************************************************** 
* 	Description:
* 		Permorfms the action on each node in range ["from", "to") 
* 		in case of sucess of each action, oterwise stops upon the first fail 
* 	Return Value: 
* 		0 on succes, "action" return value on failture.
* 	Undefined behaviour:
* 		action is NULL 
* 		"from" or "to" are invalid pointer
* 		"from" > "to"
* 		"from" and "to" are not from the same list
* 	O(n)
******************************************************************************/
int DListForEach( dlist_iter_ty from, const dlist_iter_ty to, 
				  action_func_ty action,  void* param           );

/******************************************************************************
*	Description:
* 		Checks if the iters are equal
* 	Return Value: 
* 		1 if iter1 and iter2 are of the same node, 
* 		0 otherwise.   
*	Undefined behavior:
*	 	"iter1"/"iter2" NULL
*		"iter1"/"iter2" not in the same list
* 	O(1)
******************************************************************************/
int DListIterIsEqual(const dlist_iter_ty iter1, const dlist_iter_ty iter2);
		  
/*
	syntax: 	    DListFind(start-range, end-range, matching-func, param)
	arguments:      start-range: iterator to the start of searching range (included).
					end-range: iterator to the end of the range (not included).
					matching-func: function that takes an iterator and parameter
					and decides if there is a match, in case there is it returns 
					TRUE = 1, otherwise it returns FALSE = 0.
					param: parameter can be passed to matching function.
	purpose: 	    searches for a match in iter range [from, to), and returns an 
	                iterator to first match within the range.
	return values:  if there's a match, it returns an iter to the matching node
					otherwise it returns the "to" iter.
	UB:				"from" or "to" are invalid.
					"from" and "to" do not belong to same list.
					"from" > "to".
					"is_match" function is NULL.
	time complexity:O(n)
 */
dlist_iter_ty DListFind(const dlist_iter_ty from, const dlist_iter_ty to, 
						 is_match_func_ty is_match, void* param);
/*
	syntax: 	    DListMultiFind(start-range, end-range,dest-list,
				    matching-func, param)
	arguments:      start-range: iterator to the start of searching range (included).
					end-range: iterator to the end of the range (not included).
					dest-list: a doubly-linked-list provided by the user, to insert
					matching nodes in it.
					matching-func: function that takes an iterator and parameter
					and decides if there is a match, in case there is it returns 
					TRUE = 1, otherwise it returns FALSE = 0.
					param: parameter can be passed to matching function.
	purpose: 	    searches for a match in iter range [from, to), in case of match
					it inserts these nodes in dest-list.
	return values:  if a match has been found it returns SUCCESS = 0,
					otherwise it returns FAIL = 1.
	UB:				"from" or "to" are invalid.
					"from" and "to" do not belong to same list.
					"from" > "to".
					"dest" is NULL.
					"dest" is between "from" and "to.
	time complexity:O(n)
 */							
int DListMultiFind(const dlist_iter_ty from, const dlist_iter_ty to, 
                   dlist_ty* dest, is_match_func_ty is_match, void* param);

/******************************************************************************
* 	Description:
* 		Copies nodes of the second list from "from" to "to" ("to" not
*       included), to the first list before "where". Nodes remain in their
*       original order.
*   Return value:
* 		None
*   Undefinded behavior:
* 		"from", "to" or "where" are invaild iters
*  		"from" is DListEnd
*       "from" > "to"
*		"from" == "to"
*       "where" is between "from" and "to"
*   O(1)
******************************************************************************/
void DListSplice(dlist_iter_ty from, dlist_iter_ty to, dlist_iter_ty where);


#endif /* __ILRD_DLIST_H_ */
   
