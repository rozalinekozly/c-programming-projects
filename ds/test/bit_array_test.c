/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : shir 
worksheet : 11 (ds - bit_array)
version   : 2
date      : 10 Dec 2025
stage     : pre-mimir
----------------------------------------------------------------------------*/
#include <stdio.h>		/* printf() */
#include <string.h>   		/* memcmp(), strcmp()*/
#include <limits.h>		/* CHAR_BIT */
#include <stdlib.h>		/* malloc(), free() */
#include "../include/bit_array.h"


#define BIT_ARR_SIZE		      	 (sizeof(bit_array_ty) * CHAR_BIT)
#define SIZEOF_ARR(ARR)			       (sizeof(ARR)/sizeof(*ARR))
/* macros for bit operations */
#define SHIFT_RIGHT(x,y)            	 ((x) >> (y)) 	   /* shifts x y bits to the right */
#define SHIFT_LEFT(x,y)             	 ((x) << (y)) 	   /* shifts x y bits to the left */
/* masks*/
#define LSB_MASK(x)                	 	 ((x) & 0x1)         /* keeps only LSB */
/* helpful values */
#define ALL_ON		          		 (0xFFFFFFFFFFFFFFFF) /*1(64 times)*/
#define ALL_OFF					 (0x0)

static void TestBitArraySetAll(void);
static void TestBitArrayResetAll(void);
static void TestBitArraySetOn(void);
static void TestBitArraySetOff(void);
static void TestBitArraySetBit(void);
static void TestBitArrayGetBitVal(void);
static void TestBitArrayFlipBit(void);
static void TestBitArrayMirror(void);
static void TestBitArrayRotateRight(void);
static void TestBitArrayRotateLeft(void);
static void TestBitArrayCountOn(void);
static void TestBitArrayCountOff(void);
static void TestBitArrayToString(void);


int main()
{
	TestBitArraySetAll();
	TestBitArrayResetAll();
	TestBitArraySetOn();
	TestBitArraySetOff();
	TestBitArraySetBit();
	TestBitArrayGetBitVal();
	TestBitArrayFlipBit();
	TestBitArrayMirror();
	TestBitArrayRotateRight();
	TestBitArrayRotateLeft();
	TestBitArrayCountOn();
	TestBitArrayCountOff();
	TestBitArrayToString();
	
	return 0;

}

void TestBitArraySetAll(void)
{
    bit_array_ty tests[] = {12354, 22555588, 988798, 1, 0, ALL_ON};
    size_t i = 0;
    size_t tests_arr_size = SIZEOF_ARR(tests);
    size_t set_all_res = 0;
    
    printf("set-all\t\t\t");
    for(i = 0 ; i < tests_arr_size ; i++)
    {	
		set_all_res = BitArraySetAll(tests[i]);
		if(ALL_ON != set_all_res)
		{
			   printf("FAILED at %lu, expected %lu, got %lu \n",i, ALL_ON, set_all_res);
			   return;
		}	
    }
    printf("PASSED\n");		
}

void TestBitArrayResetAll(void)
{
    bit_array_ty tests[] = {12354, 22555588, 988798, 1, 0, ALL_ON};
    size_t i = 0;
    size_t tests_arr_size = SIZEOF_ARR(tests);
    size_t reset_all_res = 0;
    
    printf("reset-all\t\t");
    for(i = 0 ; i < tests_arr_size ; i++)
    {	
		reset_all_res = BitArrayResetAll(tests[i]);
		if(ALL_OFF != reset_all_res)
		{
			   printf("FAILED at %lu, expected %d, got %lu \n",i, ALL_OFF, reset_all_res);
			   return;
		}	
    }
    printf("PASSED\n");		
}

void TestBitArraySetOn (void)
{
    bit_array_ty tests[] = {1, 2, 3, 4, 0, ALL_ON};
    size_t bits_to_on[] = {1, 2, 2, 1, 0, 21};
    bit_array_ty expected[] = {3, 6, 7, 6, 1, ALL_ON};
    size_t i = 0;
    size_t tests_arr_size = SIZEOF_ARR(tests);
    size_t set_on_res = 0;
    
    printf("set-on\t\t\t");
    for(i = 0 ; i < tests_arr_size ; i++)
    {	
		set_on_res = BitArraySetOn(tests[i], bits_to_on[i]);
		if(set_on_res != expected[i])
		{
			   printf("FAILED at %lu, expected %lu, got %lu \n",i, expected[i], set_on_res);
			   return;
		}	
    }
    printf("PASSED\n");	 
}


void TestBitArraySetOff(void)
{
    bit_array_ty tests[] =    {1, 2, 3, 5, 0};
    size_t bits_to_off[] =    {1, 0, 0, 0, 0};
    bit_array_ty expected[] = {1, 2, 2, 4, 0};
    size_t i = 0;
    size_t tests_arr_size = SIZEOF_ARR(tests);
    size_t set_off_res = 0;
    
    printf("set-off\t\t\t");
    for(i = 0 ; i < tests_arr_size ; i++)
    {	
		set_off_res = BitArraySetOff(tests[i], bits_to_off[i]);
		if(set_off_res != expected[i])
		{
			   printf("FAILED at %lu, expected %lu, got %lu \n",i, expected[i], set_off_res);
			   return;
		}	
    }
    printf("PASSED\n");	 
}

void TestBitArraySetBit(void)
{
    bit_array_ty tests_to_on[] = {1, 2, 3, 4, ALL_ON};
    size_t bits_to_on[] = {1, 2, 2, 1, 21};
    bit_array_ty expected_on[] = {3, 6, 7, 6, ALL_ON};
    size_t i = 0;
    bit_array_ty tests_to_off[] = {1, 2, 3, 5, 0};
    size_t bits_to_off[] = {1, 0, 0, 0, 0};
    bit_array_ty expected_off[] = {1, 2, 2, 4, 0};
    
    size_t tests_arr_size = SIZEOF_ARR(tests_to_on);
    size_t set_bit_res = 0;
    
    printf("set-bit\t\t\t");
    for(i = 0 ; i < tests_arr_size ; i++)
    {	
		set_bit_res = BitArraySetBit(tests_to_on[i], bits_to_on[i], 1);
		if(set_bit_res != expected_on[i])
		{
			   printf("FAILED at %lu, expected %lu, got %lu \n",i, expected_on[i], set_bit_res);
			   return;
		}	
    }
    
    for(i = 0 ; i < tests_arr_size ; i++)
    {	
		set_bit_res = BitArraySetBit(tests_to_off[i], bits_to_off[i], 0);
		if(set_bit_res != expected_off[i])
		{
			   printf("FAILED at %lu, expected %lu, got %lu \n",i, expected_off[i], set_bit_res);
			   return;
		}	
    }    
    printf("PASSED\n");	 
    
}

void TestBitArrayGetBitVal(void)
{
    bit_array_ty tests[] =     {1, 2, 3, 5, 0};
    size_t bit_to_evaluate[] = {1, 1, 0, 2, 0};
    bit_array_ty expected[] =  {0, 1, 1, 1, 0};
    size_t i = 0;
    size_t tests_arr_size = SIZEOF_ARR(tests);
    size_t get_bit_res = 0;
    
    printf("get-bit\t\t\t");
    for(i = 0 ; i < tests_arr_size ; i++)
    {	
		get_bit_res = BitArrayGetBitVal(tests[i], bit_to_evaluate[i]);
		if(get_bit_res != expected[i])
		{
			   printf("FAILED at %lu, expected %lu, got %lu \n",i, expected[i], get_bit_res);
			   return;
		}	
    }
    printf("PASSED\n");	 
}

void TestBitArrayFlipBit(void)
{
    bit_array_ty tests[] =     {1, 2, 3, 5, 0};
    size_t bit_to_flip[] =     {1, 1, 0, 1, 0};
    bit_array_ty expected[] =  {3, 0, 2, 7, 1};
    size_t i = 0;
    size_t tests_arr_size = SIZEOF_ARR(tests);
    bit_array_ty flip_bit_res = 0;
    
    printf("flip-bit\t\t");
    for(i = 0 ; i < tests_arr_size ; i++)
    {	
		flip_bit_res = BitArrayFlipBit(tests[i], bit_to_flip[i]);
		if(flip_bit_res != expected[i])
		{
			   printf("FAILED at %lu, expected %lu, got %lu \n",i, expected[i], flip_bit_res);
			   return;
		}	
    }
    printf("PASSED\n");	 
}


void TestBitArrayMirror(void)
{
	bit_array_ty test = 1;
	bit_array_ty expected = 0x8000000000000000;
	
  	test = BitArrayMirror(test);
  	printf("mirror\t\t\t");
  	if(expected == test)
  	{
	    	printf("PASSED\n");
	    	return;
         }
         printf("FAILED\n"); 
}

void TestBitArrayRotateRight(void)
{
	bit_array_ty test = 1;
	bit_array_ty expected = 0x8000000000000000;
	
  	test = BitArrayRotateRight(test,1);
  	printf("rotate-left\t\t");
  	if(expected == test)
  	{
	    	printf("PASSED\n");
	    	return;
         }
         printf("FAILED\n"); 
}

void TestBitArrayRotateLeft(void)
{
	bit_array_ty test = 1;
	bit_array_ty expected = 2;
	
  	test = BitArrayRotateLeft(test,1);
  	printf("rotate-right\t\t");
  	if(expected == test)
  	{
	    	printf("PASSED\n");
	    	return;
         }
         printf("FAILED\n"); 
}


void TestBitArrayCountOn(void)
{
    bit_array_ty tests[] =     {15, 2, 7, 5, 8};
    bit_array_ty expected[] =  {4, 1, 3, 2, 1};
    size_t i = 0;
    size_t tests_arr_size = SIZEOF_ARR(tests);
    bit_array_ty count_bit_res = 0;
    
    printf("count-on\t\t");
    for(i = 0 ; i < tests_arr_size ; i++)
    {	
		count_bit_res = BitArrayCountOn(tests[i]);
		if(count_bit_res != expected[i])
		{
			   printf("FAILED at %lu, expected %lu, got %lu \n",i, expected[i], count_bit_res);
			   return;
		}	
    }
    printf("PASSED\n");	 
}

void TestBitArrayCountOff(void)
{
    bit_array_ty tests[] =     {15, 2, 7, 5, 8};
    bit_array_ty expected[] =  {BIT_ARR_SIZE - 4, BIT_ARR_SIZE - 1, BIT_ARR_SIZE - 3, BIT_ARR_SIZE - 2, BIT_ARR_SIZE - 1};
    size_t i = 0;
    size_t tests_arr_size = SIZEOF_ARR(tests);
    bit_array_ty count_bit_res = 0;
    
    printf("count-off\t\t");
    for(i = 0 ; i < tests_arr_size ; i++)
    {	
		count_bit_res = BitArrayCountOff(tests[i]);
		if(count_bit_res != expected[i])
		{
			   printf("FAILED at %lu, expected %lu, got %lu \n",i, expected[i], count_bit_res);
			   return;
		}	
    }
    printf("PASSED\n");	       
}

void TestBitArrayToString(void)
{
	char* dest = (char*)malloc((BIT_ARR_SIZE + 1) *sizeof(char));
	/*assert(NULL == dest);*/
	bit_array_ty test = 24;
	char* test_str = "11000";
	BitArrayToString(test, dest);
	
	printf("to-string\t\t");
	if(0 == strcmp(dest, test_str))
	{
	    	printf("PASSED\n");
	    	return;
         }
         printf("FAILED\n"); 
	printf("string is :%s \n", dest);
	free(dest);
	dest = NULL;
}




