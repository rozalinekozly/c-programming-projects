#include <string.h>  /* strcmp */
#include <stdio.h>   /* printf */

#include "hmap.h"
#include "test_utils.h"
#include "utils.h"

#define CAPACITY 3
#define PEOPLE_INPUT {{"1", "Alice", 10}, {"2", "Bob", 11}, {"3", "Charlie", 15}, \
                      {"4", "Dave", 18}, {"5", "Eve", 16}, \
                      {"6", "Frank", 20}, {"7", "Karen", 21}, {"8", "Larry", 19}, \
                      {"9", "Mona", 18}, {"10", "Nina", 36}}

#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

/*---------------------------------------------------------------------------*/
typedef struct person
{
    const char* id;
    char* name;
    int age;
} person_ty;
/*---------------------------------------------------------------------------*/
static void TestHMapCreate(void);
static void TestHMapInsert(void);
static void TestHMapFind(void);
static void TestHMapRemove(void);
static void TestHMapSize(void);
static void TestHMapForEach(void);
static void TestHMapDemo(void);

size_t Hash(const void* key, const void* param);
int IsMatch(const void* key_a, const void* key_b, const void* param);
int PrintPerson(const void* key, void* data, void* param);
static int ToDigit(const char c);
int IncrementAge(const void* key, void* data, void* param);
/*---------------------------------------------------------------------------*/
int main()
{
    TestSuiteBegin("HashMap Tests");

    TestPrintSection("Create Tests");
    TestHMapCreate();

    TestPrintSection("Insert Tests");
    TestHMapInsert();

    TestPrintSection("Find Tests");
    TestHMapFind();

    TestPrintSection("Remove Tests");
    TestHMapRemove();

    TestPrintSection("Size Tests");
    TestHMapSize();

    TestPrintSection("ForEach Tests");
    TestHMapForEach();

    TestPrintSection("Demo Tests");
    TestHMapDemo();

    return TestSuiteEnd();
}
/*---------------------------------------------------------------------------*/
static void TestHMapCreate(void)
{
    hmap_ty* map = HMapCreate(CAPACITY, Hash, NULL, IsMatch, NULL);

    if (!ASSERT_NOT_NULL(map))
    {
        return;
    }

    ASSERT_TRUE(HMapIsEmpty(map));

    HMapDestroy(map);
}
/*---------------------------------------------------------------------------*/
static void TestHMapInsert(void)
{
    person_ty p1 = {"1", "Alice", 20};
    person_ty p2 = {"2", "Bob", 25};
    person_ty p3 = {"4", "John", 34};
    hmap_ty* map = HMapCreate(CAPACITY, Hash, NULL, IsMatch, NULL);

    if (!ASSERT_NOT_NULL(map))
    {
        return;
    }

    /* insert new keys */
    ASSERT_SUCCESS(HMapInsert(map, p1.id, &p1));
    ASSERT_SUCCESS(HMapInsert(map, p2.id, &p2));
    /* test collision */
    ASSERT_SUCCESS(HMapInsert(map, p3.id, &p3));

    HMapDestroy(map);
}
/*---------------------------------------------------------------------------*/
static void TestHMapFind(void)
{
    person_ty people[] = PEOPLE_INPUT;
    size_t i = 0;
    hmap_ty* map = HMapCreate(CAPACITY, Hash, NULL, IsMatch, NULL);

    if (!ASSERT_NOT_NULL(map))
    {
        return;
    }

    for (i = 0; i < ARRAY_LEN(people); ++i)
    {
        HMapInsert(map, people[i].id, &people[i]);
    }

    /* keys exist */
    for (i = 0; i < ARRAY_LEN(people); ++i)
    {
        ASSERT_STR_EQUAL(people[i].id, HMapFind(map, people[i].id).key);
    }

    /* key not exist */
    ASSERT_NULL(HMapFind(map, "non-exist-key").key);

    HMapDestroy(map);
}
/*---------------------------------------------------------------------------*/
static void TestHMapRemove(void)
{
    person_ty people[] = PEOPLE_INPUT;
    size_t i = 0;
    hmap_ty* map = HMapCreate(CAPACITY, Hash, NULL, IsMatch, NULL);

    if (!ASSERT_NOT_NULL(map))
    {
        return;
    }

    /* remove the only key in the map */
    HMapInsert(map, people[0].id, &people[0]);
    HMapRemove(map, people[0].id);
    ASSERT_NULL(HMapFind(map, people[0].id).key);

    for (i = 0; i < ARRAY_LEN(people); ++i)
    {
        HMapInsert(map, people[i].id, &people[i]);
    }

    /* remove and verify not in map */
    for (i = 0; i < ARRAY_LEN(people); ++i)
    {
        HMapRemove(map, people[i].id);
        ASSERT_NULL(HMapFind(map, people[i].id).key);
    }

    HMapDestroy(map);
}
/*---------------------------------------------------------------------------*/
static void TestHMapSize(void)
{
    person_ty people[] = PEOPLE_INPUT;
    size_t i = 0;
    size_t expected_size = 0;
    hmap_ty* map = HMapCreate(CAPACITY, Hash, NULL, IsMatch, NULL);

    if (!ASSERT_NOT_NULL(map))
    {
        return;
    }

    ASSERT_SIZE(expected_size, HMapSize(map));

    for (i = 0; i < ARRAY_LEN(people); ++i)
    {
        HMapInsert(map, people[i].id, &people[i]);
        ++expected_size;
        ASSERT_SIZE(expected_size, HMapSize(map));
    }

    for (i = 0; i < ARRAY_LEN(people); ++i)
    {
        HMapRemove(map, people[i].id);
        --expected_size;
        ASSERT_SIZE(expected_size, HMapSize(map));
    }

    ASSERT_TRUE(HMapIsEmpty(map));

    HMapDestroy(map);
}
/*---------------------------------------------------------------------------*/
static void TestHMapForEach(void)
{
    person_ty people[] = PEOPLE_INPUT;
    int new_ages[10] = {0};
    size_t i = 0;
    size_t count = 0;
    hmap_ty* map = HMapCreate(CAPACITY, Hash, NULL, IsMatch, NULL);

    if (!ASSERT_NOT_NULL(map))
    {
        return;
    }

    for (i = 0; i < ARRAY_LEN(people); ++i)
    {
        HMapInsert(map, people[i].id, &people[i]);
        new_ages[i] = people[i].age <= 15 ? people[i].age + ToDigit(*people[i].id) : people[i].age;
    }

    /* should return 1 since we stop in the middle */
    ASSERT_INT(1, HMapForEach(map, IncrementAge, &count));

    /* verify count */
    ASSERT_SIZE(3, count);

    for (i = 0; i < ARRAY_LEN(people); ++i)
    {
        ASSERT_INT(new_ages[i], people[i].age);
    }

    HMapDestroy(map);
}
/*---------------------------------------------------------------------------*/
static void TestHMapDemo(void)
{
    person_ty people[] = PEOPLE_INPUT;
    size_t i = 0;
    hmap_ty* map = HMapCreate(CAPACITY, Hash, NULL, IsMatch, NULL);

    if (!ASSERT_NOT_NULL(map))
    {
        return;
    }

    printf("\n--- Demo: inserting all people ---\n");
    for (i = 0; i < ARRAY_LEN(people); ++i)
    {
        HMapInsert(map, people[i].id, &people[i]);
    }

    printf("--- Demo: printing all people ---\n");
    HMapForEach(map, PrintPerson, NULL);

    printf("--- Demo: removing id 1 and 5 ---\n");
    HMapRemove(map, "1");
    HMapRemove(map, "5");

    printf("--- Demo: printing after remove ---\n");
    HMapForEach(map, PrintPerson, NULL);

    printf("--- Demo: map size = %lu ---\n", HMapSize(map));

    HMapDestroy(map);
}
/*---------------------------------------------------------------------------*/
size_t Hash(const void* key, const void* param)
{
    size_t hash = 5381;
    char* str = (char*)key;
    char c = 0;
    (void)param;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}
/*---------------------------------------------------------------------------*/
int IsMatch(const void* key_a, const void* key_b, const void* param)
{
    (void)param;
    return 0 == strcmp(key_a, key_b);
}
/*---------------------------------------------------------------------------*/
int PrintPerson(const void* key, void* data, void* param)
{
    person_ty* p = (person_ty*)data;
    (void)key;
    (void)param;
    printf("id: %s, name: %s, age: %d\n", p->id, p->name, p->age);
    return 0;
}
/*---------------------------------------------------------------------------*/
int IncrementAge(const void* key, void* data, void* param)
{
    size_t* count = (size_t*)param;
    person_ty* p = (person_ty*)data;
    int digit = ToDigit(*(char*)key);

    if (p->age <= 15)
    {
        p->age += digit;
        ++(*count);
    }

    if (*count == 3)
    {
        return 1;
    }

    return 0;
}
/*---------------------------------------------------------------------------*/
static int ToDigit(const char c)
{
    return c - '0';
}
