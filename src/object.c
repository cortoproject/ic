/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>
int16_t ic_object_construct(
    ic_object this)
{
    ic_storage(this)->kind = IC_OBJECT;
    ic_storage(this)->name = corto_strdup(corto_fullpath(NULL, this->ptr));
    corto_ptr_setref(&ic_storage(this)->type, corto_typeof(this->ptr));
    ic_storage(this)->isReference = TRUE;
    return ic_storage_construct(ic_storage(this));
}

