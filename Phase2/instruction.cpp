#include "instruction.h"
#include <cstring>
#include <cmath>
vector <double> numConsts;
vector <string*> stringConsts;
vector <string*> libDefFuncs;
vector <string*> userFuncs;
vector <bool> boolConst;
vector <instruction*> instructions;

extern FILE*       instructions_out;
extern FILE*       binary;

int instrStep = 1;
int magic_num = 0;
int totalNums = 0;

LibFuncsHashTable* LibHashTable = nullptr;
unsigned total_globals = 0;

//giannis addition
unsigned totalActuals = 0;
unsigned char executionFinished = 0;
unsigned char pc = 0;
unsigned currLine = 0;
unsigned codeSize = 0;
instruction*  code = (instruction*) 0;
unsigned top=0;
unsigned topsp = 0;
avm_memcell ax;
avm_memcell bx;
avm_memcell cx;
avm_memcell retval;
#define AVM_ENDING_PC codeSize
#define AVM_MAX_INSTRUCTIONS 26
#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1
#define AVM_STACKENV_SIZE 4

incomplete_jump* ij_head = (incomplete_jump*) 0;
unsigned ij_total = 0;


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

//giannis addition
tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring
};

typedef unsigned char (*tobool_func_t)(avm_memcell*);

unsigned char number_tobool(avm_memcell* m) { 
    assert(m && m->type == number_m);
    return m->data.numVal != 0; 
}

unsigned char string_tobool(avm_memcell* m) { 
    assert(m && m->type == string_m);
    return m->data.strVal[0] != 0; 
}

unsigned char bool_tobool(avm_memcell* m) { 
    assert(m && m->type == bool_m);
    return m->data.boolVal; 
}

unsigned char table_tobool(avm_memcell* m) { 
    assert(m && m->type == table_m);
    return 1; 
}

unsigned char userfunc_tobool(avm_memcell* m) { 
    assert(m && m->type == userfunc_m);
    return 1; 
}

unsigned char libfunc_tobool(avm_memcell* m) { 
    assert(m && m->type == libfunc_m);
    return 1; 
}

unsigned char nil_tobool(avm_memcell* m) { 
    assert(m && m->type == nil_m);
    return 0; 
}

unsigned char undef_tobool(avm_memcell* m) {
    assert(0);
    return 0;
}

tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool
};


typedef void (*execute_func_t)(instruction*);

execute_func_t executeFuncs[] = {
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,
    execute_or,
    execute_not,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_ret,
    execute_getretval,
    execute_funcenter,
    execute_funcexit,
    execute_tablecreate,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_jump,
    execute_nop
};

memclear_func_t memclearFuncs[] = {
    nullptr,
    memclear_string,
    nullptr,
    memclear_table,
    nullptr,
    nullptr,
    nullptr,
    nullptr
};
//till here

void generate_ADD (quad* q){
    generate(add_v,q);
}

void generate_SUB (quad* q){
    generate(sub_v,q);
}

void generate_MUL (quad* q){
    generate(mul_v,q);
}

void generate_DIV (quad* q){
    generate(div_v,q);
}

void generate_MOD (quad* q){
    generate(mod_v,q);
}

void generate_TABLEGETELEM (quad* q){
    generate(tablegetelem_v,q);
}

void generate_TABLESETELEM (quad* q){
    generate(tablesetelem_v,q);
}

void generate_NEWTABLE (quad* q){
    generate(tablecreate_v,q);
}

void generate_ASSIGN (quad *q){
    generate(assign_v,q);
}

void generate_NOT(quad* q) {
    instruction* t = new instruction;
    t->opcode = not_v;
    t->arg1 = new vmarg;
    make_operand(q->arg1, t->arg1);
    t->result = new vmarg;
    make_operand(q->result, t->result);
    emit_instr(t);
}

void generate_AND(quad *q){
    instruction* t = new instruction;
    t->opcode = and_v;
    t->arg1 = new vmarg;
    make_operand(q->arg1, t->arg1);
    t->arg2 = new vmarg;
    make_operand(q->arg2, t->arg2);
    t->result = new vmarg;
    make_operand(q->result, t->result);
    emit_instr(t);
}

void generate_OR(quad *q){
    instruction* t = new instruction;
    t->opcode = or_v;
    t->arg1 = new vmarg;
    make_operand(q->arg1, t->arg1);
    t->arg2 = new vmarg;
    make_operand(q->arg2, t->arg2);
    t->result = new vmarg;
    make_operand(q->result, t->result);
    emit_instr(t);
}

void generate_JUMP(quad *q){
    generate_relational(jump_v,q);
}

void generate_IF_EQ(quad *q){
    generate_relational(jeq_v,q);
}

void generate_IF_NOTEQ(quad *q){
    generate_relational(jne_v,q);
}

void generate_IF_GREATER(quad *q){
    generate_relational(jgt_v,q);
}

void generate_IF_GREATEREQ(quad *q){
    generate_relational(jge_v,q);
}

void generate_IF_LESS(quad *q){
    generate_relational(jlt_v,q);
}

void generate_IF_LESSEQ(quad *q){
    generate_relational(jle_v,q);
}

void generate_NOP(quad* q){
    instruction* i = new instruction;
    i->arg1 = nullptr;
    i->arg2 = nullptr;
    i->result = nullptr;
    i->opcode = nop_v;
    emit_instr(i);
}


void generate_UMINUS(quad* q){
    instruction* i = generate_Proc(mul_v,q);
    if(q->arg1){
        i->arg1 = new vmarg;
        make_operand(q->arg1,i->arg1);
    }
    i->arg2 = new vmarg;
    i->arg2->val = consts_newnumber(-1);
    i->arg2->type = number_a;
    if(i->result){
        i->result = new vmarg;
        make_operand(q->result,i->result);
    }
    emit_instr(i);
}
void generate_PARAM(quad *q){
    instruction* i = generate_Proc(pusharg_v, q);
    if(q->arg1) {
        i->arg1 = new vmarg;
        make_operand(q->arg1, i->arg1);
    }
    emit_instr(i);
}

void generate_CALL(quad *q) {
    instruction* i = generate_Proc(callfunc_v, q);
    if(q->result) {
        i->result = new vmarg;
        make_operand(q->result, i->result);
    }
    emit_instr(i);
}

void generate_GETRETVAL(quad *q){
    return;
}

void generate_FUNCSTART(quad *q){
    return;
}

void generate_FUNCEND(quad *q){
    return;
}

void generate_RETURN(quad *q){
    return;
}

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
    libDefFuncs.push_back(str);
    return libDefFuncs.size() - 1;
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

// static void avm_initstack(void){
//     for(unsigned i = 0;i < AVM_STACKSIZE; ++i){
//         AVM_WIPEOUT(stack[i]); stack[i].type = undef_m;
//     }
// }

void make_operand(expr* e, vmarg* arg){
    switch(e->type){
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:
        case newtable_e: {
            if (!e->sym) {
                arg->type = nil_a;
                arg->val = 0;
                break;
            }
            
            arg->val = e->sym->offset;
            switch (e->sym->scopespace) {
                case programvar:
                    arg->type = global_a;
                    break;
                case functionlocal:
                    arg->type = local_a;
                    break;
                case formalarg:
                    arg->type = formal_a;
                    break;
                default:
                    arg->type = global_a;
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

//helper, vale se allo
void emit_instr(instruction*i){
    if(i == nullptr){
        cerr << "assert null at emit_inst" << endl;
    }
    instructions.push_back(i);
}

void readMagic(FILE* f) {
    long int magic;
    fread(&magic, sizeof(long int), 1, f);
    cerr <<"m: " <<magic << endl;
    if (magic != 163847504) {
        cerr << "Invalid magic number in .abc file" << endl;
        exit(1);
    }
    cout << "Magic number verified: " << magic << endl;
}

void readNumbers(FILE* f) {
    int count;
    fread(&count, sizeof(int), 1, f);
    cout << "Reading " << count << " number constants:" << endl;
    
    for(int i = 0; i < count; i++) {
        double num;
        fread(&num, sizeof(double), 1, f);
        numConsts.push_back(num);
        cout << i << ": " << num << endl;
    }
}

void readStrings(FILE* f) {
    int count;
    fread(&count, sizeof(int), 1, f);
    cout << "Reading " << count << " string constants:" << endl;
    
    for(int i = 0; i < count; i++) {
        int len;
        fread(&len, sizeof(int), 1, f);
        
        char* buffer = new char[len + 1];
        fread(buffer, sizeof(char), len, f);
        buffer[len] = '\0';
        
        string* str = new string(buffer);
        stringConsts.push_back(str);
        cout << i << ": " << *str << endl;
        
        delete[] buffer;
    }
}

void readUserFunctions(FILE* f) {
    int count;
    fread(&count, sizeof(int), 1, f);
    cout << "Reading " << count << " user functions:" << endl;
    
    for(int i = 0; i < count; i++) {
        int len;
        fread(&len, sizeof(int), 1, f);
        
        char* buffer = new char[len + 1];
        fread(buffer, sizeof(char), len, f);
        buffer[len] = '\0';
        
        string* str = new string(buffer);
        userFuncs.push_back(str);
        cout << i << ": " << *str << endl;
        
        delete[] buffer;
    }
}

void readLibFunctions(FILE* f) {
    int count;
    fread(&count, sizeof(int), 1, f);
    cout << "Reading " << count << " library functions:" << endl;
    
    for(int i = 0; i < count; i++) {
        int len;
        fread(&len, sizeof(int), 1, f);
        
        char* buffer = new char[len + 1];
        fread(buffer, sizeof(char), len, f);
        buffer[len] = '\0';
        
        string* str = new string(buffer);
        libDefFuncs.push_back(str);
        cout << i << ": " << *str << endl;
        
        delete[] buffer;
    }
}

void readBoolConstants(FILE* f) {
    int count;
    fread(&count, sizeof(int), 1, f);
    cout << "Reading " << count << " boolean constants:" << endl;
    
    for(int i = 0; i < count; i++) {
        bool b;
        fread(&b, sizeof(bool), 1, f);
        boolConst.push_back(b);
        cout << i << ": " << (b ? "true" : "false") << endl;
    }
}

void readInstructions(FILE* f) {
    int count;
    fread(&count, sizeof(int), 1, f);
    cout << "Reading " << count << " instructions:" << endl;
    
    for(int i = 0; i < count; i++) {
        instruction* instr = new instruction;
        
        int opcode, result_type, result_val, arg1_type, arg1_val, arg2_type, arg2_val, srcLine;
        
        fread(&opcode, sizeof(int), 1, f);
        fread(&result_type, sizeof(int), 1, f);
        fread(&result_val, sizeof(int), 1, f);
        fread(&arg1_type, sizeof(int), 1, f);
        fread(&arg1_val, sizeof(int), 1, f);
        fread(&arg2_type, sizeof(int), 1, f);
        fread(&arg2_val, sizeof(int), 1, f);
        fread(&srcLine, sizeof(int), 1, f);
        
        instr->opcode = (vmopcode)opcode;
        instr->srcLine = srcLine;
        
        // Create result vmarg if it exists
        if (result_type != -1) {
            instr->result = new vmarg;
            instr->result->type = (vmarg_t)result_type;
            instr->result->val = result_val;
        } else {
            instr->result = nullptr;
        }
        
        // Create arg1 vmarg if it exists
        if (arg1_type != -1) {
            instr->arg1 = new vmarg;
            instr->arg1->type = (vmarg_t)arg1_type;
            instr->arg1->val = arg1_val;
        } else {
            instr->arg1 = nullptr;
        }
        
        // Create arg2 vmarg if it exists
        if (arg2_type != -1) {
            instr->arg2 = new vmarg;
            instr->arg2->type = (vmarg_t)arg2_type;
            instr->arg2->val = arg2_val;
        } else {
            instr->arg2 = nullptr;
        }
        
        instructions.push_back(instr);
        
        // Print the instruction for verification
        print_instruction(instr, i);
    }
}

void readAbcFile(const string& filename) {
    FILE* f = fopen(filename.c_str(), "rb");
    if (!f) {
        cerr << "Cannot open .abc file: " << filename << endl;
        return;
    }
    
    cout << "Reading .abc file: " << filename << endl;
    numConsts.clear();
    stringConsts.clear();
    libDefFuncs.clear();
    userFuncs.clear();
    boolConst.clear();
    instructions.clear();
    readMagic(f);
    readNumbers(f);
    readStrings(f);
    readUserFunctions(f);
    readLibFunctions(f);
    readBoolConstants(f);
    readInstructions(f);
    
    fclose(f);
    cout << "Successfully loaded .abc file!" << endl;
}

//helper, vale se allo
instruction* generate_Proc(vmopcode op,quad *q){
    instruction* i = new instruction;
    i->arg1 = nullptr;
    i->arg2 = nullptr;
    i->opcode = op;
    i->result = nullptr;
    i->srcLine = q ? q->line : 0;  
    return i;
}

void generate(vmopcode op,quad *q){
    instruction* i = generate_Proc(op,q);
    generate_make_op(i, q);
    if(q->result){
        i->result = new vmarg;
        make_operand(q->result,i->result);
    }
    emit_instr(i);
}

//helper, vale se allo
void generate_make_op(instruction* i, quad* q){
    if(q->arg1){
        i->arg1 = new vmarg;
        make_operand(q->arg1,i->arg1);
    }
    if(q->arg2){
        i->arg2 = new vmarg;
        make_operand(q->arg2,i->arg2);
    }
    return;
}

void generate_relational(vmopcode op, quad* q) {
    instruction* i = generate_Proc(op, q);
    generate_make_op(i, q);
    i->result = new vmarg;
    i->result->type = label_a;
    i->result->val = 0; // placeholder, will be patched later
    emit_instr(i);

    // If the jump target is not yet known, add to incomplete jumps
    add_incomple_jump(instructions.size() - 1, q->label);
}

void quad_to_instr(void* void_quad) {
    if(void_quad == nullptr) {
        return;
    }
    quad *q = (quad*) void_quad;
    q->taddress = instructions.size();
    cout << "Converting quad to instruction: " << quadString[q->op] << endl;  // Add this line
    generators[q->op](q);
}



// Add this function to your instruction.cpp file
void avm_memcellclear(avm_memcell* m) {
    if (m == nullptr) return;
    
    // Free dynamically allocated memory based on the cell's type
    if (m->type == string_m && m->data.strVal != nullptr) {
        delete[] m->data.strVal;
        m->data.strVal = nullptr;
    } else if (m->type == table_m && m->data.tableVal != nullptr) {
        avm_tabledecrefcounter(m->data.tableVal);
        m->data.tableVal = nullptr;
    } else if (m->type == libfunc_m && m->data.libFuncVal != nullptr) {
        delete[] m->data.libFuncVal;
        m->data.libFuncVal = nullptr;
    }
    
    // Set the type to undefined
    m->type = undef_m;
}

void print_instruction(instruction* i, int step){
    if(i == nullptr){
        assert(0);
    }
    vmarg* r = i->result;
    vmarg* arg1 = i->arg1;
    vmarg* arg2 = i->arg2;
    //string opcode = instruction_opcode_names[i->opcode];
    fprintf(instructions_out,"%d: instruction: %s ",step,instruction_opcode_names[i->opcode].c_str());
    if(arg1){
        fprintf(instructions_out,"arg1:(%s,%d) ",vmarg_names[arg1->type].c_str(),arg1->val);
    }
    if(arg2){
        fprintf(instructions_out,"arg2:(%s,%d) ",vmarg_names[arg2->type].c_str(),arg2->val);
    }
    if(r){
        fprintf(instructions_out,"result:(%s,%d) ",vmarg_names[r->type].c_str(),r->val);
    }
    fprintf(instructions_out,"[srcLine:%d] ",i->srcLine);
    fprintf(instructions_out, "\n");
}

void instruction_to_binary(instruction *i){
    if(i == nullptr){
        assert(0);
    }
    vmarg* r = i->result;
    vmarg* arg1 = i->arg1;
    vmarg* arg2 = i->arg2;
    int opcode = i->opcode;
    int result_type = -1, arg1_type = -1, arg2_type = -1;
    int result_val = -1, arg1_val = -1, arg2_val = -1;
    
    if(r) {
        result_type = r->type;
        result_val = r->val;
    }
    if(arg1) {
        arg1_type = arg1->type;
        arg1_val = arg1->val;
    }
    if(arg2) {
        arg2_type = arg2->type;
        arg2_val = arg2->val;
    }
    int srcLine = i->srcLine;
    
    // Write the binary data to the file
    fwrite(&opcode, sizeof(int), 1, binary);
    fwrite(&result_type, sizeof(int), 1, binary);
    fwrite(&result_val, sizeof(int), 1, binary);
    fwrite(&arg1_type, sizeof(int), 1, binary);
    fwrite(&arg1_val, sizeof(int), 1, binary);
    fwrite(&arg2_type, sizeof(int), 1, binary);
    fwrite(&arg2_val, sizeof(int), 1, binary);
    fwrite(&srcLine, sizeof(int), 1, binary);

}

void avm_tableincrefcounter(avm_table* t){
    ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table* t){
    assert(t->refCounter>0);
    if(!--t->refCounter){
        avm_tabledestroy(t);
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

void avm_tablebucketsdestroy(avm_table_bucket** p) {
    for(unsigned i = 0; i < AVM_TABLE_HASHSIZE; ++i) {  // Remove the ++p
        for(avm_table_bucket* b = p[i]; b;) {
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = nullptr;
    }
}

void avm_tabledestroy (avm_table* t){
    avm_tablebucketsdestroy(t->boolIndexed);
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->libIndexed);
    avm_tablebucketsdestroy(t->funcIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
}
//giannis addition till the end
double consts_getnumber(unsigned index) {
    assert(index < numConsts.size());
    return numConsts[index];
}

char* consts_getstring(unsigned index) {
    assert(index < stringConsts.size());
    return strdup(stringConsts[index]->c_str());
}

char* libfuncs_getused(unsigned index) {
    assert(index < libDefFuncs.size());
    return strdup(libDefFuncs[index]->c_str());
}

userfunc* userfuncs_getfunc(unsigned index) {
    assert(index < userFuncs.size());
    userfunc* func = new userfunc;
    func->address = index;
    func->localSize = 0; 
    return func;
}

void avm_error (char *msg) {
    cerr << "AVM Error"<< msg << " in line  " << currLine << ": "; 
}

void avm_warning (char *msg) {
    cerr << "AVM Warning: " << msg << " in line  " << currLine << ": "; 
}



userfunc* avm_getfuncinfo(unsigned address) {

}

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg) {
    switch (arg->type) {
        case global_a:
            return &stack[AVM_STACKSIZE - 1 - arg->val];
        case local_a:
            return &stack[topsp - arg->val];
        case formal_a:
            return &stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];
        case retval_a:
            return &retval;
        case number_a:
            reg->type = number_m;
            reg->data.numVal = consts_getnumber(arg->val);
            return reg;
        case string_a:
            reg->type = string_m;
            reg->data.strVal = consts_getstring(arg->val);
            return reg;
        case bool_a:
            reg->type = bool_m;
            reg->data.boolVal = boolConst[arg->val];
            return reg;
        case nil_a:
            reg->type = nil_m;
            return reg;
        case userfunc_a:
            reg->type = userfunc_m;
            reg->data.funcVal = arg->val;
            return reg;
        case libfunc_a: 
            reg->type = libfunc_m;
            reg->data.libFuncVal = libfuncs_getused(arg->val);
            return reg;
        case label_a:
            reg->type = number_m;
            reg->data.numVal = arg->val;
            return reg;
        case undefined_a:
            avm_error("Invalid operand type in avm_translate_operand");
            executionFinished = 1;
            return nullptr;
        default:
            avm_error("Invalid operand type in avm_translate_operand");
            executionFinished = 1;
            return nullptr;
    }
}

char* avm_tostring(avm_memcell* m) {
    assert(m->type >=0 && m->type <= undef_m);
    return (*tostringFuncs[m->type])(m);
}

void avm_dec_top(void) {
    if (!top) {
        avm_error("Stack overflow");
        executionFinished = 1;
    } else {
        --top;
    }
}

void avm_push_envvalue(unsigned val) {
    stack[top].type = number_m; 
    stack[top].data.numVal = (double)val;
    avm_dec_top();
}

unsigned avm_get_envvalue(unsigned i) {
    assert(stack[i].type == number_m);
    double val = stack[i].data.numVal;
    if (val < 0 || val != floor(val)) {
        avm_error("Invalid environment value");
        executionFinished = 1;
        return 0;
    }
    return (unsigned)val;
}

unsigned avm_totalactuals(void) {
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i) {
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i]; 
}


void libfunc_print(void) {
    unsigned n = avm_totalactuals();
    for (unsigned i = 0; i < n; ++i) {
        avm_memcell* arg = avm_getactual(i);
        char* s = avm_tostring(arg);
        cout << s;
        if (i < n-1) cout << " ";
        free(s);
    }
    cout << endl;  // Add newline at the end
}

void libfunc_input(void) {
    char buffer[1024];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        if (strcmp(buffer, "true") == 0) {
            retval.type = bool_m;
            retval.data.boolVal = true;
        } else if (strcmp(buffer, "false") == 0) {
            retval.type = bool_m;
            retval.data.boolVal = false;
        } else if (strcmp(buffer, "nil") == 0) {
            retval.type = nil_m;
        } else if (buffer[0] == '"' && buffer[len - 1] == '"') {
            buffer[len - 1] = '\0'; 
            retval.type = string_m;
            retval.data.strVal = strdup(buffer + 1); 
        } else {
            char* endptr;
            double num = strtod(buffer, &endptr);
            
            if (*endptr == '\0') {
                retval.type = number_m;
                retval.data.numVal = num;
            } else {
                retval.type = string_m;
                retval.data.strVal = strdup(buffer);
            }
        }
    } else {
        retval.type = nil_m;
    }
}

void avm_registerlibfunc(const char* id, library_func_t addr) {
    LibFuncsHashTable* entry = new LibFuncsHashTable;
    entry->id = strdup(id);
    entry->func = addr;
    entry->next = LibHashTable;
    LibHashTable = entry;
}


void memclear_string(avm_memcell* m) {
    assert(m->data.strVal);
    free(m->data.strVal);
}

void memclear_table(avm_memcell* m) {
    assert(m->data.tableVal);
    avm_tabledecrefcounter(m->data.tableVal);
}





void execute_cycle(){
    if (executionFinished) {
        return;
    }
    
    else if (pc == AVM_ENDING_PC) {
        executionFinished = 1;
        return;
    }
    else
     {
        assert(pc < AVM_ENDING_PC);
        instruction* instr =  code + pc;
        assert ( 
            instr->opcode >= 0 &&
             instr->opcode <= AVM_MAX_INSTRUCTIONS
            );
            if (instr->srcLine){
                currLine = instr->srcLine;
            }
            unsigned oldPC = pc;
            (*executeFuncs[instr->opcode])(instr);
            if (pc == oldPC) {
                pc++;
            }
    }
}


void avm_assign(avm_memcell* lv, avm_memcell* rv) {
    if (lv == rv) {
        return; 
    } 
    if (lv->type == table_m && rv->type == table_m &&
         lv->data.tableVal == rv->data.tableVal) { 
    return;
    }
    if (rv->type == undef_m) {
        avm_warning("assigning from 'undef' content.");
    }
    avm_memcellclear(lv); 
    memcpy(lv, rv, sizeof(avm_memcell)); 
    if (lv->type == string_m) {
        lv->data.strVal = strdup(rv->data.strVal);
    } else if (lv->type == table_m) {
        avm_tableincrefcounter(lv->data.tableVal);
    }
}

void execute_assign(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, nullptr);
    avm_memcell* rv = avm_translate_operand(instr->arg1, &ax);
    
    // Better assertion check
    assert(lv);
    assert(rv);
    
    // Check if lv is within valid stack bounds or is retval
    bool validLv = (lv >= &stack[0] && lv <= &stack[AVM_STACKSIZE-1]) || (lv == &retval);
    if (!validLv) {
        avm_error("Invalid left-value memory address in assignment");
        executionFinished = 1;
        return;
    }
    
    avm_assign(lv, rv);
}

void avm_callsaveenvironment(void) {
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc+1);
    avm_push_envvalue(top + totalActuals + 2);
    avm_push_envvalue(topsp);
}

void execute_funcenter (instruction* instr) {
    totalActuals = 0;
    userfunc* funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->localSize;
}

void execute_funcexit (instruction* unused){
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    while (oldTop++ < top) {
        avm_memcellclear(&stack[oldTop]);
    }
}

void execute_pusharg (instruction* instr) {
    avm_memcell* arg = avm_translate_operand(instr->arg1, &ax);
    assert(arg);
    
    avm_assign(&stack[top], arg); 
    ++totalActuals;
    avm_dec_top(); 
}

// library_func_t avm_getlibraryfunc(char* id){
// /*
// to be done 
// */
// }

void avm_calllibfunc(char* id) {
    library_func_t f = avm_getlibraryfunc(id);
    if (!f) {
        avm_error("Undefined library function");
        executionFinished = 1;
        return;
    }
    
    topsp = top;
    totalActuals = 0;
    (*f)();
    
    if (!executionFinished) {
        execute_funcexit((instruction*)0);
    }
}
//ayto exei ki alla den einai mono ayta.
void execute_call(instruction* instr) {
    avm_memcell* func = avm_translate_operand(instr->result, &ax);
    assert(func);

    switch (func->type) {
        case userfunc_m: { 
            // Save current environment before calling user function
            avm_callsaveenvironment();
            pc = func->data.funcVal;
            assert(pc < AVM_ENDING_PC);
            assert(code[pc].opcode == enterfunc_v);
            break;
        }
        case string_m: {
            // Save current environment before calling library function
            avm_callsaveenvironment();
            avm_calllibfunc(func->data.strVal);
            break;
        }
        case libfunc_m: {
            // Save current environment before calling library function
            avm_callsaveenvironment();
            avm_calllibfunc(func->data.libFuncVal);
            break;
        }
        default: {
            avm_error("Invalid function type in call");
            executionFinished = 1;
        }
    }
}
//copilot apla to ekana copy paste gia na kanei compile
char* number_tostring(avm_memcell* m) {
    char* buffer = new char[64];
    snprintf(buffer, 64, "%.6g", m->data.numVal);
    return buffer;
}
//copilot apla to ekana copy paste gia na kanei compile
char* string_tostring(avm_memcell* m) {
    return strdup(m->data.strVal);
}
//copilot apla to ekana copy paste gia na kanei compile
char* bool_tostring(avm_memcell* m) {
    return strdup(m->data.boolVal ? "true" : "false");
}
//copilot apla to ekana copy paste gia na kanei compile
char* table_tostring(avm_memcell* m) {
    return strdup("[table]");
}
//copilot apla to ekana copy paste gia na kanei compile
char* userfunc_tostring(avm_memcell* m) {
    char* buffer = new char[64];
    snprintf(buffer, 64, "[userfunc:%u]", m->data.funcVal);
    return buffer;
}
//copilot apla to ekana copy paste gia na kanei compile
char* libfunc_tostring(avm_memcell* m) {
    return strdup(m->data.libFuncVal);
}
//copilot apla to ekana copy paste gia na kanei compile
char* nil_tostring(avm_memcell* m) {
    return strdup("nil");
}
//copilot apla to ekana copy paste gia na kanei compile
char* undef_tostring(avm_memcell* m) {
    return strdup("undefined");
}


//copilot apla to ekana copy paste gia na kanei compile
void execute_add(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, nullptr);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    assert(lv && rv1 && rv2);
    assert(rv1->type == number_m && rv2->type == number_m);
    
    lv->type = number_m;
    lv->data.numVal = rv1->data.numVal + rv2->data.numVal;
}
//copilot apla to ekana copy paste gia na kanei compile
void execute_sub(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, nullptr);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    assert(lv && rv1 && rv2);
    assert(rv1->type == number_m && rv2->type == number_m);
    
    lv->type = number_m;
    lv->data.numVal = rv1->data.numVal - rv2->data.numVal;
}
//copilot apla to ekana copy paste gia na kanei compile
void execute_mul(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, nullptr);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    assert(lv && rv1 && rv2);
    assert(rv1->type == number_m && rv2->type == number_m);
    
    lv->type = number_m;
    lv->data.numVal = rv1->data.numVal * rv2->data.numVal;
}
//copilot apla to ekana copy paste gia na kanei compile
void execute_div(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, nullptr);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    assert(lv && rv1 && rv2);
    assert(rv1->type == number_m && rv2->type == number_m);
    
    if (rv2->data.numVal == 0) {
        avm_error("Division by zero");
        executionFinished = 1;
        return;
    }
    lv->type = number_m;
    lv->data.numVal = rv1->data.numVal / rv2->data.numVal;
}

//copilot apla to ekana copy paste gia na kanei compile
void execute_mod(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, nullptr);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);

    assert(lv && rv1 && rv2);
    assert(rv1->type == number_m && rv2->type == number_m);
    
    if (rv2->data.numVal == 0) {
        avm_error("Division by zero");
        executionFinished = 1;
        return;
    }
    lv->type = number_m;
    lv->data.numVal = fmod(rv1->data.numVal, rv2->data.numVal);
}

void execute_uminus(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, nullptr);
    avm_memcell* rv = avm_translate_operand(instr->arg1, &ax);
    
    assert(lv && rv);
    assert(rv->type == number_m);
    
    lv->type = number_m;
    lv->data.numVal = -rv->data.numVal;
}

void execute_and(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, nullptr);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
    
    assert(lv && rv1 && rv2);
    assert(rv1->type == bool_m && rv2->type == bool_m);
    
    lv->type = bool_m;
    lv->data.boolVal = rv1->data.boolVal && rv2->data.boolVal;
}

void execute_or(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, nullptr);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &bx);
    
    assert(lv && rv1 && rv2);
    assert(rv1->type == bool_m && rv2->type == bool_m);
    
    lv->type = bool_m;
    lv->data.boolVal = rv1->data.boolVal || rv2->data.boolVal;
}

void execute_not(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, nullptr);
    avm_memcell* rv = avm_translate_operand(instr->arg1, &ax);
    
    assert(lv && rv);
    assert(rv->type == bool_m);
    
    lv->type = bool_m;
    lv->data.boolVal = !rv->data.boolVal;
}

void execute_jlt(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, &ax);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &bx);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &cx);
    
    assert(lv && rv1 && rv2);
    
    // Convert operands to numbers if they aren't already
    if (rv1->type != number_m) {
        avm_memcellclear(&bx);
        bx.type = number_m;
        bx.data.numVal = avm_tobool(rv1);
        rv1 = &bx;
    }
    if (rv2->type != number_m) {
        avm_memcellclear(&cx);
        cx.type = number_m;
        cx.data.numVal = avm_tobool(rv2);
        rv2 = &cx;
    }
    
    // If lv is a label, this is a jump instruction
    if (lv->type == number_m && lv->data.numVal >= 0) {
        if (rv1->data.numVal < rv2->data.numVal) {
            pc = lv->data.numVal;
        } else {
            pc++;  // Skip the jump if condition is false
        }
    } else {
        // This is a boolean assignment
        lv->type = bool_m;
        lv->data.boolVal = (rv1->data.numVal < rv2->data.numVal);
        pc++;
    }
}

void execute_jgt(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, &ax);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &bx);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &cx);
    
    assert(lv && rv1 && rv2);
    
    // Convert operands to numbers if they aren't already
    if (rv1->type != number_m) {
        avm_memcellclear(&bx);
        bx.type = number_m;
        bx.data.numVal = avm_tobool(rv1);
        rv1 = &bx;
    }
    if (rv2->type != number_m) {
        avm_memcellclear(&cx);
        cx.type = number_m;
        cx.data.numVal = avm_tobool(rv2);
        rv2 = &cx;
    }
    
    // If lv is a label, this is a jump instruction
    if (lv->type == number_m && lv->data.numVal >= 0) {
        if (rv1->data.numVal > rv2->data.numVal) {
            pc = lv->data.numVal;
        } else {
            pc++;  // Skip the jump if condition is false
        }
    } else {
        // This is a boolean assignment
        lv->type = bool_m;
        lv->data.boolVal = (rv1->data.numVal > rv2->data.numVal);
        pc++;
    }
}

void execute_jle(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, &ax);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &bx);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &cx);
    
    assert(lv && rv1 && rv2);
    
    // Convert operands to numbers if they aren't already
    if (rv1->type != number_m) {
        avm_memcellclear(&bx);
        bx.type = number_m;
        bx.data.numVal = avm_tobool(rv1);
        rv1 = &bx;
    }
    if (rv2->type != number_m) {
        avm_memcellclear(&cx);
        cx.type = number_m;
        cx.data.numVal = avm_tobool(rv2);
        rv2 = &cx;
    }
    
    // If lv is a label, this is a jump instruction
    if (lv->type == number_m && lv->data.numVal >= 0) {
        if (rv1->data.numVal <= rv2->data.numVal) {
            pc = lv->data.numVal;
        } else {
            pc++;  // Skip the jump if condition is false
        }
    } else {
        // This is a boolean assignment
        lv->type = bool_m;
        lv->data.boolVal = (rv1->data.numVal <= rv2->data.numVal);
        pc++;
    }
}

void execute_jge(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, &ax);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &bx);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &cx);
    
    assert(lv && rv1 && rv2);
    
    // Convert operands to numbers if they aren't already
    if (rv1->type != number_m) {
        avm_memcellclear(&bx);
        bx.type = number_m;
        bx.data.numVal = avm_tobool(rv1);
        rv1 = &bx;
    }
    if (rv2->type != number_m) {
        avm_memcellclear(&cx);
        cx.type = number_m;
        cx.data.numVal = avm_tobool(rv2);
        rv2 = &cx;
    }
    
    // If lv is a label, this is a jump instruction
    if (lv->type == number_m && lv->data.numVal >= 0) {
        if (rv1->data.numVal >= rv2->data.numVal) {
            pc = lv->data.numVal;
        } else {
            pc++;  // Skip the jump if condition is false
        }
    } else {
        // This is a boolean assignment
        lv->type = bool_m;
        lv->data.boolVal = (rv1->data.numVal >= rv2->data.numVal);
        pc++;
    }
}

void execute_jeq(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, &ax);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &bx);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &cx);
    
    assert(lv && rv1 && rv2);
    
    // If lv is a label, this is a jump instruction
    if (lv->type == number_m && lv->data.numVal >= 0) {
        if (rv1->type == rv2->type) {
            if (rv1->type == number_m) {
                if (rv1->data.numVal == rv2->data.numVal) {
                    pc = lv->data.numVal;
                    return;
                }
            }
            else if (rv1->type == string_m) {
                if (strcmp(rv1->data.strVal, rv2->data.strVal) == 0) {
                    pc = lv->data.numVal;
                    return;
                }
            }
            else if (rv1->type == bool_m) {
                if (rv1->data.boolVal == rv2->data.boolVal) {
                    pc = lv->data.numVal;
                    return;
                }
            }
        }
        pc++;  // Skip the jump if condition is false
    } else {
        // This is a boolean assignment
        lv->type = bool_m;
        if (rv1->type == rv2->type) {
            if (rv1->type == number_m) {
                lv->data.boolVal = (rv1->data.numVal == rv2->data.numVal);
            }
            else if (rv1->type == string_m) {
                lv->data.boolVal = (strcmp(rv1->data.strVal, rv2->data.strVal) == 0);
            }
            else if (rv1->type == bool_m) {
                lv->data.boolVal = (rv1->data.boolVal == rv2->data.boolVal);
            }
        } else {
            lv->data.boolVal = false;
        }
        pc++;
    }
}

void execute_jne(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, &ax);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1, &bx);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2, &cx);
    
    assert(lv && rv1 && rv2);
    
    // If lv is a label, this is a jump instruction
    if (lv->type == number_m && lv->data.numVal >= 0) {
        if (rv1->type != rv2->type) {
            pc = lv->data.numVal;
            return;
        }
        
        if (rv1->type == number_m) {
            if (rv1->data.numVal != rv2->data.numVal) {
                pc = lv->data.numVal;
                return;
            }
        }
        else if (rv1->type == string_m) {
            if (strcmp(rv1->data.strVal, rv2->data.strVal) != 0) {
                pc = lv->data.numVal;
                return;
            }
        }
        else if (rv1->type == bool_m) {
            if (rv1->data.boolVal != rv2->data.boolVal) {
                pc = lv->data.numVal;
                return;
            }
        }
        pc++;  // Skip the jump if condition is false
    } else {
        // This is a boolean assignment
        lv->type = bool_m;
        if (rv1->type != rv2->type) {
            lv->data.boolVal = true;
        } else {
            if (rv1->type == number_m) {
                lv->data.boolVal = (rv1->data.numVal != rv2->data.numVal);
            }
            else if (rv1->type == string_m) {
                lv->data.boolVal = (strcmp(rv1->data.strVal, rv2->data.strVal) != 0);
            }
            else if (rv1->type == bool_m) {
                lv->data.boolVal = (rv1->data.boolVal != rv2->data.boolVal);
            }
        }
        pc++;
    }
}
void execute_ret(instruction* instr) {
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    
    while (oldTop++ < top) {
        avm_memcellclear(&stack[oldTop]);
    }
}

void execute_getretval(instruction* instr) {
    avm_memcell* lv = avm_translate_operand(instr->result, nullptr);
    assert(lv);
    avm_assign(lv, &retval);
}

void execute_tablecreate(instruction* instr) {
}

void execute_tablegetelem(instruction* instr) {
}

void execute_tablesetelem(instruction* instr) {
}

void execute_jump(instruction* instr) {
    avm_memcell* label = avm_translate_operand(instr->result, &ax);
    assert(label && label->type == number_m);
    pc = label->data.numVal;
}

void execute_nop(instruction* instr) {
    // Do nothing
}


void avm_initstack(void) {
    // Initialize the stack
    for (unsigned i = 0; i < AVM_STACKSIZE; i++) {
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }
    
    // Initialize topsp and top correctly
    topsp = AVM_STACKSIZE - 1;
    top = AVM_STACKSIZE - 1;
    
    // Initialize global variables properly
    total_globals = globalOffset;  // Set this to the number of globals you have
    
    // Register library functions
    avm_registerlibfunc("print", libfunc_print);
    avm_registerlibfunc("typeof", libfunc_typeof);
    avm_registerlibfunc("totalarguments", libfunc_totalarguments);
    avm_registerlibfunc("argument", libfunc_argument);
    avm_registerlibfunc("objecttotalmembers", libfunc_objecttotalmembers);
    avm_registerlibfunc("sqrt", libfunc_sqrt);
    avm_registerlibfunc("cos", libfunc_cos);
    avm_registerlibfunc("sin", libfunc_sin);
}

// void libfunc_print(void){
//     return;
// }
void libfunc_typeof(void){
    unsigned n = avm_totalactuals();
    if (n != 1) {
        avm_error("typeof(), expects exactly one argument!");
        executionFinished = 1;
        return;
    }
    avm_memcell* arg = avm_getactual(0);
    avm_memcellclear(&retval);
    switch (arg->type) {
        case number_m:
            cout << "number" << endl;
            retval.data.numVal = arg->data.numVal;
            break;
        case string_m:
            cout << "string" << endl;
            retval.data.strVal = strdup(arg->data.strVal);
            break;
        case bool_m:
            cout << "bool" << endl;
            retval.data.boolVal = arg->data.boolVal;
            break;
        case table_m:
            cout << "table" << endl;
            retval.data.tableVal = arg->data.tableVal;
            break;
        case userfunc_m:
            cout << "userfunc" << endl;
            retval.data.funcVal = arg->data.funcVal;
            break;
        case libfunc_m:
            cout << "libfunc" << endl;
            retval.data.libFuncVal = arg->data.libFuncVal;
            break;
        case nil_m:
            cout << "nil" << endl;
            break;
        default:
            avm_error("Invalid type in typeof()");
            executionFinished = 1;
            return;
    }
    retval.type = arg->type;
}

void libfunc_totalarguments(void){
    unsigned p_topsp = avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
    avm_memcellclear(&retval);
    if (!p_topsp) {
        avm_error("totalarguments() called outside of a function call!");
        retval.type = nil_m;
        executionFinished = 1;
        return;
    }
    retval.type = number_m;
    retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    cout << "Total arguments: " << retval.data.numVal << endl;
    
}

void libfunc_argument(void) {
    unsigned n = avm_totalactuals();
    if (n != 1) {
        avm_error("argument() expects exactly one argument!");
        cout << "argument() expects exactly one argument!" << endl;
        executionFinished = 1;
        retval.type = nil_m;
        return;
    }
    avm_memcell* arg0 = avm_getactual(0);
    if (arg0->type != number_m || arg0->data.numVal < 0 || arg0->data.numVal != floor(arg0->data.numVal)) {
        avm_error("argument() expects an integer index as argument!");
        cout << "argument() expects an integer index as argument!" << endl;
        executionFinished = 1;
        retval.type = nil_m;
        return;
    }
    unsigned i = (unsigned)arg0->data.numVal;

    unsigned p_topsp = avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
    avm_memcellclear(&retval);
    if (!p_topsp) {
        retval.type = nil_m;
        return;
    }
    unsigned total_args = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
    if (i >= total_args) {
        retval.type = nil_m;
        return;
    }
    avm_memcell* arg = &stack[p_topsp + AVM_STACKENV_SIZE + 1 + i];
    avm_assign(&retval, arg);
}

void libfunc_objecttotalmembers(void){
    return;
}
void libfunc_sqrt(void){
    return;
}
void libfunc_cos(void){
    return;
}
void libfunc_sin(void){
    return;
}
void libfunc_strtonum(void){
    return;
}
void libfunc_objectcopy(void){
    return;
}
void libfunc_objectmemberkeys(void){
    return;
}

library_func_t avm_getlibraryfunc(char* id) {
    if (strcmp(id, "print") == 0) return libfunc_print;
    if (strcmp(id, "input") == 0) return libfunc_input;
    if (strcmp(id, "typeof") == 0) return libfunc_typeof;
    if (strcmp(id, "totalarguments") == 0) return libfunc_totalarguments;
    if (strcmp(id, "argument") == 0) return libfunc_argument;
    if (strcmp(id, "objecttotalmembers") == 0) return libfunc_objecttotalmembers;
    if (strcmp(id, "sqrt") == 0) return libfunc_sqrt;
    if (strcmp(id, "cos") == 0) return libfunc_cos;
    if (strcmp(id, "sin") == 0) return libfunc_sin;
    if (strcmp(id, "strtonum") == 0) return libfunc_strtonum;
    if (strcmp(id, "objectcopy") == 0) return libfunc_objectcopy;
    if (strcmp(id, "objectmemberkeys") == 0) return libfunc_objectmemberkeys;
    return nullptr;
}

void cleanup_libfuncs() {
    LibFuncsHashTable* current = LibHashTable;
    while (current) {
        LibFuncsHashTable* next = current->next;
        free(current->id);
        delete current;
        current = next;
    }
    LibHashTable = nullptr;
}

unsigned char avm_tobool(avm_memcell* m) {
    if (!m) {
        avm_error("Null memcell in avm_tobool");
        executionFinished = 1;
        return 0;
    }
    
    if (m->type < 0 || m->type >= undef_m) {
        char error_msg[100];
        sprintf(error_msg, "Invalid memcell type in avm_tobool: %d", m->type);
        avm_error(error_msg);
        executionFinished = 1;
        return 0;
    }
    
    return (*toboolFuncs[m->type])(m);
}

void patch_incomplete_jumps() {
    incomplete_jump* x = ij_head;
    while (x) {
        if (x->iaddress == quads.size()) {
            instructions[x->instrNo]->result->val = instructions.size();
        } else {
            instructions[x->instrNo]->result->val = quads[x->iaddress]->taddress;
        }
        x = x->next;
    }
}


void add_incomple_jump(unsigned instrNo, unsigned iaddress) {
    incomplete_jump* new_jump = new incomplete_jump;
    new_jump->instrNo = instrNo;
    new_jump->iaddress = iaddress;
    new_jump->next = ij_head;
    ij_head = new_jump;
    ++ij_total;
}