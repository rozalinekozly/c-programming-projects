#include <stdlib.h>  /* malloc, free */
#include <assert.h>  /* assert */
/*----------------------------------------------------------------------------*/
#include "dhcp.h"
#include "btrie.h"   /* BTrieCreate, BTrieGet, BTrieRelease, BTrieCountAvailable */
#include "utils.h"   /* DEBUG_BAD_MEM */
/*----------------------------------------------------------------------------*/
enum
{
	IPV4 = 32,
	IPV6  = 64
};
/*----------------------------------------------------------------------------*/
struct dhcp
{
    btrie_ty* trie;       /* tracks which host addresses are allocated/free */
    addr_ty subnet_id;    /* the network part of the address (the common part)*/
    addr_ty subnet_mask;  /* separates network bits from host bits*/
};
/*----------------------------------------------------------------------------*/
dhcp_ty* DhcpCreate(addr_ty subnet_id_, unsigned int host_numb_)
{
    dhcp_ty* ret = NULL;
    btrie_ty* trie = NULL;
    addr_ty server = 0;
    addr_ty broadcast = 0;

    /* allocate dhcp */
    ret = (dhcp_ty*)malloc(sizeof(dhcp_ty));
    /* if failed return NULL */
    if (NULL == ret)
    {
        return NULL;
    }
    
    /* assert host_numb_ > 0 */
    assert(host_numb_ > 0);
    /* assert host_numb_ <= IPV4 */
    assert(host_numb_ <= IPV4);

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
    if (NULL == dhcp_)
    {
        return;
    }

    /* destroy trie */
    BTrieDestroy(dhcp_->trie);

    /* set bad mem on trie field */
    DEBUG_BAD_MEM(dhcp_->trie, btrie_ty*);

    /* free dhcp */
    free(dhcp_);
}

addr_ty DhcpAllocateIp(dhcp_ty* dhcp_, addr_ty addr_)
{
    addr_ty host = 0;
    addr_ty ret = 0;

    /* assert dhcp_ */
    assert(dhcp_);
	/*assert that addr_ belongs to passed instance dhcp_*/
	assert(dhcp_->subnet_id == (dhcp_->subnet_mask & addr_));
	
    /* extract host part from addr_ */
    /* host = addr_ & ~dhcp_->subnet_mask */
    host = addr_ & ~dhcp_->subnet_mask;

    /* ret = BTrieGet(trie, host) */
    ret = BTrieGet(dhcp_->trie, host);

    /* if 0 == ret (failed) */
    if (0 == ret)
    {
        /* ret = BTrieGet(trie, 0) */
        ret = BTrieGet(dhcp_->trie, 0);
        /* if 0 == ret (failed) */
        if (0 == ret)
        {
            /* return 0 */
            return 0;
        }
    }

    /* return ret | dhcp_->subnet_id */
    return ret | dhcp_->subnet_id;
}

void DhcpFreeIp(dhcp_ty* dhcp_, addr_ty addr_)
{
    addr_ty host = 0;

    /* assert dhcp_ */
    assert(dhcp_);
	/*assert that addr_ belongs to passed instance dhcp_*/
	assert(dhcp_->subnet_id == (dhcp_->subnet_mask & addr_));
	
    /* extract host part: host = addr_ & ~dhcp_->subnet_mask */
    host = addr_ & ~dhcp_->subnet_mask;

    /* call BTrieRelease(trie, host) */
    BTrieRelease(dhcp_->trie, host);
}

size_t DhcpCountFree(const dhcp_ty* dhcp_)
{
    /* assert dhcp_ */
    assert(dhcp_);

    /* return BTrieCountAvailable(trie) */
    return BTrieCountAvailable(dhcp_->trie);
}


