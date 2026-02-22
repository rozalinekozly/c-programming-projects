#include <stdio.h>
#include "dhcp.h"

void TestCreateDestroy()
{
    dhcp_ty* dhcp = DhcpCreate(0, 8);
    
    if (NULL == dhcp)
    {
        printf("FAIL: DhcpCreate returned NULL\n");
        return;
    }
    
    printf("PASS: DhcpCreate succeeded\n");
    
    DhcpDestroy(dhcp);
    printf("PASS: DhcpDestroy succeeded\n");
}

void TestAllocateIp()
{
    dhcp_ty* dhcp = DhcpCreate(0, 8);
    addr_ty ip = 0;

    /* allocate specific address */
    ip = DhcpAllocateIp(dhcp, 5);
    if (5 == ip)
    {
        printf("PASS: allocated requested address\n");
    }
    else
    {
        printf("FAIL: expected 5, got %lu\n", ip);
    }

    /* allocate same address again - should get next available */
    ip = DhcpAllocateIp(dhcp, 5);
    if (5 != ip && 0 != ip)
    {
        printf("PASS: got next available address\n");
    }
    else
    {
        printf("FAIL: expected next available, got %lu\n", ip);
    }

    DhcpDestroy(dhcp);
}

void TestFreeIp()
{
    dhcp_ty* dhcp = DhcpCreate(0, 8);
    addr_ty ip = 0;

    /* allocate address */
    ip = DhcpAllocateIp(dhcp, 10);
    if (10 != ip)
    {
        printf("FAIL: could not allocate address 10\n");
        DhcpDestroy(dhcp);
        return;
    }

    /* free it */
    DhcpFreeIp(dhcp, 10);

    /* allocate same address again - should get 10 back */
    ip = DhcpAllocateIp(dhcp, 10);
    if (10 == ip)
    {
        printf("PASS: address freed and reallocated correctly\n");
    }
    else
    {
        printf("FAIL: expected 10 after free, got %lu\n", ip);
    }

    DhcpDestroy(dhcp);
}

int main()
{
    TestCreateDestroy();
    TestAllocateIp();
    TestFreeIp();
    return 0;
}
