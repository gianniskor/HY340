#include "headerLib.h"
#include <iostream>
#include <cstring>

using namespace std;
extern int tmpCount;
extern SymbolTable symbolTable;
extern int yylineno;

void setToNULL(expr* e){
    e->trueList = nullptr;
    e->falseList = nullptr;
    e->nextList = nullptr;
    e->next = nullptr;
    e->prev = nullptr;
}

expr* newStringExpr(const string & val) {
    expr* e = new expr();
    e->type = conststring_e;
    e->sym = nullptr;
    e->index = nullptr;
    setToNULL(e);
    e->value.stringValue = new string(val);
    return e;
}

expr* newBoolExpr(bool val){
    expr* e = new expr();
    e->type = constbool_e;
    e->sym = nullptr;
    setToNULL(e);
    e->value.boolValue = val;
    return e;
}

expr* newIntExpr(int val){
    expr* e = new expr();
    e->type = constint_e;
    e->sym = nullptr;
    setToNULL(e);
    e->value.intValue = val;
    return e;
}

expr* newDoubleExpr(double val){
    expr* e = new expr();
    e->type = constdouble_e;
    e->sym = nullptr;
    e->index = nullptr;
    setToNULL(e);
    e->value.doubleValue = val;
    return e;
}

expr* newNilExpr(){
    expr* e = new expr();
    e->type = nil_e;
    e->sym = nullptr;
    e->index = nullptr;
    setToNULL(e);
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
    setToNULL(e);
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
    if (e->type == tableitem_e) {
        if (e->index && (e->index->type == constint_e || e->index->type == constdouble_e ||e->index->type ==conststring_e)) 
            return true;
        else if (e->index && e->index->type == var_e && e->index->sym) 
            return true;
    }
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
        tmpExpr = newTempExpr("evalNum");
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
        tmpExpr = newTempExpr("evaluninus");
        emit(uminus,e,nullptr,tmpExpr);
        return tmpExpr;
    }
}

expr* evalMem(expr* e){
    expr* ret;
    ret = newTempExpr("evalmem");
    ret->type = var_e;
    emit(tablegetelem, e, e->index, ret);
    return ret;
}

expr* evaluateAssignExp(expr* e, expr *e2){
    expr* tmpExpr = nullptr;
    //tmpExpr = newTempExpr("evalassign");
    if (e2->type == newtable_e) {
        tmpExpr = newTempExpr("evalassign");
        emit(assign, e2, nullptr, e);
        emit(assign, e, nullptr, tmpExpr);
        return tmpExpr;
    }
    if (e->type == tableitem_e) {
        if (e2->type == tableitem_e) {
            expr* rightValue = newTempExpr("evalassin ifif");
            emit(tablegetelem, e2, e2->index, rightValue);
            emit(tablesetelem, e->index, rightValue,e);
        } else {
            emit(tablesetelem, e->index, e2,e);
        }
        expr* result = newTempExpr("evalassin if");
        emit(tablegetelem, e, e->index, result);
        return result;
    }
    if(!validNumberExpr(e)){
        cerr << "Invalid assignment target, not a valid lvalue at line " << yylineno << endl;
        return nullptr;
    }
    
    // equalsExprHelper(e,e2,tmpExpr);
    tmpExpr = newTempExpr("evalassign");
    equalsExprHelper(e, e2, tmpExpr);
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
    // if(!e || !validNumberExpr(e)){
    //     cerr << "Invalid lvalue in increment/decrement operation at line "<< yylineno<< endl;
    //     return nullptr;
    // }
    expr* tmpExpr = newTempExpr("evalPP");
    tmpExpr->type = arithexpr_e;
    // if (e->type == tableitem_e) {
    //     expr* term;
    //     cerr<<"HEEYY"<<endl;
    //     if (flag==true) {

    //         cerr<<"HEEYY"<<endl;
    //     }
    //     else {
    //         // prefix: value after
    //         cerr<<"HEEYY"<<endl;
    //         // // term = term ± 1
    //         // emit(t, term, e2, term);
    //         // // write back
    //         // emit(tablesetelem, e, e->index, term);
    //         // emit(assign, term, nullptr, tmpExpr);
    //     }

    //     return tmpExpr;
    // } else {
        if(flag == true){ // postfix: a++
            if(!e || !validNumberExpr(e)){
                cerr << "Invalid lvalue in increment/decrement operation at line "<< yylineno<< endl;
                return nullptr;
            }
            if (e->type == tableitem_e) {
                expr* getelem = newTempExpr("emit_Table");
                getelem->type = var_e;
                emit(tablegetelem,e,e->index,getelem);
                emit(assign, getelem, nullptr, tmpExpr);
                emit(t, getelem, e2, getelem);
                emit(tablesetelem, e->index, getelem, e);
            }else{
            emit(assign, e, nullptr, tmpExpr);
            emit(t, e, e2, e);}
        } else { // prefix: ++a
            if(!e2 || !validNumberExpr(e2)){
                cerr << "Invalid lvalue in increment/decrement operation at line "<< yylineno<< endl;
                return nullptr;
            }
            if (e2->type == tableitem_e) {
                tmpExpr->type = arithexpr_e;
                emit(tablegetelem,e2,e2->index,tmpExpr);
                emit(t, tmpExpr, e, tmpExpr);
                emit(tablesetelem, e2->index, tmpExpr, e2);
            }else{
            emit(t, e2, e, e2);
            emit(assign, e2, nullptr, tmpExpr);}
        // }
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
    expr *t = new expr();
    t->type = tableitem_e;
    t->sym = table->sym;
    t->index = newStringExpr(key);
    setToNULL(t);
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

expr* tableBrackets(expr *table,expr *index){
    expr *tableitem;
    if (!table) {
        cerr << "Nullptr at tableBrackets" << endl;
        exit(-1);
    }
    if (isFunc(table)) {
        cerr << "Error, Function as name in value, in tableBrackets" << endl;
        exit(-1);
    }
    if(table->type == tableitem_e) {
        expr* tmp = evalMem(table);
        tableitem = new expr();
        tableitem->type = tableitem_e;
        tableitem->sym = tmp->sym;
        tableitem->index = index;
        setToNULL(tableitem);
        return tableitem;
    } else {
        tableitem = new expr();
        tableitem->type = tableitem_e;
        tableitem->sym = table->sym;
        tableitem->index = index;
        setToNULL(tableitem);
        return tableitem;
    }

}

// expr* evaluateBoolean(expr* e, expr* e2, iopcode opcode){
//     expr* retArg = nullptr;
//     if(e->)
// }

bool isTableItem(expr* e){
    if(e->type == tableitem_e){
        return true;
    }
    return false;
}

expr* evaluateBoolean(expr* e, expr* e2, iopcode opcode){
    int quad_counter;
    if (!e || !e2) {
        cerr << "Error: Null expression in evaluatebool" << endl;
        return nullptr;
    }
    bool flag1 = validNumberExpr(e) || (e->type == constbool_e);
    bool flag2 = validNumberExpr(e2) || (e2->type == constbool_e);
    if (!flag1 || !flag2) {
        printf("Error, flag in eNum is false \n");
        exit(-1);
    }
    //res
    expr* tmpExpr = nullptr;
    if (tmpCheck(e)) {
        tmpExpr = symToExpr(e->sym);
    } else if (tmpCheck(e2)) {
        tmpExpr = symToExpr(e2->sym);
    } else {
        tmpExpr = newTempExpr("evalNum");
    }
    quad_counter = nextquad();
    // expr* JumpPlus3 = newIntExpr(quad_counter+3);
    // expr* JumpPlus5 = newIntExpr(quad_counter+5);
    // expr* JumpPlus6 = newIntExpr(quad_counter+6);
    expr* JumpTrue = newBoolExpr(true);
    expr* JumpFalse = newBoolExpr(false);

    // emit(opcode,e,e2,JumpPlus3);
    // emit(assign,JumpFalse,nullptr,tmpExpr);
    // emit(jump,nullptr,nullptr,JumpPlus5);
    // emit(assign,JumpTrue,nullptr,tmpExpr);
    emit(opcode, e,e2,nullptr,quad_counter+3);
    emit(jump,nullptr,nullptr,nullptr,quad_counter+5);
    emit(assign,JumpTrue,nullptr,tmpExpr);
    emit(jump,nullptr,nullptr,nullptr,quad_counter+6);
    emit(assign,JumpFalse,nullptr,tmpExpr);
    return tmpExpr;
}

expr* evaluateAND_OR(expr* e, expr* e2, iopcode opcode){
    if (!e || !e2) {
        cerr << "Error: Null expression in evaluatebool" << endl;
        return nullptr;
    }
    bool flag1 = validNumberExpr(e) || (e->type == constbool_e);
    bool flag2 = validNumberExpr(e2) || (e2->type == constbool_e);
    if (!flag1 || !flag2) {
        printf("Error, flag in eNum is false \n");
        exit(-1);
    }
    //res
    expr* tmpExpr = nullptr;
    if (tmpCheck(e)) {
        tmpExpr = symToExpr(e->sym);
    } else if (tmpCheck(e2)) {
        tmpExpr = symToExpr(e2->sym);
    } else {
        tmpExpr = newTempExpr("evalandOR");
    }
    emit(opcode,e,e2,tmpExpr);
    return tmpExpr;
}

expr* evaluateNOT(expr* e){
    if (!e) {
        cerr << "Error: Null expression in evaluatebool" << endl;
        return nullptr;
    }
    bool flag1 = validNumberExpr(e) || (e->type == constbool_e);
    if (!flag1) {
        printf("Error, flag in eNum is false \n");
        exit(-1);
    }
    //res
    expr* tmpExpr = nullptr;
    if (tmpCheck(e)) {
        tmpExpr = symToExpr(e->sym);
    }
    else {
        tmpExpr = newTempExpr("evalnot");
    }
    emit(not_op,e,nullptr,tmpExpr);
    return tmpExpr;
}

int ifPrefix(expr* e){
    int quad_counter = nextquad();
    //expr* JumpPlus2 = newIntExpr(quad_counter+2);
    expr* JumpTrue = newBoolExpr(true);
    emit(if_eq,e,JumpTrue,nullptr,quad_counter+3);
    quad_counter = nextquad();
    //0 is gonnafixed
    emit(jump,nullptr,nullptr,0);
    return quad_counter;
}

void fixLabel(int quad_id, int label){
    if(quad_id > label){
        cerr <<"quad_id < label"<<endl;
        exit(-1);
    }
    else{
        quads[quad_id]->label = label+1;
    }
}

int elsePrefix(){
    int returnArg = nextquad();
    emit(jump,nullptr,nullptr,nullptr,0);
    return returnArg;
}