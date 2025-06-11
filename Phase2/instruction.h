#ifndef __INSTR__
#define __INSTR__

#include <string>
#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;

#include "headerLib.h"

class Symbol;
struct expr;
struct quad;

extern int magic_num;
#define AVM_STACKSIZE 4096
#define AVM_TABLE_HASHSIZE 211
#define AVM_WIPEOUT(m) memset(&(m),0,sizeof(m))


typedef enum vmopcode{
    assign_v=0,
    add_v=1,          
    sub_v=2,
    mul_v=3,          
    div_v=4,          
    mod_v=5,
    uminus_v=6,       
    and_v=7,          
    or_v=8,
    not_v=9,          
    jeq_v=10,          
    jne_v=11,
    jle_v=12,          
    jge_v=13,          
    jlt_v=14,
    jgt_v=15,          
    callfunc_v=16,     
    pusharg_v=17,
    ret_v=18,          
    getretval_v=19,    
    enterfunc_v=20,    
    exitfunc_v=21,     
    tablecreate_v=22,  
    tablegetelem_v=23, 
    tablesetelem_v=24, 
    jump_v=25,         
    nop_v=26 
} vmopcode;

typedef enum vmarg_t{
    label_a,
    global_a,
    formal_a,
    local_a,
    number_a,
    string_a,
    bool_a,
    nil_a,
    userfunc_a,
    libfunc_a,
    retval_a,
    undefined_a
} vmarg_t;

//giannis addition
typedef void (*library_func_t)(void);
library_func_t avm_getlibraryfunc(char* id);
void avm_registerlibfunc(char* id, library_func_t addr);



typedef struct vmarg{
    vmarg_t type;
    unsigned val;
} vmarg;

typedef struct instruction{
    vmopcode opcode;
    vmarg* result;
    vmarg* arg1;
    vmarg* arg2;
    unsigned srcLine;
} instruction;

typedef struct userfunc{
    unsigned address;
    unsigned localSize;
    const char* id;
} userfunc;

//giannis addition
double consts_getnumber(unsigned index);
char* consts_getstring(unsigned index);
char* libfuncs_getused(unsigned index);
userfunc* userfuncs_getfunc(unsigned index);

extern vector <double> numConsts;
extern vector <string*> stringConsts;
extern vector <string*> libDefFuncs;
extern vector <string*> userFuncs;
extern vector <bool> boolConst;
extern vector <instruction*> instructions;

void generate_ADD (quad*q);
void generate_SUB (quad*q);
void generate_MUL (quad*q);
void generate_DIV (quad*q);
void generate_MOD (quad*q);
void generate_NEWTABLE (quad*q);
void generate_TABLEGETELEM (quad*q);
void generate_TABLESETELEM (quad*q);
void generate_ASSIGN (quad*q);
void generate_NOP (quad*q);
void generate_JUMP (quad*q);
void generate_IF_EQ (quad*q);
void generate_IF_NOTEQ (quad*q);
void generate_IF_GREATER (quad*q);
void generate_IF_GREATEREQ (quad*q);
void generate_IF_LESS (quad*q);
void generate_IF_LESSEQ (quad*q);
void generate_NOT (quad*q);
void generate_OR (quad*q);
void generate_AND (quad*q);
void generate_PARAM (quad*q);
void generate_CALL (quad*q);
void generate_GETRETVAL (quad*q);
void generate_FUNCSTART (quad*q);
void generate_RETURN (quad* q);
void generate_FUNCEND (quad*q);
void generate_UMINUS (quad*q);

void generate(vmopcode op,quad *q);
void generate_relational(vmopcode op, quad* q);
instruction* generate_Proc(vmopcode op,quad *q);
void emit_instr(instruction*i);
void make_operand(expr* e, vmarg* arg);
unsigned consts_newstring(string* s);
unsigned consts_newnumber(double n);
unsigned libFuncs_newused(string* s);
unsigned userFuncs_newused(string* s);
unsigned consts_newbool(bool b);
void generate_make_op(instruction* i, quad* q);
void quad_to_instr(void* void_quad);

void instruction_to_binary(instruction *i);
void print_instruction(instruction* i, int step);

enum avm_memcell_t {
    number_m,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nil_m,
    undef_m
};

struct avm_table;
struct avm_memcell{
    avm_memcell_t type;
    union { 
        double numVal;
        char* strVal;
        bool boolVal;
        avm_table * tableVal;
        unsigned funcVal;
        char* libFuncVal;
    } data;
};
//giannis addition
typedef void (*memclear_func_t)(avm_memcell*);

extern avm_memcell stack[AVM_STACKSIZE];

void memclear_string(avm_memcell* m);
void memclear_table(avm_memcell* m);

extern memclear_func_t memclearFuncs[];


typedef char* (*tostring_func_t)(avm_memcell*);

char* number_tostring(avm_memcell*);
char* string_tostring(avm_memcell*);
char* bool_tostring(avm_memcell*);
char* table_tostring(avm_memcell*);
char* userfunc_tostring(avm_memcell*);
char* libfunc_tostring(avm_memcell*);
char* nil_tostring(avm_memcell*);
char* undef_tostring(avm_memcell*);
//till here
avm_table* avm_tablenew(void);
void avm_tabledestroy(avm_table* t);
avm_memcell* avm_tablegetelem(avm_memcell *key);
void avm_tablesetelem(avm_memcell* key, avm_memcell* value);



static void avm_initstack(void);

struct avm_table_bucket{
    avm_memcell key;
    avm_memcell value;
    avm_table_bucket* next;
};

void readMagic(FILE* f);

struct avm_table{
    unsigned refCounter;
    avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* boolIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* funcIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* libIndexed[AVM_TABLE_HASHSIZE];
    unsigned total;
};

//giannis addition
void execute_assign(instruction*);
void execute_add(instruction*); 
void execute_sub(instruction*);
void execute_mul(instruction*);
void execute_div(instruction*);
void execute_mod(instruction*);
void execute_uminus(instruction*);
void execute_and(instruction*);
void execute_or(instruction*);
void execute_not(instruction*);
void execute_jeq(instruction*);
void execute_jne(instruction*);
void execute_jle(instruction*);
void execute_jge(instruction*);
void execute_jlt(instruction*);
void execute_jgt(instruction*);
void execute_call(instruction*);
void execute_pusharg(instruction*);
void execute_ret(instruction*);
void execute_getretval(instruction*);
void execute_funcenter(instruction*);
void execute_funcexit(instruction*);
void execute_tablecreate(instruction*);
void execute_tablegetelem(instruction*);
void execute_tablesetelem(instruction*);
void execute_jump(instruction*);
void execute_nop(instruction*);

//till here
void avm_tableincrefcounter(avm_table* t);
void avm_tabledecrefcounter(avm_table* t);
void avm_tablebucketsinit(avm_table_bucket** p);

avm_table* avm_tablenew(void);

void avm_memcellclear(avm_memcell* m);

void avm_tablebucketsdestroy(avm_table_bucket**p);

void avm_tabledestroy (avm_table* t);

void readAbcFile(const string& filename);

void execute_cycle();

void readMagic(FILE* f);
void readNumbers(FILE* f);
void readStrings(FILE* f);
void readUserFunctions(FILE* f);
void readLibFunctions(FILE* f);
void readBoolConstants(FILE* f);
void readInstructions(FILE* f);
#endif