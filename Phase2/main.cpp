#include "syntax.hpp"
#include "al.hpp"
#include <stdlib.h>
#include <iostream>
#include "lexLib.hpp"
#include "symtable.h"
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
    return 0;
}
