#include "expressions.h"
#include "quad.h"
#include <iostream>
#include <cstring>

expr* newexpr(type_t t) {
    expr* e = new expr();
    e->type = t;
    e->sym = nullptr;
    e->index = nullptr;
    e->next = nullptr;
    e->truelist = -1;
    e->flaselist = -1;
    return e;
}

expr* newexpr_intconst(int value) {
    expr* e = newexpr(constint_e);
    e->content.intConst = value;
    return e;
}

expr* newexpr_doubleconst(double value) {
    expr* e = newexpr(constdouble_e);
    e->content.doubleConst = value;
    return e;
}

expr* newexpr_stringconst(const char* value) {
    expr* e = newexpr(conststring_e);
    e->content.strConst = strdup(value);
    return e;
}

expr* newexpr_boolconst(unsigned char value) {
    expr* e = newexpr(constbool_e);
    e->content.boolConst = value ? 1 : 0;
    return e;
}

expr* newexpr_nil() {
    return newexpr(nil_e);
}