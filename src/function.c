/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>
int16_t ic_function_construct(
    ic_function this)
{
    ic_node(this)->kind = IC_FUNCTION;
    return ic_node_construct(ic_node(this));
}

corto_string ic_function_str(
    ic_function this,
    char *in)
{
    in = strappend(in, "\n%%function %s", corto_fullpath(NULL, this->function));
    return in;
}

