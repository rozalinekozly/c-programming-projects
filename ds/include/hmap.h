#ifndef __HMAP_H__
#define __HMAP_H__

typedef struct hmap hmap_ty;
typedef struct pair pair_ty;

/* hash function */
typedef size_t (*hmap_hash_ty) (const void* key, const void* param);

/* is_match func for key */
typedef int (*hmap_is_match_ty) (const void* key_a, const void* key_b, const void* param);

/*returns non_zero if wants to stop*/
typedef int (*hmap_action_ty) (const void* key, void* data, void* param);


hmap_ty* HMapCreate(size_t capacity, hmap_hash_ty hash_func, const void* hash_param, hmap_is_match_ty is_match, const void* match_param);

void HMapDestroy(hmap_ty* hmap_);

void HMapRemove(hmap_ty* hmap_, const void* key);

int HMapInsert(hmap_ty* hmap, const void* key, void* data);

size_t HMapSize(const hmap_ty* hmap_);
int HMapIsEmpty(const hmap_ty* hmap_);
pair_ty HMapFind(hmap_ty* hmap, const void* key);

/*order is not specified*/
int HMapForEach(hmap_ty* hmap, hmap_action_ty action, void* param);

/*
unsigned long hashstring(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        // hash * 33 + c
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

*/

#endif /* __HMAP_H__ */
