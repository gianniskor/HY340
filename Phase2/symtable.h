#ifndef __SYM__
#define __SYM__

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

extern vector<int> loopStack;

extern int loopCounter;

extern int globalOffset;
extern int localOffset;

typedef enum SymbolType {
    GLOBAL_VAR, LOCAL_VAR, FUNCTION_PARAM, USER_FUNC, LIB_FUNC
}SymbolType;


typedef enum scopespace_t{
    programvar,
    formalarg,
    functionlocal
} scopespace_t;


class Symbol{
    
    private:
        unsigned int Iaddress;
        unsigned int totalLoc;
        int functionscope;
        //int offset = -1;
    public:
        int offset = -1;
        int funcJumpQuad;
        string name;
        int scope;
        //fix scopespace;
        scopespace_t scopespace = programvar;
        int line;
        SymbolType type;
        bool active;
        string value;
        Symbol():
            name(""), scope(0), line(0), type(), active(true), value(""),Iaddress(0), totalLoc(0) ,scopespace(programvar){}
        Symbol(string name, int scope, int line, SymbolType type, string value) 
            :name(name), scope(scope), line(line), type(type), active(true), value(value), Iaddress(0), totalLoc(0),scopespace(programvar) {}
        int getScope() const{
            return scope;
        }
        int getLine() const{
            return line;
        }
        SymbolType getType() const{
            return type;
        }
        string getName() const{
            return name;
        }
        bool isActive() const{
            return active;
        }
        void setActive(bool isActive){
            this->active = isActive;  
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

            void setIaddress(unsigned int address) {
        Iaddress = address;
    }
    unsigned int getIaddress() const {
        return Iaddress;
    }
    void setTotalLoc(unsigned int loc) {
        totalLoc = loc;
    }
    unsigned int getTotalLoc() const {
        return totalLoc;
    }
    int setFuncScope(int scope) {
        this->functionscope = scope;
        return functionscope;
    }
    int getFuncScope() const {
        return functionscope;
    }
    void setOffset(int offset) {
    this->offset = offset;
}

int getOffset() const {
    return this->offset;
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
        while (scopeTable.size() <= scope) {
            scopeTable.push_back(vector<Symbol*>());
        }
        if (type == LIB_FUNC) {
            auto symbols = lookup(name);
            for (auto& sym : symbols) {
                if (sym->getType() == LIB_FUNC) {
                    return sym;
                }
            }
        }
        Symbol* existingSymbol = lookupInScope(name, scope);
        if (existingSymbol != nullptr && existingSymbol->isActive()) {
            return nullptr;
        }
        if (type != LIB_FUNC) {
            auto symbols = lookup(name);
            for (auto& sym : symbols) {
                if (sym->getType() == LIB_FUNC) {
                    return nullptr;
                }
            }
        }
        Symbol* newSymbol = new Symbol(name, scope, line, type, value);
        if (scope == 0) {
            newSymbol->offset = globalOffset++;
            newSymbol->scopespace = programvar;
        } else {
            //ksanades edw ligo
            newSymbol->offset = localOffset++;
            newSymbol->scopespace = programvar;
        }
        scopeTable[scope].push_back(newSymbol);
        if (nameTable.find(name) == nameTable.end()) {
            nameTable[name] = vector<Symbol*>();
        }
        nameTable[name].push_back(newSymbol);
        
        return newSymbol;
    }
    
    vector<Symbol*> lookup(const string& name) {
        if (nameTable.find(name) != nameTable.end()) {
            return nameTable[name];
        }
        return vector<Symbol*>();
    }
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
    
    //lookup any symbol in specific scope
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
    
    void enterScope() {
        // loopStack.push_back(loopCounter);
        // loopCounter = 0;
        currentScope++;
        if (currentScope >= scopeTable.size()) {
            scopeTable.push_back(vector<Symbol*>());
        }
    }
    
    void exitScope() {
        if (currentScope > 0) {
            for (auto* symbol : scopeTable[currentScope]) {
                symbol->setActive(false);
            }
            currentScope--;
        }
        // int i = loopStack.back();
        // loopStack.pop_back();
    }

    int getCurrentScope() const {
        return currentScope;
    }
    
    void hideScope(int scope) {
        if (scope < scopeTable.size()) {
            for (auto* symbol : scopeTable[scope]) {
                symbol->setActive(false);
            }
        }
    }

    
unsigned int getTotalLoc(int functionScope) {
    unsigned int count = 0;
    
    if (functionScope < scopeTable.size()) {
        string functionName = "";
        for (auto* sym : scopeTable[0]) { 
            if (sym->getFuncScope() == functionScope && 
                (sym->getType() == USER_FUNC || sym->getType() == LIB_FUNC)) {
                functionName = sym->getName();
                break;
            }
        }

        for (auto* symbol : scopeTable[functionScope]) {
            if (symbol->isActive() && symbol->getType() == LOCAL_VAR) {
                count++;
                cout << "variables : " << count << " " << symbol->getName() << endl;
            }
        }
    }
    
    return count;
}


    void print() {
        printf("\n--------------------- Symbol Table ---------------------\n");
        printf("%-20s %-15s %-10s %-10s %s\n", "Name", "Type", "Line", "Scope", "Status");
        printf("--------------------------------------------------------\n");
        for (auto* symbol : scopeTable[0]) {
            if (symbol->getType() == LIB_FUNC) {
                symbol->print();
            }
        }
        for (size_t scope = 0; scope < scopeTable.size(); scope++) {
            for (auto* symbol : scopeTable[scope]) {
                if (symbol->getType() != LIB_FUNC) {
                    symbol->print();
                }
            }
        }
        printf("--------------------------------------------------------\n");
    }

    Symbol* local_lvalue(string name,int scope,int line, string value =""){
        
        Symbol *e = lookupInScope(name,scope);
        
        if(e == NULL){
            auto symbols = lookup(name);
            for (auto& sym : symbols) {
            if (sym->getType() == LIB_FUNC) {
                    //shadow libfunc
                    return NULL;
                }
            }
            Symbol* newS;
            if(scope == 0){
                newS = new Symbol(name,scope,line,GLOBAL_VAR,value);
                // newS->offset = globalOffset++;      
                // newS->scopespace = programvar;
            }else{
                newS = new Symbol(name,scope,line,LOCAL_VAR,value);
                // newS->offset = localOffset++;       
                // newS->scopespace = functionlocal;
            }
            scopeTable[scope].push_back(newS);
            if (nameTable.find(name) == nameTable.end()) {
                nameTable[name] = vector<Symbol*>();
            }
            nameTable[name].push_back(newS);
            return newS;
        } else {
            if (e->getType() == LIB_FUNC) {
                printf("Error: Cannot redefine library function %s\n", name.c_str());
                return NULL;
            }
            e->setActive(true);
            e->setValue(value);
            return e;
        }
    }
    
    Symbol* lvalue_default(string name, int scope, int line, string value = "") {
        Symbol *e = lookupActiveBottomUp(name, scope);
        if(e == nullptr) {
            auto symbols = lookup(name);
            for (auto& sym : symbols) {
                if (sym->getType() == LIB_FUNC) {
                    printf("Error: Cannot shadow library function %s at line %d\n", name.c_str(), line);
                    return NULL;
                }
            }
            Symbol* newSymbol;
            if(scope == 0){
                newSymbol = insert(name, scope, line, GLOBAL_VAR, value);
                // if(newSymbol) {
                //     newSymbol->offset = globalOffset++; 
                //     newSymbol->scopespace = programvar; 
                // }
            } else{
                newSymbol = insert(name, scope, line, LOCAL_VAR, value);
                // if(newSymbol) {
                //     newSymbol->offset = localOffset++;     
                //     newSymbol->scopespace = functionlocal; 
                // }
            }
            if(newSymbol == nullptr) {
                printf("Error: Failed to create global variable %s at line %d\n", name.c_str(), line);
            }
            return newSymbol;
        } else {
            // if (e->getType() == USER_FUNC || e->getType() == LIB_FUNC) {
            //     printf("Error: Cannot use function %s as an lvalue at line %d\n", name.c_str(), line);
            //     return NULL;
            // }
            if(!value.empty()) {
                e->setValue(value);
            }
        }
        return e;
    }
    Symbol* rvalue_default(string name, int scope, int line) {
        Symbol *e = lookupActiveBottomUp(name, scope);
        if(e == nullptr) {
            printf("Error: Undeclared identifier %s at line %d\n", name.c_str(), line);
            return NULL;
        }
        return e;
    }
};
#endif