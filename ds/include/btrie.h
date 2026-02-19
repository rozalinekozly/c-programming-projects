#ifndef __BTRIE_H__
#define __BTRIE_H__

#include <stddef.h>     /* size_t */

typedef struct btrie btrie_ty;
typedef size_t addr_ty;

/****************************************************************************** 
* 	Description:
* 		Creates an empty "btrie"
* 	Return value:
* 		On success, a pointer to the created trie
* 		On failure, NULL
* 	O(1)
******************************************************************************/
btrie_ty* BTrieCreate(size_t num_bits_);

/****************************************************************************** 
* 	Description:
* 		Destroys the trie and frees all allocated memory.
* 		No operations performed if "trie" is NULL
*   O(n)
******************************************************************************/
void BTrieDestroy(btrie_ty* trie_);

/****************************************************************************** 
* 	Description:
* 		Frees "addr" from "trie"
*   O(1)
******************************************************************************/
void BTrieFreeAddr(btrie_ty* trie_, addr_ty addr_);

/****************************************************************************** 
* 	Description:
* 		Allocates a new available address.
* 	Return value:	
* 		On success, returns the nearest address available to "addr_"
*       On fail, returns address with 0 value.
* 	Undefined behaviour:
        "trie_" is NULL.
*   O(1)
******************************************************************************/
addr_ty BTrieGetAddr(btrie_ty* trie_, addr_ty addr_);
    
/****************************************************************************** 
* 	Description:
*       Count all available addresses in trie.
* 	Return value:
*       Number of available addresses in trie.
*   Undefined behaviour:
*       "trie_" is NULL
*   O(n)
******************************************************************************/
size_t BTrieCountAvailable(const btrie_ty* trie_);

#endif /* __BTRIE_H__ */
