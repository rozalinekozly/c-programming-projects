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

int HMapInsert(hmap_ty* hmap, const void* key, void* data)
{
    /* assert hmap and key are not NULL */
    /* allocate new pair */
    /* if allocation failed return FAILURE */
    /* initialize pair->first = key and pair->second = data */
    /* calculate idx using GetEntry(hmap, key) */
    /* get list = hmap->entries[idx] */
    /* insert pair into list */
    /* if insertion failed free pair and return FAILURE */
    /* return SUCCESS */
}

void HMapRemove(hmap_ty* hmap, const void* key)
{
    /* assert hmap and key are not NULL */
    /* calculate idx using GetEntry(hmap, key) */
    /* get list = hmap->entries[idx] */
    /* initialize match_param with hmap and key */
    /* find iterator using DListFind with IsPairMatch */
    /* if iterator equals end return */
    /* extract pair from iterator */
    /* remove iterator from list */
    /* free pair */
}

pair_ty HMapFind(hmap_ty* hmap, const void* key)
{
    /* assert hmap and key are not NULL */
    /* calculate idx using GetEntry(hmap, key) */
    /* get list = hmap->entries[idx] */
    /* initialize match_param with hmap and key */
    /* find iterator using DListFind with IsPairMatch */
    /* if iterator equals end return empty pair */
    /* return pair stored in iterator */
}
