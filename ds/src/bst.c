/*
submitter: rozaline kozly
reviewer: oshrat
-------------------------------------------------------------------------------*/
#include <stdlib.h>		/* malloc(), free() */
#include <assert.h>		/* assert() */

#include "bst.h"		/* API */

/*-----------------------enums-------------------------------------------------*/
enum children { LEFT = 0, PARENT = 1, RIGHT = 2 };

/*-----------------------structs-----------------------------------------------*/
struct bst_node
{
	void* data;
	struct bst_node* child[3];	/* LEFT = 0, PARENT = 1, RIGHT = 2 */
};

struct bst
{
	bst_node_ty root;
	bst_cmp_ty cmp;
	void* cmp_func_param;
};

/*-----------------------aux functions-----------------------------------------*/
static bst_node_ty* CreateNode(void* data);
static bst_node_ty* GetRoot(const bst_ty* bst);
static bst_node_ty* TraverseDirection(bst_node_ty* node, int dir);
static void ReplaceChild(bst_node_ty* parent, bst_node_ty* old_child, bst_node_ty* new_child);
static int IsLeaf(bst_node_ty* node);
static int IsSingleChild(bst_node_ty* node);
static int CountNodesAction(void* data, void* param);

/*-----------------------------------------------------------------------------*/
bst_ty* BstCreate(bst_cmp_ty cmp_func, void* param)
{
	bst_ty* bst = NULL;
	bst_node_ty root = {0};

	assert(NULL != cmp_func);

	bst = (bst_ty*)malloc(sizeof(*bst)*sizeof(char));
	if (NULL == bst)
	{
		return (NULL);
	}

	bst->root = root;
	bst->cmp = cmp_func;
	bst->cmp_func_param = param;

	return (bst);
}
/*-----------------------------------------------------------------------------*/
void BstDestroy(bst_ty* bst)
{
	bst_node_ty* parent = NULL;
	bst_node_ty* curr = NULL;

	if (NULL == bst)
	{
		return;
	}

	curr = GetRoot(bst);

	while (!BstIsEmpty(bst))
	{
		curr = TraverseDirection(curr, LEFT);

		if (NULL != curr->child[RIGHT])
		{
			curr = curr->child[RIGHT];
		}

		if (IsLeaf(curr))
		{
			parent = curr->child[PARENT];
			ReplaceChild(parent, curr, NULL);

			free(curr);
			curr = parent;
		}
	}

	free(bst);
}
/*-----------------------------------------------------------------------------*/
bst_iter_ty BstInsert(bst_ty* bst, void* data)
{
	bst_node_ty* new_node = NULL;
	bst_node_ty* parent = NULL;
	bst_node_ty** curr = NULL;
	int cmp_result = 0;
	int dir = LEFT;

	assert(NULL != bst);

	new_node = CreateNode(data);
	if (NULL == new_node)
	{
		return (BstItEnd(bst));
	}

	curr = &bst->root.child[LEFT];
	parent = &bst->root;

	while (NULL != *curr)
	{
		cmp_result = bst->cmp((*curr)->data, data, bst->cmp_func_param);

		parent = *curr;
		dir = (0 > cmp_result) ? RIGHT : LEFT;
		curr = &(*curr)->child[dir];
	}

	new_node->child[PARENT] = parent;
	*curr = new_node;

	return (new_node);
}
/*-----------------------------------------------------------------------------*/
bst_iter_ty BstFind(const bst_ty* bst, void* data)
{
	bst_node_ty* curr = NULL;
	int cmp_result = 0;
	int dir = LEFT;

	assert(NULL != bst);

	curr = GetRoot(bst);

	while (NULL != curr)
	{
		cmp_result = bst->cmp(curr->data, data, bst->cmp_func_param);

		if (0 == cmp_result)
		{
			return (curr);
		}

		dir = (0 < cmp_result) ? LEFT : RIGHT;
		curr = curr->child[dir];
	}

	return (BstItEnd(bst));
}
/*-----------------------------------------------------------------------------*/
bst_iter_ty BstRemove(bst_iter_ty iter)
{
	bst_node_ty* parent = NULL;
	bst_node_ty* new_child = NULL;
	bst_iter_ty next = NULL;

	assert(NULL != iter);

	next = BstItNext(iter);
	parent = iter->child[PARENT];

	/* Case 1: leaf */
	if (IsLeaf(iter))
	{
		ReplaceChild(parent, iter, NULL);
		free(iter);
		return (next);
	}

	/* Case 2: one child */
	if (IsSingleChild(iter))
	{
		new_child = (NULL != iter->child[LEFT]) ? iter->child[LEFT] : iter->child[RIGHT];
		ReplaceChild(parent, iter, new_child);
		free(iter);
		return (next);
	}

	/* Case 3: two children - swap data with successor and remove successor */
	{
		iter->data = next->data;
		BstRemove(next);
		return (iter);
	}
}
/*-----------------------------------------------------------------------------*/
size_t BstSize(const bst_ty* bst)
{
	size_t size = 0;

	assert(NULL != bst);

	BstForEach(BstItBegin(bst), BstItEnd(bst), CountNodesAction, &size);

	return (size);
}
/*-----------------------------------------------------------------------------*/
int BstIsEmpty(const bst_ty* bst)
{
	assert(NULL != bst);

	return (NULL == bst->root.child[LEFT]);
}
/*-----------------------------------------------------------------------------*/
int BstForEach(bst_iter_ty from,
               bst_iter_ty to,
               bst_action_func_ty action,
               void* param)
{
	bst_iter_ty iter = NULL;
	int result = 0;

	assert(NULL != action);

	iter = from;

	while (!BstItEqual(iter, to))
	{
		result = action(iter->data, param);
		if (0 != result)
		{
			return (result);
		}
		iter = BstItNext(iter);
	}

	return (0);
}
/*-----------------------------------------------------------------------------*/
bst_iter_ty BstItBegin(const bst_ty* bst)
{
	bst_node_ty* curr = NULL;

	assert(NULL != bst);

	curr = GetRoot(bst);

	if (NULL == curr)
	{
		return (BstItEnd(bst));
	}

	return (TraverseDirection(curr, LEFT));
}
/*-----------------------------------------------------------------------------*/
bst_iter_ty BstItNext(bst_iter_ty iter)
{
	bst_node_ty* curr = NULL;
	bst_node_ty* parent = NULL;

	assert(NULL != iter);

	curr = iter;

	/* If right child exists, next is min of right subtree */
	if (NULL != curr->child[RIGHT])
	{
		return (TraverseDirection(curr->child[RIGHT], LEFT));
	}

	/* Go up until we come from a left child */
	parent = curr->child[PARENT];
	while (parent->child[RIGHT] == curr)
	{
		curr = parent;
		parent = curr->child[PARENT];
	}

	return (parent);
}
/*-----------------------------------------------------------------------------*/
bst_iter_ty BstItPrev(bst_iter_ty iter)
{
	bst_node_ty* curr = NULL;
	bst_node_ty* parent = NULL;

	assert(NULL != iter);

	curr = iter;

	/* If left child exists, prev is max of left subtree */
	if (NULL != curr->child[LEFT])
	{
		return (TraverseDirection(curr->child[LEFT], RIGHT));
	}

	/* Go up until we come from a right child */
	parent = curr->child[PARENT];
	while (parent->child[LEFT] == curr)
	{
		curr = parent;
		parent = curr->child[PARENT];
	}

	return (parent);
}
/*-----------------------------------------------------------------------------*/
bst_iter_ty BstItEnd(const bst_ty* bst)
{
	assert(NULL != bst);

	return ((bst_iter_ty)&bst->root);
}
/*-----------------------------------------------------------------------------*/
int BstItEqual(bst_iter_ty iter1, bst_iter_ty iter2)
{
	return (iter1 == iter2);
}
/*-----------------------------------------------------------------------------*/
void* BstGetData(bst_iter_ty iter)
{
	assert(NULL != iter);

	return (iter->data);
}
/*-----------------------aux functions implementation--------------------------*/
static bst_node_ty* CreateNode(void* data)
{
	bst_node_ty* node = NULL;

	node = (bst_node_ty*)malloc(sizeof(*node));
	if (NULL == node)
	{
		return (NULL);
	}

	node->data = data;
	node->child[LEFT] = NULL;
	node->child[PARENT] = NULL;
	node->child[RIGHT] = NULL;

	return (node);
}
/*-----------------------------------------------------------------------------*/
static bst_node_ty* GetRoot(const bst_ty* bst)
{
	return (bst->root.child[LEFT]);
}
/*-----------------------------------------------------------------------------*/
static bst_node_ty* TraverseDirection(bst_node_ty* node, int dir)
{
	while (NULL != node->child[dir])
	{
		node = node->child[dir];
	}

	return (node);
}
/*-----------------------------------------------------------------------------*/
static void ReplaceChild(bst_node_ty* parent, bst_node_ty* old_child, bst_node_ty* new_child)
{
	int dir = (parent->child[LEFT] == old_child) ? LEFT : RIGHT;

	parent->child[dir] = new_child;

	if (NULL != new_child)
	{
		new_child->child[PARENT] = parent;
	}
}
/*-----------------------------------------------------------------------------*/
static int IsLeaf(bst_node_ty* node)
{
	return (NULL == node->child[LEFT] && NULL == node->child[RIGHT]);
}
/*-----------------------------------------------------------------------------*/
static int IsSingleChild(bst_node_ty* node)
{
	return (!node->child[LEFT] != !node->child[RIGHT]);
}
/*-----------------------------------------------------------------------------*/
static int CountNodesAction(void* data, void* param)
{
	size_t* counter = (size_t*)param;
	(void)data;

	*counter += 1;

	return (0);
}
