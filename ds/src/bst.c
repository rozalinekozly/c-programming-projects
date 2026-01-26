/*-----------------------------------------------------------------------------
submitted by: rozaline kozly
reviewer:
note: change the implementation no need to support successor and predecessor 
(this makes it so complicated)
------------------------------------------------------------------------------*/
#include <stdlib.h>     /* malloc(), free() */
#include <assert.h>     /* assert() */ /*add size_t as well*/

#include "bst.h"        /*API */

/*--------------------objects (managing structs)------------------------------*/
struct bst_node
{
    void* data;
    struct bst_node* child[3];   /* LEFT = 0, PARENT = 1, RIGHT = 2 */
    struct bst_node* iter[2];    /* PREV = 0, NEXT = 1 */
};

struct bst
{
    /* maybe later change the name to start */
    bst_node_ty* dummy;
    bst_cmp_ty cmp;
    /*change the name to cmp_func_param*/
    void* param;
};

/*------------------------aux functions---------------------------------------*/
/*
Algorithm:
Traverse the tree from root using cmp until reaching a NULL child.
Set dir to LEFT or RIGHT according to comparison.
Return parent node.
*/
static bst_node_ty* FindInsertParent(const bst_ty* bst, void* data, int* dir)
{
    bst_node_ty* curr = bst->dummy->child[0];
    bst_node_ty* parent = bst->dummy;
    int cmp_res = 0;

    while (NULL != curr)
    {
        parent = curr;
        cmp_res = bst->cmp(data, curr->data, bst->param);
        assert(cmp_res != 0);
        *dir = (cmp_res < 0) ? 0 : 2;
        curr = curr->child[*dir];
    }

    return parent;
}
/*----------------------------------------------------------------------------*/
/*
Algorithm:
Connect new node between prev and next in in-order traversal.
*/
static void LinkPredSucc(bst_node_ty* new_node,
                         bst_node_ty* prev,
                         bst_node_ty* next)
{
    new_node->iter[0] = prev;
    new_node->iter[1] = next;
    prev->iter[1] = new_node;
    next->iter[0] = new_node;
}
/*----------------------------------------------------------------------------*/
/*
Algorithm:
Replace subtree rooted at old_node with new_node.
Fix parent and child links.
*/
static void Transplant(bst_ty* bst,
                       bst_node_ty* old_node,
                       bst_node_ty* new_node)
{
    bst_node_ty* parent = old_node->child[1];

    if (parent->child[0] == old_node)
    {
        parent->child[0] = new_node;
    }
    else
    {
        parent->child[2] = new_node;
    }

    if (NULL != new_node)
    {
        new_node->child[1] = parent;
    }
}
/*----------------------------------------------------------------------------*/
/*
Algorithm:
Return the leftmost node in the given subtree.
*/
static bst_node_ty* MinSubtree(bst_node_ty* node)
{
    while (NULL != node->child[0])
    {
        node = node->child[0];
    }
    return node;
}
/*---------------API implementations---------------------------------------*/
bst_ty* BstCreate(bst_cmp_ty cmp_func, void* param)
{
    bst_ty* bst = NULL;
    bst_node_ty* dummy = NULL;

    assert(NULL != cmp_func);

    bst = (bst_ty*)malloc(sizeof(bst_ty));
    if (NULL == bst)
    {
        return NULL;
    }

    dummy = (bst_node_ty*)malloc(sizeof(bst_node_ty));
    if (NULL == dummy)
    {
        free(bst);
        return NULL;
    }

    dummy->data = NULL;

    dummy->child[0] = NULL;
    dummy->child[1] = dummy;
    dummy->child[2] = NULL;

    dummy->iter[0] = dummy;
    dummy->iter[1] = dummy;

    bst->dummy = dummy;
    bst->cmp = cmp_func;
    bst->param = param;

    return bst;
}

void BstDestroy(bst_ty* bst)
{
    /*
    Algorithm:
    Post-order traverse the tree starting from root.
    Free all nodes.
    Free dummy and bst.
    */
    bst_iter_ty it = NULL;
    bst_iter_ty next = NULL;

    if (NULL == bst)
    {
        return;
    }

    it = BstItBegin(bst);
    while (!BstItEqual(it, BstItEnd(bst)))
    {
        next = BstItNext(it);
        free(it);
        it = next;
    }

    free(bst->dummy);
    free(bst);
}

bst_iter_ty BstInsert(bst_ty* bst, void* data)
{
    /*
    Algorithm:
    Find insertion parent and direction.
    Allocate new node.
    Attach node to tree.
    Update predecessor and successor.
    Return iterator to new node.
    */
    bst_node_ty* new_node = NULL;
    bst_node_ty* parent = NULL;
    int dir = 0;

    assert(NULL != bst);

    new_node = (bst_node_ty*)malloc(sizeof(bst_node_ty));
    if (NULL == new_node)
    {
        return BstItEnd(bst);
    }

    new_node->data = data;
    new_node->child[0] = NULL;
    new_node->child[2] = NULL;

    parent = FindInsertParent(bst, data, &dir);
    new_node->child[1] = parent;
    parent->child[dir] = new_node;

    if (parent == bst->dummy)
    {
        LinkPredSucc(new_node, bst->dummy, bst->dummy);
    }
    else if (dir == 0)
    {
        LinkPredSucc(new_node, parent->iter[0], parent);
    }
    else
    {
        LinkPredSucc(new_node, parent, parent->iter[1]);
    }

    return new_node;
}

bst_iter_ty BstFind(const bst_ty* bst, void* data)
{
    /*
    Algorithm:
    Traverse tree using cmp until match or NULL.
    */
    
    bst_node_ty* curr = NULL;
    int cmp_res = 0;

    assert(NULL != bst);

    curr = bst->dummy->child[0];
    while (NULL != curr)
    {
        cmp_res = bst->cmp(data, curr->data, bst->param);
        if (0 == cmp_res)
        {
            return curr;
        }
        curr = curr->child[(cmp_res < 0) ? 0 : 2];
    }

    return BstItEnd(bst);
}

bst_iter_ty BstRemove(bst_iter_ty iter)
{
    /*
    Algorithm:
    Save successor.
    If node has two children, swap with successor.
    Remove node with at most one child.
    Fix predecessor and successor links.
    Free node.
    Return saved successor.
    */
    bst_node_ty* node = iter;
    bst_node_ty* succ = node->iter[1];
    bst_node_ty* child = NULL;

    assert(node != NULL);

    if (NULL != node->child[0] && NULL != node->child[2])
    {
        bst_node_ty* min = MinSubtree(node->child[2]);
        node->data = min->data;
        node = min;
    }

    child = (NULL != node->child[0]) ? node->child[0] : node->child[2];
    Transplant(NULL, node, child);

    node->iter[0]->iter[1] = node->iter[1];
    node->iter[1]->iter[0] = node->iter[0];

    free(node);
    return succ;
}



int BstForEach(bst_iter_ty from,
               bst_iter_ty to,
               bst_action_func_ty action,
               void* param)
{
    /*
    Algorithm:
    Iterate from 'from' to 'to'.
    Apply action.
    Stop on first failure.
    */
    int res = 0;

    assert(NULL != action);

    while (!BstItEqual(from, to))
    {
        res = action(BstGetData(from), param);
        if (0 != res)
        {
            return res;
        }
        from = BstItNext(from);
    }

    return 0;
}





size_t BstSize(const bst_ty* bst)
{
    /*
    Algorithm:
    Iterate from begin to end counting nodes.
    */
    size_t count = 0;
    bst_iter_ty it = NULL;

    assert(NULL != bst);

    it = BstItBegin(bst);
    while (!BstItEqual(it, BstItEnd(bst)))
    {
        ++count;
        it = BstItNext(it);
    }

    return count;
}

bst_iter_ty BstItBegin(const bst_ty* bst)
{
    /*
    Algorithm:
    If empty return End.
    Otherwise return leftmost node.
    */
    bst_node_ty* curr = NULL;

    assert(NULL != bst);
    
    /*curr is tree's root '*/
    curr = bst->dummy->child[0];
    if (NULL == curr)
    {
        return bst->dummy;
    }

    return MinSubtree(curr);
}

bst_iter_ty BstItNext(const bst_iter_ty iter)
{
    /*
    Algorithm:
    Return successor directly.
    */
    return iter->iter[1];
}

bst_iter_ty BstItPrev(const bst_iter_ty iter)
{
    /*
    Algorithm:
    Return predecessor directly.
    */
    return iter->iter[0];
}

int BstItEqual(const bst_iter_ty iter1, const bst_iter_ty iter2)
{
    /*
    Algorithm:
    Compare iterators directly.
    */
    return iter1 == iter2;
}

bst_iter_ty BstItEnd(const bst_ty* bst)
{
    /*
    Algorithm:
    Return dummy iterator.
    */
    assert(NULL != bst);
    return bst->dummy;
}
void* BstGetData(const bst_iter_ty iter)
{
    /*
    Algorithm:
    Return data stored in iterator.
    */
    return iter->data;
}

