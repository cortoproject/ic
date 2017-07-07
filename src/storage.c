/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>
int16_t ic_storage_construct(
    ic_storage this)
{
    ic_node(this)->kind = IC_STORAGE;
    return ic_node_construct(ic_node(this));
}

void ic_storage_free(
    ic_storage this)
{
    corto_type type = this->type;
    if (this->isReference || ((type->kind == CORTO_PRIMITIVE) && (corto_primitive(type)->kind == CORTO_TEXT))) {
        ic_op freeIc;

        /* Insert free-instruction */
        freeIc = ic_opCreate(0, ic_free, ic_node(this), NULL, NULL, IC_DEREF_VALUE, 0, 0, FALSE);
        if (this->isReference) {
            freeIc->s1Deref = IC_DEREF_ADDRESS;
        }
        ic_program_add(ic_program_get(), ic_node(freeIc));
    }
}

corto_string ic_storage_str(
    ic_storage this,
    corto_string in)
{
    return strappend(in, this->name);
}

