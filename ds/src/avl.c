/*
submitter: Rozaline kozly
reviewer: Shalev
------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <assert.h>
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
    avl_node_ty* root;  
    avl_cmp_ty cmp_func;
    void* param;
};
/*----------------------------------------------------------------------------*/
static void DestroyRec(avl_node_ty* node);
static avl_node_ty* InsertRec(avl_node_ty* node, avl_node_ty* new_node, 
                               avl_cmp_ty cmp_func, void* param);
static avl_node_ty* RemoveRec(avl_node_ty* node, void* data, 
                               avl_cmp_ty cmp_func, void* param, int* status);
static void* FindRec(avl_node_ty* node, void* elem_to_find, 
                     avl_cmp_ty cmp_func, void* param);
static int ForEachRec(avl_node_ty* node, traverse_ty traverse, 
                      avl_action_func_ty action, void* param);
static avl_node_ty* FindMin(avl_node_ty* node);
static int GetHeight(avl_node_ty* node);
static void UpdateHeight(avl_node_ty* node);
static avl_node_ty* Balance(avl_node_ty* node);
static int GetBalanceFactor(avl_node_ty* node);
static avl_node_ty* RotateLeft(avl_node_ty* node);
static avl_node_ty* RotateRight(avl_node_ty* node);
static int CountNodes(void* data, void* param);
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
    
    avl->root = NULL;
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
    
    DestroyRec(avl->root);
    
    free(avl);
    avl = NULL;
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
    node = NULL;
}

int AvlInsert(avl_ty* avl, void* data)
{
    avl_node_ty* new_node = NULL;
    
    assert(NULL != avl);
    assert(NULL != data);
    
    new_node = (avl_node_ty*)malloc(sizeof(avl_node_ty));
    if (NULL == new_node)
    {
        return FAILURE;
    }
    
    new_node->data = data;
    new_node->height = 0;
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;
    
    if (NULL == avl->root)
    {
        avl->root = new_node;
        return SUCCESS;
    }
    
    avl->root = InsertRec(avl->root, new_node, avl->cmp_func, avl->param);
    
    return SUCCESS;
}

static avl_node_ty* InsertRec(avl_node_ty* node, avl_node_ty* new_node, 
                               avl_cmp_ty cmp_func, void* param)
{
    int cmp_result = 0;
    
    cmp_result = cmp_func(new_node->data, node->data, param);
    
    assert(0 != cmp_result);
    
    if (0 > cmp_result)
    {
        if (NULL == node->children[LEFT])
        {
            node->children[LEFT] = new_node;
        }
        else
        {
            node->children[LEFT] = InsertRec(node->children[LEFT], new_node, cmp_func, param);
        }
    }
    else
    {
        if (NULL == node->children[RIGHT])
        {
            node->children[RIGHT] = new_node;
        }
        else
        {
            node->children[RIGHT] = InsertRec(node->children[RIGHT], new_node, cmp_func, param);
        }
    }
    
    UpdateHeight(node);
    
    return Balance(node);
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
    
    if (NULL == node)
    {
        *status = FAILURE;
        return NULL;
    }
    
    cmp_result = cmp_func(data, node->data, param);
    
    if (0 > cmp_result)
    {
        node->children[LEFT] = RemoveRec(node->children[LEFT], data, cmp_func, param, status);
    }
    else if (0 < cmp_result)
    {
        node->children[RIGHT] = RemoveRec(node->children[RIGHT], data, cmp_func, param, status);
    }
    else
    {
        *status = SUCCESS;
        
        if (NULL == node->children[LEFT] && NULL == node->children[RIGHT])
        {
            free(node);
            return NULL;
        }
        else if (NULL == node->children[LEFT])
        {
            temp = node->children[RIGHT];
            free(node);
            return temp;
        }
        else if (NULL == node->children[RIGHT])
        {
            temp = node->children[LEFT];
            free(node);
            return temp;
        }
        else
        {
            temp = FindMin(node->children[RIGHT]);
            node->data = temp->data;
            node->children[RIGHT] = RemoveRec(node->children[RIGHT], temp->data, cmp_func, param, status);
        }
    }
    
    UpdateHeight(node);
    
    return Balance(node);
}

int AvlRemove(avl_ty* avl, void* data)
{
    int status = FAILURE;
    
    assert(NULL != avl);
    assert(NULL != data);
    
    avl->root = RemoveRec(avl->root, data, avl->cmp_func, avl->param, &status);
    
    return status;
}

static void* FindRec(avl_node_ty* node, void* elem_to_find, 
                     avl_cmp_ty cmp_func, void* param)
{
    int cmp_result = 0;
    
    if (NULL == node)
    {
        return NULL;
    }
    
    cmp_result = cmp_func(elem_to_find, node->data, param);
    
    if (0 == cmp_result)
    {
        return node->data;
    }
    else if (0 > cmp_result)
    {
        return FindRec(node->children[LEFT], elem_to_find, cmp_func, param);
    }
    else
    {
        return FindRec(node->children[RIGHT], elem_to_find, cmp_func, param);
    }
}

void* AvlFind(avl_ty* avl, void* elem_to_find)
{
    assert(NULL != avl);
    assert(NULL != elem_to_find);
    
    return FindRec(avl->root, elem_to_find, avl->cmp_func, avl->param);
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
    else
    {
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
    
    return ForEachRec(avl->root, traverse, action, param);
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
    
    return (NULL == avl->root);
}

size_t AvlHeight(avl_ty* avl)
{
    assert(NULL != avl);
    
    if (NULL == avl->root)
    {
        return 0;
    }
    
    return (size_t)(avl->root->height);
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
    /*KEY: bf < 0 = rightHeavy need to perform left rotation
    	   bf > 0 = leftHeavy need to perform right rotation */
    if (balance > 1)
    {
        if (GetBalanceFactor(node->children[LEFT]) < 0)
        {
            node->children[LEFT] = RotateLeft(node->children[LEFT]);
        }
        return RotateRight(node);
    }
    
    if (balance < -1)
    {
        if (GetBalanceFactor(node->children[RIGHT]) > 0)
        {
            node->children[RIGHT] = RotateRight(node->children[RIGHT]);
        }
        return RotateLeft(node);
    }
    
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
