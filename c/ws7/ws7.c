/***************************************
submitter : rozaline kozly
reviewer : shir 
version 4
worksheet 8 (struct)
<<<<<<< HEAD
branch ws7 -> merged into main
****************************************/
#include <stdio.h> 		/*printf*/
#include <stdlib.h>		/* malloc, realloc, free */
#include <string.h>		/* strcpy, strlen */
#include <assert.h>		/* assert */	

/* magic numbers */
#define MAX_LEN                   80
#define TESTING_ARR_LEN            3  
/* macros */
#define SIZE_OF_ARRAY(ARRAY)      ((sizeof(ARRAY) / (sizeof((ARRAY)[0])))

/* sizeof macros*/
#define SIZEOF_VAR(X)             ((char *)(&X + 1) - (char *)&X)   
#define SIZEOF_TYPE(T)            ((size_t)((T*)0 + 1) - (size_t)((T*)0))

/* max macros*/
#define MAX2(a, b)               (((a) > (b)) ? (a) : (b))
#define MAX3(a, b, c)            ((((a) > (b) && (a) > (c)) ? (a) : (MAX2((b), (c)))))

/* identifier of element's data type (can be expanded and modified) */
typedef enum
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} type_ty;

typedef struct element
{
    void *data;                                /* overwritten for int/float and any other primitive type*/
    /* object's methods */
    void (*Add)(struct element *e, int n);    /* method that adds n to the element's data according to type's definition of additon */
    void (*Print)(struct element *e);         /* method that prints the element's data */
    void (*Cleanup)(struct element *e);       /* method that cleans-up the data in case of allocation has been needed */
} element_ty;


/*------- functions declarations -------*/
/* testing functions */
void TestMaxMacros();
void TestElement();
void TestSizeOfMacros();

/* functions */
/* element's methods */

/* int type fucntions */
static void AddInt(element_ty *e, int n);
static void PrintInt(element_ty *e);
static void CleanupInt(element_ty *e);

/* float type funcs */
static void AddFloat(element_ty *e, int n);
static void PrintFloat(element_ty *e);
static void CleanupFloat(element_ty *e);

/* string type functions */
static void AddString(element_ty *e, int n);
static void PrintString(element_ty *e);
static void CleanupString(element_ty *e);

/* element initializer (constructor) */
void ElementInit(element_ty *e, type_ty type, void *value);
void EmptyFunction();      /* an empty function that prints to the user that something wrong has happened in the way*/
int main()
{
   TestElement();
   TestMaxMacros();
   TestSizeOfMacros();
  
return 0;
}



/*
 element object
 it has 3 function operations : add, print, cleanup.
 in order to initialize  an instance of object element type 
 1- create an instance
 2- send a pointer to it with it's type (from the enum list) and a pointer to the  value to be inserted to
    the data field)
*/
void TestElement()
{
    element_ty arr[TESTING_ARR_LEN];
    int i_val = 5;
    float f_val = 3.5f;
    size_t i = 0;
    
    ElementInit(&arr[0], TYPE_INT, &i_val);
    ElementInit(&arr[1], TYPE_FLOAT, &f_val);
    ElementInit(&arr[2], TYPE_STRING, "hi");
    
    for(i = 0 ; i < TESTING_ARR_LEN ; i++)
    {
      arr[i].Print(&arr[i]);   
      arr[i].Add(&arr[i], 10);   
      arr[i].Print(&arr[i]);   
      arr[i].Cleanup(&arr[i]); 
    }
    
}

void TestMaxMacros()
{
    int a = -3;
    int b = 415;
    int c = 22;
    
    int expected_max_a_b = b;
    int expected_max_b_c = b;
    int expected_max_a_c = c;
    int expected_max_a_b_c = b;
    
    MAX2(a, b) == expected_max_a_b ? 1 : printf("FAILED \n");
    MAX2(b, c) == expected_max_b_c ? 1 : printf("FAILED\n");
    MAX2(a, c) == expected_max_a_c ? 1 : printf("FAILED\n");
    MAX3(a, b, c) == expected_max_a_b_c ? 1 : printf("FAILED\n");

  return;
}

void TestSizeOfMacros()
{
    float f_tmp;
    size_t s_tmp;
    int i_tmp;
    
    if (SIZEOF_VAR(i_tmp) != sizeof(i_tmp))
    {
        printf("FAILED at sizeof int var\n");
    }
     if (SIZEOF_VAR(f_tmp) != sizeof(f_tmp))
    {
        printf("FAILED at sizeof int var\n");
    }
     if (SIZEOF_VAR(s_tmp) != sizeof(s_tmp))
    {
        printf("FAILED at sizeof int var\n");
    }
     if (SIZEOF_TYPE(int) != sizeof(int))
    {
        printf("FAILED at sizeof int var\n");
    }
    if (SIZEOF_TYPE(element_ty) != sizeof(element_ty))
    {
        printf("FAILED at sizeof int var\n");
    }
}



/*-INT_TYPE functions -*/

static void AddInt(element_ty *e, int n)
{
  *(int*)e += n;
}

static void PrintInt(element_ty *e)
{
  printf("%d\n", *(int*)e);
}

static void CleanupInt(element_ty *e)
{
  (void)e; /* empty function since int is a primitive type  */
}

/*- FLOAT_TYPE functions -*/
static void AddFloat(element_ty *e, int n)
{
  *(float*)e += (float)n;
}

static void PrintFloat(element_ty *e)
{
  printf("%f\n", *(float*)e);
}

static void CleanupFloat(element_ty *e)
{
  (void)e;
}

/*- STRING_TYPE functions -*/
static void AddString(element_ty *e, int n)
{
  char buf[MAX_LEN];
  char *newp;
  sprintf(buf, "%d", n);

  newp = (void*)realloc(e->data, strlen(e->data) + strlen(buf) + 1);
  if (NULL == newp)
  {
      e -> Add = EmptyFunction;
      e -> Print = EmptyFunction;
      e -> Cleanup = EmptyFunction;
      return; 
  }
  
  e -> data = newp;
  strcat(e -> data, buf);
}

static void PrintString(element_ty *e)
{
  printf("%s\n", (char*)e->data);
}

static void CleanupString(element_ty *e)
{
  free(e->data);
}

/*- initialize element wrapper  */
void ElementInit(element_ty *e, type_ty type, void *value)
{
  if (type == TYPE_INT)
  {
    *(int*)e = *(int*)value;
    e -> Add = AddInt;
    e -> Print = PrintInt;
    e -> Cleanup = CleanupInt;
    return;
  }

if (type == TYPE_FLOAT)
  {
    *(float*)e = *(float*)value;
    e -> Add = AddFloat;
    e ->Print = PrintFloat;
    e -> Cleanup = CleanupFloat;
    return;
  }

if (type == TYPE_STRING)
  {
 
    e -> data = malloc(strlen((char*)value) + 1);
    if(NULL == e -> data)
    {
      e -> Add = EmptyFunction;
      e -> Print = EmptyFunction;
      e -> Cleanup = EmptyFunction;
      return;
    }
    strcpy(e -> data, ((char*)value));

    e -> Add = AddString;
    e -> Print = PrintString;
    e -> Cleanup = CleanupString;
    }
}
void EmptyFunction()
{
    printf("\n something wrong happened in the way, botched element\n");
    return;
}

