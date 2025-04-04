#include <iostream>
#include "symtable.h"

using namespace std;

extern FILE* yyin;
FILE* yaccout = stdout; 
extern int max_scope;
extern int yyparse();

SymbolTable symtable;

class Operations {
    public :
        void print(SymbolTable *symtable, int max_scope) {
            cout << "---------  Output  -----------" << endl;
            cout << "Max scope: " << max_scope << endl;
            for (int i = 0; i <= max_scope; i++) {
                cout << "--------       Scope #" << i << "       --------" << endl;
                for (const auto& pair : symtable->getTable()) {
                    const Symbol& symbol = pair.second;
                    if (symbol.scope == i) {
                        cout << "'" << symbol.name << "'    ";
                        if (symbol.type == 2) {
                            cout << "[formal argument]  ";
                        } else if (symbol.type == 3) {
                            cout << "[user function]    ";
                        } else if (symbol.type == 4) {
                            cout << "[library function] ";
                        } else if (symbol.type == 0) {
                            cout << "[global variable]  ";
                        } else if (symbol.type == 1) {
                            cout << "[local variable]   ";
                        }
                        cout << "(line " << symbol.line << ") ";
                        cout << "(scope " << symbol.scope << ")" << endl;
                    }
                }
            }
        }        
};


int main(int _argc, char* _argv[]) {
    Operations printer;

    symtable.insertSymbol("print", 0, 0, 4);
    symtable.insertSymbol("input", 0, 0, 4);
    symtable.insertSymbol("objectmemberkeys", 0, 0, 4);
    symtable.insertSymbol("objecttotalmembers", 0, 0, 4);
    symtable.insertSymbol("objectcopy", 0, 0, 4);
    symtable.insertSymbol("totalarguments", 0, 0, 4);
    symtable.insertSymbol("argument", 0, 0, 4);
    symtable.insertSymbol("typeof", 0, 0, 4);
    symtable.insertSymbol("strtonum", 0, 0, 4);
    symtable.insertSymbol("sqrt", 0, 0, 4);
    symtable.insertSymbol("cos", 0, 0, 4);
    symtable.insertSymbol("sin", 0, 0, 4);

    if (_argc > 1) {
        yyin = fopen(_argv[1], "r");
        if (yyin == NULL) {
            cout << "Error: Could not open file " << _argv[1] << endl;
            return 1;
        }
    } else {
        yyin = stdin;
    }

    yyparse();
    
    if (_argc > 1 && yyin != stdin) {
        fclose(yyin);
    }

    cout << "--------------------------------" << endl;

    printer.print(&symtable, max_scope);
    return 0;
}

