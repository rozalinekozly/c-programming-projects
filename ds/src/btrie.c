/*
developer: rozaline
reviewer: 
*/
/*----------------------------------------------------------------------------*/
#include <stdlib.h>	/*malloc, free, NULL*/
#include <assert.h>	/*assert*/
#include <stddef.h>	/*size_t*/
#include "btrie.h"	/*API*/
/*--------------------------forward declarations------------------------------*/
static int GetIMP(btrie_node_ty** node_, size_t bit_index_, num_ty *num_,
                  size_t total_bits_);
static void ReleaseIMP(btrie_node_ty* node_, size_t bit_index_, num_ty num_,
                       size_t total_bits_);
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
/*----------------------------------------------------------------------------*/
btrie_ty* BTrieCreate(size_t num_bits_)
{
	/*asserts*/
	/* allocate btrie_ty */
    /* if fail return NULL */
    
    /* allocate root node */
    /* if fail free trie, return NULL */
    
    /*set fields of created root to be null children and is_flag is off*/
    /* set fields of created btrie(root, num_bits)*/
    
    /* reserve illegal address 000...0 */
        /* num = 0 */
        /* call BTrieGet(trie, num) */
        
    /* return trie */
}
/*----------------------------------------------------------------------------*/
void BTrieDestroy(btrie_ty* trie_)
{
	/* if trie_ is NULL return */
	/* recursively destroy all children nodes */
	/* free root */
	/*handle dangling pointer*/
	/* free trie_ */
	/*handle dangling pointer*/
}
/*----------------------------------------------------------------------------*/
void BTrieRelease(btrie_ty* trie_, num_ty num_)
{
    /* if NULL return */
    /*assert num_ is not 000..*/
    /* call ReleaseIMP from root */
}
/*----------------------------------------------------------------------------*/
num_ty BTrieGet(btrie_ty* trie_, num_ty num_)
{
    /* assert trie_ */
    /* if root full return 0  )invalid address) */
    /* call GetIMP, return result or 0 (indicates an invalid address ) */
}
/*----------------------------------------------------------------------------*/
size_t BTrieCountAvailable(trie_)
{
    /* assert trie_ */

    /* return CountAvailableIMP(root, 0, num_bits) */
}
/*----------------------------------------------------------------------------*/
static void ReleaseIMP(btrie_node_ty* node_, size_t bit_index_, num_ty num_,
                       size_t total_bits_)
{
    /* if NULL return */
    /* if leaf*/
    	/* turn off is_full flag */
    	/*return*/
    /* extract bit, recurse down */
    /* turn off is_full */
}
/*----------------------------------------------------------------------------*/
static int GetIMP(btrie_node_ty** node_, size_t bit_index_, num_ty* num_,
                  size_t total_bits_)
{
    /* if node _ is NULL*/
        /*allocate node*/
    	/*init children to NULL, is_full = 0*/
    
    /*  if node_ is leaf:*/
    	/* if full return FAIL*/
    	/* else mark full then return SUCCESS */
    	
    /* extract current bit MSB to LSB*/
		/* if child[bit] exit && is_full*/
			/*if bit is 0*/
				/* flip bit to 1*/
				/*fix num_ at this bit*/
				/* clear lower bits */
				/*if child[1] exists && is_full*/
					/*return FAIL*/
		/* else (bit is 1)*/
			/*return FAIL */
		
    /* recurse and save status*/
    
    /* if FAIL */
    	/*return FAIL*/
    	
    /*else*/
		/* if both children exist and both are full*/
			/*mark node is full*/
		/* return SUCCESS */
}
/*----------------------------------------------------------------------------*/
CountAvailableIMP(node_, bit_index_, total_bits_)
{
    /* if node_ is NULL */
        /* return 2^(total_bits_ - bit_index_) 
        (can be performed by shifting)*/

    /* if node_.is_full */
        /* return 0 */

    /* if leaf(bit_index_ == total_bits_) */
        /* return 1 */

    /* recurse return
        CountAvailableIMP(left,  bit_index_ + 1, total_bits_)
        +
        CountAvailableIMP(right, bit_index_ + 1, total_bits_)
    */
}


