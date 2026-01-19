/*-----------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : Steve
date :19 Jan 2026
------------------------------------------------------------------------------*/
#include <stddef.h>     /* size_t */
#include <assert.h>     /* assert */
#include <stdlib.h>     /* labs(abs for long)*/
#include <stdio.h>      /*printf remove later !*/
#include "vsa.h"        /* API*/
/*-----------------------------------------------------------------------------*/
#define WORD_SIZE           (sizeof(size_t))
#define ALIGN_DOWN(x)       ((x) & ~(WORD_SIZE - 1))

#define FIRST_BLOCK_IN_POOL(vsa)    ((block_header_ty*)((char*)(vsa) + sizeof(vsa_ty)))
#define IS_ILLEGAL_BLOCK(block)   ((block) == ILLEGAL_BLOCK)

#define ILLEGAL_BLOCK   ((block_header_ty*) NULL)
#define IS_USED_BLOCK(block)                 ((block)->block_size > 0)
#define IS_FREE_BLOCK(block)                 ((block)->block_size < 0)
#define IT_REACHED_THE_END(vsa, block)   ((char*)(block) < (char*)(vsa) + (vsa)->pool_size)


#define NEXT_BLOCK(block)   ((block_header_ty*)((char*)(block) + labs((block)->block_size)))
#define BLOCK_HEADER_SIZE   (sizeof(block_header_ty))
/*-----------------------------------------------------------------------------*/
struct vsa
{
    size_t pool_size;
};
/*-----------------------------------------------------------------------------*/
/*  
    utiliesed in declareing a block
    it's placed as a header of the block and contains
    a number block_size it's abs is the size of the block (till next header object
    or end of the pool), it's sign represents either it's free (+) or used (-)
*/
typedef struct 
{
    long block_size;
} block_header_ty;
/*-------------------------- aux function -------------------------------------*/
/*
    NextBlock(curr_block)
    arguments: a pointer to block header
    return value: next block (it may exceed the pool limits, check it's 
    return value)
*/
static block_header_ty* NextBlock(block_header_ty* block)
{
    return (block_header_ty*)((char*)block + labs(block->block_size));
}
/*-----------------------------------------------------------------------------*/
/*
    purpose: giving a starting block, it finds the closest free block, including 
    the start block.
    return vlaues: it returns the closest free block in case of success, otherwise it 
    returns illegal_block means did not found a free block.
*/
static block_header_ty* FindFreeBlock(vsa_ty* vsa, block_header_ty* start_block)
{
    block_header_ty* runner = start_block;
    
    while(!IT_REACHED_THE_END(vsa, runner))
    {
        if(IS_FREE_BLOCK(runner))
        {
            return runner;
        }
        runner = NEXT_BLOCK(runner);
    }
    return ILLEGAL_BLOCK;
}
/*-----------------------------------------------------------------------------*/
/*
    purpose: unify all upcoming sequenced free blocks into one block unify_to
    return values: returns closest used block, or illegal block in case 
    it reached the end.
*/
static block_header_ty* UnifyFreeBlocks(vsa_ty* vsa, block_header_ty* unify_to)
{
    block_header_ty* runner = NextBlock(unify_to);
    
    while(!IT_REACHED_THE_END(vsa, runner))
    {
        if(IS_USED_BLOCK(runner))
        {
            return runner;
        }
        unify_to->block_size += runner->block_size;
        runner = NEXT_BLOCK(runner);
    }
    return ILLEGAL_BLOCK;
}
/*-------------------------implementation--------------------------------------*/
vsa_ty* VsaInit(void* pool, size_t pool_size)
{
    block_header_ty* first = NULL;

    assert(pool);

    pool_size = ALIGN_DOWN(pool_size);

    first = (block_header_ty*)pool;
    first->block_size = (long)(pool_size - sizeof(block_header_ty));

    return (vsa_ty*)pool;
}
/*-----------------------------------------------------------------------------*/
void* VsaAlloc(vsa_ty* vsa, size_t n_bytes)
{
    /* blocks iterator */
    block_header_ty* runner = NULL;
    block_header_ty* unify_to = NULL;
    block_header_ty* next = NULL;
    size_t needed = 0;

    assert(vsa);

    /* start iterating from the begining of the pool (where first block exists) */
    runner = FIRST_BLOCK_IN_POOL(vsa);

    while (!IT_REACHED_THE_END(vsa, runner))
    {
        unify_to = FindFreeBlock(vsa,runner);
        if(IS_ILLEGAL_BLOCK(unify_to))
        {
            break;
        }
        runner = UnifyFreeBlocks(vsa, unify_to);
    }
    
    runner = FIRST_BLOCK_IN_POOL(vsa);
    needed = ALIGN_DOWN(n_bytes);
        /* -------- TRY TO ALLOCATE -------- */
    while (!IT_REACHED_THE_END(vsa, runner))
    {
        if (runner->block_size > 0 && (size_t)runner->block_size >= needed)
         {
            if ((size_t)runner->block_size >=
                needed + sizeof(block_header_ty) + WORD_SIZE)
            {
                next = (block_header_ty*)
                    ((char*)runner + sizeof(block_header_ty) + needed);

                next->block_size =
                    runner->block_size - needed - sizeof(block_header_ty);

                runner->block_size = -(long)needed;
            }
            else
            {

                runner->block_size = -runner->block_size;
            }

            return (char*)runner + BLOCK_HEADER_SIZE;
        }

        runner = NextBlock(runner);
    }

    return NULL;
}
/*-----------------------------------------------------------------------------*/
/* responsibilities: if ptr is not null then change it's block size field into positive, same amount
    so use labs */
void VsaFree(void* ptr)
{
    block_header_ty* header = NULL;

    if (NULL == ptr)
    {
        return;
    }

    header = (block_header_ty*)((char*)ptr - sizeof(block_header_ty));
    header->block_size = labs(header->block_size);
}
/*-----------------------------------------------------------------------------*/
/* responsibilities: 
*/
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

        runner = NEXT_BLOCK(runner);
    }

    return max;
}

