/* $CORTO_GENERATED
 *
 * address.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/ic/ic.h>

corto_int16 _ic_address_construct(
    ic_address this)
{
/* $begin(corto/ic/address/construct) */
    ic_node(this)->kind = IC_ADDRESS;
    return ic_node_construct(ic_node(this));
/* $end */
}
