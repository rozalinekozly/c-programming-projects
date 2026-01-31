#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <stddef.h>	/* size_t */

typedef circular_buffer circular_Buffer_ty; 

/*
	creates a circular buffer with a capacity of a passed argument
	returns NULL in case it did not work.
*/
circular_Buffer_ty* CircularBufferCreate(size_t capacity);
/*
	destories a buffer and frees it's resources.
	does nothing if NULL
*/
void CircularBufferDestroy(circular_Buffer_ty* circular_buffer_p);
/*
	returns 1 if cb is empty (indecating yes) and 0 if not (indecating no)
*/
size_t CircularBufferIsEmpty(const circular_Buffer_ty* circular_buffer_p);
/*
	returns capacity of cb
*/
size_t CircularBufferCapacity(const circular_Buffer_ty* circular_buffer_p);
/*
	returns free-space in buffer
*/
size_t CircularBufferFreeSpace(const circular_Buffer_ty* circular_buffer_p);
/*
 size argument must be 1 (chars).
*/
size_t fwrite(const circular_Buffer_ty* circular_buffer_p, size_t size, size_t nmemb, FILE* stream);



size_t fread(const circular_Buffer_ty* circular_buffer_p, size_t size, size_t nmemb, FILE* stream);

#endif __CIRCULAR_BUFFER_H__
