#ifndef __INSTR__
#define __INSTR__

#include <string>
#include <cstdio>
#include <vector>
using namespace std;

class Symbol;
struct expr;
struct quad;

#include "quad.h"

#define AVM_STACKSIZE 4096
#define AVM_TABLE_HASHSIZE 211
#define AVM_WIPEOUT(m) memset(&(m),0,sizeof(m))


typedef enum vmopcode{
    assign_v,
    add_v,          
    sub_v,
    mul_v,          
    div_v,          
    mod_v,
    uminus_v,       
    and_v,          
    or_v,
    not_v,          
    jeq_v,          
    jne_v,
    jle_v,          
    jge_v,          
    jlt_v,
    jgt_v,          
    callfunc_v,     
    pusharg_v,
    ret_v,          
    getretval_v,    
    enterfunc_v,    
    exitfunc_v,     
    tablecreate_v,  
    tablegetelem_v, 
    tablesetelem_v, 
    jump_v,         
    nop_v 
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
    retval_a
} vmarg_t;

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

vector <int> numConsts;
vector <int> stringConsts;
vector <int> libFuncs;
vector <int> userFuncs;

void generate_ADD (quad*);
void generate_SUB (quad*);
void generate_MUL (quad*);
void generate_DIV (quad*);
void generate_MOD (quad*);
void generate_NEWTABLE (quad*);
void generate_TABLEGETELEM (quad*);
void generate_TABLESETELEM (quad*);
void generate_ASSIGN (quad*);
void generate_NOP (quad*);
void generate_JUMP (quad*);
void generate_IF_EQ (quad*);
void generate_IF_NOTEQ (quad*);
void generate_IF_GREATER (quad*);
void generate_IF_GREATEREQ (quad*);
void generate_IF_LESS (quad*);
void generate_IF_LESSEQ (quad*);
void generate_NOT (quad*);
void generate_OR (quad*);
void generate_AND (quad*);
void generate_PARAM (quad*);
void generate_CALL (quad*);
void generate_GETRETVAL (quad*);
void generate_FUNCSTART (quad*);
void generate_RETURN (quad*);
void generate_FUNCEND (quad*);
void generate_UMINUS (quad*);


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
        string strVal;
        bool boolVal;
        avm_table * tableVal;
        unsigned funcVal;
        string libFuncVal;
    } data;
};

avm_memcell stack[AVM_STACKSIZE];

avm_table* avm_tablenew(void);
void avm_tabledestory(avm_table* t);
avm_memcell* avm_tablegetelem(avm_memcell *key);
void avm_tablesetelem(avm_memcell* key, avm_memcell* value);

static void avm_initstack(void);

struct avm_table_bucket{
    avm_memcell key;
    avm_memcell value;
    avm_table_bucket* next;
};

struct avm_table{
    unsigned refCounter;
    avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* boolIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* funcIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* libIndexed[AVM_TABLE_HASHSIZE];
    unsigned total;
};

void avm_tableincrefcounter(avm_table* t){
    ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table* t){
    assert(t->refCounter>0);
    if(!--t->refCounter){
        avm_tabledestory(t);
    }
}

void avm_tablebucketsinit(avm_table_bucket** p){
    for(unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i){
        p[i] = (avm_table_bucket*) 0;
    }
}

avm_table* avm_tablenew(void){
    avm_table* t = new avm_table;
    AVM_WIPEOUT(*t);
    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->boolIndexed);
    avm_tablebucketsinit(t->strIndexed);
    avm_tablebucketsinit(t->libIndexed);
    avm_tablebucketsinit(t->funcIndexed);
    avm_tablebucketsinit(t->numIndexed);
    return t;
}

void avm_memcellclear(avm_memcell* m);

void avm_tablebucketsdestroy(avm_table_bucket**p){
    for(unsigned i = 0; i <AVM_TABLE_HASHSIZE;++i,++p){
        for(avm_table_bucket* b = *p;b;){
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
       }
       p[i] = (avm_table_bucket*) 0;
    }
}

void avm_tabledestroy (avm_table* t){
    avm_tablebucketsdestroy(t->boolIndexed);
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->libIndexed);
    avm_tablebucketsdestroy(t->funcIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
}

#endif