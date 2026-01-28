/*
submitter: rozaline kozly
reviewer: Tomer
------------------------------------------------------------------------------*/
#include <stdio.h>		/*printf()*/
#include <stdlib.h>		/*malloc(), free()*/
#include <math.h>		/*pow(), to randomify data*/
#include <string.h>		/*strlen(), strcpy(), strcmp(), strstr(), strcat()*/
/*-----------------------------------------------------------------------------*/
#include "recursion.h"		/*API*/
#include "stack.h"			/*API*/
/*-----------------------------------------------------------------------------*/
#define SIZEOF_ARR(arr)					(sizeof(arr)/sizeof(arr[0]))
#define DATA_ARR_SIZE					10
#define MAX_VAL							100
#define MAX_LEN                         200
/*-----------------------------------------------------------------------------*/
static void TestFib(void);
static void TestFlip(void);
static void TestSortedStack();
static void TestStrlen(void);
static void TestStrcmp(void);
static void TestStrcpy();
static void TestStrcat();
static void TestStrstr();
/*--------------------------aux functions -------------------------------------*/
static void PrintList(node_ty*); 
static void Push(node_ty**, int*);
static void GenereateData(int* arr, size_t arr_size);
static node_ty* GenerateListFrmArr(node_ty* head, int* arr, size_t arr_size);
static void FreeList(node_ty* head);
void GenerateStkFrmArr(stack_ty* testing_stk, int* arr, size_t);
static void PrintStack(stack_ty* stk);
static int SameSign(int a, int b);
/*-----------------------------------------------------------------------------*/
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
/*-----------------------------------------------------------------------------*/
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
/*-----------------------------------------------------------------------------*/
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
/*-----------------------------------------------------------------------------*/
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
/*-----------------------------------------------------------------------------*/
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
        /* in realease mode the compiler applies optimization, and the value might 
        	not be the same, that's why i only check the sign (wheras in debug mode 
        	we get same value)*/
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
/*-----------------------------------------------------------------------------*/
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
/*-----------------------------------------------------------------------------*/
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
/*-----------------------------------------------------------------------------*/
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
            printf("[FAIL] (my=%p, lib=%p)\n", (void*)rec_res, (void*)lib_res);
        }
        else
        {
        	printf("[PASS] search %s in %s\n", str2[i], str1[i]);
        }

    }
}
/*-----------------------------------------------------------------------------*/
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
/*-----------------------------------------------------------------------------*/
static void PrintList(node_ty* head) 
{
    node_ty* tmp = head;
    while (NULL != tmp) {
        printf("%d -> ",*(int*) tmp->data);
        tmp = tmp->next;
    }
    printf("NULL\n");
}
/*-----------------------------------------------------------------------------*/
static void PrintStack(stack_ty* stk) 
{
    while (!StackIsEmpty(stk))
     {
        printf("|\t%d\t|\n",*(int*)StackPeek(stk));
        StackPop(stk);
    }
    printf("\nDONE!\n");
}
/*-----------------------------------------------------------------------------*/
static void Push(node_ty** head_ref, int* new_data)
 {
    node_ty* new_node = (node_ty*)malloc(sizeof(node_ty));
    new_node -> data = new_data;
    new_node -> next = (*head_ref);
    (*head_ref) = new_node;
}
/*-----------------------------------------------------------------------------*/
static void GenereateData(int* arr, size_t arr_size)
{
    size_t i = 0;
     
    for(i = 0 ; i < arr_size ; ++i)
    {
    	arr[i] = pow(-1,i)*(rand()%MAX_VAL);
    
    }
}
/*-----------------------------------------------------------------------------*/
static node_ty* GenerateListFrmArr(node_ty* head, int* arr, size_t arr_size)
{
 	 size_t i = 0;
 	 
  	for(i = 0 ; i < arr_size ; ++i)
  	{
		Push(&head, &arr[i]);
  	}
   	return head;
}
/*-----------------------------------------------------------------------------*/
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
/*-----------------------------------------------------------------------------*/
void GenerateStkFrmArr(stack_ty* testing_stk, int* arr, size_t arr_size)
{
    size_t i = 0;
    
    for(i = 0 ; i < arr_size ; i++)
    {
        StackPush(testing_stk, &arr[i]);
    }
}
/*-----------------------------------------------------------------------------*/
static int SameSign(int a, int b)
{
    return (a == 0 && b == 0) ||
           (a < 0 && b < 0) ||
           (a > 0 && b > 0);
}
