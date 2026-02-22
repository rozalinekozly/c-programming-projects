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
static int GetIMP(btrie_node_ty** node_, size_t bit_index_, num_ty *num_,
                  size_t total_bits_);
static void ReleaseIMP(btrie_node_ty* node_, size_t bit_index_, num_ty num_,
                       size_t total_bits_);
static size_t CountAvailableIMP(btrie_node_ty* node_, size_t bit_index_, size_t total_bits_);
/*----------------------------------------------------------------------------*/
btrie_ty* BTrieCreate(size_t num_bits_)
{
	btrie_ty* ret = NULL;
	btrie_node_ty* root  = NULL;
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
    BTrieGet(ret, 0);
        
    /* return trie */
	return ret;
}
/*----------------------------------------------------------------------------*/
void BTrieDestroy(btrie_ty* trie_)
{
	/* if trie_ is NULL return */
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
    if (NULL == node_)
    {
        return;
    }

    DestroyIMP(node_->children[0]);
    DestroyIMP(node_->children[1]);

    free(node_);
    DEBUG_BAD_MEM(node_, btrie_node_ty*);
}
/*----------------------------------------------------------------------------*/
void BTrieRelease(btrie_ty* trie_, num_ty num_)
{
    /* if NULL return */
    if (NULL == trie_)
    {
        return;
    }

    /*assert num_ is not 000..*/
    assert(num_ != 0);

    /* call ReleaseIMP from root */
    ReleaseIMP(trie_->root, 0, num_, trie_->num_bits);
}
/*----------------------------------------------------------------------------*/
static void ReleaseIMP(btrie_node_ty* node_, size_t bit_index_, num_ty num_,
                       size_t total_bits_)
{
	 size_t shift = 0;
	 size_t bit = 0;
	 
    /* if NULL return this situation happens if someone trys to free of not given address its better be assert*/
    if (NULL == node_)
    {
        return;
    }
    /*    node_->is_full = 0; <- add this here to prevent duplication*/
	/*this is the base case*/
    /* if leaf*/
    if (bit_index_ == total_bits_)
    {
        /* turn off is_full flag */
        node_->is_full = 0;
        /*return*/
        return;
    }

    /* extract bit, recurse down */
    shift = total_bits_ - 1 - bit_index_;
    bit = (num_ >> shift) & 1;

    ReleaseIMP(node_->children[bit], bit_index_ + 1, num_, total_bits_);

    /* turn off is_full */
    node_->is_full = 0;
}
/*----------------------------------------------------------------------------*/
num_ty BTrieGet(btrie_ty* trie_, num_ty num_)
{
    /* assert trie_ */
    assert(trie_);

    /* if root full return 0  )invalid address) */
    if (trie_->root->is_full)
    {
        return 0;
    }

    /* call GetIMP, return result or 0 (indicates an invalid address ) */
    if (FAIL == GetIMP(&(trie_->root), 0, &num_, trie_->num_bits))
    {
        return 0;
    }

    return num_;
}
/*----------------------------------------------------------------------------*/
static int GetIMP(btrie_node_ty** node_, size_t bit_index_, num_ty* num_,
                  size_t total_bits_)
{
	size_t shift = 0;
	size_t bit = 0;
	int ret = 0;
	
    /* if node _ is NULL*/
    if (NULL == *node_)
    {
        /*allocate node*/
        *node_ = malloc(sizeof(btrie_node_ty));
        if (NULL == *node_)
        {
            return FAIL;
        }

        /*init children to NULL, is_full = 0*/
        (*node_)->children[0] = NULL;
        (*node_)->children[1] = NULL;
        (*node_)->is_full = 0;
    }

    /*  if node_ is leaf:*/
    if (bit_index_ == total_bits_)
    {
        /* if full return FAIL*/
        if ((*node_)->is_full)
        {
            return FAIL;
        }

        /* else mark full then return SUCCESS */
        (*node_)->is_full = 1;
        return SUCCESS;
    }

    /* extract current bit MSB to LSB*/
    shift = total_bits_ - 1 - bit_index_;
    bit = (*num_ >> shift) & 1;

    /* if child[bit] exit && is_full*/
    if ((*node_)->children[bit] && (*node_)->children[bit]->is_full)
    {
        /*if bit is 0*/
        if (0 == bit)
        {
            /* flip bit to 1*/
            bit = 1;

            /*fix num_ at this bit*/
            *num_ |= ((num_ty)1 << shift);

            /* clear lower bits */
            *num_ &= ~(((num_ty)1 << shift) - 1);

            /*if child[1] exists && is_full*/
            if ((*node_)->children[1] && (*node_)->children[1]->is_full)
            {
                /*return FAIL*/
                return FAIL;
            }
        }
        /* else (bit is 1)*/
        else
        {
            /*return FAIL */
            return FAIL;
        }
    }

    /* recurse and save status*/
    ret = GetIMP(&((*node_)->children[bit]), bit_index_ + 1, num_, total_bits_);

    /* if FAIL */
    if (FAIL == ret)
    {
        /*return FAIL*/
        return FAIL;
    }

    /*else*/
    /* if both children exist and both are full*/
    if ((*node_)->children[0] &&
        (*node_)->children[1] &&
        (*node_)->children[0]->is_full &&
        (*node_)->children[1]->is_full)
    {
        /*mark node is full*/
        (*node_)->is_full = 1;
    }

    /* return SUCCESS */
    return SUCCESS;
}
/*----------------------------------------------------------------------------*/
size_t BTrieCountAvailable(const btrie_ty* trie_)
{
    /* assert trie_ */
    assert(trie_);

    /* return CountAvailableIMP(root, 0, num_bits) */
    return CountAvailableIMP(trie_->root, 0, trie_->num_bits);
}
/*----------------------------------------------------------------------------*/
static size_t CountAvailableIMP(btrie_node_ty* node_, size_t bit_index_, size_t total_bits_)
{
    size_t remaining_bits = 0;

    /* if node_ is NULL */
    if (NULL == node_)
    {
        /* return 2^(total_bits_ - bit_index_) 
        (can be performed by shifting)*/
        remaining_bits = total_bits_ - bit_index_;
        return (size_t)1 << remaining_bits;
    }

    /* if node_.is_full */
    if (node_->is_full)
    {
        /* return 0 */
        return 0;
    }

    /* if leaf(bit_index_ == total_bits_) */
    if (bit_index_ == total_bits_)
    {
        /* return 1 */
        return 1;
    }

    /* recurse return
        CountAvailableIMP(left,  bit_index_ + 1, total_bits_)
        +
        CountAvailableIMP(right, bit_index_ + 1, total_bits_)
    */
    return CountAvailableIMP(node_->children[0], bit_index_ + 1, total_bits_)
         + CountAvailableIMP(node_->children[1], bit_index_ + 1, total_bits_);
}


