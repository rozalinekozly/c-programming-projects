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
static avl_node_ty* FindMin(avl_node_ty* node);
static int GetHeight(avl_node_ty* node);
static void UpdateHeight(avl_node_ty* node);

static avl_node_ty* Balance(avl_node_ty* node);
static int GetBalanceFactor(avl_node_ty* node);
static avl_node_ty* RotateLeft(avl_node_ty* node);
static avl_node_ty* RotateRight(avl_node_ty* node);
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

static avl_node_ty* InsertRec(avl_node_ty* node, void* data, 
                               avl_cmp_ty cmp_func, void* param, int* status)
{
    int cmp_result = 0;
    
    /* Base case - found empty spot */
    if (NULL == node)
    {
        node = (avl_node_ty*)malloc(sizeof(avl_node_ty));
        if (NULL == node)
        {
            *status = FAILURE;
            return NULL;
        }
        
        node->data = data;
        node->height = 0;
        node->children[LEFT] = NULL;
        node->children[RIGHT] = NULL;
        
        *status = SUCCESS;
        return node;
    }
    
    /* Compare and recurse */
    cmp_result = cmp_func(data, node->data, param);
    
    if (0 == cmp_result)
    {
        /* Duplicate */
        *status = FAILURE;
        return node;
    }
    else if (0 > cmp_result)
    {
        /* Go left */
        node->children[LEFT] = InsertRec(node->children[LEFT], data, cmp_func, param, status);
    }
    else
    {
        /* Go right */
        node->children[RIGHT] = InsertRec(node->children[RIGHT], data, cmp_func, param, status);
    }
    
    /* Update height (for when we add balancing later) */
    UpdateHeight(node);
    
    return Balance(node);
}

int AvlInsert(avl_ty* avl, void* data)
{
    int status = SUCCESS;
    
    assert(NULL != avl);
    assert(NULL != data);
    
    avl->root.children[LEFT] = InsertRec(avl->root.children[LEFT], data, 
                                          avl->cmp_func, avl->param, &status);
    
    return status;
}

static avl_node_ty* FindMin(avl_node_ty* node)
{
    while (NULL != node->children[LEFT])
    {
        node = node->children[LEFT];
    }
    
    return node;
}

static avl_node_ty* RemoveRec(avl_node_ty* node, void* data, 
                               avl_cmp_ty cmp_func, void* param, int* status)
{
    int cmp_result = 0;
    avl_node_ty* temp = NULL;
    
    /* Base case - not found */
    if (NULL == node)
    {
        *status = FAILURE;
        return NULL;
    }
    
    /* Compare and search */
    cmp_result = cmp_func(data, node->data, param);
    
    if (0 > cmp_result)
    {
        /* Go left */
        node->children[LEFT] = RemoveRec(node->children[LEFT], data, cmp_func, param, status);
    }
    else if (0 < cmp_result)
    {
        /* Go right */
        node->children[RIGHT] = RemoveRec(node->children[RIGHT], data, cmp_func, param, status);
    }
    else
    {
        /* Found it! Now remove */
        *status = SUCCESS;
        
        /* Case 1: No left child */
        if (NULL == node->children[LEFT])
        {
            temp = node->children[RIGHT];
            free(node);
            return temp;
        }
        /* Case 2: No right child */
        else if (NULL == node->children[RIGHT])
        {
            temp = node->children[LEFT];
            free(node);
            return temp;
        }
        
        /* Case 3: Two children */
        temp = FindMin(node->children[RIGHT]);
        node->data = temp->data;
        node->children[RIGHT] = RemoveRec(node->children[RIGHT], temp->data, cmp_func, param, status);
    }
    
    /* Update height */
    UpdateHeight(node);
    
    return Balance(node);
}

int AvlRemove(avl_ty* avl, void* data)
{
    int status = FAILURE;
    
    assert(NULL != avl);
    assert(NULL != data);
    
    avl->root.children[LEFT] = RemoveRec(avl->root.children[LEFT], data, 
                                          avl->cmp_func, avl->param, &status);
    
    return status;
}

void* AvlFind(avl_ty* avl, void* elem_to_find)
{
    avl_node_ty* current = NULL;
    int cmp_result = 0;
    
    assert(NULL != avl);
    assert(NULL != elem_to_find);
    
    current = avl->root.children[LEFT];
    
    while (NULL != current)
    {
        cmp_result = avl->cmp_func(elem_to_find, current->data, avl->param);
        
        if (0 == cmp_result)
        {
            return current->data;  /* Found it! */
        }
        else if (0 > cmp_result)
        {
            current = current->children[LEFT];  /* Go left */
        }
        else
        {
            current = current->children[RIGHT];  /* Go right */
        }
    }
    
    return NULL;  /* Not found */
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
        return 0;  /* might change check with group later */
    }
    
    return avl->root.children[LEFT]->height;
}

static int GetHeight(avl_node_ty* node)
{
    if (NULL == node)
    {
        return -1;
    }
    
    return node->height;
}

static void UpdateHeight(avl_node_ty* node)
{
    int left_height = GetHeight(node->children[LEFT]);
    int right_height = GetHeight(node->children[RIGHT]);
    
    node->height = 1 + (left_height > right_height ? left_height : right_height);
}


static avl_node_ty* Balance(avl_node_ty* node)
{
    int balance = 0;
    
    UpdateHeight(node);
    balance = GetBalanceFactor(node);
    
    /* Left heavy (balance > 1) */
    if (balance > 1)
    {
        /* Left-Right case - double rotation */
        if (GetBalanceFactor(node->children[LEFT]) < 0)
        {
            node->children[LEFT] = RotateLeft(node->children[LEFT]);
        }
        /* Left-Left case - single rotation */
        return RotateRight(node);
    }
    
    /* Right heavy (balance < -1) */
    if (balance < -1)
    {
        /* Right-Left case - double rotation */
        if (GetBalanceFactor(node->children[RIGHT]) > 0)
        {
            node->children[RIGHT] = RotateRight(node->children[RIGHT]);
        }
        /* Right-Right case - single rotation */
        return RotateLeft(node);
    }
    
    /* Already balanced */
    return node;
}

static int GetBalanceFactor(avl_node_ty* node)
{
    if (NULL == node)
    {
        return 0;
    }
    
    return GetHeight(node->children[LEFT]) - GetHeight(node->children[RIGHT]);
}

static avl_node_ty* RotateRight(avl_node_ty* node)
{
    avl_node_ty* new_root = node->children[LEFT];
    
    node->children[LEFT] = new_root->children[RIGHT];
    new_root->children[RIGHT] = node;
    
    UpdateHeight(node);
    UpdateHeight(new_root);
    
    return new_root;
}

static avl_node_ty* RotateLeft(avl_node_ty* node)
{
    avl_node_ty* new_root = node->children[RIGHT];
    
    node->children[RIGHT] = new_root->children[LEFT];
    new_root->children[LEFT] = node;
    
    UpdateHeight(node);
    UpdateHeight(new_root);
    
    return new_root;
}
