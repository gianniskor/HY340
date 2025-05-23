#include "syntax.hpp"
#include "al.hpp"
#include <stdlib.h>
#include <iostream>
#include "lexLib.hpp"
#include "headerLib.h"
#include <fstream>
// extern "C++" int yylex() {
//     static alpha_token_t token;
//     return alpha_yylex(&token);
// }

// // Error handler
// void yyerror(const char* msg) {
//     fprintf(stderr, "Error: %s\n", msg);
// }

// extern int alpha_yylex(alpha_token_t* yylval);
// // Definitions (not just declarations)
// FILE* yyin = nullptr;
// alpha_token_t* token = nullptr;
extern int yyparse();
SymbolTable symbolTable;
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
        // No extension or dot is part of directory name
        test_name = input_file.substr(last_slash_pos);
    } else {
        test_name = input_file.substr(last_slash_pos, dot_pos - last_slash_pos);
    }

    // bool success = true; 
    // if (success) {
        print_quads(test_name); 
    // }

    return 0;
}
