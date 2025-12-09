/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : shir
worksheet : 11 (ds - bit_array)
version   : 1
date      : 9 Dec 2025
stage     : pre-review
----------------------------------------------------------------------------*/
#include <limits.h>			/* CHAR_BIT */
#include <string.h>			/* strlen() */
#include "../include/bit_array.h"

#define BIT_ARR_SIZE				  (sizeof(bit_array_ty)*CHAR_BIT)
#define UNUSED(x)				        (void)(x)

/*--------------------------------------- MASKS ---------------------------------------------------------------*/
#define LSB_MASK(x)                	 	  ((x) & 0x1)                     /* keeps only LSB */
#define ALTERNATE_ON_OFF_MASK(x)    	  ((x) & 0xAAAAAAAAAAAAAAAA)      /* masking with 1010 1010 10.. */
#define ALTERNATE_OFF_ON_MASK(x)     	  ((x) & 0x5555555555555555)      /* masking with 0101 0101 0.. */
#define ALTERNATE_2ON_2OFF_MASK(x)   	  ((x) & 0xCCCCCCCCCCCCCCCC)      /* masking with 1100 1100.. */
#define ALTERNATE_2OFF_2ON_MASK(x)   	  ((x) & 0x3333333333333333)      /* masking with 0011 0011.. */
#define ALTERNATE_4ON_4OFF_MASK(x)    	  ((x) & 0xF0F0F0F0F0F0F0F0)      /* masking with 1111 0000 1111.. */
#define ALTERNATE_4OFF_4ON_MASK(x)          ((x) & 0x0F0F0F0F0F0F0F0F)      /* masking with 0000 1111 0000.. */
#define ALTERNATE_8ON_8OFF_MASK(x)    	  ((x) & 0xFF00FF00FF00FF00)      /* masking with 1111 1111 0000 0000.. */
#define ALTERNATE_8OFF_8ON_MASK(x)    	  ((x) & 0x00FF00FF00FF00FF)      /* masking with 0000 0000 1111 1111.. */
#define ALTERNATE_16ON_16OFF_MASK(x)  	  ((x) & 0xFFFF0000FFFF0000)      /* masking with 1111 1111 1111 1111 0000 0000 0000 000..*/
#define ALTERNATE_16OFF_16ON_MASK(x) 	  ((x) & 0x0000FFFF0000FFFF)      /* masking with 0000 0000 0000 0000 1111 1111 1111 111.. */
#define ALTERNATE_32ON_32OFF_MASK(x)   	  ((x) & 0xFFFFFFFF00000000)      /*masking with 1(32 times) 0(32 times) */
#define ALTERNATE_32OFF_32ON_MASK(x) 	  ((x) & 0xFFFFFFFF)	          /* masking with 0(32 times) 1(32 times) */

/* macros for bit operations */
#define SHIFT_RIGHT(x,y)           	       ((x) >> (y)) /* shifts x y bits to the right */
#define SHIFT_LEFT(x,y)                    ((x) << (y)) /* shifts x y bits to the left */

/*question 1*/
bit_array_ty BitArraySetAll(bit_array_ty bit_array)
{
	UNUSED(bit_array);
	return (~(size_t)0);

}
/*question 2*/
bit_array_ty BitArrayResetAll(bit_array_ty bit_array)
{
	UNUSED(bit_array);
	return ((size_t)0);	

}
/*question 3*/
bit_array_ty BitArraySetOn(bit_array_ty bit_array, unsigned int index)
{
	return bit_array |= SHIFT_LEFT((size_t)1, index);
}

/*question 4*/
bit_array_ty BitArraySetOff(bit_array_ty bit_array, unsigned int index)
{
       return bit_array &= SHIFT_LEFT(~(size_t)1, index);
}

/* quesition 5*/
bit_array_ty BitArraySetBit(bit_array_ty bit_array, unsigned int index, unsigned int value)
{
	if(1 == value)
	{
		return BitArraySetOn(bit_array, index);
	}
	
	else return BitArraySetOff(bit_array, index);	
}

/* question  6*/
unsigned int BitArrayGetBitVal(bit_array_ty bit_array, unsigned int index)
{
	return (bit_array & SHIFT_LEFT((size_t)1, index)) ? 1 : 0;
}

/* question 7 */
bit_array_ty BitArrayFlipBit(bit_array_ty bit_array, unsigned int index)
{
	return (bit_array ^ SHIFT_LEFT((size_t)1, index));
}

/* question 8 */
bit_array_ty BitArrayMirror(bit_array_ty bit_array)
{
    bit_array =  SHIFT_LEFT (ALTERNATE_OFF_ON_MASK(bit_array), 1)      | SHIFT_RIGHT(ALTERNATE_ON_OFF_MASK(bit_array), 1);
    bit_array =  SHIFT_LEFT (ALTERNATE_2OFF_2ON_MASK(bit_array), 2)    | SHIFT_RIGHT(ALTERNATE_2ON_2OFF_MASK(bit_array), 2);
    bit_array =  SHIFT_LEFT (ALTERNATE_4OFF_4ON_MASK(bit_array), 4)    | SHIFT_RIGHT(ALTERNATE_4ON_4OFF_MASK(bit_array), 4);
    bit_array =  SHIFT_LEFT (ALTERNATE_8OFF_8ON_MASK(bit_array), 8)    | SHIFT_RIGHT(ALTERNATE_8ON_8OFF_MASK(bit_array), 8);
    bit_array =  SHIFT_LEFT (ALTERNATE_16OFF_16ON_MASK(bit_array), 16) | SHIFT_RIGHT(ALTERNATE_16ON_16OFF_MASK(bit_array), 16);
    bit_array =  SHIFT_LEFT (ALTERNATE_32OFF_32ON_MASK(bit_array), 32) | SHIFT_RIGHT(ALTERNATE_32ON_32OFF_MASK(bit_array), 32);
    
    return bit_array;
}

/* question 9 */
bit_array_ty BitArrayRotateRight(bit_array_ty bit_array, size_t num_of_rotations)
{
	num_of_rotations %= BIT_ARR_SIZE;
	bit_array = ((SHIFT_RIGHT(bit_array, num_of_rotations)) | (SHIFT_LEFT(bit_array, BIT_ARR_SIZE - num_of_rotations)));

	return bit_array;

}

/* question 10 */
bit_array_ty BitArrayRotateLeft(bit_array_ty bit_array, size_t num_of_rotations)
{
	
      num_of_rotations %= BIT_ARR_SIZE;
	bit_array = (SHIFT_RIGHT(bit_array, BIT_ARR_SIZE - num_of_rotations)) | (SHIFT_LEFT(bit_array,num_of_rotations));

	return bit_array;
}

/* question 11 */
size_t BitArrayCountOn(bit_array_ty bit_array)
{
	size_t set_bit_counter = 0;

	while(bit_array)
	{
		++set_bit_counter;
		/* turn-off an on bit */
		bit_array = bit_array & (bit_array - 1);	
	}
  	
  	return set_bit_counter;
}

/* question 12 */
size_t BitArrayCountOff(bit_array_ty bit_array)
{
	return BIT_ARR_SIZE - BitArrayCountOn(bit_array);	
}

/* question 13 */
/* auxillary function hidden from end-user */
/*
	ReverseString(ptr-to-str)
	
	-purpose: recieves a pointer to string and flipps it backwards.
	
	-UB: invalid ptr-to-str.
	     the passed string is not null-terminated.
	
	-return value: the reversed string (it changes the argument).
*/
static char* ReverseString(char* str)
{
	size_t i = 0;
	size_t len = strlen(str);
	char tmp = ' ';
	
	for (i = 0; i < len / 2; i++)
	{
		tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
	}
	
	return str;
}

char* BitArrayToString(bit_array_ty bit_array, char* dest)
{
	/* holds current bit in given argument we're looking at */
	size_t curr_bit = 0;
	/* holds the char representation of current bit we are looking at */		
	char curr_bit_char = 0;
	/* a string iterator */
	char* dest_itr = dest;
	
	/* traverse on number from right to left and insert bits as chars from left to right (a reverse step is needed) */
	while(bit_array > 0)
	{
		/* get LSB */
		curr_bit = BitArrayGetBitVal(bit_array, 0); 
		/* identify relevant char symbol for the bit */   	
		curr_bit_char = (curr_bit) ? '1' : '0';
		/* insert relevant char (1/0) in the string */
		*dest_itr = curr_bit_char;
		++dest_itr;
		/* move to next bit */
		bit_array = SHIFT_RIGHT(bit_array, 1);
	}
	*dest_itr = '\0';
	 ReverseString(dest);

	return dest;
}

