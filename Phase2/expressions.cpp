#include "headerLib.h"
#include <iostream>
#include <cstring>

using namespace std;
extern int tmpCount;
extern SymbolTable symbolTable;
extern int yylineno;

expr* newStringExpr(const string & val) {
    expr* e = new expr();
    e->type = conststring_e;
    e->sym = nullptr;
    e->index = nullptr;
    e->trueList = nullptr;
    e->falseList = nullptr;
    e->nextList = nullptr;
    e->next = nullptr;
    e->value.stringValue = new string(val);
    return e;
}

expr* newBoolExpr(bool val){
    expr* e = new expr();
    e->type = constbool_e;
    e->sym = nullptr;
    e->trueList = nullptr;
    e->falseList = nullptr;
    e->nextList = nullptr;
    e->index = nullptr;
    e->next = nullptr;
    e->value.boolValue = val;
    return e;
}

expr* newIntExpr(int val){
    expr* e = new expr();
    e->type = constint_e;
    e->sym = nullptr;
    e->trueList = nullptr;
    e->falseList = nullptr;
    e->nextList = nullptr;
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
    e->trueList = nullptr;
    e->falseList = nullptr;
    e->nextList = nullptr;
    e->value.doubleValue = val;
    return e;
}

expr* newNilExpr(){
    expr* e = new expr();
    e->type = nil_e;
    e->sym = nullptr;
    e->index = nullptr;
    e->next = nullptr;
    e->trueList = nullptr;
    e->falseList = nullptr;
    e->nextList = nullptr;
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
    e->prev = nullptr;
    e->trueList = nullptr;
    e->falseList = nullptr;
    e->nextList = nullptr;
    return e;
} 

expr* symToExpr(Symbol* symToExpr){
    if(!symToExpr){
        cerr << "Error in SymToExpr function, symbol -> null\n" << endl;
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

expr* evalMem(expr* e){
    expr* ret;
    ret = newTempExpr();
    ret->type = var_e;
    emit(tablegetelem, e, e->index, ret);
    return ret;
}

expr* evaluateAssignExp(expr* e, expr *e2){
    expr* tmpExpr = nullptr;
    tmpExpr = newTempExpr();
    if (e2->type == newtable_e) {
        emit(assign, e2, nullptr, e);
        emit(assign, e, nullptr, tmpExpr);
        return tmpExpr;
    }
    if (e->type == tableitem_e) {
        if (e2->type == tableitem_e) {
            expr* rightValue = newTempExpr();
            emit(tablegetelem, e2, e2->index, rightValue);
            emit(tablesetelem, e->index, rightValue,e);
        } else {
            emit(tablesetelem, e->index, e2,e);
        }
        expr* result = newTempExpr();
        emit(tablegetelem, e, e->index, result);
        return result;
    }
    if(!validNumberExpr(e)){
        cerr << "Invalid assignment target, not a valid lvalue at line " << yylineno << endl;
        return nullptr;
    }
    
    equalsExprHelper(e,e2,tmpExpr);
    return tmpExpr;
}

void equalsExprHelper(expr* lvalue, expr* rvalue, expr* tmpExpr){
    emit(assign, rvalue, nullptr, lvalue);
    emit(assign,lvalue, nullptr,tmpExpr);
}
/*  
    if bool == true, a++
    else ++a
*/
expr* evaluatePP(expr *e, expr* e2, bool flag, iopcode t){
    if(!e || !validNumberExpr(e)){
        cerr << "Invalid lvalue in increment/decrement operation at line "<< yylineno<< endl;
        return nullptr;
    }
    expr* tmpExpr = newTempExpr();
    tmpExpr->type = arithexpr_e;
    if(flag == true){
        emit(assign, e, nullptr, tmpExpr);
        emit(t, e, e2, e);
    } else {
        emit(t, e, e2, e);
        emit(assign, e, nullptr, tmpExpr);
    }
    
    return tmpExpr;
}

bool isFunc(expr *ptr){
    if(ptr->type == programfunc_e || ptr->type == libraryfunc_e){
        return true;
    }
    return false;
}

expr* newMember(expr *table, string key) {
    expr *t = newTempExpr();
    t->type = tableitem_e;
    t->sym = table->sym;
    t->index = newStringExpr(key);
    
    return t;
}

expr* tablePeriodId(expr *table, string pointer) {
    if (!table) {
        cerr << "Nullptr at tablePeriodId" << endl;
        exit(-1);
    }
    if (isFunc(table)) {
        cerr << "Error, Function as name in value, in tablePeriodId" << endl;
        exit(-1);
    }
    if (table->type == tableitem_e) {
        expr* tmp = evalMem(table);
        return newMember(tmp, pointer);
    } else {
        return newMember(table, pointer);
    }
}