/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>
int16_t ic_address_construct(
    ic_address this)
{
    ic_node(this)->kind = IC_ADDRESS;
    return ic_node_construct(ic_node(this));
}

