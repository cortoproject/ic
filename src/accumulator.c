/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>
int16_t ic_accumulator_construct(
    ic_accumulator this)
{
    char name[15];
    ic_storage(this)->kind = IC_ACCUMULATOR;
    sprintf(name, "#%d", ic_program_getAccId(ic_program_get()));
    ic_storage(this)->name = corto_strdup(name);

    ic_scope_addStorage(ic_program_get()->scope, ic_storage(this));

    return ic_storage_construct(ic_storage(this));
}

