#include <assert.h>     /* assert */
#include <stddef.h>     /* size_t */

#include "fsa.h"

#define WORD_SIZE (sizeof(size_t))

/* Struct Definition /

struct fsa
{
    void *free_list;
};

/*Static Helper Declarations */

static size_t AlignUp(size_t size);
static void* NextBlock(void* block, size_t block_size);

/*API Implementation */

size_t FsaSuggestedSize(size_t n_blocks, size_t block_size)
{
    size_t aligned_block_size = AlignUp(block_size);
    size_t header_size = AlignUp(sizeof(fsa_ty));

    return header_size + (n_blocks * aligned_block_size);
}

fsa_ty* FsaInit(void* pool_p, size_t pool_size, size_t block_size)
{
    fsa_ty *fsa = NULL;
    char *runner = NULL;
    size_t aligned_block_size = AlignUp(block_size);
    size_t header_size = AlignUp(sizeof(fsa_ty));
    size_t num_blocks = 0;
    size_t i = 0;

    assert(pool_p);

    fsa = (fsa_ty*)pool_p;
    runner = (char*)pool_p + header_size;

    num_blocks = (pool_size - header_size) / aligned_block_size;

    fsa->free_list = runner;

    for (i = 0; i < num_blocks - 1; ++i)
    {
        *(void**)runner = NextBlock(runner, aligned_block_size);
        runner = (char*)runner + aligned_block_size;
    }

    *(void**)runner = NULL;

    return fsa;
}

void* FsaAlloc(fsa_ty* fsa)
{
    void *allocated_block = NULL;

    assert(fsa);

    if (NULL == fsa->free_list)
    {
        return NULL;
    }

    allocated_block = fsa->free_list;
    fsa->free_list = *(void**)fsa->free_list;

    return allocated_block;
}

void FsaFree(fsa_ty* fsa, void* p)
{
    assert(fsa);
    assert(p);

    *(void**)p = fsa->free_list;
    fsa->free_list = p;
}

size_t FsaAvailableBlocks(fsa_ty* fsa)
{
    size_t count = 0;
    void *runner = NULL;

    assert(fsa);

    runner = fsa->free_list;

    while (NULL != runner)
    {
        ++count;
        runner = *(void**)runner;
    }

    return count;
}

/*Static Helper Functions */

static size_t AlignUp(size_t size)
{
    return (size + (WORD_SIZE - 1)) & ~(WORD_SIZE - 1);
}

static void* NextBlock(void* block, size_t block_size)
{
    return (char*)block + block_size;
}

