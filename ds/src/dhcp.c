struct dhcp
{
    btrie_ty* trie;       /* tracks which host addresses are allocated/free */
    addr_ty subnet_id;    /* the network part of the address (the common part)*/
    addr_ty subnet_mask;  /* separates network bits from host bits*/
};
