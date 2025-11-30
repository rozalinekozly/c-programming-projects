/***************************************
submitter : rozaline kozly
reviewer : shir 
version 2
worksheet 8 (struct)
branch ws8
****************************************/
#include <stdio.h>          /*  printf          */
#include <stdlib.h>         /* malloc,   free  */
#include <string.h>        /* strlen, strcat  */
#include <assert.h>       /* assert */
/* magic numbers */
#define MAX_LEN                   80

/* macros */
#define SIZE_OF_ARRAY(ARRAY)      ((sizeof(ARRAY) / (sizeof((ARRAY)[0])))

/* sizeof macros*/
#define SIZEOF_VAR(X)             ((char *)(&X + 1) - (char *)&X)   
#define SIZEOF_TYPE(T)            ((size_t)((T*)0 + 1) - (size_t)((T*)0))

/* max macros*/
#define MAX2(a, b)               (((a) > (b)) ? (a) : (b))
#define MAX3(a, b, c)            ((((a) > (b) && (a) > (c)) ? (a) : (MAX2((b), (c)))))

void TestMaxMacros();
void TestElement();
void TestSizeOfMacros();

typedef enum
{
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_STRING
} ElementType;

typedef struct
{
  void* data;
  void (*add)(void* data, int n);
  void (*print)(void* data);
  void (*cleanup)(void* data);
} element_ty;

/*********************************** int type functions   *************************************/
void IntAdd(void* data, int n)
{
  *(int*)data += n;
}

void IntPrint(void* data)
{
  printf("%d", *(int*)data);
}

void IntCleanup(void* data)
{
  free(data);
}

/*********************************** float type functions   *************************************/
void FloatAdd(void* data, int n)
{
  *(float*)data += (float)n;
}

void FloatPrint(void* data)
{
  printf("%f", *(float*)data);
}

void FloatCleanup(void* data)
{
  free(data);
}

/*********************************** string type functions   *************************************/
void StringAdd(void* data, int n)
{
  char buf[MAX_LEN] ; /* placement to add the integer as a string */
  size_t old_len = 0;
  size_t add_len = 0;
  char* new_data = NULL;
  
   sprintf(buf, "%d", n);
   old_len = strlen((char*)data);
   add_len = strlen(buf);
   new_data = realloc(data, old_len + add_len + 1); /* +1 for \0 */
   assert(NULL != new_data);
   data = new_data; /* data has the new size */
   strcat((char*)data, buf); /* concatenate the strings */
}

void StringPrint(void* data)
{
  printf("%s", (char*)data);
}

void StringCleanup(void* data)
{
  free(data);
}

/*********************************** element constructor  *************************************/
element_ty CreateElement(ElementType type, void* value) /* constructor for an element */
{
    element_ty e;
    e.data = NULL;

    switch(type) /* defines the relevant methods based on the instance's type*/
    {
      case (TYPE_INT):
      e.data = malloc(sizeof(int));
      *(int*)e.data = *(const int*)value;
      e.add = IntAdd;
      e.print = IntPrint;
      e.cleanup = IntCleanup;
      break;

      case (TYPE_FLOAT):
      e.data = malloc(sizeof(float));
      *(float*)e.data = *(const float*)value;
      e.add = FloatAdd;
      e.print = FloatPrint;
      e.cleanup = FloatCleanup;
      break;

      case (TYPE_STRING):
      {
      const char* src = (const char*)value;
      e.data = malloc(strlen(src) + 1);
      strcpy((char*)e.data, src);
      e.add = StringAdd;
      e.print = StringPrint;
      e.cleanup = StringCleanup;
      break;
      }
    }

return e;
}

int main()
{
    TestElement();
    TestMaxMacros();
    TestSizeOfMacros();
    
    return 0;
}

void TestElement()
{
    int i_int = 3;
    float f_float = 2.5;
    size_t i;
    
    element_ty elements[3];

    elements[0] = CreateElement(TYPE_INT, &i_int);
    elements[1] = CreateElement(TYPE_FLOAT, &f_float);
    elements[2] = CreateElement(TYPE_STRING, "hi");

   /* printing */
    for (i = 0; i < 3; i++)
    {
        elements[i].print(elements[i].data);
        printf("\n");
    }

    /* addition */
    for (i = 0; i < 3; i++)
    {
        elements[i].add(elements[i].data, 10);
    }
    
    /* printing after addition */
    for (i = 0; i < 3; i++)
    {
        elements[i].print(elements[i].data);
        printf("\n");
    }

    /* cleanup */
    for (i = 0; i < 3; i++)
    {
        elements[i].cleanup(elements[i].data);
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
    
    if( SIZEOF_VAR(i_tmp) != sizeof(i_tmp))
    {
        printf("FAILED at sizeof int var\n");
    }
     if( SIZEOF_VAR(f_tmp) != sizeof(f_tmp))
    {
        printf("FAILED at sizeof int var\n");
    }
     if( SIZEOF_VAR(s_tmp) != sizeof(s_tmp))
    {
        printf("FAILED at sizeof int var\n");
    }
     if( SIZEOF_TYPE(int) != sizeof(int))
    {
        printf("FAILED at sizeof int var\n");
    }
        if( SIZEOF_TYPE(element_ty) != sizeof(element_ty))
    {
        printf("FAILED at sizeof int var\n");
    }
}
