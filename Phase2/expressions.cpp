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
bool validNumberExpr(expr *e) {
    if (!e) return false;
    if (e->type == constint_e || e->type == constdouble_e) 
        return true;
    if (e->type == var_e && e->sym) 
        return true;
    if (e->type == arithexpr_e)
        return true; //idk
        
    return false;
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

// void backpatch(list* list, unsigned label) {
//     for (unsigned quadIndex : list->quadLabels) {
//         quads[quadIndex]->label = label;
//     }
// }
// void backpatch(unsigned quadIndex, unsigned label) {
//     quads[quadIndex]->label = label;
// }

expr* evaluateUminus(expr* e){
    expr* tmpExpr = nullptr;
    if(!validNumberExpr(e)){
        cerr << "Invalid op Uminus, not a number type, in function evaluateUminus" << endl;
        return nullptr;
    }
    if(tmpCheck(e)){
        emit(uminus,e,nullptr,e);
        return e;
    } else {
        tmpExpr = newTempExpr();
        emit(uminus,e,nullptr,tmpExpr);
        return tmpExpr;
    }
}

expr* evaluateAssignExp(expr* e, expr *e2){
    expr* tmpExpr = nullptr;
    tmpExpr = newTempExpr();
    if(!validNumberExpr(e)){
        cerr << "Invalid op Uminus, not a number type, in function evaluateUminus" << endl;
        return nullptr;
    }
    equalsExprHelper(e,e2,tmpExpr);
    return tmpExpr;
}

void equalsExprHelper(expr* lvalue, expr* rvalue, expr* tmpExpr){
    emit(assign, rvalue, nullptr, lvalue);
    emit(assign,lvalue, nullptr,tmpExpr);
}