#include "expressions.h"
#include "quad.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>

using namespace std;

extern int yylineno;
extern SymbolTable symbolTable;
vector<quad*> quads;
int currQuad = 0;

static unsigned temp_count = 0;

char quadString[26][32] = {
    "assing", "sub", "add", "div", "mul", "mod", "uminus",
    "and", "or", "not", "if_eq", "if_noteq", "if_lesseq",
    "if_greatereq", "if_less", "if_greater", "jump", "param",
    "call", "return", "getretval", "funcstart", "funcend",
    "tablecreate", "tablegetelem", "tablesetelem"
};


void emit(iopcode op, expr* arg1, expr* arg2, expr* result){
    quad *new_quad = new quad();
    new_quad->op = op;
    new_quad->arg1 = arg1;
    new_quad->arg2 = arg2;
    new_quad->result = result;
    new_quad->label = 0;
    new_quad->line = yylineno; 
    quads.push_back(new_quad);
    currQuad++;
}

expr* newetempvar(){
    string name = "_t%u" + to_string(temp_count++);
    Symbol* tempsym = symbolTable.insert(name, symbolTable.currentScope, yylineno, LOCAL_VAR);

    if (tempsym == nullptr) {
        cout << "Error: Failed to create temporary variable " << name << endl;
        return nullptr;
    }

    expr* e = new expr();
    e->type = var_e;
    e->sym = tempsym;
    return e;
}

unsigned nextquad(){
    return currQuad;
}

void print_quads(){
    cout << setw(10) << "Quad#" << setw(20) << "opcode" << setw(10) << "result" 
         << setw(10) << "arg1" << setw(10) << "arg2" << setw(10) << "label" << endl;
    cout << "---------------------------------------------------------------------------" << endl;
    for (unsigned i = 0; i < quads.size(); i++) {
        cout << setw(10) << i << setw(20) << quads[i]->op << setw(10) 
             << (quads[i]->result ? quads[i]->result->sym->name : "NULL") 
             << setw(10) << (quads[i]->arg1 ? quads[i]->arg1->sym->name : "NULL") 
             << setw(10) << (quads[i]->arg2 ? quads[i]->arg2->sym->name : "NULL") 
             << setw(10) << quads[i]->label << endl;
    }
    cout << "---------------------------------------------------------------------------" << endl; 
}