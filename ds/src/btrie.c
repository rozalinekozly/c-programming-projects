/*
developer: rozaline
reviewer: 
*/
/*----------------------------------------------------------------------------*/
#include <stdlib.h>	/*malloc, calloc, free, NULL*/
#include <assert.h>	/*assert*/
#include <stddef.h>	/*size_t*/

#include "btrie.h"	/*API*/
#include "utils.h"
/*----------------------------------------------------------------------------*/
/*change this to enums*/
#define SUCCESS (0)
#define FAIL    (1)
/*----------------------------------------------------------------------------*/
typedef struct btrie_node
{
    struct btrie_node* children[2];  /* [0] = bit 0 , [1] = bit 1 */
    int is_full;                     /* flag if 1 it indicates it's full (boolean)'*/
} btrie_node_ty;

struct btrie
{
    btrie_node_ty* root; 
    size_t num_bits;
};
/*--------------------------forward declarations------------------------------*/
static void DestroyIMP(btrie_node_ty* node_);
static int GetIMP(btrie_node_ty** node_, size_t remaining_depth_, num_ty *num_);
static size_t GetBitIMP(num_ty num_, size_t bit_index_);
static void ReleaseIMP(btrie_node_ty* node_, size_t remaining_depth_, num_ty num_);
static size_t CountAvailableIMP(btrie_node_ty* node_, size_t remaining_depth_);
/*----------------------------------------------------------------------------*/
btrie_ty* BTrieCreate(size_t num_bits_)
{
	btrie_ty* ret = NULL;
	btrie_node_ty* root  = NULL;
	num_ty num = 0;
	
	/*asserts*/
	assert(num_bits_ > 0);
	/* allocate btrie_ty */
	ret = (btrie_ty*)malloc(sizeof(btrie_ty));
    /* if fail*/
    	/*return NULL */
	if (NULL == ret)
	{
		return NULL;
	}
    
    /* allocate root node and intialize fields*/
	root = (btrie_node_ty *)calloc(1, sizeof(btrie_node_ty));
    /* if fail*/
    	/*free trie*/
    	/* return NULL */
	if (NULL == root)
	{
		free(ret);
		DEBUG_BAD_MEM(ret, btrie_ty*);
		return NULL;
	}
    
    /* set fields of created btrie(root, num_bits)*/
	ret->root = root;
	ret->num_bits = num_bits_;
    
    /* reserve illegal address 000...0 */
        /* num = 0 */
        /* call BTrieGet(trie, num) */
    if(FAIL == GetIMP(&ret->root, num_bits_, &num))
    {
    	BTrieDestroy(ret);
    	return NULL;
    }

    /* return trie */
	return ret;
}
/*----------------------------------------------------------------------------*/
void BTrieDestroy(btrie_ty* trie_)
{
	/* if trie_ is NULL do nothing */
	if (NULL == trie_)
	{
		return;
	}

	/* recursively destroy all children nodes including root*/
	DestroyIMP(trie_->root);

	/*handle dangling pointer*/
	DEBUG_BAD_MEM(trie_->root, btrie_node_ty*);
	
	/* free trie_ */
	free(trie_);

	/*handle dangling pointer*/
	DEBUG_BAD_MEM(trie_, btrie_ty*);
}
/*----------------------------------------------------------------------------*/
static void DestroyIMP(btrie_node_ty* node_)
{
	/*if node is null*/
    if (NULL == node_)
    {
    	/*do nothing*/
        return;
    }
	/*recursively call subtrees*/
    DestroyIMP(node_->children[0]);
    DestroyIMP(node_->children[1]);
	
	/*handle dangling pointer*/
	DEBUG_BAD_MEM(node_->children[0], btrie_node_ty*);
	DEBUG_BAD_MEM(node_->children[1], btrie_node_ty*);
	
	/*recursion tail: free node */
    free(node_);
}
/*----------------------------------------------------------------------------*/
void BTrieRelease(btrie_ty* trie_, num_ty num_)
{
	/*assert trie not null*/
    assert(NULL != trie_);

    /*assert num_ larger than 0*/
    assert(num_ > 0);

    /* call ReleaseIMP from root */
    ReleaseIMP(trie_->root, trie_->num_bits, num_);
}
/*----------------------------------------------------------------------------*/
static void ReleaseIMP(btrie_node_ty* node_, size_t remaining_depth_, num_ty num_)
{
    size_t bit = 0;

    assert(NULL != node_);

    /* if leaf */
    if (0 == remaining_depth_)
    {
        assert(node_->is_full);
        node_->is_full = 0;
        return;
    }

    /* extract current bit (MSB to LSB) */
    bit = GetBitIMP(num_, remaining_depth_ - 1);

    /* recurse */
    ReleaseIMP(node_->children[bit], remaining_depth_ - 1, num_);

    /* update parent state */
    node_->is_full = 0;
}
/*----------------------------------------------------------------------------*/
static size_t GetBitIMP(num_ty num_, size_t bit_index_)
{
    return (num_ >> bit_index_) & 1;
}
/*----------------------------------------------------------------------------*/
num_ty BTrieGet(btrie_ty* trie_, num_ty num_)
{
    num_ty ret = num_; 
    
    /* assert trie_ */
    assert(trie_);

    /* call GetIMP, return result or 0 (indicates an invalid address ) */
    /*here send &ret*/
    if (FAIL == GetIMP(&(trie_->root),  trie_->num_bits, &ret))
    {
        return 0;
    }

    return ret;
}
/*----------------------------------------------------------------------------*/
static int GetIMP(btrie_node_ty** node_, size_t remaining_depth_, num_ty* num_)
{
    size_t bit = 0;

    /* allocate node if needed */
    if (NULL == *node_)
    {
        *node_ = calloc(1, sizeof(btrie_node_ty));
        if (NULL == *node_)
        {
            return FAIL;
        }
    }

    /* if leaf */
    if (0 == remaining_depth_)
    {
        if ((*node_)->is_full)
        {
            return FAIL;
        }

        (*node_)->is_full = 1;
        return SUCCESS;
    }

    /* extract current bit (MSB to LSB) */
    bit = GetBitIMP(*num_, remaining_depth_ - 1);

    /* if child exists and is full */
    if ((*node_)->children[bit] &&
        (*node_)->children[bit]->is_full)
    {
        if (0 == bit)
        {
            /* flip current bit to 1 */
            *num_ |= ((num_ty)1 << (remaining_depth_ - 1));

            /* clear lower bits */
            *num_ &= ~(((num_ty)1 << (remaining_depth_ - 1)) - 1);

            bit = 1;

            if ((*node_)->children[1] &&
                (*node_)->children[1]->is_full)
            {
                return FAIL;
            }
        }
        else
        {
            return FAIL;
        }
    }

    /* recurse */
    if(FAIL == GetIMP(&((*node_)->children[bit]), remaining_depth_ - 1, num_))
    {
    	return FAIL;
    }

    /* update fullness */
    if ((*node_)->children[0] && (*node_)->children[1] &&
        (*node_)->children[0]->is_full && (*node_)->children[1]->is_full)
    {
        (*node_)->is_full = 1;
    }

    return SUCCESS;
}
/*----------------------------------------------------------------------------*/
size_t BTrieCountAvailable(const btrie_ty* trie_)
{
    /* assert trie_ */
    assert(trie_);

    /* return CountAvailableIMP(root, 0, num_bits) */
    return CountAvailableIMP(trie_->root, trie_->num_bits);
}
/*----------------------------------------------------------------------------*/
static size_t CountAvailableIMP(btrie_node_ty* node_, size_t remaining_depth_)
{
    /* if node is NULL then whole subtree is free */
    if (NULL == node_)
    {
        return (size_t)1 << remaining_depth_;
    }

    /* if node is full */
    if (node_->is_full)
    {
        return 0;
    }

    /* if leaf */
    if (0 == remaining_depth_)
    {
        return 1;
    }

    /* recurse */
    return CountAvailableIMP(node_->children[0], remaining_depth_ - 1)
         + CountAvailableIMP(node_->children[1], remaining_depth_ - 1);
}


