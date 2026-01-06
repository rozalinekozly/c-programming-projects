#include <stdio.h>
#include "uid.h"

/* Forward declaration for the test function */
static void TestUidCreate(void);

int main()
{
    TestUidCreate();
    return 0;
}

static void PrintUid(uid_ty uid)
{
    printf("--- UID Details ---\n");
    printf("Time:    %ld\n", (long)uid.time);
    printf("Counter: %lu\n", (unsigned long)uid.counter);
    printf("PID:     %d\n", (int)uid.pid);
    printf("IP:      %s\n", uid.ip);
    printf("-------------------\n");
}

static void TestUidCreate(void)
{
    uid_ty uid1 = UidCreate();
    uid_ty uid2 = UidCreate();

    PrintUid(uid1);
    PrintUid(uid2);

    /* Test 1: Check if creation failed */
    if (IsMatchId(uid1, invalid_uid_g))
    {
        printf("Error: uid1 creation failed!\n");
    }

    /* Test 2: Check if two different UIDs are incorrectly seen as equal */
    if (IsMatchId(uid1, uid2))
    {
        printf("Error: uid1 and uid2 should NOT be equal!\n");
    }
    else
    {
        printf("Success: uid1 and uid2 are unique.\n");
    }

    /* Test 3: Verify the counter is working */
    if (uid2.counter == uid1.counter + 1)
    {
        printf("Success: Counter incremented correctly.\n");
    }
}
