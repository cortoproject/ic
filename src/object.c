/* $CORTO_GENERATED
 *
 * object.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/ic/ic.h>

int16_t _ic_object_construct(
    ic_object this)
{
/* $begin(corto/ic/object/construct) */
    ic_storage(this)->kind = IC_OBJECT;
    ic_storage(this)->name = corto_strdup(corto_fullpath(NULL, this->ptr));
    corto_setref(&ic_storage(this)->type, corto_typeof(this->ptr));
    ic_storage(this)->isReference = TRUE;
    return ic_storage_construct(ic_storage(this));
/* $end */
}
