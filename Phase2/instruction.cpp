#include "instruction.h"

vector <double> numConsts;
vector <string*> stringConsts;
vector <string*> libFuncs;
vector <string*> userFuncs;
vector <bool> boolConst;

typedef void (*generator_func_t)(quad*);
avm_memcell stack[AVM_STACKSIZE];

generator_func_t generators[] = {
    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_JUMP,
    generate_NOP
};

string instruction_opcode_names[] = {
    "assign_v",
    "add_v",          
    "sub_v",
    "mul_v",         
    "div_v",          
    "mod_v",
    "uminus_v",       
    "and_v",          
    "or_v",
    "not_v",          
    "jeq_v",         
    "jne_v",
    "jle_v",          
    "jge_v",          
    "jlt_v",
    "jgt_v",          
    "callfunc_v",     
    "pusharg_v",
    "ret_v",    
    "getretval_v",    
    "enterfunc_v",    
    "exitfunc_v",     
    "tablecreate_v", 
    "tablegetelem_v", 
    "tablesetelem_v",
    "jump_v",         
    "nop_v"
};

string vmarg_names[] = {
    "label_a",
    "global_a",
    "formal_a",
    "local_a",
    "number_a",
    "string_a",
    "bool_a",
    "nil_a",
    "userfunc_a",
    "libfunc_a",
    "retval_a"
};

unsigned consts_newstring(string* s){
    string* str = new string(*s);
    stringConsts.push_back(str);
    return stringConsts.size() - 1;
}

unsigned consts_newnumber(double n){
    numConsts.push_back(n);
    return numConsts.size() - 1;
}

unsigned libFuncs_newused(string* s){
    string* str = new string(*s);
    libFuncs.push_back(str);
    return libFuncs.size() - 1;
}

unsigned userFuncs_newused(string* s){
    string* str = new string(*s);
    userFuncs.push_back(str);
    return userFuncs.size() - 1;
}

unsigned consts_newbool(bool b){
    boolConst.push_back(b);
    return boolConst.size() - 1;
}

static void avm_initstack(void){
    for(unsigned i = 0;i < AVM_STACKSIZE; ++i){
        AVM_WIPEOUT(stack[i]); stack[i].type = undef_m;
    }
}

void make_operand(expr* e, vmarg* arg){
    switch(e->type){
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:
        case newtable_e:    {
            assert(e->sym);
            arg->val = e->sym->offset;
            switch (e->sym->scope)
            {
            case programvar:
                arg->type = global_a;
                break;
            case functionlocal:
                arg->type = local_a;
            case formalarg:
                arg->type = formal_a;
            default:
                assert(0);
            }
            break;
        }
        case constbool_e:{
            arg->val = consts_newbool(e->value.boolValue);
            arg->type = bool_a;
            break;
        }
        case conststring_e:{
            arg->type = string_a;
            arg->val = consts_newstring(e->value.stringValue);
            break;
        }
        case constint_e:{
            arg->type = number_a;
            arg->val = consts_newnumber(e->value.intValue);
            break;
        }
        case constdouble_e:{
            arg->type = number_a;
            arg->val = consts_newnumber(e->value.doubleValue);
            break;
        }
        case nil_e:{
            arg->type = nil_a;
            break;
        }
        case programfunc_e:{
            arg->type = userfunc_a;
            string *name = new string;
            *name = e->sym->name;
            arg->val = userFuncs_newused(name);
            break;
        }
        case libraryfunc_e:{
            arg->type = libfunc_a;
            string *name = new string;
            *name = e->sym->name;
            arg->val = libFuncs_newused(name);
            break;
        }
        default:{
            assert(0);
        }
    }
}

void generate(vmopcode op,quad *q){
    instruction* i = new instruction;
    i->arg1 = nullptr;
    i->arg2 = nullptr;
    i->opcode = op;
    i->result = nullptr;
    i->srcLine = q->line;

}

void quad_to_instr(void* void_quad){
    if(void_quad == nullptr){
        return;
    }
    quad *q = (quad*) void_quad;
    generators[q->op](q);
    return;
}
