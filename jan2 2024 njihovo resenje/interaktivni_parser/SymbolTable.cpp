#include "SymbolTable.hpp"

bool SymbolTable::VariableDefined(const std::string& name) {

    return _vars.find(name) != _vars.end();
}

bool SymbolTable::DefineVariable(const std::string& name, const std::string& val) {

    auto it = _vars.find(name);
    if (it != _vars.end())
        return false;

    _vars[name] = val;

    return true;
}
bool SymbolTable::UpdateVariable(const std::string& name, const std::string& val) {

    auto it = _vars.find(name);
    if (it == _vars.end())
        return false;

    _vars[name] = val;

    return true;
}
std::string SymbolTable::GetVariable(const std::string& name) {

    auto it = _vars.find(name);
    if (it == _vars.end())
        throw std::invalid_argument("variable not defined");

    return it->second;
}

void SymbolTable::show(std::ostream& s) const {
    for (auto it = _vars.cbegin(); it != _vars.cend(); it++) {
        s << (it->first) << " : " << (it->second) << std::endl;
    }
}

std::ostream& operator <<(std::ostream& s, const SymbolTable& st) {

    st.show(s);
    return s;
}