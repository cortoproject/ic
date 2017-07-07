/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>
int16_t ic_literal_construct(
    ic_literal this)
{
    ic_node(this)->kind = IC_LITERAL;
    return ic_node_construct(ic_node(this));
}

corto_string ic_literal_str(
    ic_literal this,
    corto_string in)
{
    corto_string result = NULL;

    if (this->value.value) {
        if (corto_primitive(this->value.type)->kind == CORTO_TEXT) {
            in = strappend(in, "\"");
        }
        corto_ptr_cast(corto_primitive(this->value.type), this->value.value, corto_primitive(corto_string_o), &result);
        in = strappend(in, result);
        corto_dealloc(result);
        if (corto_primitive(this->value.type)->kind == CORTO_TEXT) {
            in = strappend(in, "\"");
        }
    } else {
        in = strappend(in, "(null)");
    }

    return in;
}

