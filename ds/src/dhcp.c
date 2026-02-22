struct dhcp
{
    btrie_ty* trie;       /* tracks which host addresses are allocated/free */
    addr_ty subnet_id;    /* the network part of the address (the common part)*/
    addr_ty subnet_mask;  /* separates network bits from host bits*/
};

dhcp_ty* DhcpCreate(addr_ty subnet_id_, unsigned int host_numb_)
{
/* assert host_numb_ > 0 */
/* assert host_numb_ <= 32 */

/* allocate dhcp */
/* if failed return NULL */

/* num_bits = 32 - host_numb_ */
/* subnet_mask = all ones shifted left by host_numb_ bits */

/* create trie with num_bits */
/* if failed free dhcp and return NULL */

/* set dhcp fields (trie, subnet_id, subnet_mask) */

/* server = (1 << host_numb_) - 2 */
/* broadcast = (1 << host_numb_) - 1 */

/* reserve server with BTrieGet */
/* if failed destroy trie, free dhcp, return NULL */

/* reserve broadcast with BTrieGet */
/* if failed destroy trie, free dhcp, return NULL */

/* return dhcp */
}



