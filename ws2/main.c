#include <stdio.h> /* printing */
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <strings.h>
#include "String.h" /* headers */


#define MAX_LEN 200
size_t TestStrCpy(void);
size_t TestStrnCpy(void);
size_t TestStrnCmp(void);
size_t TestStrCaseCmp(void);
size_t TestStrChr(void);
size_t TestStrDup(void);
size_t TestStrCat(void);
size_t TestStrnCat(void);
size_t TestStrStr(void);
size_t TestStrSpn(void);

size_t TestIsPalendrome(void);
void TestSevenBoom(void);
void TestWhiteSpaceReview(void);



int main()
{
	size_t counter = 0;
	counter += TestStrCpy();
	counter += TestStrnCpy();
	counter += TestStrnCmp();
	counter += TestStrCaseCmp();
	counter += TestStrChr();
	counter += TestStrDup();
	counter += TestStrCat();
	counter += TestStrnCat();
	counter += TestStrStr();
	counter += TestStrSpn();
	 TestIsPalendrome();
	TestSevenBoom();
	
	TestWhiteSpaceReview();
	
	printf(PINK"PASSED %lu TESTS\n", counter);
	return 0;
 
}


size_t TestStrCpy(void)
{
    size_t i = 0;
    const char* src[] = { "hello", "world", "Infinty Labs R&D",
                          "Rina", "Erik", "workshop 3!!@@@&&&", "",
                          "a", "ab" };

    char dst[MAX_LEN];
    size_t test_size = sizeof(src) / sizeof(src[0]);
    size_t len = 0;
    size_t test_res = 0; /* counter for passed test results */
    int strcmp_ret_val = -1;
     size_t j = 0; /*iterator */

    printf(YELLOW "\t-----TESTING StrCpy FUNCTION: -----\n");

    for (i = 0; i < test_size; ++i)
    {
        len = strlen(src[i]);

       /*in case an invalid tests entered (long string)*/
        if (len + 1 > MAX_LEN)
        {
            printf(RED "Test %lu: input too long for buffer\n", (unsigned long)(i + 1));
            return 0;
        }

        /* testing padding with \0 using memset (setting all the \0 to be X)*/
        memset(dst, 'X', MAX_LEN);
        dst[MAX_LEN - 1] = '\0'; /* to point that it's the end of the string */
        
        StrCpy(dst, src[i]);
       
        strcmp_ret_val = strcmp(dst, src[i]);
        
        if (strcmp_ret_val != 0)
        {
            printf(WHITE "Test %lu: input: ", (i + 1));
            printf(CYAN "\"%s\"", src[i]);
            printf(RED " - FAILED (strcmp != 0)\n");
            return 0;
        }

       
        { 
            for (j = len + 1; j < MAX_LEN - 1; ++j)
            {
                if (dst[j] != 'X')
                {
                    printf(RED "Test %lu: FAILED AT PADDING\n", (i+1));
                    return 0;
                }
            }
        }

        ++test_res;
    }

    printf(GREEN "\nPASSED %lu TESTS!\n", test_res);
    return 1;
}


size_t TestStrnCpy(void)
{
    size_t i = 0;
    size_t test_res = 0;

    const char* src[] = {"hello","world","Infinty Labs R&D","Rina",
        			"Erik","workshop 3!!@@@&&&","","a"};

    const size_t n_arr[] = {0,3,5,10,20,1,4,1};

    size_t test_size = sizeof(src) / sizeof(src[0]);
    char buf[50]; /*placement to hold StrnCpy result*/
    char lib_buf[50]; /*placement to hold library result */
    size_t buf_size = sizeof(buf); 

    printf(YELLOW "\t-----TESTING StrnCpy FUNCTION: -----\n");

    for (i = 0; i < test_size; ++i)
    {
        size_t n = n_arr[i];

       

        /* iniate buffers to a known pattern so we can test padding */
        memset(buf,  'X', buf_size);
        memset(lib_buf, 'X', buf_size);

        StrnCpy(buf,  src[i], n);
        strncpy(lib_buf, src[i], n);

        /* compare full buffer (including padding) */
        if (memcmp(buf, lib_buf, buf_size) != 0) /* it compares it bit-bit*/
        {
            printf(RED " - FAILED\n");
            printf(WHITE "Test %lu: src=\"%s\", n=%lu", (i + 1), src[i], n);
            return 0;
           
           
        }
         ++test_res;
    
    }

    printf(GREEN "\nPASSED %lu TESTS!\n", test_res);
    return 1;
}





size_t TestStrnCmp(void)
{
    size_t i = 0;
    size_t test_res = 0;

    const char* s1[] = {"hello","hello","hello","abc","abc","abcd",      
        		      "abcd","","a","abc"};

    const char* s2[] = {"hello","HELLO","hellp", "abc","abd","ab","abce","","abc",""};

    const size_t n_arr[] = {5, 5,5,3,3,4,4,3,1,0};

    size_t test_size = sizeof(s1) / sizeof(s1[0]);
    int ret = 0;
    int lib_ret = 0;

    printf(YELLOW "\t-----TESTING StrnCmp FUNCTION: -----\n");

    for (i = 0; i < test_size; ++i)
    {
      

        ret  = StrnCmp(s1[i], s2[i], n_arr[i]);
        lib_ret = strncmp(s1[i], s2[i], n_arr[i]);

        if (ret != lib_ret)
        {
        
              printf(WHITE "Test %lu: \"%s\" vs \"%s\" (n=%lu)", (i+1), s1[i], s2[i], n_arr[i]);
              printf(RED " - FAILED (ret=%d, lib=%d)\n", ret, lib_ret);
              return 0;
           
        
        }
        ++test_res;
       
    }

    printf(GREEN "\nPASSED %lu TESTS!\n", test_res);
    return 1;
}


size_t TestStrCaseCmp()
{
    size_t i = 0;
    const char* s1[] = {"hello", "HELLO", "abc", "ABC",
                        "abc", "abcd", "",  "",
                        "Infinty Labs R&D", "workshop 3!!@@@&&&"};
    const char* s2[] = {"hello", "hello", "abd", "abc",
                        "",    "abc",  "a", "",
                        "infinty labs r&d", "WORKSHOP 3!!@@@&&&"};
    
    size_t test_size = sizeof(s1) / sizeof(s1[0]);
    size_t test_res = 0;
    int ret = 0;
    int lib_ret = 0;

    printf(YELLOW "\t-----TESTING StrCaseCmp FUNCTION: -----\n");

    for (i = 0; i < test_size; ++i)
    {
        

        ret = StrCaseCmp(s1[i], s2[i]);
        lib_ret = strcasecmp(s1[i], s2[i]);

        if (ret != lib_ret)
        {
        
             printf(WHITE "Test %lu: \"%s\" vs \"%s\"", (i+1), s1[i], s2[i]);
              printf(RED " - FAILED (my=%d, lib=%d)\n", ret, lib_ret);
              return 0;
           
        
        }
        ++test_res;
    }

    printf(GREEN "\nPASSED %lu TESTS!\n", test_res);
    return 1;
}


size_t TestStrChr()
{
    size_t i = 0;
    size_t test_res = 0;
    char* res = NULL;
    char* lib_res = NULL;

    const char* strs[] = {"hello","world","Infinty Labs R&D","workshop 3!!@@@&&&",
       		         "","aaaaaa","xyz",""};

    const int chars[] = {
        'h', 'o', ' ', '!', '\0', 'a', 'z','K'};

    size_t test_size = sizeof(strs) / sizeof(strs[0]);

    printf(YELLOW "\t-----TESTING StrChr FUNCTION: -----\n");

    for (i = 0; i < test_size; ++i)
    {
        res  = StrChr(strs[i], chars[i]);
        lib_res = strchr(strs[i], chars[i]);

        if (res != lib_res)
        {
             printf(RED " - FAILED\n");     
            printf(RED "  my_res : %s\n", res);
            printf(RED "  lib_res: %s\n", lib_res);
            return 0;
        }
        ++test_res;

    }

    printf(GREEN "\nPASSED %lu TESTS!\n", test_res);
    return 1;
}

size_t TestStrDup()
{
    size_t i = 0;
    const char* src[] = {"hello", "world", "Infinty Labs R&D",
                         "Rina", "Erik", "workshop 3!!@@@&&&", ""};
    size_t test_size = sizeof(src) / sizeof(src[0]);
    size_t test_res = 0;
    char* dup = NULL;
    char* ref_dup = NULL;
    int cmp_res = 0;

    printf(YELLOW "\t-----TESTING StrDup FUNCTION: -----\n");

    for (i = 0; i < test_size; ++i)
    {

       dup = StrDup(src[i]);
        if (dup == NULL)
        {
            printf(RED " - MALLOC FAILED (my_dup)\n");
            return 0;
        }

       
        ref_dup = (char*)malloc(strlen(src[i]) + 1);
        if (ref_dup == NULL)
        {
            printf(RED " - MALLOC FAILED (ref_dup)\n");
            free(dup);
            return 0;
        }
        strcpy(ref_dup, src[i]);

        cmp_res = strcmp(dup, ref_dup);

        if (cmp_res != 0 )
        {
            printf(RED " - FAILED\n");
            printf(RED "  dup : \"%s\"\n", dup);
            printf(RED "  ref_dup: \"%s\"\n", ref_dup);
            free(dup);
            free(ref_dup);
            return 0;
        }
         ++test_res;

        free(dup);
        free(ref_dup);
    }

    printf(GREEN "\nPASSED %lu TESTS!\n", test_res);
    return 1;
}

size_t TestStrCat()
{
    size_t i = 0;
    size_t test_res = 0;

    const char* dest_arr[] = {"hello", "Infinty", "", "123", "coding", "aaa", ""};

    const char* src_arr[] = {" world", " Labs", "empty", "", " is fun", "bbb", ""};

    size_t test_size = sizeof(dest_arr) / sizeof(dest_arr[0]);
    char* buf;
    char* lib_buf;

    printf(YELLOW "\t-----TESTING StrCat FUNCTION: -----\n");

    for (i = 0; i < test_size; ++i)
    {

        /* allocate */
        buf = (char*)malloc(MAX_LEN);
        lib_buf = (char*)malloc(MAX_LEN);

        if (!buf || !lib_buf)
        {
            printf(RED " - MALLOC FAILED\n");
            free(buf);
            free(lib_buf);
            return 0;
        }

        /* make a copy of dst (bc strcpy changes the string) */
        strcpy(buf,  dest_arr[i]);
        strcpy(lib_buf, dest_arr[i]);

        
        StrCat(buf, src_arr[i]);
        strcat(lib_buf, src_arr[i]);

       
        if (strcmp(buf, lib_buf) != 0)
        {
        
         printf(RED " - FAILED\n");
            printf(RED "  buf : \"%s\"\n", buf);
            printf(RED "  lib_buf: \"%s\"\n", lib_buf);
            free(buf);
            free(lib_buf);
            return 0;
        }
        ++test_res;
        free(buf);
        free(lib_buf);
    }

    printf(GREEN "\nPASSED %lu TESTS!\n", test_res);
    return 1;
}

size_t TestStrnCat()
{
    size_t i = 0;
    size_t test_res = 0;

    const char* dest_arr[] = {"hello","Infinty","","123","coding","aaa",""};

    const char* src_arr[] = { " world"," Labs","empty",""," is fun","bbb",""};

    const size_t n_arr[] = {3, 5, 10, 2, 4, 1, 0};

    size_t test_size = sizeof(dest_arr) / sizeof(dest_arr[0]);
    char* buf;
    char* lib_buf;

    printf(YELLOW "\t-----TESTING StrnCat FUNCTION: -----\n");

    for (i = 0; i < test_size; ++i)
    {

        
        buf  = (char*)malloc(MAX_LEN);
        lib_buf = (char*)malloc(MAX_LEN);

        if (!buf || !lib_buf)
        {
            printf(RED " - MALLOC FAILED\n");
            free(buf);
            free(lib_buf);
            return 0;
        }

        
        strcpy(buf,  dest_arr[i]);
        strcpy(lib_buf, dest_arr[i]);

        StrnCat(buf, src_arr[i], n_arr[i]);  
        strncat(lib_buf, src_arr[i], n_arr[i]);

        /* compare */
        if (strcmp(buf, lib_buf) == 0)
        {
            ++test_res;
        }
        else
        {
            printf(RED " - FAILED\n");
            printf(RED "  my_buf : \"%s\"\n", buf);
            printf(RED "  lib_buf: \"%s\"\n", lib_buf);
            free(buf);
            free(lib_buf);
            return 0;
        }

        free(buf);
        free(lib_buf);
    }

    printf(GREEN "\nPASSED %lu TESTS!\n", test_res);
    return 1;
}

size_t TestStrStr()
{
    size_t i = 0;
    size_t test_res = 0;

    const char* str1[] = {"hello world","Infinty Labs R&D","aaaaaa","abcabcabc","no match here",
                           "","edge case","abc","abc",""};

    const char* str2[] = {"world","Labs","aaa","abcabc",
                           "zzz","","edge","abc","","x"};

    size_t test_size = sizeof(str1) / sizeof(str1[0]);
    char* res;
    char* lib_res;

    printf(YELLOW "\t-----TESTING StrStr FUNCTION: -----\n");

    for (i = 0; i < test_size; ++i)
    {
   

        res  = StrStr(str1[i], str2[i]);
        lib_res = strstr(str1[i], str2[i]);

        if (res == lib_res)
        {
            ++test_res;
        }
        else
        {
            printf(RED " - FAILED\n");
            printf(RED "  my_res : %s\n",res);
            printf(RED "  lib_res: %s\n",lib_res);
            return 0;
        }
    }

    printf(GREEN "\nPASSED %lu TESTS!\n", test_res);
    return 1;
}

size_t TestStrSpn()
{
    size_t i = 0;
    size_t test_res = 0;

    const char* s1[] = {"abcde","aaaaaa","hello","12345",
                        "xyz","","abcdef","112233","test",""};

    const char* s2[] = {"abc", "a",  "he", "012345","a",        
                        "abc","","12","t","x"};

    size_t test_size = sizeof(s1) / sizeof(s1[0]);
    size_t res = 0;
    size_t lib_res = 0;

    printf(YELLOW "\t-----TESTING StrSpn FUNCTION: -----\n");

    for (i = 0; i < test_size; ++i)
    {
        res  = StrSpn(s1[i], s2[i]);
        lib_res = strspn(s1[i], s2[i]);

        if (res == lib_res)
        {
            ++test_res;
        }
        else
        {
            printf(RED " - FAILED\n");
            printf(RED "  my_res : %lu\n", res);
            printf(RED "  lib_res: %lu\n", lib_res);
            return 0;
        }
    }

    printf(GREEN "\nPASSED %lu TESTS!\n", test_res);
    return 1;
}



size_t TestIsPalendrome()
{
    char* inputs[] = {"", "a", "aa", "ab", "aba", "abba", "abcba", "abcca", "12321", "123421"};
    size_t expected[]     = {1,1,1,0,1, 1, 1, 0, 1,  0  };

    size_t num_tests = sizeof(inputs) / sizeof(inputs[0]);
    size_t i = 0;
    size_t ret= 0;
    size_t test_res = 0;

     printf(YELLOW "\t-----TESTING IsPalindrome FUNCTION: -----\n");

    for (i = 0; i < num_tests; ++i)
    {
        ret = IsPalindrome(inputs[i]);
        if(ret != expected[i])
        {
        		printf(RED "FAILED");
        		printf("input = %s , ret = %lu, expected = %lu", inputs[i],ret , expected[i]);
        		return 0;
        }
        test_res++;
    }
    printf(GREEN "\nPASSED %lu TESTS!\n",test_res);
    return 1;
    
}

void TestSevenBoom()
{
   printf(YELLOW "\t-----TESTING 7BOOM FUNCTION: -----\n");
    printf(WHITE "Test 1: SevenBoom(1, 20)\n");
    SevenBoom(1, 20);
    printf("\n");

    printf(WHITE "Test 2: SevenBoom(7, 17)\n");
    SevenBoom(7, 17);
    printf("\n");

    printf(WHITE "Test 3: SevenBoom(68, 75)\n");
    SevenBoom(68, 75);
    printf("\n");

}



void TestWhiteSpaceReview()
{
    char test1[] = "   hi   world   ";
    char test2[] = "hello";
    char test3[] = "   \t\t   ";
    char test4[] = "a   b\t\tc";
    char test5[] = " no leading ";
    char test6[] = "\t\tTabs\t here\t";
    char test7[] = "  hi";
    char test8[] = "bye  ";
    
     printf(YELLOW "\t-----TESTING WHiteSpaceReview FUNCTION: -----\n");
    printf(WHITE"Test 1: \"%s\" --> \"%s\"\n", test1, WhiteSpaceReview(test1));
    printf("Test 2: \"%s\" --> \"%s\"\n", test2, WhiteSpaceReview(test2));
    printf("Test 3: \"%s\" --> \"%s\"\n", test3, WhiteSpaceReview(test3));
    printf("Test 4: \"%s\" --> \"%s\"\n", test4, WhiteSpaceReview(test4));
    printf("Test 5: \"%s\" --> \"%s\"\n", test5, WhiteSpaceReview(test5));
    printf("Test 6: \"%s\" --> \"%s\"\n", test6, WhiteSpaceReview(test6));
    printf("Test 7: \"%s\" --> \"%s\"\n", test7, WhiteSpaceReview(test7));
    printf("Test 8: \"%s\" --> \"%s\"\n", test8, WhiteSpaceReview(test8));
}

