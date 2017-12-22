/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>
int16_t ic_member_construct(
    ic_member this)
{
    corto_id name;

    ic_storage(this)->kind = IC_MEMBER;
    corto_set_ref(&ic_storage(this)->type, this->member->type);
    corto_set_ref(&ic_storage(this)->base, this->base);
    ic_storage(this)->isReference = this->member->type->reference;
    sprintf(name, "%s.%s", this->base->name, corto_idof(this->member));
    ic_storage(this)->name = corto_strdup(name);

    return ic_storage_construct(ic_storage(this));
}

