/* $CORTO_GENERATED
 *
 * variable.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/ic/ic.h>

int16_t _ic_variable_construct(
    ic_variable this)
{
/* $begin(corto/ic/variable/construct) */
    ic_storage(this)->kind = IC_VARIABLE;
    return ic_storage_construct(ic_storage(this));
/* $end */
}
