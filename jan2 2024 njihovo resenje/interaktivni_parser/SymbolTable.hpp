#ifndef SYM_TABLE_H
#define SYM_TABLE_H

#include <iostream>
#include <map>
#include <exception>

class SymbolTable {
private:
    std::map<std::string, std::string> _vars;
public:
    SymbolTable() {}

    bool VariableDefined(const std::string& name);
    bool DefineVariable(const std::string& name, const std::string& val);
    bool UpdateVariable(const std::string& name, const std::string& val);
    std::string GetVariable(const std::string& name);

    void show(std::ostream& s) const;
};

std::ostream& operator <<(std::ostream& s, const SymbolTable& st);


#endif

