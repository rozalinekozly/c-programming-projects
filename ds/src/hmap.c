#include <stdlib.h>  /* malloc, free, calloc */
#include <assert.h>  /* assert */
#include <stddef.h>  /* offsetof */
/*----------------------------------------------------------------------------*/
#include "hmap.h"
#include "dlist.h"   /* DListCreate, DListDestroy, DListInsertBefore, DListFind, DListRemove, DListForEach, DListCount */
#include "utils.h"   /* DEBUG_BAD_MEM */
/*----------------------------------------------------------------------------*/
typedef enum { SUCCESS = 0, FAIL = 1 } status_ty;
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
    dlist_ty** curr = NULL;
    dlist_ty** end = NULL;
    hmap_ty* hmap = NULL;

    /* assert capacity > 0 */
    assert(capacity > 0);
    /* assert hash_func not NULL */
    assert(hash_func);
    /* assert is_match not NULL */
    assert(is_match);

    /* hmap = malloc(sizeof(hmap_ty)) */
    hmap = malloc(sizeof(hmap_ty));
    /* if NULL return NULL */
    if (NULL == hmap)
    {
        return NULL;
    }

    /* hmap->buckets = calloc(capacity, sizeof(dlist_ty*)) */
    hmap->buckets = calloc(capacity, sizeof(dlist_ty*));
    /* if NULL free hmap and return NULL */
    if (NULL == hmap->buckets)
    {
        free(hmap);
        return NULL;
    }

    /* set hmap->capacity, hash_func, hash_param, is_match, match_param */
    hmap->capacity = capacity;
    hmap->hash_func = hash_func;
    hmap->hash_param = hash_param;
    hmap->is_match = is_match;
    hmap->match_param = match_param;

    /* curr = hmap->buckets */
    curr = hmap->buckets;
    /* end = hmap->buckets + capacity */
    end = hmap->buckets + capacity;
    /* while curr != end */
    while (curr != end)
    {
        /* *curr = DListCreate() */
        *curr = DListCreate();
        /* if NULL call HMapDestroy and return NULL */
        if (NULL == *curr)
        {
            HMapDestroy(hmap);
            return NULL;
        }
        /* ++curr */
        ++curr;
    }

    /* return hmap */
    return hmap;
}
/*----------------------------------------------------------------------------*/
void HMapDestroy(hmap_ty* hmap_)
{
    dlist_ty** curr = NULL;
    dlist_ty** end = NULL;

    /* if hmap_ is NULL return */
    if (NULL == hmap_)
    {
        return;
    }

    /* curr = hmap_->buckets */
    curr = hmap_->buckets;
    /* end = hmap_->buckets + hmap_->capacity */
    end = hmap_->buckets + hmap_->capacity;
    /* while curr != end */
    while (curr != end)
    {
        /* if *curr is not NULL */
        if (NULL != *curr)
        {
            /* end_it = DListEndIter(*curr) */
            dlist_iter_ty end_it = DListEndIter(*curr);
            /* DListForEach(DListBeginIter(*curr), end_it, FreePairIMP, NULL) */
            DListForEach(DListBeginIter(*curr), end_it, FreePairIMP, NULL);
            /* DEBUG_BAD_MEM(*curr, dlist_ty*) */
            DEBUG_BAD_MEM(*curr, dlist_ty*);
            /* DListDestroy(*curr) */
            DListDestroy(*curr);
        }
        /* ++curr */
        ++curr;
    }

    /* free hmap_->buckets */
    free(hmap_->buckets);
    /* free hmap_ */
    free(hmap_);
}
/*----------------------------------------------------------------------------*/
int HMapInsert(hmap_ty* hmap_, const void* key, void* data)
{
    size_t idx = 0;
    pair_ty* pair = NULL;

    /* assert hmap_ */
    assert(hmap_);
    /* assert key */
    assert(key);
    /* assert key does not exist */
    assert(NULL == HMapFind(hmap_, key).key);

    /* pair = malloc(sizeof(pair_ty)) */
    pair = malloc(sizeof(pair_ty));
    /* if NULL return FAIL */
    if (NULL == pair)
    {
        return FAIL;
    }

    /* pair->key = key */
    pair->key = key;
    /* pair->data = data */
    pair->data = data;

    /* idx = HashToIndexIMP(hmap_, key) */
    idx = HashToIndexIMP(hmap_, key);

    /* if DListInsertBefore failed */
    if (NULL == DListInsertBefore(hmap_->buckets[idx],
                                  DListBeginIter(hmap_->buckets[idx]),
                                  pair))
    {
        /* free pair and return FAIL */
        free(pair);
        return FAIL;
    }

    /* return SUCCESS */
    return SUCCESS;
}
/*----------------------------------------------------------------------------*/
void HMapRemove(hmap_ty* hmap_, const void* key)
{
    size_t idx = 0;
    dlist_iter_ty end_it;
    dlist_iter_ty it;
    find_param_ty find_param = {0};
    pair_ty* pair = NULL;

    /* assert hmap_ */
    assert(hmap_);
    /* assert key */
    assert(key);

    /* idx = HashToIndexIMP(hmap_, key) */
    idx = HashToIndexIMP(hmap_, key);
    /* find_param.hmap = hmap_ */
    find_param.hmap = hmap_;
    /* find_param.key = key */
    find_param.key = key;

    /* end_it = DListEndIter(hmap_->buckets[idx]) */
    end_it = DListEndIter(hmap_->buckets[idx]);
    /* it = DListFind(...) */
    it = DListFind(DListBeginIter(hmap_->buckets[idx]), end_it, IsKeyMatchIMP, &find_param);
    /* if it == end_it return */
    if (DListIterIsEqual(end_it, it))
    {
        return;
    }

    /* pair = DListIterGetData(it) */
    pair = (pair_ty*)DListIterGetData(it);
    /* DListRemove(it) */
    DListRemove(it);
    /* free pair */
    free(pair);
}
/*----------------------------------------------------------------------------*/
pair_ty HMapFind(hmap_ty* hmap_, const void* key)
{
    size_t idx = 0;
    dlist_iter_ty end_it;
    dlist_iter_ty it;
    find_param_ty find_param = {0};
    pair_ty ret = {0};

    /* assert hmap_ */
    assert(hmap_);
    /* assert key */
    assert(key);

    /* idx = HashToIndexIMP(hmap_, key) */
    idx = HashToIndexIMP(hmap_, key);
    /* find_param.hmap = hmap_ */
    find_param.hmap = hmap_;
    /* find_param.key = key */
    find_param.key = key;

    /* end_it = DListEndIter(hmap_->buckets[idx]) */
    end_it = DListEndIter(hmap_->buckets[idx]);
    /* it = DListFind(...) */
    it = DListFind(DListBeginIter(hmap_->buckets[idx]), end_it, IsKeyMatchIMP, &find_param);
    /* if it == end_it return ret */
    if (DListIterIsEqual(end_it, it))
    {
        return ret;
    }

    /* ret = *(pair_ty*)DListIterGetData(it) */
    ret = *(pair_ty*)DListIterGetData(it);
    /* return ret */
    return ret;
}
/*----------------------------------------------------------------------------*/
size_t HMapSize(const hmap_ty* hmap_)
{
    size_t size = 0;
    dlist_ty** curr = NULL;
    dlist_ty** end = NULL;

    /* assert hmap_ */
    assert(hmap_);

    /* curr = hmap_->buckets */
    curr = hmap_->buckets;
    /* end = hmap_->buckets + hmap_->capacity */
    end = hmap_->buckets + hmap_->capacity;
    /* while curr != end */
    while (curr != end)
    {
        /* size += DListCount(*curr) */
        size += DListCount(*curr);
        /* ++curr */
        ++curr;
    }

    /* return size */
    return size;
}
/*----------------------------------------------------------------------------*/
int HMapIsEmpty(const hmap_ty* hmap_)
{
    /* assert hmap_ */
    assert(hmap_);

    /* return 0 == HMapSize(hmap_) */
    return 0 == HMapSize(hmap_);
}
/*----------------------------------------------------------------------------*/
int HMapForEach(hmap_ty* hmap_, hmap_action_ty action, void* param)
{
    int ret = 0;
    dlist_ty** curr = NULL;
    dlist_ty** end = NULL;
    foreach_param_ty foreach_param = {0};

    /* assert hmap_ */
    assert(hmap_);
    /* assert action */
    assert(action);

    /* foreach_param.action_func = action */
    foreach_param.action_func = action;
    /* foreach_param.action_param = param */
    foreach_param.action_param = param;

    /* curr = hmap_->buckets */
    curr = hmap_->buckets;
    /* end = hmap_->buckets + hmap_->capacity */
    end = hmap_->buckets + hmap_->capacity;
    /* while curr != end && 0 == ret */
    while (curr != end && 0 == ret)
    {
        /* ret = DListForEach(...) */
        ret = DListForEach(DListBeginIter(*curr), DListEndIter(*curr), WrapActionIMP, &foreach_param);
        /* ++curr */
        ++curr;
    }

    /* return ret */
    return ret;
}
/*----------------------------------------------------------------------------*/
static size_t HashToIndexIMP(hmap_ty* hmap_, const void* key)
{
    /* assert hmap_ */
    assert(hmap_);
    /* assert key */
    assert(key);

    /* return hmap_->hash_func(key, hmap_->hash_param) % hmap_->capacity */
    return hmap_->hash_func(key, hmap_->hash_param) % hmap_->capacity;
}
/*----------------------------------------------------------------------------*/
static int IsKeyMatchIMP(const void* pair_, void* param_)
{
    find_param_ty* find_param = NULL;
    const void* key1 = NULL;
    const void* key2 = NULL;

    /* assert pair_ */
    assert(pair_);
    /* assert param_ */
    assert(param_);

    /* find_param = (find_param_ty*)param_ */
    find_param = (find_param_ty*)param_;
    /* key1 = ((pair_ty*)pair_)->key */
    key1 = ((pair_ty*)pair_)->key;
    /* key2 = find_param->key */
    key2 = find_param->key;

    /* return find_param->hmap->is_match(key1, key2, find_param->hmap->match_param) */
    return find_param->hmap->is_match(key1, key2, find_param->hmap->match_param);
}
/*----------------------------------------------------------------------------*/
static int WrapActionIMP(void* pair_, void* param_)
{
    foreach_param_ty* foreach_param = NULL;

    /* assert pair_ */
    assert(pair_);
    /* assert param_ */
    assert(param_);

    /* foreach_param = (foreach_param_ty*)param_ */
    foreach_param = (foreach_param_ty*)param_;

    /* return action_func(pair->key, pair->data, action_param) */
    return foreach_param->action_func(((pair_ty*)pair_)->key,
                                      ((pair_ty*)pair_)->data,
                                      foreach_param->action_param);
}
/*----------------------------------------------------------------------------*/
static int FreePairIMP(void* pair_, void* param_)
{
    /* (void)param_ */
    (void)param_;
    /* free pair_ */
    free(pair_);

    /* return SUCCESS */
    return SUCCESS;
}
