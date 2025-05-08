#ifndef __SYM__
#define __SYM__

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

typedef enum SymbolType {
    GLOBAL_VAR, LOCAL_VAR, FUNCTION_PARAM, USER_FUNC, LIB_FUNC
}SymbolType;


class Symbol{
    
    public:
        string name;
        int scope;
        int line;
        SymbolType type;
        bool active;
        string value;
        Symbol():
            name(""), scope(0), line(0), type(), active(true), value("") {}
        Symbol(string name, int scope, int line, SymbolType type, string value) 
            :name(name), scope(scope), line(line), type(type), active(true), value(value) {}
        int getScope() const{
            return scope;
        }
        int getLine() const{
            return line;
        }
        int getType() const{
            return type;
        }
        string getName() const{
            return name;
        }
        bool isActive() const{
            return active;
        }
        void setActive(bool active){
            active = active;
        }
        string getValue() const{
            return value;
        }
        void setValue(string value){
            this->value = value;
        }
        string getTypeAsString() const{
            switch(type){
                case GLOBAL_VAR: return "GLOBAL_VAR";
                case LOCAL_VAR: return "LOCAL_VAR";
                case FUNCTION_PARAM: return "FUNCTION_PARAM";
                case USER_FUNC: return "USER_FUNC";
                case LIB_FUNC: return "LIB_FUNC";
                default: return "UNKNOWN";
            }
        }
        void print() const {
            printf("%-20s [%s] (line: %d) (scope: %d) %s\n", 
                   name.c_str(), 
                   getTypeAsString().c_str(), 
                   line, 
                   scope, 
                   active ? "(active)" : "(inactive)");
        }
};

class SymbolTable{
    private:

        vector<vector <Symbol*>> scopeTable;
        unordered_map<string, vector<Symbol*>> nameTable;

    public:
    
    int currentScope;
    SymbolTable() : currentScope(0) {
        scopeTable.push_back(vector<Symbol*>());
        scopeTable.push_back(vector<Symbol*>());
    }
    ~SymbolTable() {
        for (auto& scope : scopeTable) {
            for (auto& symbol : scope) {
                delete symbol;
            }
        }
    }

    Symbol* insert(string name, int scope, int line, SymbolType type, string value = "") {
        // Check if we need to add new scope levels
        while (scopeTable.size() <= scope) {
            scopeTable.push_back(vector<Symbol*>());
        }
        
        // Check if it's a library function
        if (type == LIB_FUNC) {
            // Can't redefine library functions
            auto symbols = lookup(name);
            for (auto& sym : symbols) {
                if (sym->getType() == LIB_FUNC) {
                    return sym; // Already exists
                }
            }
        }
        
        // Check if symbol exists in the same scope
        Symbol* existingSymbol = lookupInScope(name, scope);
        if (existingSymbol != nullptr && existingSymbol->isActive()) {
            // Cannot redefine a symbol in the same scope
            return nullptr;
        }
        
        // Check if it's a library function name (prevent shadowing)
        if (type != LIB_FUNC) {
            auto symbols = lookup(name);
            for (auto& sym : symbols) {
                if (sym->getType() == LIB_FUNC) {
                    // Cannot shadow library functions
                    return nullptr;
                }
            }
        }
        
        // Create and add the new symbol
        Symbol* newSymbol = new Symbol(name, scope, line, type, value);
        scopeTable[scope].push_back(newSymbol);
        
        // Add to name table
        if (nameTable.find(name) == nameTable.end()) {
            nameTable[name] = vector<Symbol*>();
        }
        nameTable[name].push_back(newSymbol);
        
        return newSymbol;
    }
    
    // Lookup a symbol by name (returns all matching symbols)
    vector<Symbol*> lookup(const string& name) {
        if (nameTable.find(name) != nameTable.end()) {
            return nameTable[name];
        }
        return vector<Symbol*>();
    }
    
    // Lookup active symbol in specific scope
    Symbol* lookupInScope(const string& name, int targetScope) {
        if (targetScope >= scopeTable.size()) {
            return nullptr;
        }
        for (auto* symbol : scopeTable[targetScope]) {
            if (symbol->getName() == name && symbol->isActive()) {
                return symbol;
            }
        }
        return nullptr;
    }
    
    // Lookup any symbol (active or not) in specific scope
    Symbol* lookupAnyInScope(const string& name, int targetScope) {
        if (targetScope >= scopeTable.size()) {
            return nullptr;
        }
        
        for (auto* symbol : scopeTable[targetScope]) {
            if (symbol->getName() == name) {
                return symbol;
            }
        }
        return nullptr;
    }
    

    Symbol* lookupActiveBottomUp(const string& name, int fromScope) {
        for (int scope = fromScope; scope >= 0; scope--) {
            Symbol* result = lookupInScope(name, scope);
            if (result != nullptr) {
                return result;
            }
        }
        return nullptr;
    }
    
    // Enter a new scope
    void enterScope() {
        currentScope++;
        if (currentScope >= scopeTable.size()) {
            scopeTable.push_back(vector<Symbol*>());
        }
    }
    
    // Exit the current scope (mark symbols as inactive)
    void exitScope() {
        if (currentScope > 0) {
            for (auto* symbol : scopeTable[currentScope]) {
                symbol->setActive(false);
            }
            currentScope--;
        }
    }

    int getCurrentScope() const {
        return currentScope;
    }
    
    // Hide all symbols in a scope (mark as inactive)
    void hideScope(int scope) {
        if (scope < scopeTable.size()) {
            for (auto* symbol : scopeTable[scope]) {
                symbol->setActive(false);
            }
        }
    }

    void print() {
        printf("\n--------------------- Symbol Table ---------------------\n");
        printf("%-20s %-15s %-10s %-10s %s\n", "Name", "Type", "Line", "Scope", "Status");
        printf("--------------------------------------------------------\n");
        
        // First print library functions (scope 0)
        for (auto* symbol : scopeTable[0]) {
            if (symbol->getType() == LIB_FUNC) {
                symbol->print();
            }
        }
        
        // Then print user symbols by ascending scope
        for (size_t scope = 0; scope < scopeTable.size(); scope++) {
            for (auto* symbol : scopeTable[scope]) {
                if (symbol->getType() != LIB_FUNC) {
                    symbol->print();
                }
            }
        }
        printf("--------------------------------------------------------\n");
    }

    void local_lvalue(string name,int scope,int line, SymbolType type, string value =""){
        
        Symbol *e = lookupInScope(name,scope);
        
        if(e == NULL){
            auto symbols = lookup(name);
            for (auto& sym : symbols) {
            if (sym->getType() == LIB_FUNC) {
                    //shadow libfunc
                    return;
                }
            }
            Symbol* newS;
            if(scope == 0){
                newS = new Symbol(name,scope,line,GLOBAL_VAR,value);
            }else{
                newS = new Symbol(name,scope,line,LOCAL_VAR,value);
            }
            scopeTable[scope].push_back(newS);
            if (nameTable.find(name) == nameTable.end()) {
                nameTable[name] = vector<Symbol*>();
            }
            nameTable[name].push_back(newS);
        } else {
            if (e->getType() == LIB_FUNC) {
                printf("Error: Cannot redefine library function %s\n", name.c_str());
                return;
            }
            e->setActive(true);
            e->setValue(value);
        }
    }
    
    void lvalue_default(string name, int scope, int line, SymbolType type, string value = "") {
        Symbol *e = lookupActiveBottomUp(name, scope);
        if(e == nullptr) {
            auto symbols = lookup(name);
            for (auto& sym : symbols) {
                if (sym->getType() == LIB_FUNC) {
                    printf("Error: Cannot shadow library function %s at line %d\n", name.c_str(), line);
                    return;
                }
            }
            Symbol* newSymbol;
            if(scope == 0){
                newSymbol = insert(name, scope, line, GLOBAL_VAR, value);
            } else{
                newSymbol = insert(name, scope, line, LOCAL_VAR, value);
            }
            if(newSymbol == nullptr) {
                printf("Error: Failed to create global variable %s at line %d\n", name.c_str(), line);
            }
        } else {
            if (e->getType() == USER_FUNC || e->getType() == LIB_FUNC) {
                printf("Error: Cannot use function %s as an lvalue at line %d\n", name.c_str(), line);
                return;
            }
            if(!value.empty()) {
                e->setValue(value);
            }
        }
    }
};
#endif