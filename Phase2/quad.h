#ifndef __QUADS__
#define __QUADS__

#include "expressions.h"

extern int tmpCount;

typedef enum iopcode{
    assign,
    sub,
    add,
    div_op,
    mul,
    mod,
    uminus,
    and_op,
    or_op,
    not_op,
    if_eq,
    if_noteq,
    if_lesseq,
    if_geatereq,
    if_less,
    if_greater,
    jump,
    param,
    call,
    return_op,
    getretval,
    funcstart,
    funcend,
    tablecreate,
    tablegetelem,
    tablesetelem
} iopcode;

extern char quadString[26][32];

typedef struct quad {
    iopcode op;
    expr* result;
    expr* arg1;
    expr* arg2;
    unsigned label;
    unsigned line;
} quad;

void print_quads();
void enumToString();
void emit(iopcode op, expr* arg1, expr* arg2, expr* result);
expr* newTempExpr();
unsigned nextquad();
#endif