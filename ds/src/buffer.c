/*--------------------------------------------------------------------------
submitter : Rozaline Kozly
reviewer : steve :)
worksheet : 17 (ds - circular buffer)
version : 2
date : 21 Dec 2025
stage : peer-review
----------------------------------------------------------------------------*/
#include <stdlib.h>	 	 /* malloc(), free() */
#include <string.h>		 /* memcpy() */
#include "buffer.h"		 /* API */

#define TRUE 			1
#define FALSE 			0

/*free-ing and prevanting a dangling pointer*/
#define FREE(x) 		(free(x), (x) = NULL)
/*finds minimum in a given numbers*/
#define MIN(a,b)	    ((a)>(b) ? (b) : (a))

/*--------------------------- cbuffer struct ---------------------------------*/
struct buf
{
	/* total number of elements an instance can hold */
	size_t capacity; 
	/* front index */
	size_t read;
	/* number of bytes currently stored in an instance*/
	size_t size; 
	/* flexible array that holds the data */
	char data[1]; 
};
/*------------------------------implementations -------------------------------*/
buf_ty* BufCreate(size_t capacity)
{
	/*offsetof-based flexible array allocation*/
	buf_ty* buf = (buf_ty*)malloc(offsetof(buf_ty, data) + capacity);
	
	if (NULL == buf)
	{
		return NULL;
	}
	/* intialize instance's fields */
	buf->capacity = capacity;
	buf->read = 0;
	buf->size = 0;
	
	return buf;
}

void BufDestroy(buf_ty* buf)
{
	if (NULL != buf)
	{
		FREE(buf);
	}
}

size_t BufWrite(buf_ty* buf, size_t n_bytes, const void* src)
{
	/* index in buffer to write to, will be wrapped */
	size_t write_idx = buf->read + buf->size;
	/* bytes to be written (can't write more than empty space since
	   there is no writing on data */
	size_t bytes_to_be_written = MIN(n_bytes, BufFreeSpace(buf));
	/* dividing the data to be written into 2 chunks 
		in best case (no wrapping) first chunk will be count
		and second chunk is 0 */
	size_t first_chunk = 0;
	size_t second_chunk = 0;

	/*
	 wrapping index (without % and without branching with ifs):
	 scene 1: no wrapping, then first condition is false and = 0
	 so write_idx remains as buf->read + buf->size.
	 scene 2: there is a wrapping, then write_idx passes the writing limits
	 (by 1 it can't be more than that) and needed to be wrapped so 
	 we should subtract buf->capacity from write_idx.
	*/
	write_idx -= (write_idx >= buf->capacity) * buf->capacity;
	
	/* bytes to copy till it reaches the end */
	first_chunk = MIN(bytes_to_be_written, buf->capacity - write_idx);
	/* data to be written in the wrapped */
	second_chunk = bytes_to_be_written - first_chunk;
	
	/* write data in 2 parts */
	/* copy first chunk */
	memcpy(buf->data + write_idx, src, first_chunk);
	/*copy second chunk*/
	memcpy(buf->data, (char*)src + first_chunk, second_chunk);

	/*update buffer's size*/
	buf->size += bytes_to_be_written;

	return bytes_to_be_written;
}

size_t BufRead(buf_ty* buf, size_t n_bytes, void* dest)
{
	size_t bytes_to_be_read = MIN(n_bytes, buf->size);

	size_t first_chunk = 0;
	size_t second_chunk = 0;
	
	/* data till the end of the array's limit */
	first_chunk = MIN(bytes_to_be_read, buf->capacity - buf->read);
	/* remain data to read from the begining of the array */
	second_chunk = bytes_to_be_read - first_chunk;

	/* read from data the first chunk 
	    (second paramenter in memcpy is from where to start reading
	      since read is an index must add data address to it */
	memcpy(dest, buf->data + buf->read, first_chunk);
	/* read from data the second chunk */
	memcpy((char*)dest + first_chunk, buf->data, second_chunk);
	
	/* update read index */
	buf->read += bytes_to_be_read;
	/* wrap read index */
	buf->read -= (buf->read >= buf->capacity) * buf->capacity;
	/* update size */
	buf->size -= bytes_to_be_read;

	return bytes_to_be_read;
}

size_t BufFreeSpace(const buf_ty* buf)
{
	return buf->capacity - buf->size;
}

size_t BufCap(const buf_ty* buf)
{
	return buf->capacity;
}

int BufIsEmpty(const buf_ty* buf)
{
	return (0 == buf->size) ? TRUE : FALSE;
}
	

