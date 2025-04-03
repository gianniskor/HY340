
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;


struct Symbol{
    string name;
    int scope;
    int line;
    string type;

    Symbol() : name(""), scope(0), line(0), type("") {}

    Symbol(string name, int scope, int line, string type)
        : name(name), scope(scope), line(line), type(type) {}
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
    "strtonum"
    "sqrt",
    "cos",
    "sin"
};

enum class SymbolType {
    GLOBALVAR,
    LOCALVAR,
    FORMALARG,
    USERFUNC,
    LIBFUNC
};

class SymbolTable {
private:
    unordered_map<string, Symbol> table;

public:
    void insertSymbol(string name, int scope, int line, string type){
        table[name] = Symbol(name, scope, line, type);
    }
    bool lookupSymbol(string name){
        return table.find(name) != table.end();
    }
    void shadow();
    const unordered_map<string, Symbol>& getTable() const {
        return table;
    }
};