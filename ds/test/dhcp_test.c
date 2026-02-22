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

int main()
{
    TestCreateDestroy();
    return 0;
}
