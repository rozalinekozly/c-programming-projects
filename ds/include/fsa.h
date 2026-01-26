#ifndef __ILRD_FSA_H__
#define __ILRD_FSA_H__

#include <stddef.h>	/* size_t */

typedef struct fsa fsa_ty;

/******************************************************************************
*	Description: 
*       	Calculates the pool size required to initialize a fsa_ty.
* 
*   	Return value: 
*		Suggested pool size to be used in the FsaInit.
*	O(1)
******************************************************************************/
size_t FsaSuggestedSize(size_t n_blocks, size_t block_size);

/******************************************************************************
*	Description: 
*       	Initialize an fsa instance for the pool_p.
* 
*   	Return value: 
*		    Pointer to fsa_ty.
* 
*   	Undefined: 
*       	pool_p is NULL.
*       	pool_size is not FsaSuggestedSize() value.
*       	block_size not matching the block_size used in 
*		FsaSuggestedSize().
*	O(n)
******************************************************************************/
fsa_ty* FsaInit(void* pool_p, size_t pool_size, size_t block_size);

/******************************************************************************
*	Description: 
*       	Assignes a new block in memory of block_size 
*		provided in FsaInit.
* 
*   	Return value:
*       	On success, pointer to the new allocated block.
*       	On failure, NULL.
* 
*   	Undefined:
*       	Invalid fsa
*	O(1)
******************************************************************************/
void* FsaAlloc(fsa_ty* fsa);

/******************************************************************************
*	Description: 
*       	Free the block pointed by "p" in the pool.
*
*   	Undefined:
*       	Invalid fsa.
*       	Invalid p. 
*           P was free.
*	O(1)
******************************************************************************/
void FsaFree(fsa_ty* fsa, void* p);

/******************************************************************************
*	Description: 
*       	Calculates the available number of blocks in the pool.
*
*   	Undefined:
*       	Invalid fsa.
* 
*	O(n)
******************************************************************************/
size_t FsaAvailableBlocks(fsa_ty* fsa);

#endif /*__ILRD_FSA_H__*/ 
