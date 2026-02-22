struct dhcp
{
    btrie_ty* trie;       /* tracks which host addresses are allocated/free */
    addr_ty subnet_id;    /* the network part of the address (the common part)*/
    addr_ty subnet_mask;  /* separates network bits from host bits*/
};

dhcp_ty* DhcpCreate(addr_ty subnet_id_, unsigned int host_numb_)
{
	/* asserts */
	/* allocate dhcp */
	/* if failed return NULL */
	/* calculate host_numb (32 - subnet bits) */
	/* allocate btrie using BTrieCreate(host_numb) */
	/* if failed free dhcp and return NULL */
	/* set fields (trie, subnet_id, subnet_mask) */
	/* reserve server address 111...110 using BTrieGet */
	/* reserve broadcast address 111...111 using BTrieGet */
	/* if any reservation failed destroy trie, free dhcp and return NULL */
	/* return dhcp */
}



