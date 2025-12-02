#include <string.h>           /* testing functions such as memset(), */
#include <stdio.h>

 
#define WORD_SIZE_BYTES                           8

/*-- function declarations --*/
/* memory functions  */
void* MemSet(void* str, int value, size_t num);
void* MemCpy (void* dest_str, const void* src, size_t num);
static void* ReverseMemCpy (void* dest_str, const void* src, size_t num);
void* MemMove(void* dest_str, const void* src_str, size_t num);

/* testing functions */
void TestMemSet();
void TestMemCpy();
void TestMemMove();

 int main()
 {
       TestMemSet();
       TestMemCpy();
       TestMemMove();
       return 0;
 
 }
/* MemSet (like memset lib function) it operates at the byte level.
   it fills a specified block of memory with a constant byte value */
void* MemSet(void* str, int value, size_t num)
{
    unsigned char* str_iterator = (unsigned char*)str;          /* "spreads" val to represent a value in bites, it's size is 1 byte */
    unsigned char val = (unsigned char)value;                   /* translate value to a bit representation that fits within a 1 byte size */ 
    
    size_t fill_word = 0;
    size_t i = 0;
    size_t *aligned_p = NULL;
    
    
    /* handling unaligned prefix */
        /*
            while str iterator is pointing to an address that is not conforming to word alignment size
            which is sizeof(size_t), then perform setting bit-by-bit.
        */
    while (num > 0 && ((unsigned long)str_iterator % sizeof(size_t) != 0)) {
        *str_iterator = val;
        ++str_iterator;
        num--;
    }
    
    /* create a WORD size (8 bytes) filled with val duplicated on size_t size block */
    for ( i = 0; i < sizeof(size_t); i++)
    {
        fill_word |= ((size_t)val << (i * WORD_SIZE_BYTES));
    }

    aligned_p = (size_t*)str_iterator; /* in order to iterate on str in WORD size */ /* recheck this ! */
    while (num >= sizeof(size_t)) 
    {
        *aligned_p = fill_word;
        ++aligned_p;
        num -= sizeof(size_t);
    }

    /* handling unaligned suffix */
    str_iterator = (unsigned char *)aligned_p;    /* return to iteration bit-by-bit */
    while (num > 0) 
    {
        *str_iterator = val;
        ++str_iterator;
        num--;
    }

    return str;
}


/*
  MemCPy function copies num bytes from memory area src to memory area dst.
  the memory areas must not overlap(UB).
  return value: it returns a pointer to dest.
  optimized to support word boundary.
*/

void* MemCpy (void* dest_str, const void* src, size_t num)
{
    
   unsigned char* dest_iterator = (unsigned char*)dest_str;   
   unsigned char* src_iterator = (unsigned char*)src;   

    size_t* aligned_p = NULL;
    size_t* src_aligned_p = NULL;
    
    /* handling unaligned prefix */
        /*
            while str iterator is pointing to an address that is not conforming to word alignment size
            which is sizeof(size_t), then perform setting bit-by-bit.
        */
    while (num > 0 && ((unsigned long)dest_iterator % sizeof(size_t) != 0)) {
        *dest_iterator = *src_iterator;
        ++dest_iterator;
        ++src_iterator;
        num--;
    }
    
    aligned_p = (size_t*)dest_iterator; /* in order to iterate on str in WORD size */
    src_aligned_p = (size_t*)src_iterator;
    while (num >= sizeof(size_t)) 
    {
        *aligned_p = *(size_t*)src_aligned_p;
        ++aligned_p;
        ++src_aligned_p;
        num -= sizeof(size_t);
    }

    /* handling unaligned suffix */
    dest_iterator = (unsigned char*)aligned_p;    /* return to iteration bit-by-bit */
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

static void* ReverseMemCpy (void* dest_str, const void* src, size_t num)
{
   unsigned char* end_dest_iterator = (unsigned char*)((unsigned char*)dest_str + num - 1);   
   unsigned char* end_src_iterator = (unsigned char*)((unsigned char*)src + num - 1) ;   

    size_t* aligned_p = NULL;
    size_t* src_aligned_p = NULL;
    
    /* handling unaligned prefix */
        /*
            while str iterator is pointing to an address that is not conforming to word alignment size
            which is sizeof(size_t), then perform setting bit-by-bit.
        */
    while (num > 0 && ((unsigned long)end_dest_iterator % sizeof(size_t) != 0)) {
        *end_dest_iterator = *end_src_iterator;
        --end_dest_iterator;
        --end_src_iterator;
        num--;
    }
    
    aligned_p = (size_t*)end_dest_iterator; /* in order to iterate on str in WORD size */
    src_aligned_p = (size_t*)end_src_iterator;
    while (num >= sizeof(size_t)) 
    {
        *aligned_p = *(size_t*)src_aligned_p;
        --aligned_p;
        --src_aligned_p;
        num -= sizeof(size_t);
    }

    /* handling unaligned suffix */
    end_dest_iterator = (unsigned char*)aligned_p;    /* return to iteration bit-by-bit */
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
  this functions copies num bytes from memory area src to memory area dest.
  the memory areas may overlap.
*/
void* MemMove(void* dest_str, const void* src_str, size_t num)
{
  int there_is_a_prefix_overlap_flg = 0;
  if((unsigned char*)src_str + num > (unsigned char*)dest_str)
  {
      there_is_a_prefix_overlap_flg = 1; 
  }
  
  if(0 == there_is_a_prefix_overlap_flg)
   {
       MemCpy(dest_str, src_str, num);
       return dest_str;
   }
   
   ReverseMemCpy(dest_str, src_str, num );
   return dest_str;

}

static void TestMemSet()
{
      char buffer[30];
      size_t i = 0;
      memset(buffer, 3, 30);
      
      for(i = 0 ; i < 30 ; i++)
      {
        printf("%lu = %d\n",i, buffer[i]);
      }
       MemSet(buffer, 4, 30);
         for(i = 0 ; i < 30 ; i++)
      {
        printf("%lu = %d\n",i, buffer[i]);
      }
  return;
}

static void TestMemCpy()
{
    char dest[100];
    char* src = "hello world";
    MemCpy(dest, src, 9);
    
    printf("\n%s\n", dest);
    return;


}

static void TestMemMove()
{
    char* str = "hello world!";
    char dest_and_src[15];
    char* dest = &dest_and_src[2];
    
    strcpy(dest_and_src, str);
    
    MemMove(dest, dest_and_src, 13);
    
    printf("the mems is : %s\n", dest);


}

