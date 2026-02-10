#include <stdio.h>
#include <math.h>
#include "calculator.h"

#define EPSILON 0.000001
#define TEST(name) printf("\nTesting: %s\n", name)
#define PASS() printf("  PASS\n")
#define FAIL(msg) printf("  FAIL: %s\n", msg)

/* Helper function to compare doubles */
static int DoubleEqual(double a, double b)
{
    return fabs(a - b) < EPSILON;
}

/* Test function declarations */
static void TestBasicArithmetic(void);
static void TestOperatorPrecedence(void);
static void TestParentheses(void);
static void TestUnaryOperators(void);
static void TestComplexUnary(void);
static void TestUnaryWithParentheses(void);
static void TestWhitespace(void);
static void TestSyntaxErrors(void);
static void TestLogicErrors(void);
static void TestEdgeCases(void);

int main(void)
{
    printf("=================================================\n");
    printf("         CALCULATOR TEST SUITE\n");
    printf("=================================================\n");

    TestBasicArithmetic();
    TestOperatorPrecedence();
    TestParentheses();
    TestUnaryOperators();
    TestComplexUnary();
    TestUnaryWithParentheses();
    TestWhitespace();
    TestSyntaxErrors();
    TestLogicErrors();
    TestEdgeCases();

    printf("\n=================================================\n");
    printf("         TEST SUITE COMPLETE\n");
    printf("=================================================\n");

    return 0;
}

static void TestBasicArithmetic(void)
{
    calc_status_ty status;
    double result;

    TEST("Basic Addition");
    status = Calculate("2+3", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Basic Subtraction");
    status = Calculate("10-7", &result);
    if (status == SUCCESS && DoubleEqual(result, 3.0))
        PASS();
    else
        FAIL("Expected 3.0");

    TEST("Basic Multiplication");
    status = Calculate("4*5", &result);
    if (status == SUCCESS && DoubleEqual(result, 20.0))
        PASS();
    else
        FAIL("Expected 20.0");

    TEST("Basic Division");
    status = Calculate("20/4", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Decimal Numbers");
    status = Calculate("2.5+3.5", &result);
    if (status == SUCCESS && DoubleEqual(result, 6.0))
        PASS();
    else
        FAIL("Expected 6.0");

    TEST("Chain Addition");
    status = Calculate("1+2+3+4", &result);
    if (status == SUCCESS && DoubleEqual(result, 10.0))
        PASS();
    else
        FAIL("Expected 10.0");
}

static void TestOperatorPrecedence(void)
{
    calc_status_ty status;
    double result;

    TEST("Multiplication before Addition");
    status = Calculate("2+3*4", &result);
    if (status == SUCCESS && DoubleEqual(result, 14.0))
        PASS();
    else
        FAIL("Expected 14.0 (2+(3*4))");

    TEST("Division before Subtraction");
    status = Calculate("10-6/2", &result);
    if (status == SUCCESS && DoubleEqual(result, 7.0))
        PASS();
    else
        FAIL("Expected 7.0 (10-(6/2))");

    TEST("Mixed Precedence");
    status = Calculate("2+3*4-6/2", &result);
    if (status == SUCCESS && DoubleEqual(result, 11.0))
        PASS();
    else
        FAIL("Expected 11.0");

    TEST("Left to Right Same Precedence");
    status = Calculate("10-5-2", &result);
    if (status == SUCCESS && DoubleEqual(result, 3.0))
        PASS();
    else
        FAIL("Expected 3.0 ((10-5)-2)");

    TEST("Multiplication Chain");
    status = Calculate("2*3*4", &result);
    if (status == SUCCESS && DoubleEqual(result, 24.0))
        PASS();
    else
        FAIL("Expected 24.0");
}

static void TestParentheses(void)
{
    calc_status_ty status;
    double result;

    TEST("Simple Parentheses");
    status = Calculate("(2+3)*4", &result);
    if (status == SUCCESS && DoubleEqual(result, 20.0))
        PASS();
    else
        FAIL("Expected 20.0");

    TEST("Nested Parentheses");
    status = Calculate("((2+3)*4)", &result);
    if (status == SUCCESS && DoubleEqual(result, 20.0))
        PASS();
    else
        FAIL("Expected 20.0");

    TEST("Multiple Parentheses Groups");
    status = Calculate("(2+3)*(4+5)", &result);
    if (status == SUCCESS && DoubleEqual(result, 45.0))
        PASS();
    else
        FAIL("Expected 45.0");

    TEST("Deep Nesting");
    status = Calculate("((((2+3))))", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Complex Nested Expression");
    status = Calculate("(2+(3*(4+5)))", &result);
    if (status == SUCCESS && DoubleEqual(result, 29.0))
        PASS();
    else
        FAIL("Expected 29.0");

    TEST("Parentheses Override Precedence");
    status = Calculate("2*(3+4)", &result);
    if (status == SUCCESS && DoubleEqual(result, 14.0))
        PASS();
    else
        FAIL("Expected 14.0");
}

static void TestUnaryOperators(void)
{
    calc_status_ty status;
    double result;

    TEST("Unary Minus");
    status = Calculate("-5", &result);
    if (status == SUCCESS && DoubleEqual(result, -5.0))
        PASS();
    else
        FAIL("Expected -5.0");

    TEST("Unary Plus");
    status = Calculate("+5", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Double Negative (even)");
    status = Calculate("--5", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Triple Negative (odd)");
    status = Calculate("---5", &result);
    if (status == SUCCESS && DoubleEqual(result, -5.0))
        PASS();
    else
        FAIL("Expected -5.0");

    TEST("Five Negatives (odd)");
    status = Calculate("-----5", &result);
    if (status == SUCCESS && DoubleEqual(result, -5.0))
        PASS();
    else
        FAIL("Expected -5.0");

    TEST("Six Negatives (even)");
    status = Calculate("------5", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Unary in Expression");
    status = Calculate("3+-5", &result);
    if (status == SUCCESS && DoubleEqual(result, -2.0))
        PASS();
    else
        FAIL("Expected -2.0");

    TEST("Multiple Unary in Expression");
    status = Calculate("3+---5", &result);
    if (status == SUCCESS && DoubleEqual(result, -2.0))
        PASS();
    else
        FAIL("Expected -2.0");
}

static void TestComplexUnary(void)
{
    calc_status_ty status;
    double result;

    TEST("Mixed Plus Minus");
    status = Calculate("+-5", &result);
    if (status == SUCCESS && DoubleEqual(result, -5.0))
        PASS();
    else
        FAIL("Expected -5.0");

    TEST("Complex Unary Sequence");
    status = Calculate("+-+-5", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Long Unary Sequence");
    status = Calculate("+-+-++--5", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Unary After Operator");
    status = Calculate("10*-2", &result);
    if (status == SUCCESS && DoubleEqual(result, -20.0))
        PASS();
    else
        FAIL("Expected -20.0");

    TEST("Multiple Unary After Operator");
    status = Calculate("10*---2", &result);
    if (status == SUCCESS && DoubleEqual(result, -20.0))
        PASS();
    else
        FAIL("Expected -20.0");
}

static void TestUnaryWithParentheses(void)
{
    calc_status_ty status;
    double result;

    TEST("Negative Parentheses");
    status = Calculate("-(2+3)", &result);
    if (status == SUCCESS && DoubleEqual(result, -5.0))
        PASS();
    else
        FAIL("Expected -5.0");

    TEST("Double Negative Parentheses");
    status = Calculate("--(2+3)", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Triple Negative Parentheses");
    status = Calculate("---(2+3)", &result);
    if (status == SUCCESS && DoubleEqual(result, -5.0))
        PASS();
    else
        FAIL("Expected -5.0");

    TEST("Four Negatives Parentheses (even)");
    status = Calculate("----(2+3)", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Unary with Nested Parentheses");
    status = Calculate("-((2+3))", &result);
    if (status == SUCCESS && DoubleEqual(result, -5.0))
        PASS();
    else
        FAIL("Expected -5.0");

    TEST("Complex Expression with Unary Paren");
    status = Calculate("10+-(2*3)", &result);
    if (status == SUCCESS && DoubleEqual(result, 4.0))
        PASS();
    else
        FAIL("Expected 4.0");

    TEST("Multiple Unary Paren Groups");
    status = Calculate("-(2+3)+-(4+5)", &result);
    if (status == SUCCESS && DoubleEqual(result, -14.0))
        PASS();
    else
        FAIL("Expected -14.0");
}

static void TestWhitespace(void)
{
    calc_status_ty status;
    double result;

    TEST("Spaces Around Operators");
    status = Calculate("2 + 3", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Multiple Spaces");
    status = Calculate("2   +   3", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Tabs");
    status = Calculate("2\t+\t3", &result);
    if (status == SUCCESS && DoubleEqual(result, 5.0))
        PASS();
    else
        FAIL("Expected 5.0");

    TEST("Mixed Whitespace");
    status = Calculate(" 2 + 3 * 4 ", &result);
    if (status == SUCCESS && DoubleEqual(result, 14.0))
        PASS();
    else
        FAIL("Expected 14.0");

    TEST("Whitespace in Parentheses");
    status = Calculate("( 2 + 3 ) * 4", &result);
    if (status == SUCCESS && DoubleEqual(result, 20.0))
        PASS();
    else
        FAIL("Expected 20.0");

    TEST("Whitespace with Unary");
    status = Calculate("- 5", &result);
    if (status == SUCCESS && DoubleEqual(result, -5.0))
        PASS();
    else
        FAIL("Expected -5.0");

    TEST("Whitespace Between Unary Operators");
    status = Calculate("- - - 5", &result);
    if (status == SUCCESS && DoubleEqual(result, -5.0))
        PASS();
    else
        FAIL("Expected -5.0");
}

static void TestSyntaxErrors(void)
{
    calc_status_ty status;
    double result;

    TEST("Empty Parentheses");
    status = Calculate("()", &result);
    if (status == SYNTAX_ERROR)
        PASS();
    else
        FAIL("Expected SYNTAX_ERROR");

    TEST("Mismatched Parentheses - Extra Closing");
    status = Calculate("2+3)", &result);
    if (status == SYNTAX_ERROR)
        PASS();
    else
        FAIL("Expected SYNTAX_ERROR");

    TEST("Mismatched Parentheses - Extra Opening");
    status = Calculate("(2+3", &result);
    if (status == SYNTAX_ERROR)
        PASS();
    else
        FAIL("Expected SYNTAX_ERROR");

    TEST("Two Operators in Row (non-unary)");
    status = Calculate("2*/3", &result);
    if (status == SYNTAX_ERROR)
        PASS();
    else
        FAIL("Expected SYNTAX_ERROR");

    TEST("Operator at End");
    status = Calculate("2+3+", &result);
    if (status == SYNTAX_ERROR)
        PASS();
    else
        FAIL("Expected SYNTAX_ERROR");

    TEST("Two Operands in Row");
    status = Calculate("2 3", &result);
    if (status == SYNTAX_ERROR)
        PASS();
    else
        FAIL("Expected SYNTAX_ERROR");

    TEST("Invalid Character");
    status = Calculate("2+3@4", &result);
    if (status == SYNTAX_ERROR)
        PASS();
    else
        FAIL("Expected SYNTAX_ERROR");

    TEST("Empty Expression");
    status = Calculate("", &result);
    if (status == SYNTAX_ERROR)
        PASS();
    else
        FAIL("Expected SYNTAX_ERROR");

    TEST("Just Operator");
    status = Calculate("+", &result);
    if (status == SYNTAX_ERROR)
        PASS();
    else
        FAIL("Expected SYNTAX_ERROR");

    TEST("Nested Empty Parentheses");
    status = Calculate("2+()", &result);
    if (status == SYNTAX_ERROR)
        PASS();
    else
        FAIL("Expected SYNTAX_ERROR");
}

static void TestLogicErrors(void)
{
    calc_status_ty status;
    double result;

    TEST("Division by Zero");
    status = Calculate("5/0", &result);
    if (status == LOGIC_ERROR)
        PASS();
    else
        FAIL("Expected LOGIC_ERROR");

    TEST("Division by Zero in Expression");
    status = Calculate("2+3/0", &result);
    if (status == LOGIC_ERROR)
        PASS();
    else
        FAIL("Expected LOGIC_ERROR");

    TEST("Division by Zero Result");
    status = Calculate("5/(2-2)", &result);
    if (status == LOGIC_ERROR)
        PASS();
    else
        FAIL("Expected LOGIC_ERROR");

    TEST("Complex Division by Zero");
    status = Calculate("10/(5-2-3)", &result);
    if (status == LOGIC_ERROR)
        PASS();
    else
        FAIL("Expected LOGIC_ERROR");
}

static void TestEdgeCases(void)
{
    calc_status_ty status;
    double result;

    TEST("Single Number");
    status = Calculate("42", &result);
    if (status == SUCCESS && DoubleEqual(result, 42.0))
        PASS();
    else
        FAIL("Expected 42.0");

    TEST("Single Number in Parentheses");
    status = Calculate("(42)", &result);
    if (status == SUCCESS && DoubleEqual(result, 42.0))
        PASS();
    else
        FAIL("Expected 42.0");

    TEST("Zero");
    status = Calculate("0", &result);
    if (status == SUCCESS && DoubleEqual(result, 0.0))
        PASS();
    else
        FAIL("Expected 0.0");

    TEST("Negative Zero");
    status = Calculate("-0", &result);
    if (status == SUCCESS && DoubleEqual(result, 0.0))
        PASS();
    else
        FAIL("Expected 0.0");

    TEST("Large Number");
    status = Calculate("999999+1", &result);
    if (status == SUCCESS && DoubleEqual(result, 1000000.0))
        PASS();
    else
        FAIL("Expected 1000000.0");

    TEST("Very Long Expression");
    status = Calculate("1+1+1+1+1+1+1+1+1+1", &result);
    if (status == SUCCESS && DoubleEqual(result, 10.0))
        PASS();
    else
        FAIL("Expected 10.0");

    TEST("Decimal Point Handling");
    status = Calculate("0.5+0.5", &result);
    if (status == SUCCESS && DoubleEqual(result, 1.0))
        PASS();
    else
        FAIL("Expected 1.0");

    TEST("Leading Decimal");
    status = Calculate(".5+.5", &result);
    if (status == SUCCESS && DoubleEqual(result, 1.0))
        PASS();
    else
        FAIL("Expected 1.0");
}
