/******************************************
submitter : rozaline kozly
reviewer  : shir 
version   : clean + fixed
worksheet : 8 (structs)
******************************************/

#include <stdio.h>      /* printf */
#include <stdlib.h>     /* malloc, free, realloc */
#include <string.h>     /* strlen, strcpy, strcat */
#include <assert.h>     /* assert */

#define MAX_LEN 80

typedef enum
{
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING
} ElementType;

typedef struct
{
    void *data;

    void (*add)(void *data, int n);
    void (*print)(void *data);
    void (*cleanup)(void *data);

} element_ty;

/**********************************************
   INT IMPLEMENTATION
**********************************************/
void IntAdd(void *data, int n)
{
    *(int *)data += n;
}

void IntPrint(void *data)
{
    printf("%d", *(int *)data);
}

void IntCleanup(void *data)
{
    /* fixed-size → just free memory */
    free(data);
}

/**********************************************
   FLOAT IMPLEMENTATION
**********************************************/
void FloatAdd(void *data, int n)
{
    *(float *)data += (float)n;
}

void FloatPrint(void *data)
{
    printf("%f", *(float *)data);
}

void FloatCleanup(void *data)
{
    free(data);
}

/**********************************************
   STRING IMPLEMENTATION  (realloc allowed)
**********************************************/
void StringAdd(void *data, int n)
{
    char buf[MAX_LEN];
    size_t old_len = 0;
    size_t add_len = 0;
    char *new_data;

    sprintf(buf, "%d", n);
    old_len = strlen((char *)data);
    add_len = strlen(buf);
    new_data = realloc(data, old_len + add_len + 1);
    assert(new_data != NULL);
    printf("here");
    strcat(new_data, buf); 
    data = new_data; /* data has the new size */
   strcat(*(char**)data, buf); /* concatenate the strings */
  /*  *(void **)data = new_data; */
}

void StringPrint(void *data)
{
    printf("%s", (char *)data);
}

void StringCleanup(void *data)
{
    free(data);
}

/**********************************************
   ELEMENT CONSTRUCTOR
**********************************************/
element_ty CreateElement(ElementType type, const void *value)
{
    element_ty e;

    switch (type)
    {
        case TYPE_INT:
        {
            e.data = malloc(sizeof(int));
            assert(e.data != NULL);

            *(int *)e.data = *(const int *)value;

            e.add = IntAdd;
            e.print = IntPrint;
            e.cleanup = IntCleanup;

            break;
        }

        case TYPE_FLOAT:
        {
            e.data = malloc(sizeof(float));
            assert(e.data != NULL);

            *(float *)e.data = *(const float *)value;

            e.add = FloatAdd;
            e.print = FloatPrint;
            e.cleanup = FloatCleanup;

            break;
        }

        case TYPE_STRING:
        {
            const char *src = (const char *)value;
            e.data = malloc(strlen(src) + 1);
            assert(e.data != NULL);

            strcpy((char *)e.data, src);

            e.add = StringAdd;
            e.print = StringPrint;
            e.cleanup = StringCleanup;

            break;
        }
    }

    return e;
}

/**********************************************
   TEST
**********************************************/
int main()
{
    int i_val = 3;
    float f_val = 2.5f;

    element_ty arr[3];

    arr[0] = CreateElement(TYPE_INT, &i_val);
    arr[1] = CreateElement(TYPE_FLOAT, &f_val);
    arr[2] = CreateElement(TYPE_STRING, "hi");

    /* print initial */
    arr[0].print(arr[0].data); printf("\n");
    arr[1].print(arr[1].data); printf("\n");
    arr[2].print(arr[2].data); printf("\n");

    /* add 10 */
    arr[0].add(arr[0].data, 10);
    arr[1].add(arr[1].data, 10);

    {
        /* string special case: add needs pointer-to-pointer */
        void *tmp = arr[2].data;
        StringAdd(&tmp, 10);
        arr[2].data = tmp;
    }

    /* print after */
    arr[0].print(arr[0].data); printf("\n");
    arr[1].print(arr[1].data); printf("\n");
    arr[2].print(arr[2].data); printf("\n");

    /* cleanup */
    arr[0].cleanup(arr[0].data);
    arr[1].cleanup(arr[1].data);
    arr[2].cleanup(arr[2].data);

    return 0;
}

