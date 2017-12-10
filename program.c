/* This is a managed file. Do not delete this comment. */

#include <corto/ic/ic.h>

void ic_program_add(
    ic_program this,
    ic_node n)
{
    /* Insert implementation */
}

int16_t ic_program_assemble(
    ic_program this)
{
    /* Insert implementation */
}

int16_t ic_program_construct(
    ic_program this)
{
    /* Insert implementation */
}

ic_variable ic_program_declareVariable(
    ic_program this,
    corto_string name,
    corto_type type,
    bool isReference,
    bool holdsReturn,
    bool isParameter,
    bool isReturn)
{
    /* Insert implementation */
}

ic_program ic_program_get(void)
{
    /* Insert implementation */
}

uint32_t ic_program_getAccId(
    ic_program this)
{
    /* Insert implementation */
}

ic_element ic_program_getElement(
    ic_program this,
    ic_storage base,
    ic_node index)
{
    /* Insert implementation */
}

uint32_t ic_program_getLabel(
    ic_program this)
{
    /* Insert implementation */
}

ic_member ic_program_getMember(
    ic_program this,
    ic_storage base,
    corto_member m)
{
    /* Insert implementation */
}

ic_object ic_program_getObject(
    ic_program this,
    corto_object o)
{
    /* Insert implementation */
}

ic_variable ic_program_getVariable(
    ic_program this,
    corto_string name)
{
    /* Insert implementation */
}

void ic_program_popAccumulator(
    ic_program this)
{
    /* Insert implementation */
}

void ic_program_popScope(
    ic_program this)
{
    /* Insert implementation */
}

ic_accumulator ic_program_pushAccumulator(
    ic_program this,
    corto_type type,
    bool isReference,
    bool holdsReturn)
{
    /* Insert implementation */
}

ic_scope ic_program_pushFunction(
    ic_program this,
    corto_function function)
{
    /* Insert implementation */
}

ic_scope ic_program_pushScope(
    ic_program this)
{
    /* Insert implementation */
}

int16_t ic_program_run(
    ic_program this,
    uintptr_t result,
    corto_stringSeq argv)
{
    /* Insert implementation */
}

corto_string ic_program_str(
    ic_program this)
{
    /* Insert implementation */
}

