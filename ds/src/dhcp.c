#include <stdlib.h>  /* malloc, free */
#include <assert.h>  /* assert */
#include "dhcp.h"
#include "btrie.h"   /* BTrieCreate, BTrieGet, BTrieRelease, BTrieCountAvailable */
#include "utils.h"   /* DEBUG_BAD_MEM */

struct dhcp
{
    btrie_ty* trie;       /* tracks which host addresses are allocated/free */
    addr_ty subnet_id;    /* the network part of the address (the common part)*/
    addr_ty subnet_mask;  /* separates network bits from host bits*/
};

dhcp_ty* DhcpCreate(addr_ty subnet_id_, unsigned int host_numb_)
{
    dhcp_ty* ret = NULL;
    btrie_ty* trie = NULL;
    addr_ty server = 0;
    addr_ty broadcast = 0;

    /* assert host_numb_ > 0 */
    assert(host_numb_ > 0);
    /* assert host_numb_ <= 32 */
    assert(host_numb_ <= 32);

    /* allocate dhcp */
    ret = malloc(sizeof(dhcp_ty));
    /* if failed return NULL */
    if (NULL == ret)
    {
        return NULL;
    }

    /* subnet_mask = all ones shifted left by host_numb_ bits */
    ret->subnet_mask = (~(addr_ty)0 << host_numb_);
    /* set dhcp fields (trie, subnet_id, subnet_mask) */
    ret->subnet_id = subnet_id_;

    /* create trie with host_numb_ */
    trie = BTrieCreate(host_numb_);
    /* if failed free dhcp and return NULL */
    if (NULL == trie)
    {
        free(ret);
        return NULL;
    }

    ret->trie = trie;

    /* server = (1 << host_numb_) - 2 */
    server = ((addr_ty)1 << host_numb_) - 2;
    /* broadcast = (1 << host_numb_) - 1 */
    broadcast = ((addr_ty)1 << host_numb_) - 1;

    /* reserve server with BTrieGet */
    /* if failed destroy trie, free dhcp, return NULL */
    if (0 == BTrieGet(trie, server))
    {
        BTrieDestroy(trie);
        free(ret);
        return NULL;
    }

    /* reserve broadcast with BTrieGet */
    /* if failed destroy trie, free dhcp, return NULL */
    if (0 == BTrieGet(trie, broadcast))
    {
        BTrieDestroy(trie);
        free(ret);
        return NULL;
    }

    /* return dhcp */
    return ret;
}

void DhcpDestroy(dhcp_ty* dhcp_)
{
    /* if dhcp_ is NULL return */
	/* destroy trie */
	/* set bad mem on trie field */
	/* free dhcp */
}

size_t DhcpCountFree(const dhcp_ty* dhcp_)
{
    (void)dhcp_;
    return 0;
}


