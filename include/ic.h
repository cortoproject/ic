/* ic.h
 *
 * This file contains generated code. Do not modify!
 */

#ifndef CORTO_IC_H
#define CORTO_IC_H

#include <corto/corto.h>
#include <corto/corto.h>
#include <corto/ic/_project.h>
#include <corto/c/c.h>
#include <corto/vm/vm.h>

/* $header() */
/* Enter additional code here. */
/* $end */

#include <corto/ic/_type.h>
#include <corto/ic/_load.h>
#include <corto/ic/c/_api.h>

/* $body() */
/* Enter code that requires types here */
/* $end */

#ifdef __cplusplus
extern "C" {
#endif

#define ic_opKindFromOperator(_operator) _ic_opKindFromOperator(_operator)
CORTO_IC_EXPORT
ic_opKind _ic_opKindFromOperator(
    corto_operatorKind _operator);

#include <corto/ic/accumulator.h>
#include <corto/ic/address.h>
#include <corto/ic/element.h>
#include <corto/ic/function.h>
#include <corto/ic/label.h>
#include <corto/ic/literal.h>
#include <corto/ic/member.h>
#include <corto/ic/node.h>
#include <corto/ic/object.h>
#include <corto/ic/op.h>
#include <corto/ic/program.h>
#include <corto/ic/scope.h>
#include <corto/ic/storage.h>
#include <corto/ic/variable.h>

#ifdef __cplusplus
}
#endif

#endif

