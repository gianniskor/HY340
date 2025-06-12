#ifndef __QUADS__
#define __QUADS__

#include "expressions.h"
extern FILE *debug_temp;
extern int tmpCount;

typedef enum iopcode{
    assign,
    add,
    sub,
    mul,
    div_op,
    mod,
    uminus,
    and_op,
    or_op,
    not_op,
    if_eq,
    if_noteq,
    if_lesseq,
    if_greatereq,
    if_less,
    if_greater,
    call,
    param,
    return_op,
    getretval,
    funcstart,
    funcend,
    tablecreate,
    tablegetelem,
    
    tablesetelem,jump,
    nop
} iopcode;

extern char quadString[27][32];

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
void emit(iopcode op, expr* arg1, expr* arg2, expr* result, int label);
#endif