#include <stdio.h>
#include "dhcp.h"

void TestCreateBasic()
{
    dhcp_ty* dhcp = DhcpCreate(0, 8);
    
    if (NULL == dhcp)
    {
        printf("FAIL: DhcpCreate returned NULL\n");
        return;
    }
    
    printf("PASS: DhcpCreate succeeded\n");
    
    if (253 == DhcpCountFree(dhcp))
    {
        printf("PASS: count free correct\n");
    }
    else
    {
        printf("FAIL: count free incorrect\n");
    }
    
    DhcpDestroy(dhcp);
}

int main()
{
    TestCreateBasic();
    return 0;
}
