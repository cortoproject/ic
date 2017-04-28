/* $CORTO_GENERATED
 *
 * function.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/ic/ic.h>

int16_t _ic_function_construct(
    ic_function this)
{
/* $begin(corto/ic/function/construct) */
    ic_node(this)->kind = IC_FUNCTION;
    return ic_node_construct(ic_node(this));
/* $end */
}

corto_string _ic_function_str(
    ic_function this,
    corto_string in)
{
/* $begin(corto/ic/function/str) */
    in = strappend(in, "\n%%function %s", corto_fullpath(NULL, this->function));
    return in;
/* $end */
}
