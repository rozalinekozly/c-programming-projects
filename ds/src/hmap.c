#include <stdlib.h>  /* malloc, free, calloc */
#include <assert.h>  /* assert */
#include <stddef.h>  /* offsetof */
/*----------------------------------------------------------------------------*/
#include "hmap.h"
#include "dlist.h"   /* DListCreate, DListDestroy, DListInsertBefore, DListFind, DListRemove, DListForEach, DListCount */
#include "utils.h"   /* DEBUG_BAD_MEM */
/*----------------------------------------------------------------------------*/
struct hmap
{
    size_t capacity;            /* number of buckets */
    hmap_hash_ty hash_func;     /* function to hash a key to bucket index */
    const void* hash_param;     /* extra param passed to hash_func */
    hmap_is_match_ty is_match;  /* function to compare two keys */
    const void* match_param;    /* extra param passed to is_match */
    dlist_ty** buckets;         /* pointer to array of dlist pointers */
};
/*----------------------------------------------------------------------------*/
typedef struct
{
    hmap_ty* hmap;
    const void* key;
} find_param_ty;
/*----------------------------------------------------------------------------*/
typedef struct
{
    hmap_action_ty action_func;
    void* action_param;
} foreach_param_ty;
/*---------------------forward declarations-----------------------------------*/
static size_t HashToIndexIMP(hmap_ty* hmap_, const void* key);
static int IsKeyMatchIMP(const void* pair_, void* param_);
static int WrapActionIMP(void* pair_, void* param_);
static int FreePairIMP(void* pair_, void* param_);
/*----------------------------------------------------------------------------*/
hmap_ty* HMapCreate(size_t capacity, hmap_hash_ty hash_func,
                    const void* hash_param, hmap_is_match_ty is_match,
                    const void* match_param)
{
    /* assert capacity > 0 */
    /* assert hash_func not NULL */
    /* assert is_match not NULL */

    /* hmap = malloc(sizeof(hmap_ty)) */
    /* if NULL return NULL */

    /* hmap->buckets = calloc(capacity, sizeof(dlist_ty*)) */
    /* if NULL free hmap and return NULL */

    /* set hmap->capacity, hash_func, hash_param, is_match, match_param */

    /* curr = hmap->buckets */
    /* end = hmap->buckets + capacity */
    /* while curr != end */
        /* *curr = DListCreate() */
        /* if NULL call HMapDestroy and return NULL */
        /* ++curr */

    /* return hmap */
}
/*----------------------------------------------------------------------------*/
void HMapDestroy(hmap_ty* hmap_)
{
    /* if hmap_ is NULL return */

    /* curr = hmap_->buckets */
    /* end = hmap_->buckets + hmap_->capacity */
    /* while curr != end */
        /* if *curr is not NULL */
            /* dlist_iter_ty end_it = DListEndIter(*curr) */
            /* DListForEach(DListBeginIter(*curr), end_it, FreePairIMP, NULL) */
            /* DEBUG_BAD_MEM(*curr, dlist_ty*) */
            /* DListDestroy(*curr) */
        /* ++curr */

    /* free hmap_->buckets */
    /* free hmap_ */
}
/*----------------------------------------------------------------------------*/
int HMapInsert(hmap_ty* hmap_, const void* key, void* data)
{
    /* assert hmap_ */
    /* assert key */
    /* assert key does not exist: HMapFind(hmap_, key).key == NULL */

    /* pair = malloc(sizeof(pair_ty)) */
    /* if NULL return FAIL */

    /* pair->key = key */
    /* pair->data = data */

    /* idx = HashToIndexIMP(hmap_, key) */

    /* end_it = DListEndIter(hmap_->buckets[idx]) */
    /* if DListInsertBefore(hmap_->buckets[idx], DListBeginIter(hmap_->buckets[idx]), pair) == NULL */
        /* free pair and return FAIL */

    /* return SUCCESS */
}
/*----------------------------------------------------------------------------*/
void HMapRemove(hmap_ty* hmap_, const void* key)
{
    /* assert hmap_ */
    /* assert key */

    /* find_param_ty find_param = {0} */
    /* idx = HashToIndexIMP(hmap_, key) */
    /* find_param.hmap = hmap_ */
    /* find_param.key = key */

    /* end_it = DListEndIter(hmap_->buckets[idx]) */
    /* it = DListFind(DListBeginIter(hmap_->buckets[idx]), end_it, IsKeyMatchIMP, &find_param) */
    /* if it == end_it return */

    /* pair = DListIterGetData(it) */
    /* DListRemove(it) */
    /* free pair */
}
/*----------------------------------------------------------------------------*/
pair_ty HMapFind(hmap_ty* hmap_, const void* key)
{
    /* init ret (pair_ty) = {0} */
    /* assert hmap_ */
    /* assert key */

    /* find_param_ty find_param = {0} */
    /* idx = HashToIndexIMP(hmap_, key) */
    /* find_param.hmap = hmap_ */
    /* find_param.key = key */

    /* end_it = DListEndIter(hmap_->buckets[idx]) */
    /* it = DListFind(DListBeginIter(hmap_->buckets[idx]), end_it, IsKeyMatchIMP, &find_param) */
    /* if it == end_it return ret */

    /* ret = *(pair_ty*)DListIterGetData(it) */
    /* return ret (copy by value) */
}
/*----------------------------------------------------------------------------*/
size_t HMapSize(const hmap_ty* hmap_)
{
    /* init size = 0 */
    /* assert hmap_ */

    /* curr = hmap_->buckets */
    /* end = hmap_->buckets + hmap_->capacity */
    /* while curr != end */
        /* size += DListCount(*curr) */
        /* ++curr */

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

    /* foreach_param_ty foreach_param = {0} */
    /* foreach_param.action_func = action */
    /* foreach_param.action_param = param */

    /* curr = hmap_->buckets */
    /* end = hmap_->buckets + hmap_->capacity */
    /* while curr != end && 0 == ret */
        /* ret = DListForEach(DListBeginIter(*curr), DListEndIter(*curr), WrapActionIMP, &foreach_param) */
        /* ++curr */

    /* return ret */
}
/*----------------------------------------------------------------------------*/
static size_t HashToIndexIMP(hmap_ty* hmap_, const void* key)
{
    /* assert hmap_ */
    /* assert key */
    /* return hmap_->hash_func(key, hmap_->hash_param) % hmap_->capacity */
}
/*----------------------------------------------------------------------------*/
static int IsKeyMatchIMP(const void* pair_, void* param_)
{
    /* assert pair_ */
    /* assert param_ */
    /* find_param_ty* find_param = (find_param_ty*)param_ */
    /* key1 = ((pair_ty*)pair_)->key */
    /* key2 = find_param->key */
    /* return find_param->hmap->is_match(key1, key2, find_param->hmap->match_param) */
}
/*----------------------------------------------------------------------------*/
static int WrapActionIMP(void* pair_, void* param_)
{
    /* assert pair_ */
    /* assert param_ */
    /* foreach_param_ty* foreach_param = (foreach_param_ty*)param_ */
    /* return foreach_param->action_func(((pair_ty*)pair_)->key, ((pair_ty*)pair_)->data, foreach_param->action_param) */
}
/*----------------------------------------------------------------------------*/
static int FreePairIMP(void* pair_, void* param_)
{
    /* (void)param_ */
    /* free pair_ */
    /* return SUCCESS */
}
