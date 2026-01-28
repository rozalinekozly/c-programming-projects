/*
submitter: rozaline kozly
reviewer: Tomer
------------------------------------------------------------------------------*/
#include <stdio.h>				     /* printf(), NULL */
#include <stdlib.h> 				 /* malloc(), free(), rand() */
/* to randomify data */
#include <math.h>					 /* pow()   */
#include <string.h>                 /* strlen(), strcmp() , strcpy(), strncmp() (lib comparing )*/
#include <assert.h>                 /*assert()*/

#include "stack.h"                  /*stack_ty, pop(), peek(), push()*/
/*----------------------------------------------------------------------------*/
#define SIZEOF_ARR(arr)     (sizeof(arr)/sizeof(arr[0]))
/*----------------------------------------------------------------------------*/
/* data's array size */
#define DATA_ARR_SIZE					10
/* to make the values readable used for modulu */
#define MAX_VAL							100
#define MAX_LEN                         200
/*----------------------------------------------------------------------------*/
typedef struct node
{
	void *data;
	struct node* next;
}node_ty;
/*----------------------------------------------------------------------------*/
/* fibonacci */
int Fibonacci(int x);
static void TestFib(void);

/*flip*/
node_ty* FlipList(node_ty* node);
/* testing functions*/
static void TestFlip(void);
/* printing list to the terminal */
static void PrintList(node_ty*); 
/* push to list (pushes to head)*/
static void Push(node_ty**, int*);
/* function to generate random data */
static void GenereateData(int* arr, size_t arr_size);
/* function to generate a list from given array */
static node_ty* GenerateListFrmArr(node_ty* head, int* arr, size_t arr_size);
/* free list*/
static void FreeList(node_ty* head);

/*sort stack*/
void SortStack(stack_ty* s);
static void InsertSorted(stack_ty* s, int x);
static void TestSortedStack();
void GenerateStkFrmArr(stack_ty* testing_stk, int* arr, size_t);
static void PrintStack(stack_ty* stk);
	
/*strings */
size_t Strlen(const char* str);
static void TestStrlen(void);


int Strcmp(const char* str1, const char* str2);
static void TestStrcmp(void);
static int SameSign(int a, int b);

char* Strcpy(char* dest, const char* src);
static void StrcpyWrapped(char* dest, const char* src);
static void TestStrcpy();

char* Strcat(char* cat_to, const char* cat_frm);
static void TestStrcat();
void StrcatWrapped(char* cat_to, const char* cat_frm);


char* Strstr(char* search_str, const char* sub_str);
static void TestStrstr();
/*----------------------------------------------------------------------------*/
int main()
{
    TestFib();
    TestFlip();
    TestSortedStack();
    TestStrlen();
    TestStrcmp();
    TestStrcpy();
    TestStrcat();
    TestStrstr();
    return (0);
}

/*------------------------ implementations -----------------------------------*/
int Fibonacci(int x)
{
    if(0 > x)
    {
        return -1; /*not defined*/
    }
    if(1 == x || 0 == x)
    {
        return x;
    }
    
    return (Fibonacci(x-1) + Fibonacci(x-2));
}
/*----------------------------------------------------------------------------*/
node_ty* FlipList(node_ty* node)
{
    node_ty* new_head = NULL;
    
    if(NULL == node || NULL == node->next)
    {
        return (node);
    }
    /* flip rest of the list starting from second node_ty*/
    new_head = FlipList(node->next);
    /* place first node as the new tail*/
    node->next->next = node;
    node->next = NULL;
    
    return (new_head);
}
/*----------------------------------------------------------------------------*/
void SortStack(stack_ty *s)
{
    int x = 0;
    if(StackIsEmpty(s))
    {
    return;
    }
    x = *(int*)StackPeek(s);
    StackPop(s);
    SortStack(s);
    InsertSorted(s,x);
}


/*----------------------------------------------------------------------------*/
size_t Strlen(const char* str)
{
    if(NULL == str || '\0' == *str)
    {
        return (0);
    }
    return (1 + Strlen(++str)); 
}
/*----------------------------------------------------------------------------*/
int Strcmp(const char* str1, const char* str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    if ('\0' == *str1 || *str1 != *str2)
    {
        return (unsigned char)*str1 - (unsigned char)*str2;
    }

    return Strcmp(str1 + 1, str2 + 1);
}
/*----------------------------------------------------------------------------*/
char* Strcpy(char* dest, const char* src)
{
    char* dest_iter = dest;
    
    assert(dest != NULL);
    assert(src != NULL);
    
    StrcpyWrapped(dest_iter, src);
    
    return dest;
}

static void StrcpyWrapped(char* dest, const char* src)
{
    if('\0' == *src)
    {
        *dest = '\0';
        return;
    }
    *dest = *src;
    ++dest;
    ++src;
    StrcpyWrapped(dest, src);
}
/*----------------------------------------------------------------------------*/
char* Strcat(char* cat_to, const char* cat_frm)
{
	char* cat_to_iter = cat_to;
	
	assert(cat_to != NULL);
	assert(cat_frm != NULL);
	
	StrcatWrapped(cat_to_iter, cat_frm);
	
	return cat_to;
}


void StrcatWrapped(char* cat_to, const char* cat_frm)
{
    if (*cat_to != '\0')
    {
        StrcatWrapped(cat_to + 1, cat_frm);
        return;
    }
    if (*cat_frm == '\0')
    {
        *cat_to = '\0';  
        return;
    }
    *cat_to = *cat_frm;
    StrcatWrapped(cat_to + 1, cat_frm + 1);

}


/*----------------------------------------------------------------------------*/
char* Strstr(char* search_str, const char* sub_str)
{
    assert(search_str != NULL);
    assert(sub_str != NULL);
    
    if (*sub_str == '\0')  
    {
        return search_str;
    }
    
    if (*search_str == '\0')  
    {
        return NULL;
    }
    
    if (strncmp(search_str, sub_str, strlen(sub_str)) == 0)  
    {
        return search_str;
    }
    
    return Strstr(search_str + 1, sub_str);  
}

/*---------------------------Testing functions -------------------------------*/
static void TestFib()
{
    int test_array[] = {0, 1, 2, 5, 18 ,29 ,18};
    size_t arr_size = SIZEOF_ARR(test_array);
    size_t i = 0;
    
    printf("\t------------ testing fibonacci ------------\n");
    for(i = 0 ; i < arr_size ; i++)
    {
        printf("fib[%d] = %d\n", test_array[i], Fibonacci(test_array[i]));
    }
}
/*----------------------------------------------------------------------------*/
static void TestFlip()
{
	node_ty* head = NULL;
	int arr[DATA_ARR_SIZE] = {0};

    printf("\t------------ testing flip ------------\n");
	GenereateData(arr, DATA_ARR_SIZE);
	head = GenerateListFrmArr(head, arr, DATA_ARR_SIZE);
	printf("flip:\n");
	printf("Original list: ");
	PrintList(head);
	head = FlipList(head);
	printf("Flipped list: ");
	PrintList(head);
	FreeList(head);
}
/*----------------------------------------------------------------------------*/
static void TestStrlen()
{
    char* strings[] = {"","hello world","tomas","roza roza rozaaa"};
    size_t arr_size = SIZEOF_ARR(strings);
    size_t i = 0;
    
    printf("\t------------ testing strlen ------------\n");
    for(i = 0 ; i < arr_size ; i++)
    {
        if(Strlen(strings[i]) != strlen(strings[i]))
        {
            printf("failed at string %s\n", strings[i]);
        }
        else
        {
            printf("[PASS] \"%s\"\n", strings[i]);
        }
    }
}
/*----------------------------------------------------------------------------*/
static void TestStrcmp(void)
{
    char* strings1[] = {"","hello world","tomas","roza roza rozaaa",""};
    char* strings2[] = {" ","hellO worlD","tomeR", "la rozalia","P"};
    size_t arr_size = SIZEOF_ARR(strings1);
    size_t i = 0;
    int lib_res = 0;
    int rec_res = 0;
    
    printf("\t------------ testing strcmp ------------\n");
    for(i = 0 ; i < arr_size ; i++)
    {
        rec_res = Strcmp(strings1[i], strings2[i]);
        lib_res = strcmp(strings1[i], strings2[i]);
        if(!SameSign(lib_res, rec_res))
        {
            printf("[FAIL] \"%s\" and \"%s\", rec res is %d lib res is %d \n", strings1[i], strings2[i], rec_res, lib_res);
        }
        else
        {
            printf("[PASS] \"%s\" vs \"%s\"\n", strings1[i], strings2[i]);
        }
    }
}
/*----------------------------------------------------------------------------*/
static void TestStrcpy()
{
    char dest1[MAX_LEN];
    char dest2[MAX_LEN];
    const char* src[] = {"hello", "world", "Infinty Labs R&D", "Rina", "Erik",
                         "workshop 3!!@@@&&&", "", "a", "ab"};
    size_t arr_size = SIZEOF_ARR(src);
    size_t i = 0;
    char* lib_res;
    char* rec_res;
    
    printf("\t------------ testing Strcpy ------------\n");
    for(i = 0; i < arr_size; i++)
{
    dest1[0] = '\0';
    dest2[0] = '\0';

    rec_res = Strcpy(dest1, src[i]);
    lib_res = strcpy(dest2, src[i]);

    if(0 != Strcmp(rec_res, lib_res))
    {
        printf("[FAIL] recursion result is %s whereas library result is %s\n",
               rec_res, lib_res);
    }
    else
    {
        printf("[PASS] %s\n", rec_res);
    }
}

}

/*expand later to array of tests*/
static void TestStrcat()
{
    char dest1[MAX_LEN];
    char dest2[MAX_LEN];

    const char* base = "hello";
    const char* add  = "world";

    char* lib_res;
    char* rec_res;

    printf("\t------------ testing Strcat ------------\n");
    
	memset(dest1, 0, MAX_LEN);
	memset(dest2, 0, MAX_LEN);

    strcpy(dest1, base);
    strcpy(dest2, base);

    rec_res = Strcat(dest1, add);
    lib_res = strcat(dest2, add);

    if(0 != Strcmp(rec_res, lib_res))
    {
        printf("[FAIL] recursion result is %s whereas library result is %s\n",
                   rec_res, lib_res);
    }
    else
    {
        printf("[PASS] %s\n", rec_res);
    }
}

static void TestStrstr()
{
    char* str1[] = {"hello world","Infinty Labs R&D","aaaaaa","abcabcabc","no match here","","edge case","abc","abc",""};
    char* str2[] = {"world","Labs","aaa","abcabc","zzz","","edge","abc","","x"};

    size_t arr_size = SIZEOF_ARR(str1);
    size_t i = 0;
    char* rec_res;
    char* lib_res;

    printf("\t------------ testing Strstr ------------\n");

    for(i = 0; i < arr_size; ++i)
    {
        rec_res = Strstr(str1[i], str2[i]);
        lib_res = strstr(str1[i], str2[i]);

        if(rec_res != lib_res)
        {
            printf(" - FAILED (my=%p, lib=%p)\n", (void*)rec_res, (void*)lib_res);
        }
        else
        {
        	printf("[PASSED]\n");
        }

    }
}



/*----------------------------------------------------------------------------*/
static void TestSortedStack()
{
    stack_ty* testing_stk = StackCreate(DATA_ARR_SIZE ,sizeof(int));
    int arr[DATA_ARR_SIZE] = {0};
    
    printf("\t------------ testing sort stack ------------\n");
	GenereateData(arr, DATA_ARR_SIZE);
	GenerateStkFrmArr(testing_stk, arr, DATA_ARR_SIZE);
	SortStack(testing_stk);
	PrintStack(testing_stk);
	StackDestroy(testing_stk);
}
/*---------------------- aux functions ----------------------------------------*/
static void PrintList(node_ty* head) 
{
    node_ty* tmp = head;
    while (NULL != tmp) {
        printf("%d -> ",*(int*) tmp->data);
        tmp = tmp->next;
    }
    printf("NULL\n");
}

static void PrintStack(stack_ty* stk) 
{
    while (!StackIsEmpty(stk))
     {
        printf("|\t%d\t|\n",*(int*)StackPeek(stk));
        StackPop(stk);
    }
    printf("\nDONE!\n");
}

static void Push(node_ty** head_ref, int* new_data)
 {
    node_ty* new_node = (node_ty*)malloc(sizeof(node_ty));
    new_node -> data = new_data;
    new_node -> next = (*head_ref);
    (*head_ref) = new_node;
}

static void GenereateData(int* arr, size_t arr_size)
{
    size_t i = 0;
     
    /* intialize data's array */
    for(i = 0 ; i < arr_size ; ++i)
    {
    	arr[i] = pow(-1,i)*(rand()%MAX_VAL);
    
    }
}

static node_ty* GenerateListFrmArr(node_ty* head, int* arr, size_t arr_size)
{
 	 size_t i = 0;
 	 
  	for(i = 0 ; i < arr_size ; ++i)
  	{
		Push(&head, &arr[i]);
  	}
   	return head;
}

static void FreeList(node_ty* head)
{
	node_ty* tmp = head;
	while(NULL != head)
	{
		tmp = head -> next;
		free(head);
		head = tmp;
	}
}

static void InsertSorted(stack_ty* s, int x)
{
    int tmp = 0;
    if (StackIsEmpty(s) || *(int*)StackPeek(s) <= x)
    {
        StackPush(s, &x);
        return;
    }

    tmp = *(int*)StackPeek(s);
    StackPop(s);
    InsertSorted(s, x);
    StackPush(s, &tmp);
}

void GenerateStkFrmArr(stack_ty* testing_stk, int* arr, size_t arr_size)
{
    size_t i = 0;
    
    for(i = 0 ; i < arr_size ; i++)
    {
        StackPush(testing_stk, &arr[i]);
    }
}


static int SameSign(int a, int b)
{
    return (a == 0 && b == 0) ||
           (a < 0 && b < 0) ||
           (a > 0 && b > 0);
}

