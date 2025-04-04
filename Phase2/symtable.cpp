#include "symtable.h"
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unordered_map>


using namespace std;



SymbolTable::SymbolTable() {
    scope = 0;
}

SymbolTable::~SymbolTable() {
}



int SymbolTable::getScope() const {
    return scope;
}

Symbol* SymbolTable::insertSymbol(string name, int symbolScope, int line, int type) {
    string key = name + "_" + to_string(scope);
    Symbol newSymbol(name, scope, line, type);

    auto result = scopeTable.insert({key, newSymbol});
    if (!result.second) {
        cout << "Warning: Symbol '" << name << "' already exists in this scope " << scope << endl;
    }

    nameTable[name].push_back(key);
    table[name]= newSymbol;
    return &(result.first->second);
}


Symbol* SymbolTable::lookupInScope(const string& name, int targetScope) {
    string key = name + "_" + to_string(targetScope);
    
    auto it = scopeTable.find(key);
    if (it != scopeTable.end() && it->second.isActive) {
        return &(it->second);
    }
    
    return nullptr;
}

Symbol* SymbolTable::lookupFunction(const string& name, int targetScope) {
    Symbol* sym = lookupInScope(name, targetScope);
    if (sym && (sym->type == 3 || sym->type == 4)) {
            return sym;
    }
    return nullptr;
}

Symbol* SymbolTable::lookupExtra(const string& name, bool isGlobal) {
    if (isGlobal) {
        return lookupInScope(name, 0);
    }

    Symbol* res= lookupInScope(name, scope);
    if (res) return res;

    for (int i = scope - 1; i >= 0; i--) {
        Symbol* func= lookupFunction(name, i);
        if (func) return func;
    }

    return lookupInScope(name, 0);
}

bool SymbolTable::lookup(string name) {
    return lookupExtra(name, false) != nullptr;
}

vector<Symbol*> SymbolTable::getAllSymbolsWithName(const string& name) {
    vector<Symbol*> result;
    
    auto it = nameTable.find(name);
    if (it != nameTable.end()) {
        for (const string& key : it->second) {
            auto symIt = scopeTable.find(key);
            if (symIt != scopeTable.end() && symIt->second.isActive) {
                result.push_back(&(symIt->second));
            }
        }
    }
    
    return result;
}

void SymbolTable::shadow() {
    for (auto& pair : scopeTable) {
        if (pair.second.scope == scope) {
            pair.second.isActive = false;
        }
    }
}

