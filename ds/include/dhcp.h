#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h>     /* size_t */

typedef struct dhcp dhcp_ty;
typedef size_t addr_ty;

/*
 * Allocates 
 * 		X.000...000 (Network Address)
 * 		X.111...110 (Server Address)
 * 		X.111...111 (Broadcast Address)
 * On failure returns NULL
 * Undefined Behaviour:
 *      host_numb_ is larger than IPV4 num bits together
 * O(log(n)), n - number of available addresses
*/
dhcp_ty* DhcpCreate(addr_ty subnet_id_, unsigned int host_numb_);

/*
*   NULL is allowed
*   O(n)
*/
void DhcpDestroy(dhcp_ty* dhcp_);

/*
 * Tries to allocate the requested address,
 * 		If "addr_" is not available, tries to allocated the closest bigger available address
 * 		If "addr_" is 0, arbitrary available address will be allocated
 *      On failure, returns 0
 * Undefined behaviour:
 * 		"dhcp_" is NULL
 * O(log(n)), n - number of available addresses
*/
addr_ty DhcpAllocateIp(dhcp_ty* dhcp_, addr_ty addr_);

/*
 * Frees "addr_" from "dhcp_"
 * Undefined behaviour:
 * 		"dhcp_" is NULL
 * 		addr_ wasn't previously allocated
 * O(log(n)), n - number of available addresses
*/
void DhcpFreeIp(dhcp_ty* dhcp_, addr_ty addr_);

/*
 * Undefined behaviour:
 * 		"dhcp_" is NULL
 *  O(n)
*/
size_t DhcpCountFree(const dhcp_ty* dhcp_);

#endif /* __DHCP_H__ */

