/*-----------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : ?
date :18 Jan 2026
------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>

#include "vsa.h"

#define POOL_SIZE 512
/*units tests*/
/*void TestInit();
void TestAllocFree();
void TestLargestChunk();*/

/*user demo(s) tests*/
void UserDemo();
/* black box testing and not white box testing 
amit: to map to ur test some locations, and he said to perform malloc on it or smth */
int main(void)
{
   /*TestInit();
    TestAllocFree();
    TestLargestChunk();*/
    UserDemo();
    return 0;
}
/* user do nothing about blocks within the pool and it's implementation '*/
void UserDemo()
{
    int pool[POOL_SIZE];
    vsa_ty* vsa_pool = NULL;
    size_t largest_chunk = 0;
    int* ptr1 = NULL;
    vsa_pool = VsaInit(pool, POOL_SIZE);
    
    largest_chunk = VsaLargestChunk(vsa_pool);
    /* check that largest chunk = pool size - vsa size 
       also check that it's the value saved in */
    if(largest_chunk + sizeof(vsa_pool) != POOL_SIZE)
    {
        printf("[FAIL]\tmissed space\n");
    }
    printf("largest chunk after init is %lu\n", largest_chunk);
    printf("sizeof vsa struct is %lu\n", sizeof(vsa_pool));
    
    ptr1 = (int*)VsaInit(vsa_pool, 4*sizeof(int));
    if(NULL == ptr1)
    {
        printf("[FAIL]\tfailed at allocation\n");
    }
    else
    {
        printf("[PASS] allocation 1\n");
    }
    VsaFree(ptr1);
    if(ptr1 != NULL)
    {
        printf("[FAIL]ptr is not null after free-ing\n");
    
    }
    else
    {
        printf("[PASS] ptr is null after free-ing");
    }
    return;
}
