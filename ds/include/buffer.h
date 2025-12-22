#ifndef __BUF_H_
#define __BUF_H_

#include <stddef.h>				/*size_t*/

typedef struct buf buf_ty;

/*----------------- CONSTRUCTOR & DESTRUCTOR ---------------------------------*/
/*
	syntax: 	    BufCreate(capacity)
	arguments:      capacity: number of elements (chars) the buffer can fit
	purpose: 	    construct a buffer with capacity passed as an argument, 
				    it intialize the instant's fields as well.
	return values:  pointer to the buffer (buf_ty*), in case of failed
				    construction, it returns NULL.
	time complexity:O(1)
 */
buf_ty* BufCreate(size_t capacity);

/*
	syntax: 	    BufDestroy(ptr-to-buff)
	arguments:      ptr-to-buff: pointer to the buffer to be destroied
	purpose: 	    destruct a buffer, free it's resourses.
	return values:  void.
	time complexity:O(n)
*/
void BufDestroy(buf_ty* buf);

/*--------------------------- GETTERS ----------------------------------------*/
/*
	syntax: 	    BufFreeSpace(ptr-to-buff)
	arguments:      ptr-to-buff: pointer to the buffer.
	purpose: 	    returns free space in the buffer.
	return values:  >= 0.
	UB: 			buf is invalid.
	time complexity:O(1)
 */
size_t BufFreeSpace(const buf_ty* buf);

/*
	syntax: 	    BufCap(ptr-to-buff)
	arguments:      ptr-to-buff: pointer to the buffer.
	purpose: 	    returns capacity of the buffer.
	return values:  >= 0.
	UB: 			buf is invalid.
	time complexity:O(1)
 */
size_t BufCap(const buf_ty* buf);

/*
	syntax: 	    BufIsEmpty(ptr-to-buff)
	arguments:      ptr-to-buff: pointer to the buffer.
	purpose: 	    answers "is the buffer empty".
	return values:  1= it is empty, 0 = otherwise .
	UB: 			buf is invalid.
	time complexity:O(1)
 */
int BufIsEmpty(const buf_ty* buf);

/*-------------------- MANIPULATIONS ON DATA ---------------------------------*/
/*
	syntax: 	    BufRead(ptr-to-buff, num-bytes-to-read, dest)
	arguments:      ptr-to-buff: pointer to the buffer.
					num-bytes-to-read: number of bytes to read and remove from 
					buffer.
					dest: destination to add read data into.
	purpose: 	    read from buffer according to FIFO mechanism and 
					remove num-bytes-to-read (or all data in case passed number 
					is larger than number of elements in current buffer) read data 
					into dest.
	return values:  number of bytes that were read successfully.
	UB: 			buf or dest are NULL.
					dest size can't hold read data.
	time complexity:O(n)
*/
size_t BufRead(buf_ty* buf, size_t n_bytes, void* dest);
/*
	syntax: 	    BufWrite(ptr-to-buff, num-bytes-to-write, src)
	arguments:      ptr-to-buff: pointer to the buffer.
					num-bytes-to-write: number of bytes to write to the buffer.
					src: content to write.
	purpose: 	    write num-bytes-to-write amount data given (if it surpaces empty
					space in instance, it writes only empty-space bytes) from src 
					into buffer.
	return values:  number of bytes that were writen successfully.
	UB: 			buf or dest are NULL.
					src size smaller than num-bytes-to-write .
	time complexity:O(n)
*/
size_t BufWrite(buf_ty* buf, size_t n_bytes, const void* src);

#endif /* __BUF_H_ */
