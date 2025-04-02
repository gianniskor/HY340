#include <iostream>
#include "symtable.h"

using namespace std;

int main() {
    SymbolTable symtable;
    printAll printer;

    for (int i = 0; i < sizeof(func_Names)/sizeof(func_Names[0]); i++) {
        symtable.insertSymbol(func_Names[i], 0, 0, "LIBFUNC");
    }

    printer.print(&symtable, 0);
    return 0;
}

class printAll {
    public :
        void print(SymbolTable *symtable, int maxScope) {
            cout << "---------  Output  -----------" << endl;
            cout << "Max scope: " << maxScope << endl;
            for (int i = 0; i <= maxScope; i++) {
                cout << "--------       Scope #" << i << "       --------" << endl;
                for (const auto& pair : symtable->getTable()) {
                    const Symbol& symbol = pair.second;
                    if (symbol.scope == i) {
                        cout << "'" << symbol.name << "'    ";
                        if (symbol.type == "FORMALARG") {
                            cout << "[formal argument]  ";
                        } else if (symbol.type == "USERFUNC") {
                            cout << "[user function]    ";
                        } else if (symbol.type == "LIBFUNC") {
                            cout << "[library function] ";
                        } else if (symbol.type == "GLOBALVAR") {
                            cout << "[global variable]  ";
                        } else if (symbol.type == "LOCALVAR") {
                            cout << "[local variable]   ";
                        }
                        cout << "(line " << symbol.line << ")   ";
                        cout << "(scope " << symbol.scope << ")" << endl;
                    }
                }
            }
        }
};