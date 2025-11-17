/*******************************************
* SUBMITTER : ROZALINE KOZLY
* REVIWER : NIMROD
* DATE 17 NOV 2025
* VERSION 2
********************************************/

#include <stdio.h> /* printing to the terminal if invalid input passwed to the functions*/
#include <string.h> /*to compare with libarary functions*/
#include <stdlib.h> /* malloc and free*/
#include <strings.h> /*to compare with library functions*/
#include <stddef.h> /*size_t type */
#include "String.h" /* declarations of functions-to-test*/


#define MAX_LEN 200 /* max length of an input (all functions assume they recived a valid input) */
#define NUM_OF_TESTS 12 /* total number of tests */

/*colors used in printing */		
#define RED           "\033[1;91m"
#define WHITE         "\033[1;97m"
#define CYAN          "\033[1;96m"
#define GREEN         "\033[1;92m"
#define YELLOW        "\033[1;93m"



/* declarations on tests */
size_t TestStrLen(void);
size_t TestStrCmp(void);
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



int main()
{
	size_t counter = 0;
	counter += TestStrLen();
	counter += TestStrCmp();
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
	

	printf(YELLOW"\t-----TESTING RESULTS: -----\n");
	printf(WHITE"\t\tPASSED %lu TESTS\n \t\tout of %d\n\n", counter, NUM_OF_TESTS);
	
	if(NUM_OF_TESTS == counter)
	{
		printf(CYAN"\t\tWELL DONE ROZA!\n\n");
	}
	return 0;
 
}


size_t TestStrLen(void)
{
    const char* tests[] = {"","a","hello","hello world","abc\0xyz","123456789"};

    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t i = 0;
    size_t val = 0;
    size_t lib_val = 0;
    size_t passed = 0;

    printf(YELLOW "\t-----TESTING StrLen FUNCTION: -----\n");

    for(i = 0; i < num_tests; ++i)
    {
        val = StrLen(tests[i]);
        lib_val = strlen(tests[i]);

        if(val != lib_val)
        {
            printf(WHITE "\tTest %lu: \"%s\"", i + 1, tests[i]);
            printf(RED " - FAILED (my=%lu, lib=%lu)\n", val, lib_val);
            return 0;
        }

        ++passed;
    }

    printf(GREEN "\t\tPASSED %lu tests\n", passed);
    return 1;
}



size_t TestStrCmp(void)
{
    const char* s1[] = {"a","abc","hello","hello","abc","A",""};
    const char* s2[] = {"b","abc","hello","heLlo","abcd","a",""};

    size_t num_tests = sizeof(s1) / sizeof(s1[0]);
    size_t i = 0;
    int val = 0;
    int lib_val = 0;
    size_t passed = 0;

    printf(YELLOW "\t-----TESTING StrCmp FUNCTION: -----\n");

    for(i = 0; i < num_tests; ++i)
    {
        val = StrCmp(s1[i], s2[i]);
        lib_val = strcmp(s1[i], s2[i]);

        if(val != lib_val)
        {
            printf(WHITE "\tTest %lu: (\"%s\",\"%s\")", i + 1, s1[i], s2[i]);
            printf(RED " - FAILED (my=%d, lib=%d)\n", val, lib_val);
            return 0;
        }

        ++passed;
    }

    printf(GREEN "\t\tPASSED %lu tests\n", passed);
    return 1;
}


size_t TestStrCpy(void)
{
    const char* src[] = {"hello", "world", "Infinty Labs R&D", "Rina", "Erik", "workshop 3!!@@@&&&", "", "a", "ab"};
    char dst[MAX_LEN];
    size_t test_size = sizeof(src) / sizeof(src[0]);
    size_t i = 0;
    size_t j = 0;
    size_t len = 0;
    int cmp = 0;
    size_t passed = 0;

    printf(YELLOW "\t-----TESTING StrCpy FUNCTION: -----\n");

    for(i = 0; i < test_size; ++i)
    {
        len = StrLen(src[i]);

        if(len + 1 > MAX_LEN)
        {
            printf(RED "\tFAILED on test %lu: input too long\n", i + 1);
            return 0;
        }

        memset(dst, 'X', MAX_LEN);
        dst[MAX_LEN - 1] = '\0';

        StrCpy(dst, src[i]);

        cmp = StrCmp(dst, src[i]);
        if(cmp != 0)
        {
            printf(RED "\tFAILED on test %lu: input=\"%s\" StrCmp!=0\n", i + 1, src[i]);
            return 0;
        }

        for(j = len + 1; j < MAX_LEN - 1; ++j)
        {
            if(dst[j] != 'X')
            {
                printf(RED "\tFAILED on test %lu: padding corrupted\n", i + 1);
                return 0;
            }
        }

        ++passed;
    }

    printf(GREEN "\t\tPASSED %lu tests\n", passed);
    return 1;
}



size_t TestStrnCpy(void)
{
    const char* src[] = {"hello","world","Infinty Labs R&D","Rina","Erik","workshop 3!!@@@&&&","","a"};
    const size_t n_arr[] = {0,3,5,10,20,1,4,1};

    size_t test_size = sizeof(src) / sizeof(src[0]);
    size_t i = 0;
    size_t test_res = 0;
    size_t n = 0;
    char buf[50];
    char lib_buf[50];
    size_t buf_size = sizeof(buf);

    printf(YELLOW "\t-----TESTING StrnCpy FUNCTION: -----\n");

    for(i = 0; i < test_size; ++i)
    {
        n = n_arr[i];

        memset(buf, 'X', buf_size);
        memset(lib_buf, 'X', buf_size);

        StrnCpy(buf, src[i], n);
        strncpy(lib_buf, src[i], n);

        if(memcmp(buf, lib_buf, buf_size) != 0)
        {
            printf(RED "\tFAILED on test %lu: src=\"%s\", n=%lu\n", i + 1, src[i], n);
            return 0;
        }

        ++test_res;
    }

    printf(GREEN "\t\tPASSED %lu tests\n", test_res);
    return 1;
}

size_t TestStrnCmp(void)
{
    const char* s1[] = {"hello","hello","hello","abc","abc","abcd","abcd","","a","abc"};
    const char* s2[] = {"hello","HELLO","hellp","abc","abd","ab","abce","","abc",""};
    const size_t n_arr[] = {5,5,5,3,3,4,4,3,1,0};

    size_t test_size = sizeof(s1) / sizeof(s1[0]);
    size_t i = 0;
    size_t test_res = 0;
    int ret = 0;
    int lib_ret = 0;

    printf(YELLOW "\t-----TESTING StrnCmp FUNCTION: -----\n");

    for(i = 0; i < test_size; ++i)
    {
        ret = StrnCmp(s1[i], s2[i], n_arr[i]);
        lib_ret = strncmp(s1[i], s2[i], n_arr[i]);

        if(ret != lib_ret)
        {
            printf(WHITE "\tTest %lu: \"%s\" vs \"%s\" (n=%lu)", i + 1, s1[i], s2[i], n_arr[i]);
            printf(RED " - FAILED (ret=%d, lib=%d)\n", ret, lib_ret);
            return 0;
        }

        ++test_res;
    }

    printf(GREEN "\t\tPASSED %lu tests\n", test_res);
    return 1;
}



size_t TestStrCaseCmp(void)
{
    const char* s1[] = {"hello","HELLO","abc","ABC","abc","abcd","","","Infinty Labs R&D","workshop 3!!@@@&&&"};
    const char* s2[] = {"hello","hello","abd","abc","","abc","a","","infinty labs r&d","WORKSHOP 3!!@@@&&&"};

    size_t test_size = sizeof(s1) / sizeof(s1[0]);
    size_t i = 0;
    size_t test_res = 0;
    int ret = 0;
    int lib_ret = 0;

    printf(YELLOW "\t-----TESTING StrCaseCmp FUNCTION: -----\n");

    for(i = 0; i < test_size; ++i)
    {
        ret = StrCaseCmp(s1[i], s2[i]);
        lib_ret = strcasecmp(s1[i], s2[i]);

        if(ret != lib_ret)
        {
            printf(WHITE "\tTest %lu: \"%s\" vs \"%s\"", i + 1, s1[i], s2[i]);
            printf(RED " - FAILED (my=%d, lib=%d)\n", ret, lib_ret);
            return 0;
        }

        ++test_res;
    }

    printf(GREEN "\t\tPASSED %lu tests\n", test_res);
    return 1;
}


size_t TestStrChr(void)
{
    const char* strs[] = {"hello","world","Infinty Labs R&D","workshop 3!!@@@&&&","","aaaaaa","xyz",""};
    const int chars[] = {'h','o',' ','!','\0','a','z','K'};

    size_t test_size = sizeof(strs) / sizeof(strs[0]);
    size_t i = 0;
    size_t test_res = 0;
    char* res = NULL;
    char* lib_res = NULL;

    printf(YELLOW "\t-----TESTING StrChr FUNCTION: -----\n");

    for(i = 0; i < test_size; ++i)
    {
        res = StrChr(strs[i], chars[i]);
        lib_res = strchr(strs[i], chars[i]);

        if(res != lib_res)
        {
            printf(WHITE "\tTest %lu: str=\"%s\", ch='%c'", i + 1, strs[i], chars[i] ? chars[i] : '0');
            printf(RED " - FAILED (my_res=%p, lib_res=%p)\n", (void*)res, (void*)lib_res);
            return 0;
        }

        ++test_res;
    }

    printf(GREEN "\t\tPASSED %lu tests\n", test_res);
    return 1;
}

size_t TestStrDup(void)
{
    const char* src[] = {"hello","world","Infinty Labs R&D","Rina","Erik","workshop 3!!@@@&&&",""};
    size_t test_size = sizeof(src) / sizeof(src[0]);
    size_t i = 0;
    size_t test_res = 0;
    char* dup = NULL;
    char* ref_dup = NULL;
    int cmp_res = 0;

    printf(YELLOW "\t-----TESTING StrDup FUNCTION: -----\n");

    for(i = 0; i < test_size; ++i)
    {
        dup = StrDup(src[i]);
        if(dup == NULL)
        {
            printf(RED "\tFAILED on test %lu: malloc failed\n", i + 1);
            return 0;
        }

        ref_dup = (char*)malloc(StrLen(src[i]) + 1);
        if(ref_dup == NULL)
        {
            printf(RED "\tFAILED on test %lu: ref malloc failed\n", i + 1);
            free(dup);
            return 0;
        }

        strcpy(ref_dup, src[i]);
        cmp_res = StrCmp(dup, ref_dup);

        if(cmp_res != 0)
        {
            printf(WHITE "\tTest %lu: \"%s\"", i + 1, src[i]);
            printf(RED " - FAILED (my=\"%s\", ref=\"%s\")\n", dup, ref_dup);
            free(dup);
            free(ref_dup);
            return 0;
        }

        ++test_res;
        free(dup);
        free(ref_dup);
    }

    printf(GREEN "\t\tPASSED %lu tests\n", test_res);
    return 1;
}


size_t TestStrCat(void)
{
    const char* dest_arr[] = {"hello","Infinty","","123","coding","aaa",""};
    const char* src_arr[] = {" world"," Labs","empty",""," is fun","bbb",""};
    size_t test_size = sizeof(dest_arr) / sizeof(dest_arr[0]);
    size_t i = 0;
    size_t test_res = 0;
    char* buf;
    char* lib_buf;

    printf(YELLOW "\t-----TESTING StrCat FUNCTION: -----\n");

    for(i = 0; i < test_size; ++i)
    {
        buf = (char*)malloc(MAX_LEN);
        lib_buf = (char*)malloc(MAX_LEN);

        if(!buf || !lib_buf)
        {
            printf(RED "\tFAILED on test %lu: malloc failed\n", i + 1);
            free(buf);
            free(lib_buf);
            return 0;
        }

        strcpy(buf, dest_arr[i]);
        strcpy(lib_buf, dest_arr[i]);

        StrCat(buf, src_arr[i]);
        strcat(lib_buf, src_arr[i]);

        if(StrCmp(buf, lib_buf) != 0)
        {
            printf(WHITE "\tTest %lu", i + 1);
            printf(RED " - FAILED (my=\"%s\", lib=\"%s\")\n", buf, lib_buf);
            free(buf);
            free(lib_buf);
            return 0;
        }

        ++test_res;
        free(buf);
        free(lib_buf);
    }

    printf(GREEN "\t\tPASSED %lu tests\n", test_res);
    return 1;
}

size_t TestStrnCat(void)
{
    const char* dest_arr[] = {"hello","Infinty","","123","coding","aaa",""};
    const char* src_arr[] = {" world"," Labs","empty",""," is fun","bbb",""};
    const size_t n_arr[] = {3,5,10,2,4,1,0};

    size_t test_size = sizeof(dest_arr) / sizeof(dest_arr[0]);
    size_t i = 0;
    size_t test_res = 0;
    char* buf;
    char* lib_buf;

    printf(YELLOW "\t-----TESTING StrnCat FUNCTION: -----\n");

    for(i = 0; i < test_size; ++i)
    {
        buf = (char*)malloc(MAX_LEN);
        lib_buf = (char*)malloc(MAX_LEN);

        if(!buf || !lib_buf)
        {
            printf(RED "\tFAILED on test %lu: malloc failed\n", i + 1);
            free(buf);
            free(lib_buf);
            return 0;
        }

        strcpy(buf, dest_arr[i]);
        strcpy(lib_buf, dest_arr[i]);

        StrnCat(buf, src_arr[i], n_arr[i]);
        strncat(lib_buf, src_arr[i], n_arr[i]);

        if(StrCmp(buf, lib_buf) != 0)
        {
            printf(WHITE "\tTest %lu", i + 1);
            printf(RED " - FAILED (my=\"%s\", lib=\"%s\")\n", buf, lib_buf);
            free(buf);
            free(lib_buf);
            return 0;
        }

        ++test_res;
        free(buf);
        free(lib_buf);
    }

    printf(GREEN "\t\tPASSED %lu tests\n", test_res);
    return 1;
}

size_t TestStrStr(void)
{
    const char* str1[] = {"hello world","Infinty Labs R&D","aaaaaa","abcabcabc","no match here","","edge case","abc","abc",""};
    const char* str2[] = {"world","Labs","aaa","abcabc","zzz","","edge","abc","","x"};

    size_t test_size = sizeof(str1) / sizeof(str1[0]);
    size_t i = 0;
    size_t test_res = 0;
    char* res;
    char* lib_res;

    printf(YELLOW "\t-----TESTING StrStr FUNCTION: -----\n");

    for(i = 0; i < test_size; ++i)
    {
        res = StrStr(str1[i], str2[i]);
        lib_res = strstr(str1[i], str2[i]);

        if(res != lib_res)
        {
            printf(WHITE "\tTest %lu", i + 1);
            printf(RED " - FAILED (my=%p, lib=%p)\n", (void*)res, (void*)lib_res);
            return 0;
        }

        ++test_res;
    }

    printf(GREEN "\t\tPASSED %lu tests\n", test_res);
    return 1;
}

size_t TestStrSpn(void)
{
    const char* s1[] = {"abcde","aaaaaa","hello","12345","xyz","","abcdef","112233","test",""};
    const char* s2[] = {"abc","a","he","012345","a","abc","","12","t","x"};

    size_t test_size = sizeof(s1) / sizeof(s1[0]);
    size_t i = 0;
    size_t test_res = 0;
    size_t res = 0;
    size_t lib_res = 0;

    printf(YELLOW "\t-----TESTING StrSpn FUNCTION: -----\n");

    for(i = 0; i < test_size; ++i)
    {
        res = StrSpn(s1[i], s2[i]);
        lib_res = strspn(s1[i], s2[i]);

        if(res != lib_res)
        {
            printf(WHITE "\tTest %lu", i + 1);
            printf(RED " - FAILED (my=%lu, lib=%lu)\n", res, lib_res);
            return 0;
        }

        ++test_res;
    }

    printf(GREEN "\t\tPASSED %lu tests\n", test_res);
    return 1;
}




