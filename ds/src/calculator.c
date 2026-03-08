#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"
#include "calculator.h"

#define ASCII_SIZE 128


/* States */

typedef enum state
{
    EXPECTED_OPERAND = 0,
    EXPECTED_OPERATOR = 1,
    END_STATE = 2
} state_ty;


/* Token Types */

typedef enum token_type
{
    OPERAND = 0,
    OPERATOR = 1,
    OPEN_PAREN = 2,
    CLOSE_PAREN = 3,
    END_TOKEN = 4,
    INVALID = 5,
    NUM_TOKEN_TYPES = 6
} token_type_ty;


/* Token */

typedef struct token
{
    token_type_ty type;
    union
    {
        double num;
        char op;
    } data;
} token_ty;


/* Operator Info */

typedef calc_status_ty (*calc_func)(double, double, double*);

typedef struct operator
{
    char symbol;
    int precedence;
    calc_func action;
} operator_ty;


/* Handler Function Pointer */

typedef calc_status_ty (*handler_ty)(token_ty* token, char** expr, stack_ty* opd_stack,
                                     stack_ty* opt_stack, state_ty* state);


/* Global Tables */
static operator_ty lut_g[ASCII_SIZE];
static handler_ty fsm_g[NUM_TOKEN_TYPES][3]; /* 3 states */


/* Forward Declarations */

/* Initialization */
static void InitLut(void);
static void InitFsm(void);

/* Tokenizer */
static token_ty GetNextToken(char** expr);

/* Handlers */
static calc_status_ty HandleOperand(token_ty* token, char** expr,
                                     stack_ty* opd_stack, stack_ty* opt_stack,
                                     state_ty* state);
static calc_status_ty HandleOperator(token_ty* token,
                                      char** expr,
                                      stack_ty* opd_stack,
                                      stack_ty* opt_stack,
                                      state_ty* state);
static calc_status_ty HandleUnaryOperator(token_ty* token,
                                           char** expr,
                                           stack_ty* opd_stack,
                                           stack_ty* opt_stack,
                                           state_ty* state);
static calc_status_ty HandleOpenParen(token_ty* token,
                                       char** expr,
                                       stack_ty* opd_stack,
                                       stack_ty* opt_stack,
                                       state_ty* state);
static calc_status_ty HandleCloseParen(token_ty* token,
                                        char** expr,
                                        stack_ty* opd_stack,
                                        stack_ty* opt_stack,
                                        state_ty* state);
static calc_status_ty HandleEnd(token_ty* token,
                                 char** expr,
                                 stack_ty* opd_stack,
                                 stack_ty* opt_stack,
                                 state_ty* state);
static calc_status_ty HandleError(token_ty* token,
                                   char** expr,
                                   stack_ty* opd_stack,
                                   stack_ty* opt_stack,
                                   state_ty* state);

/* Helpers */
static calc_status_ty ComputeTopOperator(stack_ty* opt_stack,
                                          stack_ty* opd_stack);

/* Operator Actions */
static calc_status_ty Add(double a, double b, double* res);
static calc_status_ty Sub(double a, double b, double* res);
static calc_status_ty Mul(double a, double b, double* res);
static calc_status_ty Div(double a, double b, double* res);


/* Calculator Main Function */

calc_status_ty Calculate(const char* expression, double* res)
{
    char* runner = NULL;
    state_ty state = EXPECTED_OPERAND;
    calc_status_ty status = SUCCESS;
    token_ty token;
    stack_ty* opd_stack = NULL;
    stack_ty* opt_stack = NULL;

    assert(expression);
    assert(res);

    runner = (char*)expression;

    opd_stack = StackCreate(strlen(expression) + 10, sizeof(double));
    if (!opd_stack)
    {
        return OUT_OF_MEMORY;
    }

    opt_stack = StackCreate(strlen(expression) + 10, sizeof(operator_ty));
    if (!opt_stack)
    {
        StackDestroy(opd_stack);
        return OUT_OF_MEMORY;
    }

    InitLut();
    InitFsm();

    while (status == SUCCESS && state != END_STATE)
    {
        token = GetNextToken(&runner);
        status = fsm_g[token.type][state](&token, &runner, opd_stack, opt_stack, &state);
    }

    if (status == SUCCESS)
    {
        if (StackSize(opd_stack) != 1)
        {
            status = SYNTAX_ERROR;
        }
        else
        {
            *res = *(double*)StackPeek(opd_stack);
        }
    }

    StackDestroy(opd_stack);
    StackDestroy(opt_stack);

    return status;
}


/* Initialization Functions */

static void InitLut(void)
{
    size_t i;

    for (i = 0; i < ASCII_SIZE; ++i)
    {
        lut_g[i].symbol = (char)i;
        lut_g[i].precedence = -1;
        lut_g[i].action = NULL;
    }

    lut_g['+'].precedence = 1;
    lut_g['+'].action = Add;

    lut_g['-'].precedence = 1;
    lut_g['-'].action = Sub;

    lut_g['*'].precedence = 2;
    lut_g['*'].action = Mul;

    lut_g['/'].precedence = 2;
    lut_g['/'].action = Div;

    lut_g['('].precedence = 0;
    lut_g['('].action = NULL;
}

static void InitFsm(void)
{
    /* EXPECTED_OPERAND state */
    fsm_g[OPERAND][EXPECTED_OPERAND] = HandleOperand;
    fsm_g[OPERATOR][EXPECTED_OPERAND] = HandleUnaryOperator;
    fsm_g[OPEN_PAREN][EXPECTED_OPERAND] = HandleOpenParen;
    fsm_g[CLOSE_PAREN][EXPECTED_OPERAND] = HandleError;
    fsm_g[END_TOKEN][EXPECTED_OPERAND] = HandleError;
    fsm_g[INVALID][EXPECTED_OPERAND] = HandleError;

    /* EXPECTED_OPERATOR state */
    fsm_g[OPERAND][EXPECTED_OPERATOR] = HandleError;
    fsm_g[OPERATOR][EXPECTED_OPERATOR] = HandleOperator;
    fsm_g[OPEN_PAREN][EXPECTED_OPERATOR] = HandleError;
    fsm_g[CLOSE_PAREN][EXPECTED_OPERATOR] = HandleCloseParen;
    fsm_g[END_TOKEN][EXPECTED_OPERATOR] = HandleEnd;
    fsm_g[INVALID][EXPECTED_OPERATOR] = HandleError;

    /* END_STATE (should not be reached) */
    fsm_g[OPERAND][END_STATE] = HandleError;
    fsm_g[OPERATOR][END_STATE] = HandleError;
    fsm_g[OPEN_PAREN][END_STATE] = HandleError;
    fsm_g[CLOSE_PAREN][END_STATE] = HandleError;
    fsm_g[END_TOKEN][END_STATE] = HandleError;
    fsm_g[INVALID][END_STATE] = HandleError;
}


/* Tokenizer */

static token_ty GetNextToken(char** expr)
{
    token_ty token;
    char* runner = *expr;
    char* end = NULL;

    token.type = INVALID;
    token.data.num = 0;

    /* Skip whitespace */
    while (*runner == ' ' || *runner == '\t')
    {
        ++runner;
    }

    /* Check for end of string */
    if (*runner == '\0')
    {
        token.type = END_TOKEN;
        *expr = runner;
        return token;
    }

    /* Try to parse number */
    if (isdigit(*runner) || (*runner == '.' && isdigit(*(runner + 1))))
    {
        token.data.num = strtod(runner, &end);
        if (end != runner)
        {
            token.type = OPERAND;
            *expr = end;
            return token;
        }
    }

    /* Check for operators */
    if (*runner == '+' || *runner == '-' || *runner == '*' || *runner == '/')
    {
        token.type = OPERATOR;
        token.data.op = *runner;
        *expr = runner + 1;
        return token;
    }

    /* Check for parentheses */
    if (*runner == '(')
    {
        token.type = OPEN_PAREN;
        token.data.op = *runner;
        *expr = runner + 1;
        return token;
    }

    if (*runner == ')')
    {
        token.type = CLOSE_PAREN;
        token.data.op = *runner;
        *expr = runner + 1;
        return token;
    }

    /* Invalid character */
    token.type = INVALID;
    *expr = runner + 1;
    return token;
}


/* Handlers */

static calc_status_ty HandleOperand(token_ty* token,
                                     char** expr,
                                     stack_ty* opd_stack,
                                     stack_ty* opt_stack,
                                     state_ty* state)
{
    (void)expr;
    (void)opt_stack;

    assert(token);
    assert(opd_stack);
    assert(state);

    StackPush(opd_stack, &token->data.num);
    *state = EXPECTED_OPERATOR;
    
    return SUCCESS;
}

static calc_status_ty HandleOperator(token_ty* token,
                                      char** expr,
                                      stack_ty* opd_stack,
                                      stack_ty* opt_stack,
                                      state_ty* state)
{
    operator_ty* curr;
    operator_ty* top;
    calc_status_ty status = SUCCESS;

    (void)expr;

    assert(token);
    assert(opd_stack);
    assert(opt_stack);
    assert(state);

    curr = &lut_g[(int)token->data.op];

    /* Collapse operators with higher or equal precedence */
    while (!StackIsEmpty(opt_stack) && status == SUCCESS)
    {
        top = (operator_ty*)StackPeek(opt_stack);
        
        if (top->symbol == '(')
        {
            break;
        }
        
        if (top->precedence >= curr->precedence)
        {
            status = ComputeTopOperator(opt_stack, opd_stack);
        }
        else
        {
            break;
        }
    }

    if (status == SUCCESS)
    {
        StackPush(opt_stack, curr);
        *state = EXPECTED_OPERAND;
    }

    return status;
}

static calc_status_ty HandleUnaryOperator(token_ty* token,
                                           char** expr,
                                           stack_ty* opd_stack,
                                           stack_ty* opt_stack,
                                           state_ty* state)
{
    int sign = 1;
    char* runner = *expr - 1; /* back up to operator we just parsed */
    double minus_one = -1.0;

    (void)token;

    assert(expr);
    assert(opd_stack);
    assert(opt_stack);
    assert(state);

    /* onnly handle + and - as unary operators */
    /* If it's * or /, this is a syntax error */
    if (*runner != '+' && *runner != '-')
    {
        return SYNTAX_ERROR;
    }

    /* consume (collapsing) all consecutive +/- operators */
    while (*runner == '+' || *runner == '-')
    {
        if (*runner == '-')
        {
            sign *= -1;
        }
        ++runner;

        /* skip whitespace */
        while (*runner == ' ' || *runner == '\t')
        {
            ++runner;
        }
    }

    /* special case: -(expression) */
    if (sign == -1 && *runner == '(')
    {
        StackPush(opd_stack, &minus_one);
        StackPush(opt_stack, &lut_g['*']);
        
        *expr = runner;
        *state = EXPECTED_OPERAND;
        
        return SUCCESS;
    }

    /* General case: unary before number */
    if (sign == -1)
    {
        StackPush(opd_stack, &minus_one);
        StackPush(opt_stack, &lut_g['*']);
    }

    *expr = runner;
    *state = EXPECTED_OPERAND;

    return SUCCESS;
}

static calc_status_ty HandleOpenParen(token_ty* token,
                                       char** expr,
                                       stack_ty* opd_stack,
                                       stack_ty* opt_stack,
                                       state_ty* state)
{
    (void)token;
    (void)expr;
    (void)opd_stack;

    assert(opt_stack);
    assert(state);

    StackPush(opt_stack, &lut_g['(']);
    *state = EXPECTED_OPERAND;

    return SUCCESS;
}

static calc_status_ty HandleCloseParen(token_ty* token,
                                        char** expr,
                                        stack_ty* opd_stack,
                                        stack_ty* opt_stack,
                                        state_ty* state)
{
    calc_status_ty status = SUCCESS;
    operator_ty* top;
    int found_open_paren = 0;

    (void)token;
    (void)expr;

    assert(opd_stack);
    assert(opt_stack);
    assert(state);

    /* collapse until we find opening parenthesis */
    while (!StackIsEmpty(opt_stack) && status == SUCCESS)
    {
        top = (operator_ty*)StackPeek(opt_stack);
        
        if (top->symbol == '(')
        {
            found_open_paren = 1;
            break;
        }
        
        status = ComputeTopOperator(opt_stack, opd_stack);
    }

    /* check for matching opening parenthesis */
    if (!found_open_paren || StackIsEmpty(opt_stack))
    {
        return SYNTAX_ERROR;
    }

    /* check we have at least one operand (to catch empty parentheses) */
    if (StackIsEmpty(opd_stack))
    {
        return SYNTAX_ERROR;
    }

    /* pop the opening parenthesis */
    StackPop(opt_stack);

    *state = EXPECTED_OPERATOR;
    return status;
}

static calc_status_ty HandleEnd(token_ty* token,
                                 char** expr,
                                 stack_ty* opd_stack,
                                 stack_ty* opt_stack,
                                 state_ty* state)
{
    calc_status_ty status = SUCCESS;

    (void)token;
    (void)expr;

    assert(opd_stack);
    assert(opt_stack);
    assert(state);

    /* collapse all remaining operators */
    while (!StackIsEmpty(opt_stack) && status == SUCCESS)
    {
        operator_ty* top = (operator_ty*)StackPeek(opt_stack);
        
        /* unclosed parenthesis */
        if (top->symbol == '(')
        {
            return SYNTAX_ERROR;
        }
        
        status = ComputeTopOperator(opt_stack, opd_stack);
    }

    *state = END_STATE;
    return status;
}

static calc_status_ty HandleError(token_ty* token,
                                   char** expr,
                                   stack_ty* opd_stack,
                                   stack_ty* opt_stack,
                                   state_ty* state)
{
    (void)token;
    (void)expr;
    (void)opd_stack;
    (void)opt_stack;
    (void)state;

    return SYNTAX_ERROR;
}


/* Helper Functions */

static calc_status_ty ComputeTopOperator(stack_ty* opt_stack,
                                          stack_ty* opd_stack)
{
    double rhs, lhs, result;
    operator_ty* op;
    calc_status_ty status;

    assert(opt_stack);
    assert(opd_stack);

    if (StackSize(opd_stack) < 2)
    {
        return SYNTAX_ERROR;
    }

    rhs = *(double*)StackPeek(opd_stack);
    StackPop(opd_stack);

    lhs = *(double*)StackPeek(opd_stack);
    StackPop(opd_stack);

    op = (operator_ty*)StackPeek(opt_stack);
    StackPop(opt_stack);

    if (!op->action)
    {
        return SYNTAX_ERROR;
    }

    status = op->action(lhs, rhs, &result);
    
    if (status == SUCCESS)
    {
        StackPush(opd_stack, &result);
    }

    return status;
}


/* operator Actions */

static calc_status_ty Add(double a, double b, double* res)
{
    assert(res);
    
    *res = a + b;
    return SUCCESS;
}

static calc_status_ty Sub(double a, double b, double* res)
{
    assert(res);
    
    *res = a - b;
    return SUCCESS;
}

static calc_status_ty Mul(double a, double b, double* res)
{
    assert(res);
    
    *res = a * b;
    return SUCCESS;
}

static calc_status_ty Div(double a, double b, double* res)
{
    assert(res);
    
    if (b == 0.0)
    {
        return LOGIC_ERROR;
    }
    
    *res = a / b;
    return SUCCESS;
}
