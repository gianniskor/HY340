#include "headerLib.h"
#include <iostream>
#include <cstring>

using namespace std;
extern int tmpCount;
extern SymbolTable symbolTable;
extern 

expr* newStringExpr(const string & val) {
    expr* e = new expr();
    e->type = conststring_e;
    e->sym = nullptr;
    e->index = nullptr;
    e->next = nullptr;
    e->value.stringValue = new string(val);
    return e;
}

expr* newBoolExpr(bool val){
    expr* e = new expr();
    e->type = constbool_e;
    e->sym = nullptr;
    e->index = nullptr;
    e->next = nullptr;
    e->value.boolValue = val;
    return e;
}

expr* newIntExpr(int val){
    expr* e = new expr();
    e->type = constint_e;
    e->sym = nullptr;
    e->index = nullptr;
    e->next = nullptr;
    e->value.intValue = val;
    return e;
}

expr* newDoubleExpr(double val){
    expr* e = new expr();
    e->type = constdouble_e;
    e->sym = nullptr;
    e->index = nullptr;
    e->next = nullptr;
    e->value.doubleValue = val;
    return e;
}

expr* newNilExpr(){
    expr* e = new expr();
    e->type = nil_e;
    e->sym = nullptr;
    e->index = nullptr;
    e->next = nullptr;
    return e;
}

void deleteExpr(expr* e){
    if(!e){
        return;
    }
    if(e->type == conststring_e && e->value.stringValue){
        delete e->value.stringValue;
    }
    delete e;
}

expr* newSymbolExpr(type_t t,Symbol* symToExpr){
    expr* e = new expr();
    e->type = t;
    e->sym = symToExpr;
    e->index = nullptr;
    e->next = nullptr;
    return e;
} 

expr* symToExpr(Symbol* symToExpr){
    if(!symToExpr){
        cerr << "Error in SymToExpr functioin, symbol -> null\n" << endl;
        exit(-1);
    }
    expr *e;
    if(symToExpr->getType()==LIB_FUNC){
        e = newSymbolExpr(libraryfunc_e,symToExpr);
    } else if(symToExpr->getType()==USER_FUNC){
        e = newSymbolExpr(programfunc_e,symToExpr);
    } else {
        e = newSymbolExpr(var_e,symToExpr);
    }
    return e;
}
bool validNumberExpr(expr *e){
    switch (e->type)
    {
    case var_e:
    case tableitem_e:
    case arithexpr_e:
    case assignexpr_e:
    case constint_e:
    case constdouble_e:
        return true;
        /*break;*/
    default:
        printf("Invalid arithmetic op, at %d -> line\n");
        return false;
        /*break;*/
    }
}

bool tmpCheck(expr* e) {
    if (!e || !e->sym) return false;
    const string symName = e->sym->getName();
    if ((e->sym->type == LOCAL_VAR || e->sym->type == GLOBAL_VAR) && 
        !symName.empty() && symName.front() == '_') {
        return true;
    }
    return false;
}

expr* evaluateNumber(expr* e, expr* e2, iopcode opcode) {
    if (!e || !e2) {
        cerr << "Error: Null expression in evaluateNumber" << endl;
        return nullptr;
    }
    bool flag1 = validNumberExpr(e);
    bool flag2 = validNumberExpr(e2);
    expr* tmpExpr = nullptr;
    if (!flag1 || !flag2) {
        printf("Error, flag in eNum is false \n");
        exit(-1);
    }
    if (tmpCheck(e)) {
        tmpExpr = symToExpr(e->sym);
    } else if (tmpCheck(e2)) {
        tmpExpr = symToExpr(e2->sym);
    } else {
        tmpExpr = newTempExpr();
    }
    if (opcode != sub && opcode != add && opcode != div_op && opcode != mul && opcode != mod) {
        cerr << "Invalid opcode in function evaluateNumber" << endl;
        return nullptr;
    } else {
        emit(opcode, e, e2, tmpExpr);
    }
    
    return tmpExpr;
}
