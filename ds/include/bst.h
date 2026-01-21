#ifndef __ILRD_BST_H__
#define __ILRD_BST_H__

#include <stddef.h>         /* size_t */

typedef struct bst bst_ty;

typedef struct bst_node bst_node_ty; 

typedef bst_node_ty* bst_iter_ty; 

/****************************************************************************** 
*   Function compares "data1" and "data2", any other parameter may be
*		passed with "param".
*	Return value:
* 		0 > result if data1 comes before data2,
* 		0 < result if data2 comes before data1,
*		0 == result if data1 and data2 are equal
******************************************************************************/
typedef int (*bst_cmp_ty)(const void* data1, const void* data2, void* param);

/****************************************************************************** 
*   Function receives node's data ("data"), any other parameter may be
*		passed with "param".
*	Function should return 0 on success, any other value will be considered
*		failure.
******************************************************************************/
typedef int (*bst_action_func_ty)(void* data, void* param);


/****************************************************************************** 
* 	Description:
* 		Creates an empty bst,
* 	Return value:	
* 		On success, a pointer to the created bst
* 		On failure, NULL
*   Undefined Behaviour : 
*       cmp_func is NULL
* 	O(1)
******************************************************************************/
bst_ty* BstCreate(bst_cmp_ty cmp_func, void* param);


/****************************************************************************** 
* 	Description:
* 		Destroys the bst
* 		No operations performed if bst is NULL
* 	Return value:
* 		None
*   O(n)
******************************************************************************/
void BstDestroy(Bsy_ty* bst);

/****************************************************************************** 
* 	Description:
* 		Insert a new node with a passed data to the bst
* 	Return value:	
* 		On success, iterator to the newly allocated node,
* 		On failure, "BstEnd"
* 	Undefined behaviour:
* 		bst is NULL
*   O(log n)
******************************************************************************/
bst_iter_ty BstInsert(bst_ty* bst, void* data);

/****************************************************************************** 
*  	Description:
* 		Searches for a matching node for the passed value
*   Return value:
* 		On success, returns iter to the matching node 
* 		On failure, returns "BstEnd"
*   Undefinded behavior:
*       bst is NULL
*   O(log n)
******************************************************************************/
bst_iter_ty BstFind(const bst_ty* bst, void* data);

/****************************************************************************** 
*   Description:
* 		Removes a node pointed by iter from the bst
* 	Return value: 
* 		iter to next node
* 	Undefined behavior: 
* 		iter is "BstEnd"
*   O(1)
******************************************************************************/
bst_iter_ty BstRemove(bst_iter_ty iter);

/****************************************************************************** 
* 	Description:
* 		Counts the size of bst	  
* 	Return value: 
* 		Number of nodes in bst (Not including dummy)
* 	Undefined behavior: 
* 		bst is NULL
*   O(n)
******************************************************************************/
size_t BstSize(const bst_ty* bst);

/****************************************************************************** 
* 	Description:
* 		Permorfms the action on each node in range ["from", "to") 
* 		in case of sucess of each action, oterwise stops upon the first fail 
* 	Return Value: 
* 		0 on succes, "action" return value on failture.
* 	Undefined behaviour:
* 		action is NULL 
* 		"from" or "to" are invalid iters
* 		"from" > "to"
* 		"from" and "to" are not from the same bst
* 	O(n)
******************************************************************************/
int BstForEach(bst_iter_ty from,
               bst_iter_ty to,
               bst_action_func_ty action,
               void* param);
               
/****************************************************************************** 
*   Description:
* 		Returns iter to the first node(in-order) in the bst
* 	Return value: 
* 		iterator to the first node
* 		In case of empty bst - returns "BstEndIter", the dummy node 
* 	Undefined behavior:
* 		bst is NULL
* 	O(n)
******************************************************************************/
bst_iter_ty BstItBegin(const bst_ty* bst);

/******************************************************************************
*	Description:
* 		Returns iter to next node(in-order)
* 	Return value: 
* 		iterator to the next node
*	Undefined behavior:
* 		iter is "BstEndIter"
* 	O(1)
******************************************************************************/
bst_iter_ty BstItNext(const bst_iter_ty iter);

/******************************************************************************
*	Description:
* 		Returns iter to prev node(in-order)
* 	Return value: 
* 		iterator to the prev node
*	Undefined behavior:
* 		Node
* 	O(1)
******************************************************************************/
bst_iter_ty BstItPrev(const bst_iter_ty iter);

/****************************************************************************** 
*	Description:
* 		Returns iter to "dummy" node - invalid node
* 	Return value: 
* 		iterator to the "dummy" node
* 	Undefined behavior:
* 		bst is NULL
* 	O(1)
******************************************************************************/
bst_iter_ty BstItEnd(const bst_ty* bst); 
  /******************************************************************************
*   Description:
*   Checks if iter1 equal to iter2 
* 	Return value: 
*       Return 1 if iter1 == iter2. 
*       else return 0; 
* 	Undefined behavior: 
*       "iter1"/"iter2" not in the same bst
*   O(1)
******************************************************************************/
int  BstItEqual(const bst_iter_ty iter1, const bst_iter_ty iter2);

/******************************************************************************
*   Description:
* 		Get data from node pointed by iter from the bst
* 	Return value: 
* 		data of node pointed by iter 
* 	Undefined behavior: 
* 		iter is "BstEnd"
*   O(1)
******************************************************************************/
void* BstGetData(const bst_iter_ty iter);


#endif /* __ILRD_BST_H__ */

