#ifndef __EXPR__
#define __EXPR__

#include "symtable.h"

typedef enum type_t{ 
    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,

    constint_e,
    constdouble_e,
    constbool_e,
    conststring_e,

    nil_e,
} type_t;

typedef struct expr{
    type_t type;
    Symbol* sym;
    expr* index;
    union {
        int             intConst;
        double          doubleConst;
        char*           strConst;
        unsigned char   boolConst;
    } content;
    expr* next;
    int truelist;
    int flaselist;
} expr;

#endif