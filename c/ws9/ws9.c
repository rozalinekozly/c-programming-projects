/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : Nimrod
worksheet : 9 (word boundary optimization)
version   : 2
date      : 7 Dec 2025
stage     : post mimr
----------------------------------------------------------------------------*/

#include <stdio.h>	       /* printf() - for testing*/
#include <string.h>    	       /* strcpy(), strlen(), memset(), memcmp(), memmove() */
#include <assert.h>	       /* assert() - for debugging */
#include <limits.h>	       /* CHAR_BIT */

#define WORD_SIZE_BYTES                       (sizeof(size_t))		/* by not adding a hard-coded number, it makes the code adapts to 32-bit and 64-bit machines */

/*-- function declarations --*/
/* public API */
void* MemSet(void* str, int value, size_t num);
void* MemCpy (void* dest_str, const void* src, size_t num);
void* MemMove(void* dest_str, const void* src_str, size_t num);

/* auxillary function, hidden from end-user */
static void* ReverseMemCpy (void* dest_str, const void* src, size_t num);

/* internal testing functions */
static void TestMemSet();
static void TestMemCpy();
static void TestMemMove();

 int main()
 {
       TestMemSet();
       TestMemCpy();
       TestMemMove();
       return 0;
 }
 
 /*----------------------------------- function's implementations  -----------------------------------------------*/
 
/* 
  MemSet(target-ptr, value, bytes-to-fill)
  - purpose: fills amount of bytes-to-fill with value in the memory target-ptr points at.
  
  - UB: 1- the target-ptr is invalid (such as NULL pointer, pointer to freed memory)
        2- the memory block is too small (bytes-to-fill > allocated memory of target-ptr) 
        
  - return values: it retruns the same pointer you passed in.     
 */
 
void* MemSet(void* str, int value, size_t num)
{
    unsigned char* str_iterator = (unsigned char*)str;          /* a byte size iterator on str, to not miss the begining of the string */
    unsigned char val = (unsigned char)value;                   /* memset works with bytes, and uses lowest 8 bits (byte) of the value, to match this, 
    							    we must reduce the value to 1 byte so we perform casting */ 
    
    size_t fill_word = 0;					/* a constructed word setted with val in all it's 8 bytes (word size)*/
    size_t i = 0;
    size_t *aligned_p = NULL;
    
    /* handeling un-aligned prefix by setting the memory byte by byte*/
    /* a casting of the address (from char* to unsigned long) to compute modulu and check alignemnt */
    /* chose unsigned long because it is big enough to hold pointer's numeric value */
    while (num > 0 && ((unsigned long)str_iterator % WORD_SIZE_BYTES != 0)) 
    {
        *str_iterator = val;
        ++str_iterator;
        num--;
    }
    
    /* construct a word that contains a setted value in every byte */
    for ( i = 0; i < WORD_SIZE_BYTES ; i++)
    {
        fill_word |= ((size_t)val << (i * CHAR_BIT));
    }

    /* converting the pointer from byte pointer to word pointer - i think that's cool!!! */
    aligned_p = (size_t*)str_iterator; 
    /* from now on treat memory as 8-byte (CHAR_BIT size) blocks "chunks" */
    while (num >= WORD_SIZE_BYTES) 
    {
        *aligned_p = fill_word;
        ++aligned_p;
        num -= WORD_SIZE_BYTES;
    }

    /* handling unaligned suffix */
    /* cast the pointer back to byte pointer so we can write 1 byte at a time */
    str_iterator = (unsigned char*)aligned_p;   
    while (num > 0) 
    {
        *str_iterator = val;
        ++str_iterator;
        num--;
    }

    return str;
}


/* 
  MemCpy(dest-ptr, src-ptr, bytes-to-copy)
  - purpose: copies bytes-to-copy bytes from src-ptr into dest-ptr as raw memory. 

  - UB: 1-  dest-ptr or src-ptr is invalid (NULL, freed memory, unallocated memory)
        2-  bytes-to-copy exceeds allocated memory at dest-ptr or src-ptr
        3-  the source and destination memory ranges overlap 
            (use MemMove instead for overlapping regions)

  - return values: returns dest-ptr.
*/

void* MemCpy (void* dest_str, const void* src, size_t num)
{
    
   unsigned char* dest_iterator = (unsigned char*)dest_str;  		/* a byte size iterator on dest */ 
   unsigned char* src_iterator = (unsigned char*)src;   		/* a byte size iterator on src */

    size_t* aligned_p = NULL;					/* word size pointer */
    size_t* src_aligned_p = NULL;                                       /* word size pointer on src to read chunks */
    
    /* handling unaligned prefix */
    while (num > 0 &&  ( ((unsigned long)dest_iterator % WORD_SIZE_BYTES) != 0 || ((unsigned long)src_iterator  % WORD_SIZE_BYTES)  != 0 ))

    {
        *dest_iterator = *src_iterator;
        ++dest_iterator;
        ++src_iterator;
        num--;
    }
    
    /* now we insert to dest word size data */
    aligned_p = (size_t*)dest_iterator; 
    /* and also read from src in word size data */		
    src_aligned_p = (size_t*)src_iterator;
    while (num >= WORD_SIZE_BYTES) 
    {
        *aligned_p = *src_aligned_p;
        ++aligned_p;
        ++src_aligned_p;
        num -= WORD_SIZE_BYTES;
    }

    /* handling unaligned suffix */
    /* go back to insertion data 1 byte at a time */
    dest_iterator = (unsigned char*)aligned_p;   
    /* go back to reading data 1 byte at a time */
    src_iterator = (unsigned char*)src_aligned_p;
    while (num > 0) 
    {
        *dest_iterator = *src_iterator;
        ++dest_iterator;
        ++src_iterator;
        num--;
    }

    return dest_str;
}


/* 
  ReverseMemCpy(dest-ptr, src-ptr, bytes-to-copy)
  purpose: internal helper used by MemMove to safely copy memory when the 
           source and destination regions overlap in a forward-destructive 
           direction. copies bytes in reverse order (from end to start).

  notes: this function is static and hidden from the end user and is not meant 
         to be called directly. it assumes byte-by-byte reverse copying.

  UB: same as MemCpy 
      1  dest-ptr or src-ptr is invalid
      2  bytes-to-copy exceed allocated ranges

  return values: returns dest-ptr
*/

static void* ReverseMemCpy (void* dest_str, const void* src, size_t num)
{ 
   /* set iterators to the last byte of each region so the copy proceeds backward */
   unsigned char* end_dest_iterator = (unsigned char*)((unsigned char*)dest_str + num - 1);   
   unsigned char* end_src_iterator = (unsigned char*)((unsigned char*)src + num - 1) ;   

    /* word size pointers, used for word boundary optimization */
    size_t* aligned_p = NULL; 
    size_t* src_aligned_p = NULL;
    
    /* handling unaligned prefix */
    while (num > 0 && ( ((unsigned long)end_dest_iterator % WORD_SIZE_BYTES != 0) || ((unsigned long)end_src_iterator % WORD_SIZE_BYTES != 0)))
     {
        *end_dest_iterator = *end_src_iterator;
        --end_dest_iterator;
        --end_src_iterator;
        num--;
    }
    
    /* now we can insert in word size */
    aligned_p = (size_t*)end_dest_iterator;
    /* now we can read in word size */ 
    src_aligned_p = (size_t*)end_src_iterator;
    
    while (num >= WORD_SIZE_BYTES) 
    {
        *aligned_p = *src_aligned_p;
        --aligned_p;
        --src_aligned_p;
        num -= WORD_SIZE_BYTES;
    }

    /* handling unaligned suffix */
    /* go back to read and write in bytes */
    end_dest_iterator = (unsigned char*)aligned_p;    
    end_src_iterator = (unsigned char*)src_aligned_p;
    
    while (num > 0) 
    {
        *end_dest_iterator = *end_src_iterator;
        --end_dest_iterator;
        --end_src_iterator;
        num--;
    }

    return dest_str;
}

/* 
  MemMove(dest-ptr, src-ptr, bytes-to-copy)
  -purpose: copies bytes-to-copy bytes from src-ptr to dest-ptr, correctly handling 
           overlapping memory regions. if the regions overlap in a forward-destructive 
           direction, it performs a reverse copy to avoid data corruption.

  -UB: 1-  dest-ptr or src-ptr is invalid (NULL, freed memory, unallocated memory)
      2-  bytes-to-copy exceeds the allocated size of dest-ptr or src-ptr

  -return values: returns dest-ptr .
*/
void* MemMove(void* dest_str, const void* src_str, size_t num)
{
   /* pointers that treat */
   unsigned char* dest = (unsigned char*)dest_str; 		
   unsigned char* src  = (unsigned char*)src_str;

    /* check for forward-destructive overlap */
    if (dest > src && dest < src + num)
    {
        /* destructive overlap: must copy backward */
        ReverseMemCpy(dest_str, src_str, num);
    }
    else
    {
        /* safe forward copy */
        MemCpy(dest_str, src_str, num);
    }

    return dest_str;
}

/*---------------------------------------------- testing functions -----------------------------------------------------*/
static void TestMemSet(void)
{
    char expected[16];
    char result[16];
    int passed = 1;

    memset(expected, 'A', 5);
    expected[5] = '\0';

    MemSet(result, 'A', 5);
    result[5] = '\0';

    if (memcmp(expected, result, 6) != 0)
    {
        passed = 0;
        printf("TestMemSet FAIL\n");
        printf("expected: \"%s\"\n", expected);
        printf("got     : \"%s\"\n", result);
    }

    if (passed)
    {
        printf("TestMemSet PASS\n");
    }
}

static void TestMemCpy(void)
{
    const char src[] = "hello world";
    char expected[32];
    char result[32];
    size_t len = strlen(src) + 1;
    int passed = 1;

    memset(expected, 0, sizeof(expected));
    memset(result, 0, sizeof(result));

    memcpy(expected, src, len);
    MemCpy(result, src, len);

    if (memcmp(expected, result, len) != 0)
    {
        passed = 0;
        printf("TestMemCpy FAIL\n");
        printf("expected: \"%s\"\n", expected);
        printf("got     : \"%s\"\n", result);
    }

    if (passed)
    {
        printf("TestMemCpy PASS\n");
    }
}

static void TestMemMove(void)
{
    char expected[32];
    char result[32];
    int passed = 1;
    size_t len;

    /* non overlapping case */
    strcpy(expected, "abcdefghij");
    strcpy(result,   "abcdefghij");
    len = strlen(expected) + 1;

    memmove(expected, expected + 2, 5);
    MemMove(result, result + 2, 5);

    if (memcmp(expected, result, len) != 0)
    {
        passed = 0;
        printf("TestMemMove non overlap FAIL\n");
        printf("expected: \"%s\"\n", expected);
        printf("got     : \"%s\"\n", result);
    }

    /* overlapping forward destructive case */
    strcpy(expected, "abcdefghij");
    strcpy(result,   "abcdefghij");
    len = strlen(expected) + 1;

    memmove(expected + 2, expected, 5);
    MemMove(result + 2, result, 5);

    if (memcmp(expected, result, len) != 0)
    {
        passed = 0;
        printf("TestMemMove overlap FAIL\n");
        printf("expected: \"%s\"\n", expected);
        printf("got     : \"%s\"\n", result);
    }

    if (passed)
    {
        printf("TestMemMove PASS\n");
    }
}

