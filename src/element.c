/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>
int16_t ic_element_construct(
    ic_element this)
{
    corto_id name;
    corto_collection type = corto_collection(this->base->type);

    ic_storage(this)->kind = IC_ELEMENT;
    corto_ptr_setref(&ic_storage(this)->type, type->elementType);
    corto_ptr_setref(&ic_storage(this)->base, this->base);
    ic_storage(this)->isReference = type->elementType->reference;

    if (this->index) {
        corto_string elemStr = ic_node_str(this->index, NULL);
        sprintf(name, "%s[%s]", this->base->name, elemStr);
        corto_dealloc(elemStr);
    } else {
        sprintf(name, "*%s", this->base->name);
    }

    ic_storage(this)->name = corto_strdup(name);

    return ic_storage_construct(ic_storage(this));

}

