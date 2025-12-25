/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : steve 
worksheet : 17 (ds - circular buffer)
version : 2
date : 21 Dec 2025
stage : peer-review
----------------------------------------------------------------------------*/
#include <stdio.h> 		/* printf() */
#include <string.h> 	/* memcmp() */

#include "buffer.h"		/* API */
/*------------------- macros for printing test results -----------------------*/
#define PASS(msg) printf("[PASS] %s\n", msg)
#define FAIL(msg) printf("[FAIL] %s\n", msg)
/*------------------------------ magic numbers  ------------------------------*/
#define CAPACITY 10
/*--------------------- declaring on testing functions -----------------------*/
/* testing constructor and destructor */
static void TestCreateDestroy();
/* testing getters */
static void TestIsEmpty();
static void TestCapacityAndFreeSpace();
/* testing manipulation operations on data*/
static void TestWriteRead();
static void TestWrapAround();
static void TestReadMoreThanAvailable();
static void TestWriteMoreThanCapacity();
/*------------------------ peer testing functions ----------------------------*/
static void SteveTest();
/*--------------- aux functions for visualizing cbuffs -----------------------*/
/*static void PrintBuffer(buf_ty* buf);*/
/*------------------------------implementations -------------------------------*/
int main(void)
{
	TestCreateDestroy();
	TestIsEmpty();
	TestCapacityAndFreeSpace();
	TestWriteRead();
	TestWrapAround();
	TestReadMoreThanAvailable();
	TestWriteMoreThanCapacity();
	SteveTest();

return 0;
}
/*-----------------------tests implementations -------------------------------*/
static void TestCreateDestroy()
{
	buf_ty* buf = BufCreate(10);

	if (NULL != buf)
	{
		PASS("BufCreate returned non-NULL");
	}
	else
	{
		FAIL("BufCreate returned NULL");
	}

	BufDestroy(buf);
}
/*----------------------------------------------------------------------------*/

static void TestIsEmpty()
{
	buf_ty* buf = BufCreate(5);

	if (BufIsEmpty(buf))
	{
		PASS("Buffer is empty after creation");
	}
	else
	{
		FAIL("Buffer is not empty after creation");
	}

	BufWrite(buf, 1, "A");

	if (!BufIsEmpty(buf))
	{
		PASS("Buffer is not empty after write");
	}
	else
	{
		FAIL("Buffer is empty after write");
	}

	BufDestroy(buf);
}
/*----------------------------------------------------------------------------*/
static void TestCapacityAndFreeSpace()
{
	buf_ty* buf = BufCreate(8);

	if (8 == BufCap(buf))
	{
		PASS("BufCap returned correct capacity");
	}
	else
	{
		FAIL("BufCap returned wrong capacity");
	}

	if (8 == BufFreeSpace(buf))
	{
		PASS("Free space equals capacity on empty buffer");
	}
	else
	{
		FAIL("Free space incorrect on empty buffer");
	}

	BufWrite(buf, 3, "ABC");

	if (5 == BufFreeSpace(buf))
	{
		PASS("Free space updated after write");
	}
	else
	{
		FAIL("Free space incorrect after write");
	}

	BufDestroy(buf);
}
/*----------------------------------------------------------------------------*/
static void TestWriteRead()
{
	buf_ty* buf = BufCreate(10);
	char out[6] = {0};

	BufWrite(buf, 5, "HELLO");
	BufRead(buf, 5, out);

	if (0 == memcmp(out, "HELLO", 5))
	{
		PASS("Write then read preserved data");
	}
	else
	{
		FAIL("Data mismatch after write/read");
	}

	BufDestroy(buf);
}
/*----------------------------------------------------------------------------*/
static void TestWrapAround()
{
	buf_ty* buf = BufCreate(5);
	char out[6] = {0};

	BufWrite(buf, 5, "ABCDE");
	BufRead(buf, 3, out); /* removes ABC */
	BufWrite(buf, 3, "123"); /* wraps */

	BufRead(buf, 5, out);

	if (0 == memcmp(out, "DE123", 5))
	{
		PASS("Wraparound preserved FIFO order");
	}
	else
	{
		FAIL("Wraparound order incorrect");
	}

	BufDestroy(buf);
}
/*----------------------------------------------------------------------------*/
static void TestReadMoreThanAvailable()
{
	buf_ty* buf = BufCreate(5);
	char out[10] = {0};
	size_t read = 0;

	BufWrite(buf, 3, "XYZ");
	read = BufRead(buf, 10, out);

	if (3 == read && 0 == memcmp(out, "XYZ", 3))
	{
		PASS("Reading more than available reads only existing data");
	}
	else
	{
		FAIL("Read beyond available data");
	}

	BufDestroy(buf);
}
/*----------------------------------------------------------------------------*/
static void TestWriteMoreThanCapacity()
{
	buf_ty* buf = BufCreate(4);
	size_t written = 0;

	written = BufWrite(buf, 10, "ABCDEFGHIJ");

	if (4 == written)
	{
		PASS("Write limited by buffer capacity");
	}
	else
	{
		FAIL("Write exceeded buffer capacity");
	}

	BufDestroy(buf);
}
/*----------------------------------------------------------------------------*/	
static void SteveTest()
{
	buf_ty* buf = BufCreate(10);
	size_t read = 0;
	size_t written = BufWrite(buf, 10, "0123456789");
	char out[10] = {'\0'};

	if (10 == written)
	{
		PASS("Write limited by buffer capacity");
	}
	else
	{
		FAIL("Write exceeded buffer capacity");
	}
	
	read = BufRead(buf, 7, out);
	if (7 == read)
	{
		PASS("read");
	}
	else
	{
		FAIL("read");
	}
	written = BufWrite(buf, 4, "0123");
	if (4 == written)
	{
		PASS("Write limited by buffer capacity");
	}
	else
	{
		FAIL("Write exceeded buffer capacity");
	}
	written = BufWrite(buf, 5, "01234");
	if (3 == written)
	{
		PASS("Write limited by buffer capacity");
	}
	else
	{
		FAIL("Write exceeded buffer capacity");
	}
	BufDestroy(buf);
}

