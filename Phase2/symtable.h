
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;


struct Symbol{
    string name;
    int scope;
    int line;
    int type;
    bool isActive;

    Symbol(const string& name = "", int scope = 0, int line = 0, int type = 0)
        : name(name), scope(scope), line(line), type(type), isActive(true) {}
};

struct Variable{
    string name;
    int scope;
    int line;
    int type;

    Variable() : name(""), scope(0), line(0), type(0) {}

    Variable(string name, int scope, int line, int type)
        : name(name), scope(scope), line(line), type(type) {}
};

struct Function{
    string name;
    int scope;
    int line;
    int type;

    Function() : name(""), scope(0), line(0), type(0) {}

    Function(string name, int scope, int line, int type)
        : name(name), scope(scope), line(line), type(type) {}
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
    unordered_map<string, Symbol> scopeTable;
    unordered_map<string, vector<string>> nameTable;


    int scope;

public:

    SymbolTable();
    ~SymbolTable();
    int getScope() const;
    void insertSymbol(string name, int scope, int line, int type);
    Symbol* lookupInScope(const string& name, int targetScope);
    Symbol* lookupFunction(const string& name, int targetScope);
    Symbol* lookupExtra(const string& name, bool isGlobal);  
    bool lookup(string name);
    vector<Symbol*> getAllSymbolsWithName(const string& name);
    void shadow();
    const unordered_map<string, Symbol>& getTable() const {
        return table;
    }
};