
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Symbol{
    string name;
    int scope;
    int line;
    int type;
    bool isActive;
    string value;
    public:
    Symbol(string name, int scope, int line, int type, string value) : name(name), scope(scope), line(line), type(type), isActive(true) {
        this->name = name;
        this->scope = scope;
        this->line = line;
        this->type = type;
        this->isActive = true;
        this -> value = value;
    }
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
        return isActive;
    }
    void setActive(bool active){
        isActive = active;
    }
    string getValue() const{
        return value;
    }
    void setValue(string value){
        this->value = value;
    }
};

class SymbolTable{
    int size;
    int scope;
    unordered_map<string, Symbol> scopeTable;
    public:
    bool add(string name, int scope, int line, int type);
    Symbol * lookupInScope(const string& name, int targetScope);
    bool remove(string name, int scope);
};