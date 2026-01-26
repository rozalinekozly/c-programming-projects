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
*   Function receives node's *** // amit: stored data - dont mention node here, its an implementation detail *** data ("data"), any other parameter may be
*		passed with "param".
*	Function should return 0 on success, any other value will be considered
*		failure.
******************************************************************************/
typedef int (*bst_action_func_ty)(void* data, void* param);


/****************************************************************************** 
* 	Description:
* 		Creates an empty bst, *** amit: My lesson here is - dont write what is obvious, any word you add you should maintain, you should mention this if its not the intuitive behaviour like beeing initialized with some default data. 
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
* 		No operations performed if bst is NULL - *** amit: I would write- bst can be NULL ***
* 	Return value:
* 		None
*   O(n)
******************************************************************************/
void BstDestroy(bst_ty* bst);

/****************************************************************************** 
* 	Description:
* 		Insert a new node with a passed data to the bst *** amit: Inserts data to the bst  - dont mention node ***
* 	Return value:	
* 		On success, iterator to the newly allocated node, *** amit: why newly allocated node? if its implemented using array? dont mention how you do it, just what happens - new data is inserted ***
* 		On failure, "BstEnd"
* 	Undefined behaviour:
* 		bst is NULL
* 		the data is alredy in the bst *** amit: correct, and useful note. assert that on debug version
*   O(log n)
******************************************************************************/
bst_iter_ty BstInsert(bst_ty* bst, void* data);

/****************************************************************************** 
*  	Description:
* 		Searches for a matching node *** amit: data, not node, according to bst_cmp_ty result equals 0 *** for the passed value 
*   Return value:
* 		On success, returns iter to the matching node *** amit : data ***
* 		On failure, returns "BstEnd"
*   Undefinded behavior:
*       bst is NULL
*   O(log n)
******************************************************************************/
bst_iter_ty BstFind(const bst_ty* bst, void* data);

/****************************************************************************** 
*   Description:
* 		Removes a node pointed by iter from the bst *** amit: iter does not point (its not a pointer), its an iteration object for data iteration ***
* 	Return value: 
* 		iter to next node *** amit: iterator to the next element in in-order traverasl ***
* 	Undefined behavior: 
* 		iter is "BstEnd"
*   O(1)
******************************************************************************/
bst_iter_ty BstRemove(bst_iter_ty iter);

/****************************************************************************** 
* 	Description:
* 		Counts the size of bst *** amit: counts sounds like implementation detail, it tells the size. Amount of data inserted into the bst is enough.
* 	Return value: 
* 		Number of nodes in bst (Not including dummy) *** amit: Say whattttttttttttttt, dummy? who is dummy? again, implementation detail
*        *** amit: it clarifies the fact that amount of distinct iteration objects != amount of data inserted, but its not releveant here ***
* 	Undefined behavior: 
* 		bst is NULL
*   O(n)
******************************************************************************/
size_t BstSize(const bst_ty* bst);

/****************************************************************************** 
* 	Description:
* 		Permorfms the action on each node in range ["from", "to") *** amit: is it a convention for excluded/included? I would explicitly tell. also, the order is in-order
* 		in case of sucess of each action, oterwise stops upon the first fail 
* 	Return Value: 
* 		0 on succes, "action" return value on failture.
* 	Undefined behaviour:
* 		action is NULL 
* 		"from" or "to" are invalid iters *** amit: how would a user get an invalid iterator? what is that exactly? the rest is good ***
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
* 		Returns iter to the first node(in-order) in the bst *** amit: smallest data in the bst (according to bst_cmp_ty)
* 	Return value: 
* 		iterator to the first node
* 		In case of empty bst - returns "BstEndIter", the dummy node *** amit: dont mention dummy, but yes when you iterate on an empty list you start at the end ***
* 	Undefined behavior:
* 		bst is NULL
* 	O(n)o *** amit: its O(logn) on average ***
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
*       iter is "BstBeginIter"
* 	O(1)
******************************************************************************/
bst_iter_ty BstItPrev(const bst_iter_ty iter);

/****************************************************************************** 
*	Description:
* 		Returns iter to "dummy" node - invalid node *** amit: marks the end of the in-order bst iteration ***
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
*       Return 1 if iter1 == iter2. *** amit: if user can do iter1 == iter2 why does he need your function? ***
*       else return 0; 
* 	Undefined behavior: 
*       "iter1"/"iter2" not in the same bst
*   O(1)
******************************************************************************/
int  BstItEqual(const bst_iter_ty iter1, const bst_iter_ty iter2);

/******************************************************************************
*   Description:
* 		Get data from node pointed by iter from the bst *** amit: dont mention node.. you got my point already... ***
* 	Return value: 
* 		data of node pointed by iter 
* 	Undefined behavior: 
* 		iter is "BstEnd"
*   O(1)
******************************************************************************/
void* BstGetData(const bst_iter_ty iter);


#endif /* __ILRD_BST_H__ */

