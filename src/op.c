/* $CORTO_GENERATED
 *
 * op.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/ic/ic.h>

/* $header() */
static corto_bool ic_validateSet(ic_op op) {
    corto_bool result = TRUE;
    op->s1 && (ic_node(op->s1)->kind != IC_STORAGE) ? result = FALSE: 0;
    !op->s2 || (ic_node(op->s2)->kind != IC_STORAGE) ? result = FALSE: 0;
    !op->s2 ? result = FALSE : 0;
    return result;
}

static corto_bool ic_validateCast(ic_op op) {
    corto_bool result = TRUE;
    op->s1 && (ic_node(op->s1)->kind != IC_STORAGE) ? result = FALSE: 0;
    !op->s2 || (ic_node(op->s2)->kind != IC_STORAGE) ? result = FALSE: 0;
    !op->s3 || (ic_node(op->s3)->kind != IC_STORAGE) ? result = FALSE: 0;
    return result;
}

static corto_bool ic_validateBinary(ic_op op) {
    corto_bool result = TRUE;
    op->s1 && (ic_node(op->s1)->kind != IC_STORAGE) ? result = FALSE: 0;
    !op->s2 || !op->s3 ? result = FALSE: 0;
    if (result) {
        if ((ic_node(op->s2)->kind != IC_STORAGE) && (ic_node(op->s3)->kind != IC_STORAGE)) {
            result = FALSE;
        }
    }
    return result;
}

static corto_bool ic_validateUnary(ic_op op) {
    corto_bool result = TRUE;
    op->s1 && (ic_node(op->s1)->kind != IC_STORAGE) ? result = FALSE: 0;
    op->s2 && (ic_node(op->s2)->kind != IC_STORAGE) ? result = FALSE: 0;
    return result;
}

static corto_bool ic_validatePush(ic_op op) {
    if (!op->s1) {
        return FALSE;
    } else {
        return TRUE;
    }
}

static corto_string ic_op_derefToString(corto_string string, ic_node s, ic_derefKind mode) {
    if (s->kind == IC_STORAGE) {
        corto_type t = ic_storage(s)->type;
        if (t->reference) {
            if (mode == IC_DEREF_VALUE) {
                string = strappend(string, " *");
            } else {
                string = strappend(string, " ");
            }
        } else {
            if (mode == IC_DEREF_ADDRESS) {
                string = strappend(string, " &");
            } else {
                string = strappend(string, " ");
            }
        }
    } else {
        string = strappend(string, " ");
    }

    return string;
}

/* $end */

int16_t _ic_op_construct(
    ic_op this)
{
/* $begin(corto/ic/op/construct) */
    ic_node(this)->kind = IC_OP;
    return ic_node_construct(ic_node(this));
/* $end */
}

corto_string _ic_op_str(
    ic_op this,
    corto_string in)
{
/* $begin(corto/ic/op/str) */
    in = strappend(in, "  %s", corto_ptr_str(&this->kind, ic_opKind_o, 0));
    if (this->s1) {
        in = ic_op_derefToString(in, this->s1, this->s1Deref);
        in = ic_node_str(this->s1, in);
    } else if (this->s2 || this->s3) {
        in = strappend(in, " .");
    }
    if (this->s2) {
        in = ic_op_derefToString(in, this->s2, this->s2Deref);
        in = ic_node_str(this->s2, in);
    } else if (this->s3) {
        in = strappend(in, " .");
    }
    if (this->s3) {
        in = ic_op_derefToString(in, this->s3, this->s3Deref);
        in = ic_node_str(this->s3, in);
    }
    return in;
/* $end */
}

bool _ic_op_validate(
    ic_op this)
{
/* $begin(corto/ic/op/validate) */
    corto_bool result = TRUE;

    switch(this->kind) {
    case ic_set: result = ic_validateSet(this); break;
    case ic_cast: result = ic_validateCast(this); break;
    case ic_strcat: result = TRUE; break;
    case ic_strcpy: result = TRUE; break;
    case ic_new: result = TRUE; break;
    case ic_define: result = TRUE; break;
    case ic_free: result = TRUE; break;
    case ic_keep: result = TRUE; break;
    case ic_update: result = TRUE; break;
    case ic_updatebegin: result = TRUE; break;
    case ic_updateend: result = TRUE; break;
    case ic_updatecancel: result = TRUE; break;
    case ic_init: result = TRUE; break;
    case ic_deinit: result = TRUE; break;
    case ic_add: result = ic_validateBinary(this); break;
    case ic_sub: result = ic_validateBinary(this); break;
    case ic_mul: result = ic_validateBinary(this); break;
    case ic_div: result = ic_validateBinary(this); break;
    case ic_mod: result = ic_validateBinary(this); break;
    case ic_inc: result = ic_validateUnary(this); break;
    case ic_dec: result = ic_validateUnary(this); break;
    case ic_xor: result = ic_validateBinary(this); break;
    case ic_or: result = ic_validateBinary(this); break;
    case ic_and: result = ic_validateBinary(this); break;
    case ic_not: result = ic_validateUnary(this); break;
    case ic_shift_left: result = ic_validateBinary(this); break;
    case ic_shift_right: result = ic_validateBinary(this); break;
    case ic_cond_or: result = ic_validateBinary(this); break;
    case ic_cond_and: result = ic_validateBinary(this); break;
    case ic_cond_not: result = ic_validateUnary(this); break;
    case ic_cond_eq: result = ic_validateBinary(this); break;
    case ic_cond_neq: result = ic_validateBinary(this); break;
    case ic_cond_gt: result = ic_validateBinary(this); break;
    case ic_cond_lt: result = ic_validateBinary(this); break;
    case ic_cond_gteq: result = ic_validateBinary(this); break;
    case ic_cond_lteq: result = ic_validateBinary(this); break;
    case ic_jump: result = TRUE; break;
    case ic_jeq: result = TRUE; break;
    case ic_jneq: result = TRUE; break;
    case ic_stop: result = TRUE; break;
    case ic_push: result = ic_validatePush(this); break;
    case ic_call: result = TRUE; break;
    case ic_ret: result = TRUE; break;
    default: printf("unknown operation!\n"); result = FALSE; break;
    }

#ifdef IC_TRACING
    if (!result) {
        printf("%s:%d: invalid operands for '%s' (%s, %s, %s)\n",
               ic_program_get()->filename,
               this->line, ic_opKindStr(this->kind),
               this->s1 ? ic_kindStr(ic_node(this->s1)->kind) : "<none>",
               this->s2 ? ic_kindStr(ic_node(this->s2)->kind) : "<none>",
               this->s3 ? ic_kindStr(ic_node(this->s3)->kind) : "<none>");
    }
#else
    if (!result) {
    printf("%s:%d: invalid operands (build with IC_TRACING to get more information)\n",
           ic_program_get()->filename,
           this->line);
    }
#endif
    return result;
/* $end */
}
