#ifndef __EXPR__
#define __EXPR__
#include <variant>
#include "symtable.h"
typedef enum type_t { 
    var_e ,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

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
        int intValue;
        double doubleValue;
        bool boolValue;
        string* stringValue;
    } value;
    expr* next;
} expr;

expr* newIntExpr(int val);
expr* newDoubleExpr(double val);
expr* newNilExpr();
expr* newStringExpr(const string & val); 
void deleteExpr(expr* e);
expr* newSymbolExpr(type_t t,Symbol* symToExpr);
expr* symToExpr(Symbol* symToExpr);
expr* newBoolExpr(bool val);
#endif