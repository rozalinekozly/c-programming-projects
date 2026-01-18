/*-----------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : ?
date :18 Jan 2026
------------------------------------------------------------------------------*/
#include <stddef.h>     /* size_t */
#include <assert.h>     /* assert */
#include <stdlib.h>     /* labs(abs for long)*/
#include <stdio.h> /*printf remove later !*/
#include "vsa.h"    /* API*/
/*-----------------------------------------------------------------------------*/
#define WORD_SIZE (sizeof(size_t))
#define ALIGN_UP(x) ((x + WORD_SIZE - 1) & ~(WORD_SIZE - 1))
/*-----------------------------------------------------------------------------*/
struct vsa
{
    size_t occupied_offset;
};

typedef struct 
{
    long block_size;
} block_header_ty;
/*-------------------------- aux function -------------------------------------*/
/*
    arguments: a pointer to block header
    return value: next block (it may exceed the pool limits,
                  check it's return value)
*/
static block_header_ty* NextBlock(block_header_ty* block)
{
    return (block_header_ty*)((char*)block + labs(block->block_size));
}
/*-------------------------implementation--------------------------------------*/
vsa_ty* VsaInit(void* pool, size_t pool_size)
{
    block_header_ty* first = NULL;

    assert(pool);

    pool_size = ALIGN_UP(pool_size);

    first = (block_header_ty*)pool;
    first->block_size = (long)(pool_size - sizeof(block_header_ty));

    return (vsa_ty*)pool;
}
/*-----------------------------------------------------------------------------*/
void* VsaAlloc(vsa_ty* vsa, size_t n_bytes)
{
    /*blocks iterator*/
    block_header_ty* runner = NULL;
    /*to mark end of an allocated block, and new block (if there's enough space)*/
    block_header_ty* next = NULL;
    /*stores aligned n_bytes so the CPU can can access it efficiently*/
    size_t needed = 0;

    assert(vsa);

    needed = ALIGN_UP(n_bytes);
    
    /*start running from the first block */
    runner = (block_header_ty*)vsa;
    
    /*while we have not passed the pool limit*/
    while ((char*)runner < (char*)vsa + labs(runner->block_size))
    {
        /*found a block that can fit needed ??*/
        if (runner->block_size > 0 && (size_t)runner->block_size >= needed)
        {
            if ((size_t)runner->block_size >= needed
                + sizeof(block_header_ty) + WORD_SIZE)
            {
                next = (block_header_ty*)((char*)runner + sizeof(block_header_ty) + needed);
                next->block_size = runner->block_size - needed - sizeof(block_header_ty);
                runner->block_size = -(long)needed;
            }
            else
            {
                runner->block_size = -runner->block_size;
            }
   
            return (char*)runner + sizeof(block_header_ty);
        }

        runner = NextBlock(runner);
    }

    return NULL;
}
/*-----------------------------------------------------------------------------*/
/* preventing internal fragmentation! */
/* remove assert if null it must do nothing just add a  case if null then 
    return so u won't dereference it if u dont derefernce then u dont need that !'*/
void VsaFree(void* ptr)
{
    block_header_ty* curr = NULL;
    block_header_ty* next = NULL;
    size_t curr_size = 0;


    /* get current block header */
    curr = (block_header_ty*)((char*)ptr - sizeof(block_header_ty));

    /* mark current block as free */
    curr->block_size = labs(curr->block_size); /* from negative to positive */
    /* here we free the current passed block */
    curr_size = curr->block_size; /* used to go to next block in order to check it */

    ptr = NULL;
    /* calculate next block header *//* use function NextBlock to go for it */
    next = (block_header_ty*)((char*)curr + sizeof(block_header_ty) + curr_size);
    if(NULL == next)
    {
        printf("next is NULL!\n");
    }
    printf("here\n");
    

    /* unify with next block if it is free */
    if (next->block_size > 0)
    {
    printf("here2");
        curr->block_size += sizeof(block_header_ty) + next->block_size;
    }
}
/*-----------------------------------------------------------------------------*/

size_t VsaLargestChunk(vsa_ty* vsa)
{
    block_header_ty* runner = NULL;
    size_t max = 0;

    assert(vsa);

    runner = (block_header_ty*)vsa;

    while ((char*)runner < (char*)vsa + labs(runner->block_size))
    {
        if (runner->block_size > 0 &&
            (size_t)runner->block_size > max)
        {
            max = (size_t)runner->block_size;
        }

        runner = NextBlock(runner);
    }

    return max;
}

