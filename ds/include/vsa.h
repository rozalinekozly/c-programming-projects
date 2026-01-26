#ifndef __ILRD_VSA_H__
#define __ILRD_VSA_H__

#include <stddef.h>     /*size_t*/

typedef struct vsa vsa_ty;

/******************************************************************************
*	Description: 
*       Initializes a vsa_ty for the input pool
*   Return value: 
*		vsa_ty* pointer on success
*       NULL on fail
*   Undefined behavior:
*       pool is NULL
*	O(1)
******************************************************************************/
vsa_ty* VsaInit(void* pool, size_t pool_size);

/******************************************************************************
*	Description: 
*       Allocates "n_bytes" in the pool "vsa" manages
*   Return value: 
*		A pointer to the beginning of the allocated region, on success
*       NULL on fail
*   Undefined behavior:
*       vsa is NULL
*	O(n)
******************************************************************************/
void* VsaAlloc(vsa_ty* vsa, size_t n_bytes);


/******************************************************************************
*	Description: 
*       Frees the allocated memory region starting in "ptr" address
*   Undefined behavior:
*       ptr is NULL
*	O(1)
******************************************************************************/
void VsaFree(void* ptr);


/******************************************************************************
*	Description: 
*       Searches the pool for the largest chunk of bytes available for
*       allocation
*   Return value: 
*		The largest chunk available
*   Undefined behavior:
*       vsa is NULL
*	O(n)
******************************************************************************/
size_t VsaLargestChunk(vsa_ty* vsa);

#endif /*__ILRD_VSA_H__*/
