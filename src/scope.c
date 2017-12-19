/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>
void ic_scope_add(
    ic_scope this,
    ic_node n)
{
    corto_ll_append(this->program, n);
}

void ic_scope_addStorage(
    ic_scope this,
    ic_storage s)
{
    corto_ll_append(this->storages, s);
    corto_ptr_setref(&s->scope, this);
}

int16_t ic_scope_construct(
    ic_scope this)
{
    ic_node(this)->kind = IC_SCOPE;
    return ic_node_construct(ic_node(this));
}

ic_storage ic_scope_lookupStorage(
    ic_scope this,
    const char *name,
    bool recursive)
{
    corto_iter storageIter;
    ic_storage result = NULL;

    storageIter = corto_ll_iter(this->storages);
    while(corto_iter_hasNext(&storageIter)) {
        result = corto_iter_next(&storageIter);
        if (!strcmp(result->name, name)) {
            break;
        } else {
            result = NULL;
        }

    }

    if (!result && this->parent && recursive && !this->isFunction) {
        result = ic_scope_lookupStorage(this->parent, name, TRUE);
    }

    return result;
}

corto_string ic_scope_str(
    ic_scope this,
    char *in)
{
    corto_iter programIter, storageIter;
    ic_storage storage;
    corto_uint32 storages = 0;
    ic_node ic;
    corto_string result = in;

    storageIter = corto_ll_iter(this->storages);
    while(corto_iter_hasNext(&storageIter)) {
        storage = corto_iter_next(&storageIter);
        if (storage->kind == IC_VARIABLE) {
            storages ++;
        }

    }

    if (storages) {
        result = strappend(result, "%%scopepush\n");
    }

    storageIter = corto_ll_iter(this->storages);
    while(corto_iter_hasNext(&storageIter)) {
        storage = corto_iter_next(&storageIter);
        if (storage->kind == IC_VARIABLE) {
            result = strappend(
              result,
              "%%var %s %s%s\n",
              storage->name,
              corto_fullpath(NULL, storage->type),
              storage->isReference ? "&" : "");
        }

    }

    programIter = corto_ll_iter(this->program);
    while(corto_iter_hasNext(&programIter)) {
        ic = corto_iter_next(&programIter);
        result = ic_node_str(ic, result);
        result = strappend(result, "\n");
    }

    if (storages) {
        result = strappend(result, "%%scopepop\n");
    }

    return result;
}

