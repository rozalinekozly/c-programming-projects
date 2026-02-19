/*
developer: rozaline
reviewer: 
*/
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
    
    /*assign fields of created root to be null children and is_flag is off*/
    /* assign fields of created btrie(root, num_bits)*/
    
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
static void ReleaseIMP(btrie_node_ty* node_, size_t bit_index_, num_ty num_,
                       size_t total_bits_)
{
    /* if NULL return */
    /* if leaf, turn off is_full, return */
    /* extract bit, recurse down */
    /* turn off is_full */
}
/*----------------------------------------------------------------------------*/
void BTrieRelease(btrie_ty* trie_, num_ty num_)
{
    /* if NULL return */
    /* ReleaseIMP from root */
}
/*----------------------------------------------------------------------------*/
num_ty BTrieGet(btrie_ty* trie_, num_ty num_)
{
    /* assert trie_ */
    /* if root full return 0  )invalid address) */
    /* call GetIMP, return result or 0 (indicates an invalid address ) */
}
/*----------------------------------------------------------------------------*/
static int GetIMP(btrie_node_ty** node_, size_t bit_index_, num_ty* num_,
                  size_t total_bits_)
{
    /* if node _ is NULL*/
    /*allocate and init*/
    
    /*  if node_ is leaf:
    	/* if full return FAIL*/
    	/* else mark full then return SUCCESS */
    	
    /* extract current bit */
		/* if child[bit] full, flip bit */
		/* if child[bit] still full return FAIL */
		/* if flipped, fix num_ at this position, clear lower bits */
    /* recurse, if FAIL return FAIL(save status) */
    /* update is_full */
    /* return SUCCESS */
}




