#ifndef __EXPR__
#define __EXPR__
#include <string>
#include <cstdio>
class Symbol;
struct expr;
struct quad;
#include "quad.h"
extern vector<quad*> quads;

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

struct list {
    vector<unsigned> quadLabels;
    void merge(list* other) {
        quadLabels.insert(quadLabels.end(), 
                          other->quadLabels.begin(), 
                          other->quadLabels.end());
    }
};

typedef struct ifstmt{
    expr* condition;
    expr* then;
    expr* elsep;
    list* next;
} ifstmt;

typedef struct expr{
    list* trueList;
    list* falseList;
    list* nextList;
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
    expr* prev;
} expr;

bool isFunc(expr *ptr);

expr* newIntExpr(int val);

expr* newDoubleExpr(double val);

expr* newNilExpr();

expr* newStringExpr(const string & val); 

void deleteExpr(expr* e);

ifstmt* newIfStmt(expr* condition, expr* then, expr* elsep);

void deleteIfStmt(ifstmt* ifs);

expr* newSymbolExpr(type_t t,Symbol* symToExpr);

expr* symToExpr(Symbol* symToExpr);

expr* newBoolExpr(bool val);

bool validNumberExpr(expr *e);

bool tmpCheck(expr* e);

expr* evaluateNumber(expr* e, expr* e2, iopcode opcode);

expr* newTempExpr();

void backpatch(list* list, unsigned label);

expr* evaluateUminus(expr* e);

void equalsExprHelper(expr* lvalue, expr* rvalue, expr* tmpExpr);

expr* evaluateAssignExp(expr*e, expr *e2);

expr* evaluatePP(expr *e, expr* e2, bool flag, iopcode t);

expr* tablePeriodId(expr *table, string pointer);

expr* newMember(expr *member, string key);

expr* evalMem(expr* e);

expr* tableBrackets(expr *table,expr *index);

void setToNULL(expr* e);

bool isTableItem(expr* e);
 
expr* evaluateBoolean(expr* e, expr* e2, iopcode opcode);

expr* evaluateAND_OR(expr* e, expr* e2, iopcode opcode);

expr* evaluateNOT(expr* e);
#endif