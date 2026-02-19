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
    
    /* assign fields of created btrie(root, num_bits)*/
    
    /* return trie */
}
