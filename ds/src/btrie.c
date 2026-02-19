/*
developer: rozaline
reviewer: 
*/
#include "btrie.h"	/*API*/
/*--------------------------forward declarations------------------------------*/
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
	/* free trie_ */
}
/*----------------------------------------------------------------------------*/
void BTrieRelease(btrie_ty* trie_, num_ty num_)
{
	/* if trie_ is NULL return */
	/* search for the node representing num_ */
	/* if not found or already free return */
	/* mark leaf's field is_full as not full*/
	/* while climbing up
		turn off is_full flag*/
}
/*----------------------------------------------------------------------------*/








