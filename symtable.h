#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;


struct Symbol{
    string name;
    int scope;
    int line;
    Symbol(string name, int scope, int line) 
        : name(name), scope(scope), line(line) {}
};

const string func_Names[] = {
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

class SymbolTable {
    private: 
        unordered_map<string, Symbol> table;

    public: 
        void insertSymbol(string name, int scope, int line){
            table[name] = Symbol(name, scope, line);
        }
        bool lookupSymbol(string name){
            return table.find(name) != table.end();
        }
        void shadow();
};
