#ifndef __UTILS_H__
#define __UTILS_H__

#include <stddef.h> /* size_t */

/* Casts a pointer to a bad memory address for debugging */
#define BAD_MEM(type) ((type)0xDEADBEEF)

/* Executes code only in debug mode (when NDEBUG is not defined) */
#ifdef NDEBUG
    #define DEBUG_ONLY(x) ((void)0)
    #define DEBUG_BAD_MEM(ptr, type) ((void)0)
#else
    #define DEBUG_ONLY(x) (x)
    #define DEBUG_BAD_MEM(ptr, type) ((ptr) = BAD_MEM(type))
#endif

#endif /* __UTILS_H__ */
