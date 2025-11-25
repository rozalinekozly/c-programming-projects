/**********************
* submitter : rozaline kozly
* reviewer: 
* date : 24 - nov - 25
* version: 1 
* worksheet 6 (bitwise)
***********************/
#include <stdio.h> /* printf */
#include <string.h> /* memcpy */

/* boolean digits status */
#define ON 1
#define OFF 0
/* return values */
#define TRUE 1
#define FALSE 0
#define POWER_OF_2 1
#define NOT_POWER_OF_2 0
/* bit-operations */
#define XOR ^
/* tests framework */
#define NUM_OF_TESTS    15
#define PASSED          1
#define FAILED          0

/* macros of standard bit-masking
   operation (assuming the input
   = unsigned int type is 32-bit)*/
#define LSB_MASK(x)                   ((x) & 0x1)             /* keeps only LSB */
#define ALTERNATE_ON_OFF_MASK(x)      ((x) & 0xAAAAAAAA)      /* masking with 1010101010.. */
#define ALTERNATE_OFF_ON_MASK(x)      ((x) & 0x55555555)      /* masking with 010101010.. */
#define ALTERNATE_2ON_2OFF_MASK(x)    ((x) & 0xCCCCCCCC)      /* masking with 11001100.. */
#define ALTERNATE_2OFF_2ON_MASK(x)    ((x) & 0x33333333)      /* masking with 00110011.. */
#define ALTERNATE_4ON_4OFF_MASK(x)    ((x) & 0xF0F0F0F0)      /* masking with 111100001111.. */
#define ALTERNATE_4OFF_4ON_MASK(x)    ((x) & 0x0F0F0F0F)      /* masking with 000011110000.. */
#define ALTERNATE_8ON_8OFF_MASK(x)    ((x) & 0xFF00FF00)      /* masking with 1111111100000000.. */
#define ALTERNATE_8OFF_8ON_MASK(x)    ((x) & 0x00FF00FF)      /* masking with 0000000011111111.. */
#define ALTERNATE_16ON_16OFF_MASK(x)  ((x) & 0xFFFF0000)      /* masking with 1111111111111111000000000000000..*/
#define ALTERNATE_16OFF_16ON_MASK(x)  ((x) & 0x0000FFFF)      /* masking with 0000000000000000111111111111111.. */

/* Non-standard bit-masking macros */
#define TURN_OFF_4_LSB(x)     ((x) & 0xFFFFFFF0)   /* clear bits 0–3 */
#define TURN_OFF_3RD_INDEX(x) ((x) & 0xFFFFFFF7)   /* clear bit 3 */
#define TURN_OFF_5TH_INDEX(x) ((x) & 0xFFFFFFDF)   /* clear bit 5 */

/* macros for bit-operations */
#define SHIFT_RIGHT(x,y)               ((x) >> (y)) /* shifts x y bits to the right */
#define SHIFT_LEFT(x,y)               ((x) << (y)) /* shifts x y bits to the left */


/**** question 1 ****/
unsigned int pow2(unsigned int x, unsigned int y);
static size_t TestPow2();

/**** question 2 *****/
size_t IsPow2(unsigned int num);
size_t IsPow2WithoutLoop(unsigned int num);
static size_t TestIsPow2();
static size_t TestIsPow2WithoutLoop();

/**** question 3 ****/
unsigned long AddOneBinary(unsigned long num);
static size_t TestAddOneBinary();

/**** question 4 ****/
static size_t AuxCountSetBits(unsigned int num);
void PrintBinWithThreeSetBits(unsigned int arr[], size_t size);
static size_t TestPrintBinWithThreeSetBits();

/**** question 5 ****/
unsigned int ByteMirror(unsigned int num);
unsigned int ByteMirrorWithoutLoop(unsigned int num);
static size_t TestByteMirror();
static size_t TestByteMirrorWithoutLoop();

/**** question 6 ****/
size_t CheckBothBitsOn(unsigned char num);
size_t CheckAtLeastOneBitOn(unsigned char num);
void SwapBetweenBites(unsigned char* num);
static size_t TestCheckBothBitsOn();
static size_t TestCheckAtLeastOneBitOn();
static size_t TestSwapBetweenBites();

/**** question 7 ****/
unsigned int FindClosestDivBySixteen(unsigned int num);
static size_t TestFindClosestDivBySixteen();

/**** question 8 ****/
void SwapWithoutThirdVariable(unsigned int* num1, unsigned int* num2);
static size_t TestSwapWithoutThirdVariable();

/**** question 9 ****/
size_t CountSetBits(unsigned int num);
size_t CountSetBitsWithoutLoop(unsigned int num);
static size_t TestCountSetBits();
static size_t TestCountSetBitsWithoutLoop();

/**** question 10 ****/
void PrintFloatBits(float num);
static size_t TestPrintFloatBits();

int main()
{
    size_t passed_tests = 0;

    passed_tests += TestPow2();
    passed_tests += TestIsPow2();
    passed_tests += TestIsPow2WithoutLoop();

    passed_tests += TestAddOneBinary();

    passed_tests += TestPrintBinWithThreeSetBits();

    passed_tests += TestByteMirror();
    passed_tests += TestByteMirrorWithoutLoop();

    passed_tests += TestCheckBothBitsOn();
    passed_tests += TestCheckAtLeastOneBitOn();
    passed_tests += TestSwapBetweenBites();

    passed_tests += TestFindClosestDivBySixteen();

    passed_tests += TestSwapWithoutThirdVariable();

    passed_tests += TestCountSetBits();
    passed_tests += TestCountSetBitsWithoutLoop();

    passed_tests += TestPrintFloatBits();

    printf("Total tests passed: %lu out of %d\n", passed_tests, NUM_OF_TESTS);

    return 0;
}


/*question 1*/
/***************************************
* Function:    pow2
* Purpose:     Computes x * 2^y using bit-shift.
* Input:       x – base value (unsigned int)
*              y – power of two (unsigned int)
* Returns:     x shifted left by y bits
* Complexity:  O(1)
****************************************/
unsigned int pow2 (unsigned int x, unsigned int y)
{
  return SHIFT_LEFT(x, y);
}

static size_t TestPow2()
{
    unsigned int x_vals[5] = {1, 2, 3, 4, 5};
    unsigned int y_vals[5] = {0, 1, 2, 3, 4};
    long expected[5]       = {1, 4, 12, 32, 80};

    size_t i = 0;

    for (i = 0; i < 5; ++i)
    {
        long result = pow2(x_vals[i], y_vals[i]);

        if (result != expected[i])
        {
            printf("TestPow2 FAILED at index %lu: expected = %ld, got = %ld\n",
                    i, expected[i], result);

            return FAILED;
        }
    }

    return PASSED;
}


/*question 2 */
/***********************************************
* Function:    IsPow2
* Purpose:     Checks if a number is a power of 2.
* Logic:       Counts how many bits set to 1.
*              A power-of-two has exactly one '1' bit.
* Input:       num type unsigned int
* Returns:     POWER_OF_2 (1) = if exactly one bit is on
*              NOT_POWER_OF_2 (0) = otherwise
* Complexity:  O(number of bits)
************************************************/
size_t IsPow2(unsigned int num)
{
    size_t on_bits_counter = 0;

    while (num > 0)
    {
        if (LSB_MASK(num))
        {
            ++on_bits_counter;
        }

        num = SHIFT_RIGHT(num, 1);
    }

    return (on_bits_counter == 1 ? POWER_OF_2 : NOT_POWER_OF_2);
}

static size_t TestIsPow2()
{
    unsigned int arr[]     = {1, 2, 3, 4, 5, 8, 16, 18};
    size_t expected[]      = {TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, TRUE, FALSE};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        size_t result = IsPow2(arr[i]);

        if (result != expected[i])
        {
            printf("TestIsPow2 FAILED at index %lu: num=%u expected=%lu got=%lu\n",
                   i, arr[i], expected[i], result);

            return FAILED;
        }
    }

    return PASSED;
}

/************************************************
  Function:    IsPow2WithoutLoop
  Purpose:     Checks if a number is a power of 2
               without using a loop
  Logic:       Uses the identity:
                   n & (n - 1) == 0 if and only if number has a
                   single bit set
  Input:       num  unsigned int
  Returns:     POWER_OF_2 (1)  
               NOT_POWER_OF_2 (0)
  Complexity:  O(1)
*************************************************/
size_t IsPow2WithoutLoop(unsigned int num)
{
    if (num == 0)
    {
        return NOT_POWER_OF_2;
    }

    return ((num & (num - 1)) == 0 ? POWER_OF_2 : NOT_POWER_OF_2);
}

static size_t TestIsPow2WithoutLoop()
{
    unsigned int arr[]    = {0, 1, 2, 3, 4, 5, 8, 16, 18};
    size_t expected[]     = {FALSE, TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, TRUE, FALSE};

    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        size_t result = IsPow2WithoutLoop(arr[i]);

        if (result != expected[i])
        {
            printf("TestIsPow2WithoutLoop FAILED at index %lu: num=%u expected=%lu got=%lu\n",
                   i, arr[i], expected[i], result);

            return FAILED;
        }
    }

    return PASSED;
}

/*question 3 */
/************************************************
  Function:    AddOneBinary
  Purpose:     Adds one to an unsigned long using
               pure bit operations without using +
  Logic:       The function simulates binary addition:
               as long as the current bit is 1 it is
               turned off and the carry moves to the
               next bit. When it finds a zero bit it
               turns it on and stops.
  Input:       x  unsigned long
  Returns:     x + 1  computed by bit manipulation
  Complexity:  O(k) where k is number of consecutive
               trailing ones in the input number
*************************************************/
unsigned long AddOneBinary(unsigned long x)
{
    size_t i = 0;

    while (1)
    {
        if (x & SHIFT_LEFT(1UL, i))
        {
            x &= ~SHIFT_LEFT(1UL, i);
            ++i;
        }
        else
        {
            x |= SHIFT_LEFT(1UL, i);
            break;
        }
    }

    return x;
}


static size_t TestAddOneBinary()
{
    unsigned long arr[]      = {0, 1, 2, 3, 7, 8, 15, 16};
    unsigned long expected[] = {1, 2, 3, 4, 8, 9, 16, 17};

    size_t i = 0;
    size_t size = sizeof(arr) / sizeof(arr[0]);

    for (i = 0; i < size; ++i)
    {
        unsigned long result = AddOneBinary(arr[i]);

        if (result != expected[i])
        {
            printf("TestAddOneBinary FAILED at index %lu: input=%lu expected=%lu got=%lu\n",
                   i, arr[i], expected[i], result);

            return FAILED;
        }
    }

    return PASSED;
}

/*question 4 */
/************************************************
  Function:    AuxCountSetBits
  Purpose:     Counts how many bits are set to 1
               in an unsigned int value
  Logic:       The function checks the least
               significant bit using LSB_MASK.
               After each check the number is
               shifted right by one bit until
               all bits have been examined.
  Input:       num  unsigned int
  Returns:     Number of bits set to 1 in num
  Complexity:  O(log n) where n is the numeric
               value of the input
*************************************************/
static size_t AuxCountSetBits(unsigned int num)
{
    size_t count = 0;

    while (num > 0)
    {
        if (LSB_MASK(num))
        {
            ++count;
        }
        num = SHIFT_RIGHT(num, 1);
    }

    return count;
}

/************************************************
  Function:    PrintBinWithThreeSetBits
  Purpose:     Prints all numbers in an array that
               contain exactly three bits set to 1
  Logic:       For each element in the array the
               function calls AuxCountSetBits.
               If the count equals three the number
               is printed to the standard output.
  Input:       arr   array of unsigned int values
               size  number of elements in arr
  Returns:     void  prints matching values only
  Complexity:  O(size * log n) due to calling the
               helper on each array element
*************************************************/
void PrintBinWithThreeSetBits(unsigned int arr[], size_t size)
{
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        if (AuxCountSetBits(arr[i]) == 3)
        {
            printf("%u\n", arr[i]);
        }
    }
}

static size_t TestPrintBinWithThreeSetBits()
{
    unsigned int arr[]      = {7, 8, 11, 28, 31, 19};
    unsigned int expected[] = {7, 11, 28, 19};
    unsigned int output[10];

    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t exp_size = sizeof(expected) / sizeof(expected[0]);

    size_t i = 0;
    size_t out_i = 0;

    for (i = 0; i < size; ++i)
    {
        if (AuxCountSetBits(arr[i]) == 3)
        {
            output[out_i++] = arr[i];
        }
    }

    if (out_i != exp_size)
    {
        return FAILED;
    }

    for (i = 0; i < exp_size; ++i)
    {
        if (output[i] != expected[i])
        {
            printf("TestPrintBinWithThreeSetBits FAILED at %lu\n", i);
            return FAILED;
        }
    }

    return PASSED;
}

/* question 5 */
/************************************************
  Function:    ByteMirror
  Purpose:     Reverses the bit order of a 32-bit
               unsigned integer (bit 0 <-> bit 31)
  Logic:       The function scans all 32 bits of
               the input. For each bit that is set,
               the corresponding mirrored position
               in the result is set as well
               (bit i maps to bit 31 - i).
  Input:       num  unsigned int
  Returns:     A new unsigned int whose bits are
               the complete mirror of the input
  Complexity:  O(32) = O(1) because the loop
               always iterates 32 times
*************************************************/
unsigned int ByteMirror(unsigned int num)
{
    unsigned int result = 0;
    size_t i = 0;

    for (i = 0; i < 32; ++i)
    {
        if (num & (1U << i))
        {
            result |= (1U << (31 - i));
        }
    }

    return result;
}

static size_t TestByteMirror()
{
    unsigned int arr[]      = {0x00000001, 0x80000000, 0xAAAAAAAA, 0x12345678};
    unsigned int expected[] = {0x80000000, 0x00000001, 0x55555555, 0x1E6A2C48};

    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        unsigned int result = ByteMirror(arr[i]);

        if (result != expected[i])
        {
            printf("TestByteMirror FAILED at index %lu: input=0x%X expected=0x%X got=0x%X\n",
                   i, arr[i], expected[i], result);
            return FAILED;
        }
    }

    return PASSED;
}


/*question 5 - b an implementation without loop */
/************************************************
  Function:    ByteMirrorWithoutLoop
  Purpose:     Reverses all 32 bits of an unsigned
               integer *without using any loop*.

  Logic:       The function performs a fixed 5-stage
               bit-reversal technique. In every stage,
               alternating bit blocks are selected by
               the predefined masking macros 
               (ALTERNATE_OFF_ON_MASK, 
                ALTERNATE_ON_OFF_MASK, etc.).

               Each masked block is then shifted using
               SHIFT_LEFT and SHIFT_RIGHT so that the 
               bits move toward their mirrored positions.
               After shifting, the complementary blocks
               are OR-ed together to rebuild the number.

               This is a classical bit-hack approach to
               full 32-bit reversal.

  Input:       num  unsigned int (32-bit)
  Returns:     A fully bit-mirrored form of num
  Complexity:  O(1)   (always 5 fixed operations)
*************************************************/

unsigned int ByteMirrorWithoutLoop(unsigned int num)
{
    num =  SHIFT_LEFT (ALTERNATE_OFF_ON_MASK(num), 1)
         | SHIFT_RIGHT(ALTERNATE_ON_OFF_MASK(num), 1);

    num =  SHIFT_LEFT (ALTERNATE_2OFF_2ON_MASK(num), 2)
         | SHIFT_RIGHT(ALTERNATE_2ON_2OFF_MASK(num), 2);

    num =  SHIFT_LEFT (ALTERNATE_4OFF_4ON_MASK(num), 4)
         | SHIFT_RIGHT(ALTERNATE_4ON_4OFF_MASK(num), 4);

    num =  SHIFT_LEFT (ALTERNATE_8OFF_8ON_MASK(num), 8)
         | SHIFT_RIGHT(ALTERNATE_8ON_8OFF_MASK(num), 8);

    num =  SHIFT_LEFT (ALTERNATE_16OFF_16ON_MASK(num), 16)
         | SHIFT_RIGHT(ALTERNATE_16ON_16OFF_MASK(num), 16);

    return num;
}


static size_t TestByteMirrorWithoutLoop()
{
    unsigned int arr[]      = {0x00000001, 0x80000000, 0xAAAAAAAA, 0x12345678};
    unsigned int expected[] = {0x80000000, 0x00000001, 0x55555555, 0x1E6A2C48};

    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        unsigned int result = ByteMirrorWithoutLoop(arr[i]);

        if (result != expected[i])
        {
            printf("TestByteMirrorWithoutLoop FAILED at index %lu: input=0x%X expected=0x%X got=0x%X\n",
                   i, arr[i], expected[i], result);
            return FAILED;
        }
    }

    return PASSED;
}

/**** question 6 ****/
/************************************************
  Function:    CheckBothBitsOn
  Purpose:     Checks if two specific bits in an
               unsigned char are both turned on
  Logic:       Extracts bit 2 and bit 6 by shifting
               the number right and masking the LSB
               Returns TRUE only if both bits equal 1
  Input:       num  unsigned char
  Returns:     TRUE  if both bits are on
               FALSE otherwise
  Complexity:  O(1)
*************************************************/
size_t CheckBothBitsOn(unsigned char num)
{
  int bit1 = LSB_MASK(SHIFT_RIGHT(num, 2));
  int bit2 = LSB_MASK(SHIFT_RIGHT(num, 6));
  
  if(bit1 == ON && bit2 == ON)
  {
      return TRUE;
  }
      return FALSE;
      
}
/************************************************
  Function:    CheckAtLeastOneBitOn
  Purpose:     Checks if at least one of two
               specific bits in an unsigned char
               is turned on
  Logic:       Extracts bit 2 and bit 6 using shift
               and LSB mask and checks if either is 1
  Input:       num  unsigned char
  Returns:     TRUE  if one or both bits are on
               FALSE if both are zero
  Complexity:  O(1)
*************************************************/

size_t CheckAtLeastOneBitOn(unsigned char num)
{
  int bit1 = LSB_MASK(SHIFT_RIGHT(num, 2));
  int bit2 = LSB_MASK(SHIFT_RIGHT(num, 6));
  
  if ((bit1 == ON) || (bit2 == ON))
  {
    return TRUE;
  }
  return FALSE;
}
/************************************************
  Function:    SwapBetweenBites
  Purpose:     Swaps the values of bit 3 and bit 5
               inside an unsigned char
  Logic:       Extracts the two bits
               Clears bit 3 and bit 5 in the number
               Rewrites the bits in swapped places
  Input:       num  pointer to unsigned char
  Returns:     void  modifies the value in place
  Complexity:  O(1)
*************************************************/

void SwapBetweenBites(unsigned char* num)
{
   int bit1 = LSB_MASK(SHIFT_RIGHT(*num, 3));
  
   int bit2 = LSB_MASK(SHIFT_RIGHT(*num, 5));

   unsigned char num1 = SHIFT_LEFT(bit1, 5);
   unsigned char num2 = SHIFT_LEFT(bit2, 3);
   
   *num = TURN_OFF_3RD_INDEX(*num); 

   *num = TURN_OFF_5TH_INDEX(*num);
   
   *num = (*num | num1 | num2);
}


static size_t TestCheckBothBitsOn()
{
    unsigned char arr[]    = {1,2,3,4,5,6,7,8,9,10};
    size_t expected[]       = {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        if (CheckBothBitsOn(arr[i]) != expected[i])
        {
            printf("TestCheckBothBitsOn FAILED at %lu: num=%u expected=%lu got=%lu\n",
                   i, arr[i], expected[i], CheckBothBitsOn(arr[i]));
            return FAILED;
        }
    }

    return PASSED;
}

static size_t TestCheckAtLeastOneBitOn()
{
    unsigned char arr[]    = {1,2,3,4,5,6,7,8,9,10};
    size_t expected[]       = {FALSE,FALSE,FALSE,TRUE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        if (CheckAtLeastOneBitOn(arr[i]) != expected[i])
        {
            printf("TestCheckAtLeastOneBitOn FAILED at %lu: num=%u expected=%lu got=%lu\n",
                   i, arr[i], expected[i], CheckAtLeastOneBitOn(arr[i]));
            return FAILED;
        }
    }

    return PASSED;
}

static size_t TestSwapBetweenBites()
{
    unsigned char num = 0x37;
    unsigned char expected = 0x1F;

    SwapBetweenBites(&num);

    if (num != expected)
    {
        printf("TestSwapBetweenBites FAILED: expected=0x%X got=0x%X\n",
               expected, num);
        return FAILED;
    }

    return PASSED;
}
/** question 7 ***/
/************************************************
  Function:    FindClosestDivBySixteen
  Purpose:     Rounds a given unsigned int down to
               the closest number divisible by 16
  Logic:       Clears the lowest 4 bits (LSB 0–3)
               because any number divisible by 16
               ends with four zeros in binary
               Achieved by masking with 0xFFFFFFF0
  Input:       num  unsigned int
  Returns:     The closest smaller or equal number
               divisible by 16
  Complexity:  O(1)
*************************************************/

unsigned int FindClosestDivBySixteen(unsigned int num)
{
   return TURN_OFF_4_LSB(num);
}

static size_t TestFindClosestDivBySixteen()
{
    unsigned int arr[]      = {0x16, 0x09, 0x7F}; 
    unsigned int expected[] = {0x10, 0x00, 0x70};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        unsigned int result = FindClosestDivBySixteen(arr[i]);

        if (result != expected[i])
        {
            printf("TestFindClosestDivBySixteen FAILED at %lu: input=0x%X expected=0x%X got=0x%X\n",
                   i, arr[i], expected[i], result);
            return FAILED;
        }
    }

    return PASSED;
}




/* question 8 : swaps content of two given variables without a use of third variable, and using bit-operations */
/************************************************
  Function:    SwapWithoutThirdVariable
  Purpose:     Swaps two unsigned integers without
               using a temporary variable
  Logic:       Uses XOR properties:
               a ^= b
               b ^= a    (b becomes original a)
               a ^= b    (a becomes original b)
               This works because XOR is reversible
               and symmetric
  Input:       num1  pointer to first unsigned int
               num2  pointer to second unsigned int
  Returns:     None (swap occurs in-place)
  Complexity:  O(1)
*************************************************/

void SwapWithoutThirdVariable(unsigned int* num1, unsigned int* num2)
{
  *num1 = *num1 XOR *num2;
  *num2 = *num2 XOR *num1;
  *num1 = *num1 XOR *num2;
}

/* question 8 test */
static size_t TestSwapWithoutThirdVariable()
{
    unsigned int arr1[]      = {0x0001,0x0002, 0x00AB,0x00CD, 0x0000,0x000F};
    unsigned int expected1[] = {0x0002,0x0001, 0x00CD,0x00AB, 0x000F,0x0000};

    unsigned int arr2[]      = {0x00DF,0x4CCECFCD, 0x12345678,0x87654321, 0xFFFFFFFF,0x00000000};
    unsigned int expected2[] = {0x4CCECFCD,0x00DF, 0x87654321,0x12345678, 0x00000000,0xFFFFFFFF};

    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t i = 0;

    for (i = 0; i < size1; i += 2)
    {
        unsigned int a = arr1[i];
        unsigned int b = arr1[i + 1];

        SwapWithoutThirdVariable(&a, &b);

        if (a != expected1[i] || b != expected1[i + 1])
        {
            printf("TestSwapWithoutThirdVariable FAILED at small-set index %lu: got (0x%X,0x%X) expected (0x%X,0x%X)\n",
                   i / 2, a, b, expected1[i], expected1[i + 1]);
            return FAILED;
        }
    }

    for (i = 0; i < size2; i += 2)
    {
        unsigned int a = arr2[i];
        unsigned int b = arr2[i + 1];

        SwapWithoutThirdVariable(&a, &b);

        if (a != expected2[i] || b != expected2[i + 1])
        {
            printf("TestSwapWithoutThirdVariable FAILED at big-set index %lu: got (0x%X,0x%X) expected (0x%X,0x%X)\n",
                   i / 2, a, b, expected2[i], expected2[i + 1]);
            return FAILED;
        }
    }

    return PASSED;
}


/* question 9-a : counting set bits (1) of a given number, an implementation with a loop 
   check the bit value in LSB via bit-masking with 0x1 (= 1 in binary), if it is not equal to zero 
    then raise sit_bits_counter by 1 */
/************************************************
  Function:    CountSetBits
  Purpose:     Counts how many bits with value 1
               exist in the binary representation
               of an unsigned integer
  Logic:       Repeatedly checks the LSB using
               LSB_MASK(num). If it is 1, the
               counter increments. Then the number
               is shifted right by one bit until
               all bits are processed.
  Input:       num  unsigned int
  Returns:     Number of bits set to 1
  Complexity:  O(k) where k is the number of bits
               in an unsigned int (typically 32)
*************************************************/
size_t CountSetBits(unsigned int num)
{
  size_t set_bits_counter = 0;
  while(num > 0) /* maybe do a macro later */
  {
    if (LSB_MASK(num))
    {
      ++set_bits_counter;
    }
    num = SHIFT_RIGHT(num,1); /* shifts num to the right by 1 digit */
  }
  return set_bits_counter;
}

/* question 9-b : counting set bits (1) of a given number, an implementation without a loop */
/************************************************
  Function:    CountSetBitsWithoutLoop
  Purpose:     Counts how many bits are set to 1
               in an unsigned integer without
               using any loop
  Logic:       Uses a known parallel bit counting
               technique. In every step the number
               is split into fixed-size groups and
               partial sums are accumulated:
               first 1-bit groups become 2-bit sums,
               then 2-bit groups become 4-bit sums,
               then 4-bit groups become 8-bit sums,
               then 8-bit groups become 16-bit sums,
               and finally 16-bit groups become one
               total 32-bit sum.
               After the last step the number holds
               the total count of bits that are 1.
  Input:       num  unsigned int
  Returns:     the number of set bits
  Complexity:  O(1)
*************************************************/

size_t CountSetBitsWithoutLoop(unsigned int num)
{
    num =  ALTERNATE_OFF_ON_MASK(num) + SHIFT_RIGHT(ALTERNATE_ON_OFF_MASK(num), 1);
    num = ALTERNATE_2OFF_2ON_MASK(num) + SHIFT_RIGHT(ALTERNATE_2ON_2OFF_MASK(num), 2);
    num = ALTERNATE_4OFF_4ON_MASK(num) + SHIFT_RIGHT(ALTERNATE_4ON_4OFF_MASK(num), 4);
    num = ALTERNATE_8OFF_8ON_MASK(num) + SHIFT_RIGHT(ALTERNATE_8ON_8OFF_MASK(num), 8);
    num = ALTERNATE_16OFF_16ON_MASK(num) + SHIFT_RIGHT(ALTERNATE_16ON_16OFF_MASK(num), 16);
    return (size_t)num;
}


static size_t TestCountSetBits()
{
    unsigned int arr[]      = {0xDF, 0x9F, 0x4CCECFCD};
    size_t       expected[] = {7,    6,    19};

    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        size_t result = CountSetBits(arr[i]);

        if (result != expected[i])
        {
            printf("TestCountSetBits FAILED at index %lu: input=0x%X expected=%lu got=%lu\n",
                   i, arr[i], expected[i], result);
            return FAILED;
        }
    }

    return PASSED;
}

static size_t TestCountSetBitsWithoutLoop()
{
    unsigned int arr[]      = {0xDF, 0x9F, 0x4CCECFCD};
    size_t       expected[] = {7,    6,    19};

    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        size_t result = CountSetBitsWithoutLoop(arr[i]);

        if (result != expected[i])
        {
            printf("TestCountSetBitsWithoutLoop FAILED at index %lu: input=0x%X expected=%lu got=%lu\n",
                   i, arr[i], expected[i], result);
            return FAILED;
        }
    }

    return PASSED;
}


/* question 10*/
/************************************************
  Function:    PrintFloatBits
  Purpose:     Prints the exact IEEE-754 bit
               representation of a float value
  Logic:       A float is copied byte-by-byte
               into an unsigned int using memcpy.
               This avoids strict-aliasing issues.
               The resulting 32-bit integer is then
               scanned from bit 31 down to bit 0.
               Bit 31 is the sign bit.
               Bits 30 to 23 are the exponent.
               Bits 22 to 0 are the fraction.
               Spaces are printed to visually
               separate these fields.
  Input:       num  float value to inspect
  Returns:     void  only prints to stdout
  Complexity:  O(1)  always processes 32 bits
*************************************************/

void PrintFloatBits(float num)
{
    unsigned int bits = 0;
    int i = 0;
    
    memcpy(&bits, &num, sizeof(unsigned int));
   
    for (i = 31; i >= 0; --i)
    {
        unsigned int mask = 1U << i;

        if (bits & mask)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }

        if (i == 31 || i == 23)
        {
            printf(" ");
        }
    }

    printf("\n");
}


static size_t TestPrintFloatBits()
{
    float arr[] = {0.0f, 1.0f, -1.0f, 1.5f, 2.75f, 100.0f, -32.0f};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        printf("input = %f -> ", arr[i]);
        PrintFloatBits(arr[i]);
    }

    return PASSED;
}

