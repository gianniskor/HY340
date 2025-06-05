#include "syntax.hpp"
#include "al.hpp"
#include <stdlib.h>
#include <iostream>
#include "lexLib.hpp"
#include "instruction.h"
#include "headerLib.h"
#include <fstream>

FILE*       instructions_out;
FILE*       binary;

extern int yyparse();

extern int magic_num;

extern int globalOffset;
extern int localOffset;

SymbolTable symbolTable;
vector<int> loopStack;
char libFuncs [][30]={
    "print",
    "input",
    "objectmemberkeys",
    "objecttotalmembers",
    "objectcopy",
    "totalarguments",
    "argument",
    "typeof",
    "strtonum",
    "sqrt",
    "cos",
    "sin"
};

extern void print_quads(const std::string& filename);

int main(int argc, char *argv[]) {
    if (argc > 1)
    {
        if (!(yyin = fopen(argv[1], "r")))
        {
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    }
    for (const char* function : libFuncs) {
        symbolTable.insert(function, 0, 0, LIB_FUNC);
    }
    yyparse();
    symbolTable.print();

    std::string input_file = argv[1]; 
    std::string test_name;

    size_t last_slash_pos = input_file.find_last_of("/\\");
    size_t dot_pos = input_file.find_last_of(".");

    if (last_slash_pos == std::string::npos) {
        last_slash_pos = 0; 
    } else {
        last_slash_pos++; 
    }

    if (dot_pos == std::string::npos || dot_pos < last_slash_pos) {
        test_name = input_file.substr(last_slash_pos);
    } else {
        test_name = input_file.substr(last_slash_pos, dot_pos - last_slash_pos);
    }
    print_quads(test_name); 
    string instructions_path = test_name + ".instructions";
    string binary_path = test_name + ".abc";
    instructions_out = fopen(instructions_path.c_str(), "w");
    binary = fopen(binary_path.c_str(), "wb");
    for(int i = 0;i<quads.size();i++){
        quad_to_instr(quads[i]);
    }
    magic_num = 163847504;
    fprintf(instructions_out, "magicnumber: %ld\n", (long int)163847504); fwrite(&magic_num, sizeof(long int), 1, binary);
    fprintf(instructions_out, "*********** NUMCONSTS ***********\n");
    fprintf(instructions_out, "numConsts: %lu\n", numConsts.size());
    int sizee = numConsts.size();
    fwrite(&sizee, sizeof(int), 1, binary);
    for(int i = 0;i<numConsts.size();i++){
        fprintf(instructions_out,"%d: %lf\n",i,numConsts[i]);
        fwrite(&numConsts[i],sizeof(double),1,binary);
    }
    fprintf(instructions_out, "*********** STRING CONSTS ***********\n");
    fprintf(instructions_out, "stringConsts: %zu\n", stringConsts.size());
    int stringCount = stringConsts.size();
    fwrite(&stringCount, sizeof(int), 1, binary);
    for(int i = 0; i < stringConsts.size(); i++){
        fprintf(instructions_out, "%d: %s\n", i, stringConsts[i]->c_str());
        int len = stringConsts[i]->length();
        fwrite(&len, sizeof(int), 1, binary);
        fwrite(stringConsts[i]->c_str(), sizeof(char), len, binary);
    }

    fprintf(instructions_out, "*********** USER FUNCTIONS ***********\n");
    fprintf(instructions_out, "userFuncs: %zu\n", userFuncs.size());
    int userFuncsCount = userFuncs.size();
    fwrite(&userFuncsCount, sizeof(int), 1, binary);
    for(int i = 0; i < userFuncs.size(); i++){
        fprintf(instructions_out, "%d: %s\n", i, userFuncs[i]->c_str());
        int len = userFuncs[i]->length();
        fwrite(&len, sizeof(int), 1, binary);
        fwrite(userFuncs[i]->c_str(), sizeof(char), len, binary);
    }

    fprintf(instructions_out, "*********** LIB FUNCTIONS ***********\n");
    fprintf(instructions_out, "libFuncs: %zu\n", libDefFuncs.size());
    int libFuncsCount = libDefFuncs.size();
    fwrite(&libFuncsCount, sizeof(int), 1, binary);
    for(int i = 0; i < libDefFuncs.size(); i++){
        fprintf(instructions_out, "%d: %s\n", i, libDefFuncs[i]->c_str());
        int len = libDefFuncs[i]->length();
        fwrite(&len, sizeof(int), 1, binary);
        fwrite(libDefFuncs[i]->c_str(), sizeof(char), len, binary);
    }
    fprintf(instructions_out, "*********** BOOL CONSTS ***********\n");
    fprintf(instructions_out, "boolConsts: %zu\n", boolConst.size());
    int boolCount = boolConst.size();
    fwrite(&boolCount, sizeof(int), 1, binary);
    for(int i = 0; i < boolConst.size(); i++){
        fprintf(instructions_out, "%d: %s\n", i, boolConst[i] ? "true" : "false");
        bool tmp_bool = boolConst[i];
        fwrite(&tmp_bool, sizeof(bool), 1, binary);
    }
    fprintf(instructions_out, "*********** CODE ***********\n");
    fprintf(instructions_out, "Instructions: %zu\n", instructions.size());
    int instructionsCount = instructions.size();
    fwrite(&instructionsCount, sizeof(int), 1, binary);
    for(int i = 0; i < instructions.size(); i++){
        print_instruction(instructions[i], i);
        instruction_to_binary(instructions[i]);
    }
    fclose(instructions_out);
    fclose(binary);

    //test
    // unsigned sz;
    // fopen(binary_path.c_str(), "rb");
    // fseek(binary,0L,SEEK_END);
    // sz = ftell(binary);
    // rewind(binary);
    readAbcFile(binary_path.c_str());
    
    // Now you can use the loaded data
    cout << "Loaded " << instructions.size() << " instructions" << endl;
    cout << "Loaded " << numConsts.size() << " number constants" << endl;
    cout << "Loaded " << stringConsts.size() << " string constants" << endl;
    
    return 0;
}
