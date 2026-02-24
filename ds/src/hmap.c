#include "dlist"

struct pair_ty
{
	void* key;
	void* data;
};

struct hmap
{
	size_t capacity;
	dlist_iter_ty* arr; /*its dlist_node** data field points at pair_Ty */
}

hmap_ty* HMapCreate(size_t capacity, hmap_hash_ty hash_func,
                    const void* hash_param, hmap_is_match_ty is_match,
                    const void* match_param)
{
    /* assert capacity > 0 and hash_func and is_match are not NULL */
    /* allocate memory for hmap including capacity buckets */
    /* if allocation failed return NULL */
    /* set capacity, hash_func, hash_param, is_match, match_param in struct */
    /* for each bucket index create empty DList */
    /* if any DListCreate fails destroy created lists and free hmap then return NULL */
    /* return initialized hmap */
}

void HMapDestroy(hmap_ty* hmap)
{
    /* if hmap is NULL return */
    /* for each bucket */
        /* free all pairs using DListForEach with FreePair */
        /* destroy the DList */
    /* free hmap structure */
}
