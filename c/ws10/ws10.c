/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer  : 
worksheet : 10 (atoi/itoa)
version   : 1
date      : 8 Dec 2025
stage     : pre-review
----------------------------------------------------------------------------*/
#include <stdio.h>		/* printf() */
#include <string.h>		/* strcmp() */
#include <stdlib.h>		/* atoi(), size_t data type */

#define ZERO_ASCII 	 	  	  '0'
#define NINE_ASCII 	 	  	  '9'
#define ASCII_TABLE_SIZE			   256
#define SIZEOF_ARR(ARR)                  (sizeof(ARR)/sizeof(*ARR))

typedef enum
{
    NEGATIVE = -1,
    POSITIVE = 1
} sign_ty;

typedef enum
{
    FALSE = 0,
    TRUE = 1
} bool_ty;

/*--- end-user API ---*/
void Itoa(int, char*);
int Atoi(const char*);
void ItoaWithBase(int, char*, int);
void PrintCharsInFirstAndSecondAndNotThird(char*, size_t, char*, size_t, char*, size_t);
bool_ty IsSystemLittleEndian(void);

/*--- auxillary functions (hidden from end-user) ---*/
static sign_ty FindNumSgn(int);
static int Abs(int);
static char* AddReverseNumInStr(size_t, char*);
static char* AddNumSgnToStr(char*, sign_ty);
static void ReverseString(char*);
static sign_ty FindSgnAndSkipSpaces(const char**);
static int ReadNumIntoStr(const char*);

/*--- inner hidden testing functions ---*/
static void TestItoa(void);
static void TestAtoi(void);
static void TestItoaWithBase(void);
static void TestPrintChars(void);
static void TestEndian(void);

/*------------------------------------------- testing use ---------------------------------------*/
int main()
{
    TestItoa();
    TestAtoi();
    TestItoaWithBase();
    TestPrintChars();
    TestEndian();
    return 0;
}
/*------------------------------------------- function's implementations ---------------------------------------*/

/**----------------------------- Itoa -----------------------------**/
/*
    Itoa(integer, ptr-to-str)
    - purpose: converts a given integer to a string and stores it in the memory location the ptr-to-str points at.
    
    - UB: 1- ptr-to-str not holding enough memory space to hold the number with the null-terminated character.
    	 2- ptr-to-str is NULL.
    	 
    - return value: void, the passed ptr-to-str argument should change and represent the integer in string format.
*/
void Itoa(int num, char* str)
{
    char* itr = str;
    sign_ty sgn = FindNumSgn(num);
    
    num = Abs(num);
    itr = AddReverseNumInStr(num, itr);
    itr = AddNumSgnToStr(itr, sgn);
    *itr = '\0';
    ReverseString(str);
}

/*---------- aux functions for Itoa ----------*/
/*
    FindNumSgn(integer)
    - purpose: return the sign of the passed integer (negative/ positive).
    
    - UB: the passed integer do not represent a valid number.
    
    - return value: sign_ty type, it is an enum with 2 values positive or negative.
*/
static sign_ty FindNumSgn(int num)
{
    return num < 0 ? NEGATIVE : POSITIVE;
}

/*
    Abs(integer)
    - purpose: return the absolute value of the passed integer (negative/ positive).
    
    - UB: the passed integer do not represent a valid number.
    
    - return value: abs value of the argument. 
*/
static int Abs(int num)
{
    return num < 0 ? -num : num;
}

/*
    AddReverseNumInStr(integer, ptr-to-str)
    - purpose: converts a given positive integer to a semi-string (not null terminated) in backward.
    
    - UB: the passed integer do not represent a valid number.
    
    - return value: a pointer to the end of the string. 
*/
static char* AddReverseNumInStr(size_t num, char* str)
{
    char* itr = str;

    if (num == 0)
    {
        *itr = ZERO_ASCII;
        return itr + 1;
    }

    while (num)
    {
        *itr = (num % 10) + ZERO_ASCII;
        ++itr;
        num /= 10;
    }

    return itr;
}

/*
    AddNumSgnToStr(ptr-to-str, sign-ty)
    - purpose: inserts the sign '-' in the string in case the passed sign-ty is negative.
    
    - UB: ptr-to-str is not valid or pt-to-str + 1 is outside the allowed range to write.
    
    - return value: a pointer to the end of the string. 
*/
static char* AddNumSgnToStr(char* itr, sign_ty sgn)
{
    if (sgn == NEGATIVE)
    {
        *itr = '-';
        ++itr;
    }

    return itr;
}

/*
    ReverseString(ptr-to-str)
    - purpose: flips a given string.
    
    - UB: 1- ptr-to-str is not valid.
    	 2- ptr-to-str do not represent a null-terminated string.
    
    - return value: void. 
*/
static void ReverseString(char* str)
{
    size_t len = 0;
    size_t i = 0;
    char tmp = ' ';

    while ('\0' != str[len])
    {
        ++len;
    }

    for (i = 0; i < len / 2; ++i)
    {
        tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}

/**----------------------------- Atoi -----------------------------**/
/*
    Atoi(const ptr-to-str)
    - purpose: converts a given ptr-to-str to an integer.
    
    - UB: 1- ptr-to-str not valid.
    	 2- ptr-to-str is not null-terminated.
    	 
    - return value: integer, that represents the given string in an integer format. 
*/

int Atoi(const char* str)
{
    sign_ty sgn = FindSgnAndSkipSpaces(&str);
    return ReadNumIntoStr(str) * sgn;
}
/*---------- aux functions for Atoi ----------*/
/*
    FindSgnAndSkipSpaces(const ptr-to-ptr-to-str)
    
    - purpose: skip on spaces if they appear in the prefix of the string, and read the sign '-' then negative, otherwise positive
	      it changes the position of the string ptr to point on first char that is not sign neither space  .
    
    - UB:  passed ptr is not valid.
    
    - return value: sign_ty type.
*/

static sign_ty FindSgnAndSkipSpaces(const char** str)
{
    while (**str == ' ')
    {
        ++(*str);
    }

    if (**str == '-')
    {
        ++(*str);
        return NEGATIVE;
    }

    if (**str == '+')
    {
        ++(*str);
    }

    return POSITIVE;
}

/*
    ReadNumIntoStr(const ptr-to-str)
    
    - purpose: skip on spaces if they appear in the prefix of the string, and read the sign '-' then negative, otherwise positive
	      it changes the position of the string ptr to point on first char that is not sign neither space  .
    
    - UB:  passed ptr is not valid.
    
    - return value: sign_ty type.
*/
static int ReadNumIntoStr(const char* str)
{
    int num = 0;

    while (*str >= ZERO_ASCII && *str <= NINE_ASCII)
    {
        num = num * 10 + (*str - ZERO_ASCII);
        str++;
    }

    return num;
}

/**----------------------------- ItoaWithBase -----------------------------**/
/*
    ItoaWithBase(integer, ptr-to-str, base)
    - purpose: converts a given integer according to it's base to a string and stores it in the memory location the ptr-to-str points at.
    
    - UB: 1- ptr-to-str not holding enough memory space to hold the number with the null-terminated character.
    	 2- ptr-to-str is NULL.
    	 
    - return value: void, the passed ptr-to-str argument should change and represent the integer in string format.
*/
void ItoaWithBase(int num, char* str, int base)
{
    /* all the digits out there (26 english letters + 10 digits) */
    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    /* str iterator */
    char* itr = str;
    /* only numbers in base 10 has a sign */
    sign_ty sgn = num < 0 && base == 10 ? NEGATIVE : POSITIVE;
    num = Abs(num);

    if (0 == num)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    while (num)
    {
        *itr++ = digits[num % base];
        num /= base;
    }

    if (sgn == NEGATIVE)
    {
        *itr++ = '-';
    }

    *itr = '\0';
    ReverseString(str);
}
/**----------------------------- PrintCharsInFirstAndSecondAndNotThird -----------------------------**/
/*
    PrintCharsInFirstAndSecondAndNotThird(arr1,size1,arr2,size2,arr3,size3)
    
    - purpose: prints characters that appears in both first and second array and not the third.
    	 
    - return value: void.
*/
void PrintCharsInFirstAndSecondAndNotThird(char* arr1, size_t size1, char* arr2, size_t size2, char* arr3, size_t size3)
{
    int hist[ASCII_TABLE_SIZE] = {0};
    size_t i;

    for (i = 0; i < size1; ++i)
    {
        hist[(unsigned char)arr1[i]] = 1;
    }

    for (i = 0; i < size2; ++i)
    {
        if (hist[(unsigned char)arr2[i]] == 1)
        {
            hist[(unsigned char)arr2[i]] = 2;
        }
    }

    for (i = 0; i < size3; ++i)
    {
        if (hist[(unsigned char)arr3[i]] == 2)
        {
            hist[(unsigned char)arr3[i]] = 0;
        }
    }

    for (i = 0; i < 256; ++i)
    {
        if (hist[i] == 2)
        {
            printf("%c ", (char)i);
        }
    }

    printf("\n");
}

/**----------------------------- IsSystemLittleEndian -----------------------------**/
/*
    IsSystemLittleEndian(void)
    
    - purpose: check if the system is Little endian. (propably it is, otherwise buy new computer)
    	 
    - return value: boolian true = it is, flase = it is not.
*/

bool_ty IsSystemLittleEndian()
{
    unsigned int x = 1;
    return (*(unsigned char*)&x == 1) ? TRUE : FALSE;
}


/*------------------------------------------- function's testing functions ---------------------------------------*/
static void TestItoa()
{
    char buf[50];
    int inputs[] = {0, 123, -456, 98765, -1000000};
    const char *expected[] = {"0", "123", "-456", "98765", "-1000000"};
    size_t n = 5;
    size_t i;

    for (i = 0; i < n; ++i)
    {
        Itoa(inputs[i], buf);
        if (strcmp(buf, expected[i]) == 0)
        {
            printf("Itoa test %lu input %d expected %s got %s PASS\n", (unsigned long)i, inputs[i], expected[i], buf);
        }
        else
        {
            printf("Itoa test %lu input %d expected %s got %s FAIL\n", (unsigned long)i, inputs[i], expected[i], buf);
        }
    }
}

static void TestAtoi()
{
    const char* inputs[] = {"123", "-456", "   789", "+42", "-1000"};
    size_t inputs_size = SIZEOF_ARR(inputs);
    size_t i = 0;
    int Atoi_res = 0, atoi_res = 0;

    for (i = 0; i < inputs_size ; i++)
    {
        Atoi_res = Atoi(inputs[i]);
        atoi_res = atoi(inputs[i]);
        if (Atoi_res == atoi_res)
        {
            printf("Atoi test %lu input %s expected %d got %d PASS\n", (unsigned long)i, inputs[i], atoi_res, Atoi_res);
        }
        else
        {
            printf("Atoi test %lu input %s expected %d got %d FAIL\n", (unsigned long)i, inputs[i], atoi_res, Atoi_res);
        }
    }
}

static void TestItoaWithBase()
{
    char buf[50];

    ItoaWithBase(255, buf, 16);
    printf("ItoaWithBase hex 255 -> %s\n", buf);

    ItoaWithBase(255, buf, 2);
    printf("ItoaWithBase bin 255 -> %s\n", buf);

    ItoaWithBase(123456, buf, 36);
    printf("ItoaWithBase base36 123456 -> %s\n", buf);
}

static void TestPrintChars()
{
    char a1[] = "abcdxyz";
    char a2[] = "bdyz";
    char a3[] = "dy";
    PrintCharsInFirstAndSecondAndNotThird(a1, 7, a2, 4, a3, 2);
}

static void TestEndian()
{
    printf("Endian %d\n", IsSystemLittleEndian());
}

