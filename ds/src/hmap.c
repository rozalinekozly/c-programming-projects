#include <stdlib.h>  /* malloc, free */
#include <assert.h>  /* assert */
#include "dlist.h"   /* DListCreate, DListDestroy, DListInsertBefore, DListFind, DListRemove, DListForEach, DListCount */
#include "utils.h"   /* DEBUG_BAD_MEM */
#include <stddef.h>  /* offsetof */
/*----------------------------------------------------------------------------*/
#include "hmap.h"
/*----------------------------------------------------------------------------*/
struct pair
{
    const void* key;   /* key used for lookup */
    void* data;        /* value stored */
};

struct hmap
{
    size_t capacity;            /* number of buckets */
    hmap_hash_ty hash_func;     /* function to hash a key to bucket index */
    const void* hash_param;     /* extra param passed to hash_func */
    hmap_is_match_ty is_match;  /* function to compare two keys */
    const void* match_param;    /* extra param passed to is_match */
    dlist_ty* buckets[1];       /* flexible array of dlist pointers */
};
/*----------------------------------------------------------------------------*/
hmap_ty* HMapCreate(size_t capacity, hmap_hash_ty hash_func,
                    const void* hash_param, hmap_is_match_ty is_match,
                    const void* match_param)
{
    /* assert capacity > 0 */
    /* assert hash_func not NULL */
    /* assert is_match not NULL */

    /* hmap_size = offsetof(hmap_ty, buckets) + sizeof(dlist_ty*) * capacity */
    /* hmap = malloc(hmap_size) */
    /* if NULL return NULL */

    /* set hmap->capacity, hash_func, hash_param, is_match, match_param */

    /* for i = 0 to < capacity */
        /* hmap->buckets[i] = DListCreate() */
        /* if NULL call HMapDestroy and return NULL */

    /* return hmap */
}
/*----------------------------------------------------------------------------*/
void HMapDestroy(hmap_ty* hmap_)
{
    /* if hmap_ is NULL return */

    /* for i = 0 to < capacity */
        /* DListForEach to free each pair */
        /* DListDestroy(hmap_->buckets[i]) */
        /* DEBUG_BAD_MEM(hmap_->buckets[i], dlist_ty*) */

    /* free hmap_ */
}
/*----------------------------------------------------------------------------*/
int HMapInsert(hmap_ty* hmap_, const void* key, void* data)
{
    /* assert hmap_ */
    /* assert key */

    /* pair = malloc(sizeof(pair_ty)) */
    /* if NULL return FAIL */

    /* pair->key = key */
    /* pair->data = data */

    /* idx = hash_func(key, hash_param) % capacity */

    /* DListInsertBefore(buckets[idx], DListBeginIter(buckets[idx]), pair) */
    /* if fail free pair and return FAIL */

    /* return SUCCESS */
}
/*----------------------------------------------------------------------------*/
void HMapRemove(hmap_ty* hmap_, const void* key)
{
    /* assert hmap_ */

    /* idx = hash_func(key, hash_param) % capacity */

    /* it = DListFind(buckets[idx], start, end, IsPairMatch, key) */
    /* if it == end return */

    /* pair = DListGetData(it) */
    /* DListRemove(it) */
    /* free pair */
}
/*----------------------------------------------------------------------------*/
pair_ty HMapFind(hmap_ty* hmap_, const void* key)
{
    /* init ret = {0} */
    /* assert hmap_ */

    /* idx = hash_func(key, hash_param) % capacity */

	/* it = DListFind(DListBeginIter(buckets[idx]), DListEndIter(buckets[idx]), IsPairMatch, &match_param) */
    /* if it == end return ret */

    /* ret = *(pair_ty*)DListGetData(it) */
    /* return ret */
}
/*----------------------------------------------------------------------------*/
size_t HMapSize(const hmap_ty* hmap_)
{
    /* init size = 0 */
    /* assert hmap_ */

    /* for i = 0 to < capacity */
        /* size += DListCount(buckets[i]) */

    /* return size */
}
/*----------------------------------------------------------------------------*/
int HMapIsEmpty(const hmap_ty* hmap_)
{
    /* assert hmap_ */

    /* return 0 == HMapSize(hmap_) */
}
/*----------------------------------------------------------------------------*/
int HMapForEach(hmap_ty* hmap_, hmap_action_ty action, void* param)
{
    /* init ret = 0 */
    /* assert hmap_ */
    /* assert action */

    /* for i = 0 to < capacity and ret == 0 */
        /* ret = DListForEach(buckets[i], action, param) */

    /* return ret */
}
/*----------------------------------------------------------------------------*/
