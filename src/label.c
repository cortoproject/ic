/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>
int16_t ic_label_construct(
    ic_label this)
{
    ic_node(this)->kind = IC_LABEL;
    this->id = ic_program_getLabel(ic_program_get());
    return ic_node_construct(ic_node(this));
}

corto_string ic_label_str(
    ic_label this,
    corto_string in)
{
    in = strappend(in, "%%L%d", this->id);
    return in;
}

