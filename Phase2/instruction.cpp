#include "instruction.h"

vector <double> numConsts;
vector <string*> stringConsts;
vector <string*> libDefFuncs;
vector <string*> userFuncs;
vector <bool> boolConst;
vector <instruction*> instructions;
std::set<std::string> usedLibFunctions;

extern FILE*       instructions_out;
extern FILE*       binary;

int instrStep = 1;
int magic_num = 0;
int totalNums = 0;


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
    instruction* t;
    
    // First instruction: if arg1 == false jump to "result = true" instruction
    t = new instruction;
    t->opcode = jeq_v;
    t->arg1 = new vmarg;
    make_operand(q->arg1, t->arg1);
    t->arg2 = new vmarg;
    t->arg2->type = bool_a;
    t->arg2->val = consts_newbool(false);
    t->result = new vmarg;
    t->result->type = label_a;
    t->result->val = nextquad() + 3;  // Jump to "true" assignment if arg1 is false
    emit_instr(t);
    
    // Second instruction: result = false (when arg1 is true)
    t = new instruction;
    t->opcode = assign_v;
    t->arg1 = new vmarg;
    t->arg1->type = bool_a;
    t->arg1->val = consts_newbool(false);
    t->arg2 = nullptr;  // reset_operand
    t->result = new vmarg;
    make_operand(q->result, t->result);
    emit_instr(t);
    
    // Third instruction: jump over "result = true" to end
    t = new instruction;
    t->opcode = jump_v;
    t->arg1 = nullptr;  // reset_operand
    t->arg2 = nullptr;  // reset_operand
    t->result = new vmarg;
    t->result->type = label_a;
    t->result->val = nextquad() + 2;
    emit_instr(t);
    
    // Fourth instruction: result = true (when arg1 is false)
    t = new instruction;
    t->opcode = assign_v;
    t->arg1 = new vmarg;
    t->arg1->type = bool_a;
    t->arg1->val = consts_newbool(true);
    t->arg2 = nullptr;  // reset_operand
    t->result = new vmarg;
    make_operand(q->result, t->result);
    emit_instr(t);
}

void generate_AND(quad *q){
    instruction* t;
    // First instruction: if arg1 == false jump to false-assignment
    t = new instruction;
    t->opcode = jeq_v;
    t->arg1 = new vmarg;
    make_operand(q->arg1, t->arg1);
    t->arg2 = new vmarg;
    t->arg2->type = bool_a;
    t->arg2->val = consts_newbool(false);
    t->result = new vmarg;
    t->result->type = label_a;
    t->result->val = nextquad() + 4;  // Jump to false-assignment if arg1 is false
    emit_instr(t);
    
    // Second instruction: if arg2 == false jump to false-assignment
    t = new instruction;
    t->opcode = jeq_v;
    t->arg1 = new vmarg;
    make_operand(q->arg2, t->arg1);
    t->arg2 = new vmarg;
    t->arg2->type = bool_a;
    t->arg2->val = consts_newbool(false);
    t->result = new vmarg;
    t->result->type = label_a;
    t->result->val = nextquad() + 3;  // Jump to false-assignment if arg2 is false
    emit_instr(t);
    
    // Third instruction: result = true (when both arg1 and arg2 are true)
    t = new instruction;
    t->opcode = assign_v;
    t->arg1 = new vmarg;
    t->arg1->type = bool_a;
    t->arg1->val = consts_newbool(true);
    t->arg2 = nullptr;  // reset_operand
    t->result = new vmarg;
    make_operand(q->result, t->result);
    emit_instr(t);
    
    // Fourth instruction: jump over false-assignment to end
    t = new instruction;
    t->opcode = jump_v;
    t->arg1 = nullptr;  // reset_operand
    t->arg2 = nullptr;  // reset_operand
    t->result = new vmarg;
    t->result->type = label_a;
    t->result->val = nextquad() + 2;
    emit_instr(t);
    
    // Fifth instruction: result = false (when either arg1 or arg2 is false)
    t = new instruction;
    t->opcode = assign_v;
    t->arg1 = new vmarg;
    t->arg1->type = bool_a;
    t->arg1->val = consts_newbool(false);
    t->arg2 = nullptr;
    t->result = new vmarg;
    make_operand(q->result, t->result);
    emit_instr(t);
    return;
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

void generate_OR(quad *q){
    instruction* t;
    
    // First instruction: if arg1 == true jump to true-assignment
    t = new instruction;
    t->opcode = jeq_v;
    t->arg1 = new vmarg;
    make_operand(q->arg1, t->arg1);
    t->arg2 = new vmarg;
    t->arg2->type = bool_a;
    t->arg2->val = consts_newbool(true);
    t->result = new vmarg;
    t->result->type = label_a;
    t->result->val = nextquad() + 4;  // Jump to true-assignment if arg1 is true
    emit_instr(t);
    
    // Second instruction: if arg2 == true jump to true-assignment
    t = new instruction;
    t->opcode = jeq_v;
    t->arg1 = new vmarg;
    make_operand(q->arg2, t->arg1);
    t->arg2 = new vmarg;
    t->arg2->type = bool_a;
    t->arg2->val = consts_newbool(true);
    t->result = new vmarg;
    t->result->type = label_a;
    t->result->val = nextquad() + 3;  // Jump to true-assignment if arg2 is true
    emit_instr(t);
    
    // Third instruction: result = false (when both arg1 and arg2 are false)
    t = new instruction;
    t->opcode = assign_v;
    t->arg1 = new vmarg;
    t->arg1->type = bool_a;
    t->arg1->val = consts_newbool(false);
    t->arg2 = nullptr;  // reset_operand
    t->result = new vmarg;
    make_operand(q->result, t->result);
    emit_instr(t);
    
    // Fourth instruction: jump over true-assignment to end
    t = new instruction;
    t->opcode = jump_v;
    t->arg1 = nullptr;  // reset_operand
    t->arg2 = nullptr;  // reset_operand
    t->result = new vmarg;
    t->result->type = label_a;
    t->result->val = nextquad() + 2;
    emit_instr(t);
    
    // Fifth instruction: result = true (when either arg1 or arg2 is true)
    t = new instruction;
    t->opcode = assign_v;
    t->arg1 = new vmarg;
    t->arg1->type = bool_a;
    t->arg1->val = consts_newbool(true);
    t->arg2 = nullptr;
    t->result = new vmarg;
    make_operand(q->result, t->result);
    emit_instr(t);
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
    return;
}

void generate_CALL(quad *q){
    if (!q || !q->result || !q->result->sym) {
        cerr << "ERROR: Invalid CALL quad at line " << (q ? q->line : 0) << endl;
        return;
    }

    // Register library calls
    if (q->result->sym->type == LIB_FUNC) {
        usedLibFunctions.insert(q->result->sym->name);
    }
    return;
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

void generate_relational(vmopcode op, quad* q){
    instruction* i = generate_Proc(op,q);
    generate_make_op(i, q);
    i->result = new vmarg;
    i->result->type = label_a;
    i->result->val = q->label;
    //patch incomplete jump
    emit_instr(i);
}

void quad_to_instr(void* void_quad){
    if(void_quad == nullptr){
        return;
    }
    quad *q = (quad*) void_quad;
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