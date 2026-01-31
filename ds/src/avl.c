/*
submitter: Rozaline kozly
reviewer: 
------------------------------------------------------------------------------*/
#include <stdlib.h>     /* malloc, free */
#include <assert.h>     /* assert */
/*----------------------------------------------------------------------------*/
#include "avl.h"
/*----------------------------------------------------------------------------*/
#define SUCCESS 0
#define FAILURE 1
/*----------------------------------------------------------------------------*/
typedef enum children
{
    LEFT = 0,
    RIGHT = 1
} children_ty;
/*----------------------------------------------------------------------------*/
typedef struct avl_node
{
    struct avl_node* children[2];
    void* data;
    int height; 
} avl_node_ty;

struct avl
{
    avl_node_ty root;  
    avl_cmp_ty cmp_func;
    void* param;
};
/*----------------------------------------------------------------------------*/
static void DestroyRec(avl_node_ty* node);
static avl_node_ty* InsertRec(avl_node_ty* node, void* data, 
                               avl_cmp_ty cmp_func, void* param, int* status);
static avl_node_ty* RemoveRec(avl_node_ty* node, void* data, 
                               avl_cmp_ty cmp_func, void* param, int* status);
static int ForEachRec(avl_node_ty* node, traverse_ty traverse, 
                      avl_action_func_ty action, void* param);
/*----------------------------------------------------------------------------*/
avl_ty* AvlCreate(avl_cmp_ty cmp_func, void* param)
{
    avl_ty* avl = NULL;
    
    assert(NULL != cmp_func);
    
    avl = (avl_ty*)malloc(sizeof(avl_ty));
    if (NULL == avl)
    {
        return NULL;
    }
    
    avl->root.children[LEFT] = NULL;
    avl->root.children[RIGHT] = NULL;
    avl->root.height = -1;  /* doesn't matter for dummy */
    avl->root.data = NULL;
    
    avl->cmp_func = cmp_func;
    avl->param = param;
    
    return avl;
}

void AvlDestroy(avl_ty* avl)
{
    if (NULL == avl)
    {
        return;
    }
    
    DestroyRec(avl->root.children[LEFT]);
    free(avl);
}

static void DestroyRec(avl_node_ty* node)
{
    if (NULL == node)
    {
        return;
    }
    
    DestroyRec(node->children[LEFT]);
    DestroyRec(node->children[RIGHT]);
    free(node);
}

int AvlInsert(avl_ty* avl, void* data)
{
    /* Algorithm:
     * 1. Assert avl and data are not NULL
     * 2. Call InsertRec starting from root.children[LEFT]
     * 3. Update root.children[LEFT] with returned node
     * 4. Return status (0 success, 1 failure)
     */
}

/*aux function : InsertRec
  actual function (recursive) that performs the insertion, update heights
  and returns a pointer to the root of the subtree after insertion(phase1) and
  balancing
  (phase 2).*/
static avl_node_ty* InsertRec(avl_node_ty* node, void* data, 
                               avl_cmp_ty cmp_func, void* param, int* status)
{
    /* Algorithm:
     * Base case - empty spot found:
     *   - malloc new node
     *   - if malloc fails -> *status = FAILURE, return NULL
     *   - set data, height = 0, children = NULL
     *   - *status = SUCCESS
     *   - return new node
     * 
     * Recursive case:
     *   - compare data with node->data
     *   - if equal -> duplicate, *status = FAILURE, return node
     *   - if less -> go left: node->children[LEFT] = InsertRec(left, ...)
     *   - if greater -> go right: node->children[RIGHT] = InsertRec(right, ...)
     *   - update my height
     *   - balance me
     *   - return me (or new root after balance)
     */
}
/*aux function RemoveRec */
static avl_node_ty* RemoveRec(avl_node_ty* node, void* data, 
                               avl_cmp_ty cmp_func, void* param, int* status)
{
    /* Algorithm:
     * Base case - not found:
     *   - if node is NULL -> *status = FAILURE (not found), return NULL
     * 
     * Recursive case - search for node:
     *   - compare data with node->data
     *   - if less -> go left: node->children[LEFT] = RemoveRec(left, ...)
     *   - if greater -> go right: node->children[RIGHT] = RemoveRec(right, ...)
     *   - if equal -> found it! now remove:
     * 
     * Found node to remove (3 cases):
     *   Case 1: No children (leaf)
     *     - free node
     *     - *status = SUCCESS
     *     - return NULL
     * 
     *   Case 2: One child
     *     - save the non-NULL child
     *     - free node
     *     - *status = SUCCESS
     *     - return the saved child
     * 
     *   Case 3: Two children
     *     - find minimum in right subtree
     *     - copy min's data to current node
     *     - remove min from right subtree: node->children[RIGHT] = RemoveRec(right, min_data, ...)
     *     - *status = SUCCESS
     * 
     * After recursive removal:
     *   - update my height
     *   - balance me
     *   - return me (or new root after balance)
     */
}
int AvlRemove(avl_ty* avl, void* data)
{
    /* Algorithm:
     * 1. Assert avl and data are not NULL
     * 2. Call RemoveRec starting from root.children[LEFT]
     * 3. Update root.children[LEFT] with returned node
     * 4. Return status (0 found and removed, 1 not found)
     */
}

void* AvlFind(avl_ty* avl, void* elem_to_find)
{
    /* Algorithm:
     * 1. Assert avl and elem_to_find are not NULL
     * 2. Start from root.children[LEFT] (actual root)
     * 3. While current node is not NULL:
     *    a. Compare elem_to_find with current data
     *    b. If equal, return current data
     *    c. If less, go left
     *    d. If greater, go right
     * 4. Return NULL if not found
     */
}

static int ForEachRec(avl_node_ty* node, traverse_ty traverse, 
                      avl_action_func_ty action, void* param)
{
    int status = SUCCESS;
    
    if (NULL == node)
    {
        return SUCCESS;
    }
    
    if (PRE_ORDER == traverse)
    {
        /* action -> left -> right */
        status = action(node->data, param);
        if (SUCCESS != status)
        {
            return status;
        }
        
        status = ForEachRec(node->children[LEFT], traverse, action, param);
        if (SUCCESS != status)
        {
            return status;
        }
        
        status = ForEachRec(node->children[RIGHT], traverse, action, param);
        return status;
    }
    else if (IN_ORDER == traverse)
    {
        /* left -> action -> right */
        status = ForEachRec(node->children[LEFT], traverse, action, param);
        if (SUCCESS != status)
        {
            return status;
        }
        
        status = action(node->data, param);
        if (SUCCESS != status)
        {
            return status;
        }
        
        status = ForEachRec(node->children[RIGHT], traverse, action, param);
        return status;
    }
    else /* POST_ORDER */
    {
        /* left -> right -> action */
        status = ForEachRec(node->children[LEFT], traverse, action, param);
        if (SUCCESS != status)
        {
            return status;
        }
        
        status = ForEachRec(node->children[RIGHT], traverse, action, param);
        if (SUCCESS != status)
        {
            return status;
        }
        
        status = action(node->data, param);
        return status;
    }
}

int AvlForEach(avl_ty* avl, traverse_ty traverse, avl_action_func_ty action, void* param)
{
    assert(NULL != avl);
    assert(NULL != action);
    
    if (NULL == avl->root.children[LEFT])
    {
        return SUCCESS;
    }
    
    return ForEachRec(avl->root.children[LEFT], traverse, action, param);
}


static int CountNodes(void* data, void* param)
{
    (void)data;
    (*(size_t*)param)++;
    return SUCCESS;
}

size_t AvlSize(avl_ty* avl)
{
    size_t count = 0;
    
    assert(NULL != avl);
    
    AvlForEach(avl, IN_ORDER, CountNodes, &count);
    
    return count;
}

int AvlIsEmpty(const avl_ty* avl)
{
    assert(NULL != avl);
    
    return (NULL == avl->root.children[LEFT]);
}

size_t AvlHeight(avl_ty* avl)
{
    assert(NULL != avl);
    
    if (NULL == avl->root.children[LEFT])
    {
        return -1;  /* might change check with group later */
    }
    
    return avl->root.children[LEFT]->height;
}

