#include <string.h>  /* strcmp */

#include "dhcp.h"
#include "test_utils.h"

#define SUBNET_ID   0
#define HOST_NUMB   8
#define TOTAL_ADDRS 256
#define RESERVED    3
#define FREE_ADDRS  (TOTAL_ADDRS - RESERVED)
/*---------------------------------------------------------------------------*/
static void TestCreateDestroy(void);
static void TestAllocateIp(void);
static void TestFreeIp(void);
static void TestCountFree(void);
static void TestDemo(void);
/*---------------------------------------------------------------------------*/
int main()
{
    TestSuiteBegin("DHCP Tests");

    TestPrintSection("Create Destroy Tests");
    TestCreateDestroy();

    TestPrintSection("Allocate IP Tests");
    TestAllocateIp();

    TestPrintSection("Free IP Tests");
    TestFreeIp();

    TestPrintSection("Count Free Tests");
    TestCountFree();

    TestPrintSection("Demo Tests");
    TestDemo();

    return TestSuiteEnd();
}
/*---------------------------------------------------------------------------*/
static void TestCreateDestroy(void)
{
    dhcp_ty* dhcp = DhcpCreate(SUBNET_ID, HOST_NUMB);

    if (!ASSERT_NOT_NULL(dhcp))
    {
        return;
    }

    ASSERT_SIZE(FREE_ADDRS, DhcpCountFree(dhcp));

    DhcpDestroy(dhcp);
}
/*---------------------------------------------------------------------------*/
static void TestAllocateIp(void)
{
    dhcp_ty* dhcp = DhcpCreate(SUBNET_ID, HOST_NUMB);
    addr_ty ip = 0;

    if (!ASSERT_NOT_NULL(dhcp))
    {
        return;
    }

    /* allocate specific address */
    ip = DhcpAllocateIp(dhcp, 5);
    ASSERT_SIZE(5, ip);

    /* allocate same address again - should get next available */
    ip = DhcpAllocateIp(dhcp, 5);
    ASSERT_TRUE(5 != ip && 0 != ip);

    /* allocate arbitrary address */
    ip = DhcpAllocateIp(dhcp, 0);
    ASSERT_TRUE(0 != ip);

    DhcpDestroy(dhcp);
}
/*---------------------------------------------------------------------------*/
static void TestFreeIp(void)
{
    dhcp_ty* dhcp = DhcpCreate(SUBNET_ID, HOST_NUMB);
    addr_ty ip = 0;

    if (!ASSERT_NOT_NULL(dhcp))
    {
        return;
    }

    ip = DhcpAllocateIp(dhcp, 10);
    if (!ASSERT_SIZE(10, ip))
    {
        DhcpDestroy(dhcp);
        return;
    }

    DhcpFreeIp(dhcp, 10);

    /* after free should get 10 back */
    ip = DhcpAllocateIp(dhcp, 10);
    ASSERT_SIZE(10, ip);

    DhcpDestroy(dhcp);
}
/*---------------------------------------------------------------------------*/
static void TestCountFree(void)
{
    dhcp_ty* dhcp = DhcpCreate(SUBNET_ID, HOST_NUMB);

    if (!ASSERT_NOT_NULL(dhcp))
    {
        return;
    }

    /* after create */
    ASSERT_SIZE(FREE_ADDRS, DhcpCountFree(dhcp));

    /* after allocate */
    DhcpAllocateIp(dhcp, 10);
    ASSERT_SIZE(FREE_ADDRS - 1, DhcpCountFree(dhcp));

    /* after free */
    DhcpFreeIp(dhcp, 10);
    ASSERT_SIZE(FREE_ADDRS, DhcpCountFree(dhcp));

    DhcpDestroy(dhcp);
}
/*---------------------------------------------------------------------------*/
static void TestDemo(void)
{
    dhcp_ty* dhcp = DhcpCreate(SUBNET_ID, HOST_NUMB);
    addr_ty ips[5] = {0};
    size_t i = 0;

    if (!ASSERT_NOT_NULL(dhcp))
    {
        return;
    }

    /* allocate 5 addresses */
    for (i = 0; i < 5; ++i)
    {
        ips[i] = DhcpAllocateIp(dhcp, 0);
        ASSERT_TRUE(0 != ips[i]);
    }

    ASSERT_SIZE(FREE_ADDRS - 5, DhcpCountFree(dhcp));

    /* free all 5 */
    for (i = 0; i < 5; ++i)
    {
        DhcpFreeIp(dhcp, ips[i]);
    }

    ASSERT_SIZE(FREE_ADDRS, DhcpCountFree(dhcp));

    DhcpDestroy(dhcp);
}
