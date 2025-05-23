#include "headerLib.h"
#include <iostream>
#include <cstring>

using namespace std;
extern int tmpCount;
extern SymbolTable symbolTable;
extern int yylineno;
int flagg1 = 1;
int flagg2 = 2;

void setToNULL(expr* e){
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
    if (e2->type == newtable_e) {
        tmpExpr = newTempExpr();
        emit(assign, e2, nullptr, e);
        emit(assign, e, nullptr, tmpExpr);
        return tmpExpr;
    }
    if (e->type == tableitem_e) {
           flagg1 = e->type;
    flagg2 = e->type;
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
        //return e2;
    }
    if(!validNumberExpr(e)){
        cerr << "Invalid assignment target, not a valid lvalue at line " << yylineno << endl;
        return nullptr;
    }
    tmpExpr = newTempExpr();
    flagg1 = e->type;
    flagg2 = e->type;
    equalsExprHelper(e, e2, tmpExpr);
    return tmpExpr;
}

void equalsExprHelper(expr* lvalue, expr* rvalue, expr* tmpExpr){
    emit(assign, rvalue, nullptr, lvalue,flagg1);
    emit(assign,lvalue, nullptr,tmpExpr,flagg2);
}
/*  
    if bool == true, a++
    else ++a
*/
expr* evaluatePP(expr *e, expr* e2, bool flag, iopcode t){
    expr* tmpExpr = newTempExpr();
    tmpExpr->type = arithexpr_e;
        if(flag == true){
            if(!e || !validNumberExpr(e)){
                cerr << "Invalid lvalue in increment/decrement operation at line "<< yylineno<< endl;
                return nullptr;
            }
            if (e->type == tableitem_e) {
                expr* getelem = newTempExpr();
                getelem->type = var_e;
                emit(tablegetelem,e,e->index,getelem);
                emit(assign, getelem, nullptr, tmpExpr);
                emit(t, getelem, e2, getelem);
                emit(tablesetelem, e->index, getelem, e);
            }else{
            emit(assign, e, nullptr, tmpExpr);
            emit(t, e, e2, e);}
        } else {
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
        cerr << "lal" <<endl;
        expr* tmp = evalMem(table);
        return newMember(tmp, pointer);
    } else {
        cerr << "la3l" <<endl;
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
        tmpExpr = newTempExpr();
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
        tmpExpr = newTempExpr();
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
        tmpExpr = newTempExpr();
    }
    emit(not_op,e,nullptr,tmpExpr);
    return tmpExpr;
}

int ifPrefix(expr* e){
    int quad_counter = nextquad();
    expr* JumpTrue = newBoolExpr(true);
    emit(if_eq,e,JumpTrue,nullptr,quad_counter+3);
    quad_counter = nextquad();
    //0 is gonnabefixed
    emit(jump,nullptr,nullptr,0);
    return quad_counter;
}

void fixLabel(int quad_id, int label){
    static int i = 0;
    ++i;
    if(quad_id > nextquad()){
        cerr <<"quad_id < label, i: "<<i<<endl;
        cerr <<"a = "<< quad_id<< " b = "<<label<<endl;
        exit(-1);
    }
    else{
        quads[quad_id]->label = label+1;
        //quads[quad_id]->label = label;
    }
}

int elsePrefix(){
    int returnArg = nextquad();
    emit(jump,nullptr,nullptr,nullptr,0);
    return returnArg;
}

void jumpStartWhile(int &start){
    start = nextquad();
}

void incLoop(){
    ++loopCounter;
}

void decLoop(){
    --loopCounter;
    if(loopCounter == 0){
        cerr << "weird, loopcounter negval" << endl;
    }
}

void incFunc(){
    --funcCounter;
}

void decFunc(){
    --funcCounter;
    if(funcCounter == 0){
        cerr << "weird, funcCounter negval" << endl;
    }
}


/*
if flag == 0 then "break"
if flag == 1 then "cont"
if bool == 2 then "return"
else idk error
*/

stmt_t* setStmtList(int flag){
    stmt_t *s = new stmt_t();
    s->breakLabel = 0;
    s->continueLabel = 0;
    s->returnLabel = 0;
    int idx = nextquad();
    emit(jump, nullptr, nullptr, nullptr);
    if      (flag == 0) s->breakLabel    = idx;
    else if (flag == 1) s->continueLabel = idx;
    else if (flag == 2) s->returnLabel   = idx;

    return s;
}

stmt_t* initLists(){
    stmt_t *s = new stmt_t();
    s->breakLabel = 0;
    s->continueLabel = 0;
    s-> returnLabel = 0;
    return s;
} 

int mergeList(int l1,int l2){
    if(!l1){
        return l2;
    } else if(!l2){
        return l1;
    } else{
        int i = l1;
        while(quads[i]->label){
            i = quads[i]->label;
        }
        quads[i]->label = l2;
        return l1;
    }
}

void fixList(int list, int label){
    int next = 0;
    while(list){
        next = quads[list]->label;
        quads[list]->label = label+1;
        list = next;
    }
}

int setWhileCont(expr* e){
    int quad_counter = nextquad();
    expr* JumpTrue = newBoolExpr(true);
    emit(if_eq,e,JumpTrue,nullptr,quad_counter+3);
    quad_counter = nextquad();
    emit(jump, nullptr, nullptr, nullptr, 0);
    return quad_counter;
}

stmt_t* evaluateWhile(int cond, stmt_t* stmt, int start){
    emit(jump, nullptr, nullptr, nullptr, start+1);
    int tmp = nextquad();
    fixLabel(cond,tmp);
    tmp = nextquad();
    fixList(stmt->breakLabel,tmp);
    fixList(stmt->continueLabel,start);
    return stmt;
}

stmt_t* evaluateIfElse(int ifConst, int elseConst, stmt_t* s1, stmt_t* s2){
    stmt_t* s= initLists();
    s->breakLabel = mergeList(s1->breakLabel, s2->breakLabel); 
    s->continueLabel = mergeList(s1->continueLabel, s2->continueLabel); 
    s->returnLabel = mergeList(s1->returnLabel, s2->returnLabel); 
    return s;
}

forConst_t* evaluateForPrefix(expr* e, int M){
    forConst_t* ret = new forConst_t();
    ret->test = M;
    ret->enter = nextquad();
    int quad_counter = nextquad();
    expr* JumpTrue = newBoolExpr(true);
    emit(if_eq,e,JumpTrue,nullptr,quad_counter);
    return ret;
}
stmt_t* evaluateFor(forConst_t* forConstP, int N1,stmt_t* loop,int N2,int N3){
    int nextQ = nextquad();
    fixLabel(forConstP->enter,N2+1);
    fixLabel(N1,nextQ);
    fixLabel(N2,forConstP->test);
    fixLabel(N3, N1 + 1);
    fixList(loop->breakLabel,nextQ);
    fixList(loop->continueLabel,N1 +1);
    return loop;
}
/*
(type == 1) -> glob
(type == 2) -> local
(type == 3) -> reg
*/
expr* lvaluesIncert(string name, int type){
    Symbol *ret = nullptr;
    if(type == 1){
       ret = symbolTable.local_lvalue(name,0,yylineno);
    }else if(type == 2){
        ret = symbolTable.local_lvalue(name,symbolTable.currentScope,yylineno);
    }else if(type == 3){
        ret = symbolTable.lvalue_default(name,symbolTable.currentScope,yylineno);
    }else{
        cerr << "unknown type in lvaluesIncert " << yylineno << endl;
    }
    expr* e = symToExpr(ret);
    return e;
}