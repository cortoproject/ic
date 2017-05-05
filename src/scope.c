/* $CORTO_GENERATED
 *
 * scope.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/ic/ic.h>

void _ic_scope_add(
    ic_scope this,
    ic_node n)
{
/* $begin(corto/ic/scope/add) */
    corto_llAppend(this->program, n);
/* $end */
}

void _ic_scope_addStorage(
    ic_scope this,
    ic_storage s)
{
/* $begin(corto/ic/scope/addStorage) */
    corto_llAppend(this->storages, s);
    corto_setref(&s->scope, this);
/* $end */
}

int16_t _ic_scope_construct(
    ic_scope this)
{
/* $begin(corto/ic/scope/construct) */
    ic_node(this)->kind = IC_SCOPE;
    return ic_node_construct(ic_node(this));
/* $end */
}

ic_storage _ic_scope_lookupStorage(
    ic_scope this,
    corto_string name,
    bool recursive)
{
/* $begin(corto/ic/scope/lookupStorage) */
    corto_iter storageIter;
    ic_storage result = NULL;

    storageIter = corto_llIter(this->storages);
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
/* $end */
}

corto_string _ic_scope_str(
    ic_scope this,
    corto_string in)
{
/* $begin(corto/ic/scope/str) */
    corto_iter programIter, storageIter;
    ic_storage storage;
    corto_uint32 storages = 0;
    ic_node ic;
    corto_string result = in;

    storageIter = corto_llIter(this->storages);
    while(corto_iter_hasNext(&storageIter)) {
        storage = corto_iter_next(&storageIter);
        if (storage->kind == IC_VARIABLE) {
            storages ++;
        }
    }

    if (storages) {
        result = strappend(result, "%%scopepush\n");
    }

    storageIter = corto_llIter(this->storages);
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

    programIter = corto_llIter(this->program);
    while(corto_iter_hasNext(&programIter)) {
        ic = corto_iter_next(&programIter);
        result = ic_node_str(ic, result);
        result = strappend(result, "\n");
    }

    if (storages) {
        result = strappend(result, "%%scopepop\n");
    }

    return result;
/* $end */
}
