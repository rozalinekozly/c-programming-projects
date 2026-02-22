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
static int GetIMP(btrie_node_ty** node_, size_t current_depth_, num_ty *num_,
                  size_t max_depth_);
static size_t GetBitIMP(num_ty num_, size_t bit_index_);
static void ReleaseIMP(btrie_node_ty* node_, size_t remaining_depth_, num_ty num_);
static size_t CountAvailableIMP(btrie_node_ty* node_, size_t current_depth_, size_t max_depth_);
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
    if(FAIL == GetIMP(&ret->root, 0, &num, num_bits_))
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
    num_ty ret = num_; /*and this is what u need to return do not change the argument val!*/
    /*standart: do not change value of a perameter */
    /* assert trie_ */
    assert(trie_);

	/*redundant */
    /* if root full return 0  )invalid address) */
    if (trie_->root->is_full)
    {
        return 0;
    }

    /* call GetIMP, return result or 0 (indicates an invalid address ) */
    /*here send &ret*/
    if (FAIL == GetIMP(&(trie_->root), 0, &ret, trie_->num_bits))
    {
        return 0;
    }

    return ret;
}
/*----------------------------------------------------------------------------*/
/*TODO: 
	1- remove max_depth argument
	2- travrse on number from msb to lsb
	3- and --depth to reach 0 (then it is a leaf)
	*/
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
static size_t CountAvailableIMP(btrie_node_ty* node_, size_t current_depth_, size_t max_depth_)
{
    size_t remaining_bits = 0;

    /* if node_ is NULL */
    if (NULL == node_)
    {
        /* return 2^(max_depth_- current_depth_) 
        (can be performed by shifting)*/
        remaining_bits = max_depth_- current_depth_;
        return (size_t)1 << remaining_bits;
    }

    /* if node_.is_full */
    if (node_->is_full)
    {
        /* return 0 */
        return 0;
    }

    /* if leaf(current_depth_ == max_depth_) */
    if (current_depth_ == max_depth_)
    {
        /* return 1 */
        return 1;
    }

    /* recurse return
        CountAvailableIMP(left,  current_depth_ + 1, max_depth_)
        +
        CountAvailableIMP(right, current_depth_ + 1, max_depth_)
    */
    return CountAvailableIMP(node_->children[0], current_depth_ + 1, max_depth_)
         + CountAvailableIMP(node_->children[1], current_depth_ + 1, max_depth_);
}


