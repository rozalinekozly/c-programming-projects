/**********************
* submitter : Rozaline kozly
* reviewer: Nimrod 
* date : 24 - nov - 25
* version: 1 
* worksheet 6 (bitwise)
***********************/
#include <stdio.h> /* printf */
#include <string.h> /* memcpy */

/* boolean digits status */
#define ON             1
#define OFF            0
#define BYTE_SIZE      8
#define POWER_OF_2     1
#define NOT_POWER_OF_2 0
/* bit-operations */
#define XOR ^
/* tests framework */
#define NUM_OF_TESTS   15
#define PASSED          1
#define FAILED          0

/* macros of standard bit-masking
   operation works for all sizes 
   <= 32 bits (unsigned int) */
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
#define TURN_OFF_4_LSB(x)            ((x) & 0xFFFFFFF0)   /* clear bits 0–3 */
#define TURN_OFF_3RD_INDEX(x)        ((x) & 0xFFFFFFF7)   /* clear bit 3 */
#define TURN_OFF_5TH_INDEX(x)        ((x) & 0xFFFFFFDF)   /* clear bit 5 */

/* macros for bit
  operations */
#define SHIFT_RIGHT(x,y)             ((x) >> (y)) /* shifts x y bits to the right */
#define SHIFT_LEFT(x,y)              ((x) << (y)) /* shifts x y bits to the left */

/* repetitive 
   operations */
#define SIZE_OF_ARRAY(x)      ((sizeof(x)) / (sizeof((x)[0])))

/* type for true/false */
typedef enum 
{
   FALSE = 0,
   TRUE = 1
} bool_ty;

/**** question 1 ****/
long Pow2(unsigned int, unsigned int);
static size_t TestPow2();

/**** question 2 *****/
bool_ty IsPow2(unsigned int);
bool_ty IsPow2WithoutLoop(unsigned int);
static size_t TestIsPow2();
static size_t TestIsPow2WithoutLoop();

/**** question 3 ****/
unsigned int AddOneBinary(unsigned int);
static size_t TestAddOneBinary();

/**** question 4 ****/
static bool_ty IsSetBitsReqInNum(unsigned int, size_t); /* aux function */
void PrintBinaryWithThreeSetBits(unsigned int*, size_t);
static size_t TestPrintBinaryWithThreeSetBits();



/**** question 5 ****/
unsigned char ByteMirror(unsigned char);
unsigned char ByteMirrorWithoutLoop(unsigned char);
static size_t TestByteMirror();
static size_t TestByteMirrorWithoutLoop();

/**** question 6 ****/
bool_ty CheckBothBitsOn(unsigned char);
bool_ty CheckAtLeastOneBitOn(unsigned char);
void SwapBetweenBites(unsigned char*);
static size_t TestCheckBothBitsOn();
static size_t TestCheckAtLeastOneBitOn();
static size_t TestSwapBetweenBites();

/**** question 7 ****/
unsigned int FindClosestDivBySixteen(unsigned int);
static size_t TestFindClosestDivBySixteen();

/**** question 8 ****/
void SwapWithoutThirdVariable(unsigned int* num1, unsigned int* num2);
static size_t TestSwapWithoutThirdVariable();

/**** question 9 ****/
size_t CountSetBits(unsigned int);
size_t CountSetBitsWithoutLoop(unsigned int);
static size_t TestCountSetBits();
static size_t TestCountSetBitsWithoutLoop();

/**** question 10 ****/
void PrintFloatBits(float);
static size_t TestPrintFloatBits();

int main()
{
    size_t passed_tests = 0;

    passed_tests += TestPow2();
    
    passed_tests += TestIsPow2();
    passed_tests += TestIsPow2WithoutLoop();

    passed_tests += TestAddOneBinary();
    
    passed_tests += TestPrintBinaryWithThreeSetBits();
    
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

/***************************************
* Function:    IsSetBitsReqInNum
* Purpose:     an aux func , checks if number of set bits in number 
               is equal to set bit number passed to it as
               argument
* Input:       num = number to test (unsigned int)
*              set_bits_required = required set bits (size_t)
* Returns:     TRUE or FALSE
****************************************/
static bool_ty IsSetBitsReqInNum(unsigned int num, size_t set_bits_required)
{
  size_t set_bits_counter = 0;
  
  set_bits_counter = CountSetBits(num);
  if(set_bits_required ==  set_bits_counter)
  {
    return TRUE;
  }
  return FALSE;

}
/*question 1*/
/***************************************
* Function:    Pow2
* Purpose:     Computes x * 2^y
* Input:       x = base value (unsigned int)
*              y = power of two (unsigned int)
* Returns:     result of  x * 2^y
* Undefined
* Behaviour:   1- sizeof(x) > sizeof(long) 
               2- sizeof(y) > sizeof(long)
               3- x < 0 or y < 0
****************************************/
long pow2 (unsigned int x, unsigned int y)
{
  return SHIFT_LEFT(x, y);
}

/******* question 1 test  ********/
static size_t TestPow2()
{
    unsigned int x_vals[5] = {1, 2, 3, 4, 5};
    unsigned int y_vals[5] = {0, 1, 2, 3, 4};
    long expected[5]       = {1, 4, 12, 32, 80};

    size_t i = 0;

    for (i = 0; i < 5; i++)
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
* Input:       num = number to test (unsigned int)
* Returns:     TRUE (1) = if exactly one bit is on
*              FALSE (0) = otherwise
************************************************/
bool_ty IsPow2(unsigned int num)
{
    /* Logic: Counts how many bits set to 1
       a power of two has exactly one set bit */
    return (IsSetBitsReqInNum(num,1));
}

static size_t TestIsPow2()
{
    unsigned int arr[]    = {1, 2, 3, 4, 5, 8, 16, 18};
    bool_ty expected[]    = {TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, TRUE, FALSE};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        size_t result = IsPow2(arr[i]);

        if (result != expected[i])
        {
            printf("TestIsPow2 FAILED at index %lu: num=%u expected=%u got=%lu\n",
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
  Input:       num = number to test ( unsigned int
  Returns:     TRUE (1)  
               FALSE (0)
*************************************************/
bool_ty IsPow2WithoutLoop(unsigned int num)
{
    if (0 == num)
    {
        return FALSE;
    }

    return ((num & (num - 1)) == 0 ? TRUE : FALSE);
}

static size_t TestIsPow2WithoutLoop()
{
    unsigned int arr[]    = {0, 1, 2, 3, 4, 5, 8, 16, 18};
    bool_ty expected[]   = {FALSE, TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, TRUE, FALSE};

    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        size_t result = IsPow2WithoutLoop(arr[i]);

        if (result != expected[i])
        {
            printf("TestIsPow2WithoutLoop FAILED at index %lu: num=%u expected=%u got=%lu\n",
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
  Input:       num = number to add to (unsigned long)
  Returns:     num + 1  computed by bit manipulation
  Undefined 
  Behavior:    sizeof(num) >= sizeof(unsigned int) 
*************************************************/
unsigned int AddOneBinary(unsigned int num)
{
/*  Logic: The function simulates binary addition as long as the current bit is 1 it is turned off and the carry moves to the
    next bit.. when it finds a zero bit it turns it on and stops.*/
    size_t i = 0;

    while (1)
    {
        if (num & SHIFT_LEFT(1, i))
        {
            num &= ~SHIFT_LEFT(1, i);
            ++i;
        }
        else
        {
            num |= SHIFT_LEFT(1, i);
            break;
        }
    }

    return num;
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
  Function:    PrintBinWithThreeSetBits
  Purpose:     Prints all numbers in an array that
               contain exactly three bits set to 1
  Input:       arr = array of unsigned int values
               size = number of elements in arr
  Returns:     void , prints matching values only
*************************************************/
void PrintBinaryWithThreeSetBits(unsigned int arr[], size_t size)
{
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        if (IsSetBitsReqInNum(arr[i], 3) == TRUE)
        {
            printf("%u\n", arr[i]);
        }
    }
}


static size_t TestPrintBinaryWithThreeSetBits()
{
  unsigned int arr[] = {8,2,9,11,14};
  PrintBinaryWithThreeSetBits(arr, SIZE_OF_ARRAY(arr));
  return PASSED;

}

/* question 5 */
/************************************************
  Function:    ByteMirror
  Purpose:     Reverses the bit order of a 8-bit
               unsigned char (=1 byte)
  Input:       num = var to mirror (unsigned int)
  Returns:      a new unsigned charwhose bits are
               the complete mirror of the input

*************************************************/
unsigned char ByteMirror(unsigned char num)
{
    unsigned char result = 0;
    size_t i = 0;

    for (i = 0; i < BYTE_SIZE ; ++i)
    {
        if (num & (1 << i))
        {
            result |= (1 << (BYTE_SIZE - 1 - i));
        }
    }

    return result;
}

static size_t TestByteMirror()
{
    unsigned char arr[]      = {123, 237, 135};
    unsigned char expected[] = {222, 183, 225};

    size_t size = SIZE_OF_ARRAY(arr);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        unsigned char result = ByteMirror(arr[i]);

        if (result != expected[i])
        {
            printf("TestByteMirror FAILED at index %lu: input=%d expected=%d got=%d\n",
                   i, arr[i], expected[i], result);
            return FAILED;
        }
    }

    return PASSED;
}


/*question 5 - b an implementation without loop */
/************************************************
  Function:    ByteMirrorWithoutLoop
  Purpose:     mirrors the bits of a given number 
  Input:       num = num to mirror type unsigned char (8 bit) = byte size
  Returns:     bit mirrored form of num
*************************************************/

unsigned char ByteMirrorWithoutLoop(unsigned char num)
{
   
    num =  SHIFT_LEFT (ALTERNATE_OFF_ON_MASK(num), 1)      | SHIFT_RIGHT(ALTERNATE_ON_OFF_MASK(num), 1);
    num =  SHIFT_LEFT (ALTERNATE_2OFF_2ON_MASK(num), 2)    | SHIFT_RIGHT(ALTERNATE_2ON_2OFF_MASK(num), 2);
    num =  SHIFT_LEFT (ALTERNATE_4OFF_4ON_MASK(num), 4)    | SHIFT_RIGHT(ALTERNATE_4ON_4OFF_MASK(num), 4);
    return num;
}


static size_t TestByteMirrorWithoutLoop()
{
    unsigned char arr[]      = {123, 237, 135};
    unsigned char expected[] = {222, 183, 225};

    size_t size = SIZE_OF_ARRAY(arr);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        unsigned char result = ByteMirrorWithoutLoop(arr[i]);

        if (result != expected[i])
        {
            printf("TestByteMirrorWithoutLoop FAILED at index %lu: input=%d expected=%d got=%d\n",
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
*************************************************/
bool_ty IsBitSet(unsigned char num, size_t digit_index)
{
   int bit = LSB_MASK(SHIFT_RIGHT(num, digit_index));
   if(ON == bit)
   {
    return TRUE;
   }
   return FALSE;
}

bool_ty CheckBothBitsOn(unsigned char num)
{
  
  if(IsBitSet(num,2) == TRUE && IsBitSet(num,6) == TRUE )
  {
      return TRUE;
  }
      return FALSE;
      
}

static size_t TestCheckBothBitsOn()
{
    unsigned char arr[]    = {1,2,3,4,5,6,7,8,9,10};
    size_t expected[]       = {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE};
    size_t size = SIZE_OF_ARRAY(arr);

    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        if (CheckBothBitsOn(arr[i]) != expected[i])
        {
            printf("TestCheckBothBitsOn FAILED at %lu: num=%u expected=%lu got=%u\n",
                   i, arr[i], expected[i], CheckBothBitsOn(arr[i]));
            return FAILED;
        }
    }

    return PASSED;
}
/************************************************
  Function:    CheckAtLeastOneBitOn
  Purpose:     Checks if at least one of two
               specific bits in an unsigned char
               is turned on
  Input:       num =unsigned char
  Returns:     TRUE  if one or both bits are on
               FALSE if both are zero
*************************************************/

bool_ty CheckAtLeastOneBitOn(unsigned char num)
{
  if(IsBitSet(num,2) == TRUE || IsBitSet(num,6) == TRUE )
  {
      return TRUE;
  }
      return FALSE;
      
}

static size_t TestCheckAtLeastOneBitOn()
{
    unsigned char arr[]    = {1,2,3,4,5,6,7,8,9,10};
    size_t expected[]       = {FALSE,FALSE,FALSE,TRUE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE};
    size_t size = SIZE_OF_ARRAY(arr);

    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        if (CheckAtLeastOneBitOn(arr[i]) != expected[i])
        {
            printf("TestCheckAtLeastOneBitOn FAILED at %lu: num=%u expected=%lu got=%u\n",
                   i, arr[i], expected[i], CheckAtLeastOneBitOn(arr[i]));
            return FAILED;
        }
    }

    return PASSED;
}
/************************************************
  Function:    SwapBetweenBites
  Purpose:     Swaps the values of bit 3 and bit 5
               inside an unsigned char
  Input:       num = pointer to unsigned char
  Returns:     void , modifies the value in place
*************************************************/

void SwapBetweenBites(unsigned char* num)
{
   int bit1 = IsBitSet(*num, 3);
  
   int bit2 = IsBitSet(*num, 5);

   unsigned char num1 = SHIFT_LEFT(bit1, 5);
   unsigned char num2 = SHIFT_LEFT(bit2, 3);
   
   *num = TURN_OFF_3RD_INDEX(*num); 

   *num = TURN_OFF_5TH_INDEX(*num);
   
   *num = (*num | num1 | num2);
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
    size_t size = SIZE_OF_ARRAY(arr);
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




/* question 8  */
/************************************************
  Function:    SwapWithoutThirdVariable
  Purpose:     Swaps two unsigned integers without
               using a temporary variable
               and symmetric
  Input:       num1 = pointer to first unsigned int
               num2 = pointer to second unsigned int
  Returns:     None (swap occurs in-place) (void)
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
    unsigned int arr[]      = {0x0001,0x0002, 0x00AB,0x00CD, 0x0000,0x000F};
    unsigned int expected[] = {0x0002,0x0001, 0x00CD,0x00AB, 0x000F,0x0000};


    size_t size = SIZE_OF_ARRAY(arr);

    size_t i = 0;

    for (i = 0; i < size; i += 2)
    {
        unsigned int a = arr[i];
        unsigned int b = arr[i + 1];

        SwapWithoutThirdVariable(&a, &b);

        if (a != expected[i] || b != expected[i + 1])
        {
            printf("TestSwapWithoutThirdVariable FAILED at small-set index %lu: got (0x%X,0x%X) expected (0x%X,0x%X)\n",
                   i / 2, a, b, expected[i], expected[i + 1]);
            return FAILED;
        }
    }

    return PASSED;
}


/* question 9-a */
/************************************************
  Function:    CountSetBits
  Purpose:     Counts how many bits with value 1
               exist in the binary representation
               of an unsigned integer
  Input:       num  unsigned int
  Returns:     Number of bits set to 1
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

/* question 9-b */
/************************************************
  Function:    CountSetBitsWithoutLoop
  Purpose:     Counts how many bits are set to 1
               in an unsigned integer without
               using any loop
  Input:       num  = unsigned int
  Returns:     the number of set bits
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
    unsigned int arr[] = {0xDF, 0x9F, 0x4CCECFCD};
    size_t expected[] = {7, 6,19};

    size_t size = SIZE_OF_ARRAY(arr);
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
    size_t expected[] = {7, 6, 19};

    size_t size = SIZE_OF_ARRAY(arr);
    size_t i = 0;

    for (i = 0 ; i < size ; ++i)
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
  Input:       num  float value to inspect
  Returns:     void  only prints to stdout 
*************************************************/

void PrintFloatBits(float num)
{
    unsigned int bits = 0;
    int i = 0;
    
    memcpy(&bits, &num, sizeof(unsigned int));
   
    for (i = 31 ; i >= 0 ; --i)
    {
        unsigned int mask = 1 << i;

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
    size_t size = SIZE_OF_ARRAY(arr);
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        printf("input = %f -> ", arr[i]);
        PrintFloatBits(arr[i]);
    }

    return PASSED;
}

