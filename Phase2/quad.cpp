#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include "headerLib.h"
#include <fstream>
using namespace std;

extern int yylineno;
extern SymbolTable symbolTable;
vector<quad*> quads;
int currQuad = 0;


static unsigned temp_count = 0;
/// FIX THIS, EINAI ME KAKO


char quadString[27][32] = {
    "assign","add", "sub",  "mul", "div", "mod", "uminus",
    "and", "or", "not", "if_eq", "if_noteq", "if_lesseq",
    "if_greatereq", "if_less", "if_greater", "call", "param",
    "return", "getretval", "funcstart", "funcend",
    "tablecreate", "tablegetelem", "tablesetelem","jump","nop"
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

void emit(iopcode op, expr* arg1, expr* arg2, expr* result, int label){
    quad *new_quad = new quad();
    new_quad->op = op;
    new_quad->arg1 = arg1;
    new_quad->arg2 = arg2;
    new_quad->result = result;
    new_quad->label = label;
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

void print_quads(const string& filename = "") {
    ofstream outfile;
    ostream* out_stream = &cout; 
    
    if (!filename.empty()) {
        #ifdef _WIN32
        system("if not exist outputs mkdir outputs");
        #else
        system("mkdir -p outputs");
        #endif

        string out_filename = "outputs/" + filename + ".quad";
        outfile.open(out_filename);
        if (outfile.is_open()) {
            cout << "Writing quads to " << out_filename << endl;
            out_stream = &outfile;
        } else {
            cerr << "Error: Failed to open output file " << out_filename << endl;
        }
    }
    *out_stream << "NO.  OPCODE          RESULT      ARG1        ARG2        LABEL\n\n";
    
    for (unsigned i = 0; i < quads.size(); i++) {
        quad* q = quads[i];
        string result_str = "";
        string arg1_str = "";
        string arg2_str = "";
        if (q->result) {
            if (q->result->type == constint_e) 
                result_str = to_string(q->result->value.intValue);
            else if (q->result->type == constdouble_e) 
                result_str = to_string(q->result->value.doubleValue);
            else if (q->result->type == constbool_e) 
                result_str = q->result->value.boolValue ? "true" : "false";
            else if (q->result->type == conststring_e && q->result->value.stringValue) 
                result_str = *q->result->value.stringValue;
            else if (q->result->sym) 
                result_str = q->result->sym->getName();
        }
        if (q->arg1) {
            if (q->arg1->type == constint_e) 
                arg1_str = to_string(q->arg1->value.intValue);
            else if (q->arg1->type == constdouble_e) 
                arg1_str = to_string(q->arg1->value.doubleValue);
            else if (q->arg1->type == constbool_e) 
                arg1_str = q->arg1->value.boolValue ? "true" : "false";
            else if (q->arg1->type == conststring_e && q->arg1->value.stringValue) 
                arg1_str = *q->arg1->value.stringValue;
            else if (q->arg1->sym) 
                arg1_str = q->arg1->sym->getName();
        }
        if (q->arg2) {
            if (q->arg2->type == constint_e) 
                arg2_str = to_string(q->arg2->value.intValue);
            else if (q->arg2->type == constdouble_e) 
                arg2_str = to_string(q->arg2->value.doubleValue);
            else if (q->arg2->type == constbool_e) 
                arg2_str = q->arg2->value.boolValue ? "true" : "false";
            else if (q->arg2->type == conststring_e && q->arg2->value.stringValue) 
                arg2_str = *q->arg2->value.stringValue;
            else if (q->arg2->sym) 
                arg2_str = q->arg2->sym->getName();
        }
        *out_stream << "#" << (i+1) << left << setw(4) << " " 
             << setw(15) << quadString[q->op]
             << setw(12) << result_str
             << setw(12) << arg1_str
             << setw(12) << arg2_str;
        if (q->label != 0) {
            *out_stream << setw(5) << q->label;
        }
        *out_stream << endl;
    }
    if (outfile.is_open()) {
        outfile.close();
    }
}

expr* newTempExpr() {
    string tempName = "_t" + to_string(tmpCount++);
    Symbol* sym = symbolTable.lookupInScope(tempName, 0);
    if (!sym) {
        sym = symbolTable.insert(tempName, 0, 0, LOCAL_VAR);
    }
    return symToExpr(sym);
}
