/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>
#include "corto/ic/assemble.h"
void ic_program_add(
    ic_program this,
    ic_node n)
{

    if (n->kind == IC_OP) {
        if (!ic_op_isValid(ic_op(n))) {
            this->errors++;
        }

    }

    if (corto_instanceof(corto_type(ic_storage_o), n)) {
        ic_nodeListAppend(this->scope->storages, n);
    } else {
        ic_nodeListAppend(this->scope->program, n);
    }

}

int16_t ic_program_assemble(
    ic_program this)
{

    if (CORTO_DEBUG_ENABLED) {
        corto_string str = ic_program_str(this);
        if (str) {
            printf("%s\n", str);
            corto_dealloc(str);
        }

    }

    this->vmprogram = (corto_word)ic_vmAssemble(this);
    if (!this->vmprogram) {
        goto error;
    }

    return 0;
error:
    return -1;
}

int16_t ic_program_construct(
    ic_program this)
{
    extern corto_tls IC_PROGRAM_KEY;
    corto_tls_set(IC_PROGRAM_KEY, this);
    return 0;
}

ic_variable ic_program_declareVariable(
    ic_program this,
    const char *name,
    corto_type type,
    bool isReference,
    bool holdsReturn,
    bool isParameter,
    bool isReturn)
{
    ic_variable result = ic_variable(ic_scope_lookupStorage(this->scope, name, FALSE));
    if (!result) {
        result = ic_variableCreate(name, type, isReference, holdsReturn, isParameter, isReturn);
        ic_scope_addStorage(this->scope, ic_storage(result));
    }

    return result;
}

ic_program ic_program_get(void)
{
    extern corto_tls IC_PROGRAM_KEY;
    return (ic_program)corto_tls_get(IC_PROGRAM_KEY);
}

uint32_t ic_program_getAccId(
    ic_program this)
{
    return ++this->autoAccId;
}

ic_element ic_program_getElement(
    ic_program this,
    ic_storage base,
    ic_node index)
{
    corto_id name;
    ic_element result;
    if (index) {
        corto_string elemStr = ic_node_str(index, NULL);
        sprintf(name, "%s[%s]", base->name, elemStr);
        corto_dealloc(elemStr);
    } else {
        sprintf(name, "*%s", base->name);
    }

    result = ic_element(ic_scope_lookupStorage(base->scope, name, FALSE));
    if (!result) {
        result = ic_elementCreate(base, index);
        ic_scope_addStorage(this->scope, ic_storage(result));
    }

    return result;
}

uint32_t ic_program_getLabel(
    ic_program this)
{
    return ++this->labelCount;
}

ic_member ic_program_getMember(
    ic_program this,
    ic_storage base,
    corto_member m)
{
    corto_id name;
    ic_member result;
    sprintf(name, "%s.%s", base->name, corto_idof(m));
    result = ic_member(ic_scope_lookupStorage(base->scope, name, FALSE));
    if (!result) {
        result = ic_memberCreate(base, m);
        ic_scope_addStorage(this->scope, ic_storage(result));
    }

    return result;
}

ic_object ic_program_getObject(
    ic_program this,
    corto_object o)
{
    ic_scope root = this->scope;
    ic_object result = NULL;
    while(root->parent) {
        root = root->parent;
    }

    result = ic_object(ic_scope_lookupStorage(root, corto_fullpath(NULL, o), FALSE));
    if (!result) {
        result = ic_objectCreate(o);
        ic_scope_addStorage(root, ic_storage(result));
    }

    return result;
}

ic_variable ic_program_getVariable(
    ic_program this,
    const char *name)
{
    return ic_variable(ic_scope_lookupStorage(this->scope, name, TRUE));
}

void ic_program_popAccumulator(
    ic_program this)
{
    ic_storage acc;

    this->accumulatorSp--;
    acc = ic_storage(this->accumulatorStack[this->accumulatorSp]);

    if (acc->holdsReturn) {
        ic_storage_free(acc);
    }

}

void ic_program_popScope(
    ic_program this)
{
    if (this->scope->storages) {
        corto_iter storageIter;
        ic_storage storage;

        storageIter = corto_ll_iter(this->scope->storages);
        while(corto_iter_hasNext(&storageIter)) {
            storage = corto_iter_next(&storageIter);
            if ((storage->kind == IC_VARIABLE) && !((ic_variable)storage)->isReturn && !((ic_variable)storage)->isParameter) {
                ic_storage_free(storage);
            }

        }

    }

    if (this->scope->parent) {
        this->scope = this->scope->parent;
    }

}

ic_accumulator ic_program_pushAccumulator(
    ic_program this,
    corto_type type,
    bool isReference,
    bool holdsReturn)
{
    corto_id name;

    sprintf(name, "#%d", this->autoAccId);
    this->autoAccId++;

    this->accumulatorStack[this->accumulatorSp] =
        ic_accumulatorCreate(name, type ? type : corto_void_o, isReference, holdsReturn);

    this->accumulatorSp++;
    return this->accumulatorStack[this->accumulatorSp-1];
}

ic_scope ic_program_pushFunction(
    ic_program this,
    corto_function function)
{
    ic_function label;
    ic_scope scope;

    /* Add function-label */
    label = ic_functionCreate(function);
    ic_program_add(this, ic_node(label));

    /* Push function-scope */
    scope = ic_program_pushScope(this);
    scope->isFunction = TRUE;

    function->kind = CORTO_PROCEDURE_VM;

    return scope;
}

ic_scope ic_program_pushScope(
    ic_program this)
{
    this->scope = ic_scopeCreate(this->scope, FALSE);

    if (this->scope->parent) {
        corto_ll_append(this->scope->parent->program, this->scope);
    }

    return this->scope;
}

int16_t ic_program_run(
    ic_program this,
    uintptr_t result,
    corto_stringSeq argv)
{
    vm_program program = (vm_program)this->vmprogram;
    return vm_run(program, argv, (void*)result);
}

corto_string ic_program_str(
    ic_program this)
{
    corto_string result = NULL;

#ifdef CORTO_IC_TRACING
    result = strappend(result, "%%file %s\n", this->filename);
    result = ic_scope_str(this->scope, result);
#endif
    return result;
}

