#include <stdio.h>    /* printf(), fopen(), fclose() */
#include <string.h>   /* strlen() , strncmp() */
#include <stdlib.h>  	/* malloc(),free() */

/* macros */
/* macro to silent an argument (to prevent unused parameter warning) */
#define UNUSED(x) (void)(x)
/* macro that runs the expression (function call) and in case the return_status changed (not SUCCESS anymore) then return it (like a fail)*/
/* also in case the user requested to remove the file, exit the program the main using this macro, gets out of the program*/
/* with the proper return value */
/* using this macro we return status from the main */
#define CHECK_AND_RETURN(expr)\
    (expr);\
    if (return_status != SUCCESS || return_status == EXIT_FILE || return_status == REMOVED_FILE )\
        return return_status;

/* since handlers identifiers has similar pattern i made a macro to prevent code duplications */    
/* this function reads the global variable holding the input string from user, and compares it to the special input syntax */
/* it returns TRUE if it was the special input, otherwise FALSE */
#define HANDLER_IDENTIFIER(func_name, STR)\
static size_t func_name() \
{  \
    size_t n = strlen(STR);\
    if (strncmp(curr_str_frm_input, STR, n) == 0)\
    {\
        return TRUE; \
    }\
    return FALSE; \
}

/* floating values */
#define MAX_LEN 100 
#define HANDLERS_SIZE 5
#define PRINT_ME_SIZE 10
/* special inputs strings */
#define REMOVE "-remove"
#define COUNT "-count"
#define EXIT "-exit"
#define PREPEND "<"
#define NOTHING ""
/* true and false */
#define TRUE 0
#define FALSE 1

/* error types numerations */
typedef enum return_status
{
    SUCCESS = 0,
    FAILED_BASH_OPERATION,
    FAILED_FGETS,
    FAILED_REMOVE_FILE,
    FAILED_OPEN_FILE,
    FAILED_ALLOC,
    FAILED_WRITE_FILE,
    FAILED_READ_FILE,
    REMOVED_FILE,
    EXIT_FILE,
    FAILED_CLOSING_FILE,
    METHOD_PICKED,
    METHOD_NOT_PICKED
} return_status_t;

/* structure of a handler */
typedef struct handler {
  char* str; 
  size_t (*can_handle)(); 
  void (*handle)(); 
} handler_t;

typedef struct print_me {
    int num;
    void (*func_ptr)(int);
} print_me_t;

/* declarations on functions */
static void PrepareTheTerminal();  
static void WelcomeMessage();       
static void ReadInput();      
static void IdentifyAndCallHandler();
static size_t IsRemove(void);
static size_t IsCount(void);
static size_t IsExit(void);
static size_t IsPrepend(void);
static size_t IsAppend(void);
static void Remove(void);
static void Count(void);
static void Exit(void);
static void Prepend(void);
static void Append(void);

static void InitializeAndPrintMe(void);
static void Print(int x);

/* global static variables */
static return_status_t return_status = SUCCESS;
static char* file_name;
static char curr_str_frm_input[MAX_LEN];

static handler_t handlers[HANDLERS_SIZE] = { {REMOVE, IsRemove,Remove}, {COUNT,IsCount,Count}, {EXIT, IsExit,Exit},{PREPEND, IsPrepend,Prepend},
                                           {NOTHING,IsAppend,Append}};

static print_me_t arr[PRINT_ME_SIZE];

int main(int argc , char* argv[])
{
    file_name = argv[1];
    UNUSED(argc);

    CHECK_AND_RETURN(PrepareTheTerminal());
    InitializeAndPrintMe();
    WelcomeMessage();
  
    while (1)
    {
        CHECK_AND_RETURN(ReadInput());
        CHECK_AND_RETURN(IdentifyAndCallHandler());
    }
}

static void WelcomeMessage()
{
    printf("\t--------------WELCOME TO YOUR LOGGER--------------\n");
    printf("\t\tlogging into file :  %s\n", file_name);
    printf("GO AHEAD:\n");
}

static void PrepareTheTerminal(void)
{
    if (system("clear") != SUCCESS)
    {
        return_status = FAILED_BASH_OPERATION;
    }
}

static void ReadInput(void)
{
    if (fgets(curr_str_frm_input, MAX_LEN, stdin) == NULL)
    {
        return_status = FAILED_FGETS;
    }
}

static void IdentifyAndCallHandler(void)
{
    size_t i;

    for (i = 0 ; i < HANDLERS_SIZE ; i++)
    {
        if (TRUE == handlers[i].can_handle())
        {
            handlers[i].handle();
            return;
        }
    }
}

HANDLER_IDENTIFIER(IsRemove, REMOVE)
HANDLER_IDENTIFIER(IsCount,  COUNT)
HANDLER_IDENTIFIER(IsExit,   EXIT)

static size_t IsPrepend()
{
    if (curr_str_frm_input[0] == '<')
    {
        return TRUE;
    }
    return FALSE;
}

static size_t IsAppend()
{
    return TRUE;
}

static void Remove(void)
{
    if (SUCCESS != remove(file_name))
    {
        return_status = FAILED_REMOVE_FILE;
        return;
    }

    return_status = REMOVED_FILE;
}

static void Count(void)
{
    FILE* fopen_ret_val = fopen(file_name, "r");
    int c;
    int count = 0;

    if (!fopen_ret_val)
    {
        return_status = FAILED_OPEN_FILE;
        return;
    }

    while ((c = fgetc(fopen_ret_val)) != EOF)
    {
        if (c == '\n') count++;
    }

    if (!fclose(fopen_ret_val))
    {
        return_status = FAILED_CLOSING_FILE;
    }

    printf("%d\n", count);
    return_status = SUCCESS;
}

static void Exit(void)
{
    return_status = EXIT_FILE;
}

static void Prepend(void)
{
    FILE* fopen_ret_val;
    char* buffer;
    size_t size;
    char* newtext = curr_str_frm_input + 1;

    fopen_ret_val = fopen(file_name, "r");
    if (!fopen_ret_val)
    {
        return_status = FAILED_OPEN_FILE;
        return;
    }

    fseek(fopen_ret_val, 0, SEEK_END);
    size = ftell(fopen_ret_val);
    fseek(fopen_ret_val, 0, SEEK_SET);

    buffer = (char*)malloc(size + 1);
    if (!buffer)
    {
        fclose(fopen_ret_val);
        return_status = FAILED_ALLOC;
        return;
    }

    if (!fread(buffer, 1, size, fopen_ret_val))
    {
        return_status = FAILED_READ_FILE;
        return;
    }

    buffer[size] = '\0';
    fclose(fopen_ret_val);

    fopen_ret_val = fopen(file_name, "w");
    if (!fopen_ret_val)
    {
        free(buffer);
        return_status = FAILED_OPEN_FILE;
        return;
    }

    fputs(newtext, fopen_ret_val);
    fputs(buffer, fopen_ret_val);

    fclose(fopen_ret_val);
    free(buffer);
    return_status = SUCCESS;
}

static void Append(void)
{
    FILE* fopen_ret_val = fopen(file_name, "a");

    if (!fopen_ret_val)
    {
        return_status = FAILED_OPEN_FILE;
        return;
    }

    if (fputs(curr_str_frm_input, fopen_ret_val) == EOF)
    {
        fclose(fopen_ret_val);
        return_status = FAILED_WRITE_FILE;
        return;
    }

    if (!fclose(fopen_ret_val))
    {
        return_status = FAILED_CLOSING_FILE;
    }

    return_status = SUCCESS;
}

static void Print(int x)
{
    printf("Value: %d\n", x);
}

static void InitializeAndPrintMe(void)
{
    size_t i = 0;

    for (i = 0; i < PRINT_ME_SIZE; i++)
    {
        arr[i].num = i;
        arr[i].func_ptr = Print;
    }

    for (i = 0; i < PRINT_ME_SIZE; i++)
    {
        arr[i].func_ptr(arr[i].num);
    }
}

