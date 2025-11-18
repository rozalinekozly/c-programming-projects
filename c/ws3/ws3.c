#include <stdio.h> /* printf() */
#include <string.h> /* strlen() */
#include <stdlib.h> /* malloc and free and size_t type */
#include <ctype.h> /* tolower */
#include "ws3.h" /* define COLS*/



/*colors used in printing */		
#define RED           "\033[1;91m"
#define WHITE         "\033[1;97m"
#define CYAN          "\033[1;96m"
#define GREEN         "\033[1;92m"
#define YELLOW        "\033[1;93m"


/* functions declarations */
void RowSum2D(int arr[][COLS], size_t rows, int res[]);

void PrintEnvVarInLowerCase(char *envp[]);
size_t GetEnvSize(char *envp[]);
char **AllocateEnvCopy(size_t size);
char *ToLowerString(const char *src);
char **CloneEnvToLower(char *envp[]);
void PrintEnv(char *envp[]);
void FreeEnv(char *envp[]);

void RowSum2D(int arr[][COLS], size_t rows, int res[])
{
    size_t i = 0;
    size_t j = 0;
  

    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < COLS; ++j)
        {
            res[i] += arr[i][j];
        }
          
    }
}


size_t JosephusCircularArray(size_t n)
{
    size_t* arr = NULL;
    size_t alive = n;
    size_t i = 0; /* current soldier holding sword */
    size_t k; /* loop iterator */
    size_t victim = 0;
    
    if (0 == n)
    {
        return 0;
    }

    arr = (size_t*)malloc(n * sizeof(size_t));
    if (!arr)
    {
        return -1;
    }

    /* initialize all alive */
    for (k = 0; k < n; k++)
    {
        arr[k] = 1;
    }

    while (alive > 1)
    {
        victim = (i + 1) % n;

        /* find next alive (victim) */
        while (arr[victim] == 0)
        {
            victim = (victim + 1) % n;
        }

        arr[victim] = 0;   /* kill victim */
        alive--;

        /* new sword holder: next alive after victim */
        i = (victim + 1) % n;
        while (0 == arr[i])
        {
            i = (i + 1) % n;
        }
    }

    /* find the last alive (should be i already) */
    free(arr);
    return i;
}



void PrintDataTypeSizes(void)
{
    printf(WHITE"\tchar: %lu bytes\n", (unsigned long)sizeof(char));
    printf("\tunsigned char: %lu bytes\n", (unsigned long)sizeof(unsigned char));
    printf("\tsigned char: %lu bytes\n", (unsigned long)sizeof(signed char));

    printf("\tshort: %lu bytes\n", (unsigned long)sizeof(short));
    printf("\tunsigned short: %lu bytes\n", (unsigned long)sizeof(unsigned short));

    printf("\tint: %lu bytes\n", (unsigned long)sizeof(int));
    printf("\tunsigned int: %lu bytes\n", (unsigned long)sizeof(unsigned int));

    printf("\tlong: %lu bytes\n", (unsigned long)sizeof(long));
    printf("\tunsigned long: %lu bytes\n", (unsigned long)sizeof(unsigned long));

    printf("\tfloat: %lu bytes\n", (unsigned long)sizeof(float));
    printf("\tdouble: %lu bytes\n", (unsigned long)sizeof(double));

    /* Long double is supported in C90 */
    printf("\tlong double: %lu bytes\n", (unsigned long)sizeof(long double));

    printf("\tsize_t: %lu bytes\n", (unsigned long)sizeof(size_t));
    printf("\tptrdiff_t: %lu bytes\n", (unsigned long)sizeof(ptrdiff_t));
    printf("\tvoid*: %lu bytes\n", (unsigned long)sizeof(void *));
}


void PrintEnvVarInLowerCase(char *envp[])
{
    char** copy = NULL; /* array to hold lower case env vars*/

    copy = CloneEnvToLower(envp); /* create an array of strings , fill them with relevant strings (callee duty to free)*/

    if (NULL == copy)
    {
        printf(RED"Memory allocation failure in printEnv\n");
        return;
    }

    PrintEnv(copy); /* print strings */
    FreeEnv(copy); /* free malloced memory*/
}

char** CloneEnvToLower(char* envp[])
{
    size_t size = 0;
    char** copy = NULL;
    size_t i = 0;
    size_t j = 0;

    size = GetEnvSize(envp); /* size = number of env vars*/
    copy = AllocateEnvCopy(size); /* mallocs a pointer to pointer with sizeof size */
    /* check if malloc worked */
    if (NULL == copy)
    {
        return NULL;
    }

    for (i = 0 ; envp[i] != NULL ; i++)
    {
        copy[i] = ToLowerString(envp[i]); /* mallocs a string and puts the lower case string in it */

        /* if malloc failed - free everything! */
        if (NULL == copy[i])
        {
            for (j = 0; j < i; j++)
            {
                free(copy[j]);
            }
            free(copy);
            return NULL;
        }
    }

    copy[i] = NULL; /* add NULL to know it ended (for printing) */
    return copy;
}

/* this function returns number of env vars*/
size_t GetEnvSize(char* envp[])
{
    size_t size = 0;

    while (NULL != envp[size])
    {
        ++size;
    }

    return size + 1; /* null at the end */
}

/* malloc*/
char** AllocateEnvCopy(size_t size)
{
    return (char**)malloc(size * sizeof(char*));
}

/* function that creates a string that contains lowered case env vars */
char* ToLowerString(const char* src)
{
    size_t len = 0;
    char* dest = NULL;
    size_t i = 0;

   len = strlen(src);
    dest = (char*)malloc(len + 1); /* because string is const and cant be changed*/

    if (!dest)
    {
        return NULL;
    }

    for (i = 0; i < len; i++)
    {
      
        dest[i] = (char)tolower((unsigned char)src[i]);
    }

    dest[len] = '\0';

    return dest;
}



/* prints the array*/
void PrintEnv(char* lowered_envp[])
{
    size_t i = 0;
    while (lowered_envp[i] != NULL)
    {
        printf(WHITE"\t%s\n", lowered_envp[i]);
        i++;
    }
}
/*frees the array*/
void FreeEnv(char* envp[])
{
    size_t i = 0;
    while (NULL !=  envp[i])
    {
        free(envp[i]);
        i++;
    }

    free(envp);
}

