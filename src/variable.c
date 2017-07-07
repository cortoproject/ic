/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>
int16_t ic_variable_construct(
    ic_variable this)
{
    ic_storage(this)->kind = IC_VARIABLE;
    return ic_storage_construct(ic_storage(this));
}

