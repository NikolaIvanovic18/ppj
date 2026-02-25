#include "SyntaxTree.hpp"

extern void yyerror(std::string s);

std::ostream& operator <<(std::ostream& s, const SyntaxTreeNode& stn) {

    stn.Print(s);
    return s;
}

ConstNode::ConstNode(const std::string& s) {
    _value = s;
}

std::string ConstNode::Interpret(SymbolTable& st) const {
    
    return _value.substr(1, _value.size() - 2);
}
void ConstNode::Print(std::ostream& s) const {
    s << "\"" << _value << "\"";
}
SyntaxTreeNode* ConstNode::Clone() const {
    return new ConstNode(*this);
}

IdentifierNode::IdentifierNode(const std::string& s) {
    _name = s;
}

std::string IdentifierNode::Interpret(SymbolTable& st) const {

    if (!st.VariableDefined(_name)) 
        yyerror("Promenljiva nije definisana");

    return st.GetVariable(_name);
}
void IdentifierNode::Print(std::ostream& s) const {
    s << _name;
}
SyntaxTreeNode* IdentifierNode::Clone() const {
    return new IdentifierNode(*this);
}

GroupNode::GroupNode(SyntaxTreeNode* expr) {
    _expr = expr;
}
GroupNode::GroupNode(const GroupNode& gn) {
    _expr = gn._expr->Clone();
}
GroupNode::~GroupNode() {
    delete _expr;
}

std::string GroupNode::Interpret(SymbolTable& st) const {

    return _expr->Interpret(st);
}

void GroupNode::Print(std::ostream& s) const {
    s << "(" << (*_expr) << ")";
}
SyntaxTreeNode* GroupNode::Clone() const {

    return new GroupNode(*this);    
}

ReverseNode::ReverseNode(SyntaxTreeNode* expr) {
    _expr = expr;
}
ReverseNode::ReverseNode(const ReverseNode& gn) {
    _expr = gn._expr->Clone();
}
ReverseNode::~ReverseNode() {
    delete _expr;
}

std::string ReverseNode::Interpret(SymbolTable& st) const {
    std::string result = _expr->Interpret(st);
    std::reverse(result.begin(), result.end());
    return result;
}
void ReverseNode::Print(std::ostream& s) const {
    s << "!" << (*_expr);
}
SyntaxTreeNode* ReverseNode::Clone() const {
    return new ReverseNode(*this);
}

BinaryNode::BinaryNode(const std::string& sym, SyntaxTreeNode* l, SyntaxTreeNode* r) {
    _symbol = sym;
    _left = l;
    _right = r;
}
BinaryNode::BinaryNode(const BinaryNode& gn) {
    _symbol = gn._symbol;
    _left = gn._left->Clone();
    _right = gn._right->Clone();
}
BinaryNode::~BinaryNode() {
    delete _left;
    delete _right;
}

std::string BinaryNode::Interpret(SymbolTable& st) const {
    std::string s1 = _left->Interpret(st);
    std::string s2 = _right->Interpret(st);

    if (_symbol == "+") {
        return s1 + s2;
    }
    else if (_symbol == "*") {
        int i = 0;
        for (i = 0; i < std::min(s1.size(), s2.size()); i++) {
            if (s1[i] != s2[i]) {
                break;
            }
        }

        return i == 0 ? "" : s1.substr(0, i);
    }
    else if (_symbol == "==") {
        return s1 == s2 ? "1" : "0";
    }
    else if (_symbol == "!=") {
        return s1 != s2 ? "1" : "0";
    }
    else {
        yyerror("nepoznat operator");
    }

    return "0";
}
void BinaryNode::Print(std::ostream& s) const {
    s << (*_left) << " " << _symbol << " " << (*_right);
}
SyntaxTreeNode* BinaryNode::Clone() const {
    return new BinaryNode(*this);
}

IfNoElseNode::IfNoElseNode(SyntaxTreeNode* c, SyntaxTreeNode* e) {
    _cond = c;
    _expr = e;
}
IfNoElseNode::IfNoElseNode(const IfNoElseNode& gn) {
    _cond = gn._cond->Clone();
    _expr = gn._expr->Clone();
}
IfNoElseNode::~IfNoElseNode() {
    delete _cond;
    delete _expr;
}

std::string IfNoElseNode::Interpret(SymbolTable& st) const {
    std::string c = _cond->Interpret(st);
    if (c == "1") {
        return _expr->Interpret(st);
    }

    return "0";
}
void IfNoElseNode::Print(std::ostream& s) const {
    s << "if ( " << (*_cond) << " ) {" << std::endl;
    s << (*_expr) << std::endl;
    s << "};" << std::endl;
}
SyntaxTreeNode* IfNoElseNode::Clone() const {
    return new IfNoElseNode(*this);
}

IfElseNode::IfElseNode(SyntaxTreeNode* c, SyntaxTreeNode* e1, SyntaxTreeNode* e2) {
    _cond = c;
    _if_expr = e1;
    _else_expr = e2;
}
IfElseNode::IfElseNode(const IfElseNode& gn) {
    _cond = gn._cond->Clone();
    _if_expr = gn._if_expr->Clone();
    _else_expr = gn._else_expr->Clone();
}
IfElseNode::~IfElseNode() {
    delete _cond;
    delete _if_expr;
    delete _else_expr;
}

std::string IfElseNode::Interpret(SymbolTable& st) const {
    std::string c = _cond->Interpret(st);
    if (c == "1") {
        return _if_expr->Interpret(st);
    }
    else {
        return _else_expr->Interpret(st);
    }
}
void IfElseNode::Print(std::ostream& s) const {
    s << "if ( " << (*_cond) << " ) {" << std::endl;
    s << (*_if_expr) << std::endl;
    s << "}" << std::endl;
    s << "else {" << std::endl;
    s << (*_else_expr) << std::endl;
    s << "}" << std::endl;
}
SyntaxTreeNode* IfElseNode::Clone() const {
    return new IfElseNode(*this);
}

AssignmentNode::AssignmentNode(const std::string& n, SyntaxTreeNode* val) {
    _name = n;
    _expr = val;
}
AssignmentNode::AssignmentNode(const AssignmentNode& gn) {
    _name = gn._name;
    _expr = gn._expr->Clone();
}
AssignmentNode::~AssignmentNode() {
    delete _expr;
}

std::string AssignmentNode::Interpret(SymbolTable& st) const {
    if (!st.VariableDefined(_name))
        yyerror("Promenljiva nije definisana");

    std::string result = _expr->Interpret(st);
    st.UpdateVariable(_name, result);
    return result;
}
void AssignmentNode::Print(std::ostream& s) const {
    s << _name << " = " << (*_expr) << ";";
}
SyntaxTreeNode* AssignmentNode::Clone() const {
    return new AssignmentNode(*this);
}

DeclarationNode::DeclarationNode(const std::string& n) {
    _name = n;
}

std::string DeclarationNode::Interpret(SymbolTable& st) const {
    if (st.VariableDefined(_name))
        yyerror("Promenljiva vec definisana");
    
    st.DefineVariable(_name, "");
    return "";
}
void DeclarationNode::Print(std::ostream& s) const {
    s << "string " << _name << ";";
}
SyntaxTreeNode* DeclarationNode::Clone() const {
    return new DeclarationNode(*this);
}

DefinitionNode::DefinitionNode(const std::string& n, SyntaxTreeNode* val) {
    _name = n;
    _expr = val;
}
DefinitionNode::DefinitionNode(const DefinitionNode& gn) {
    _name = gn._name;
    _expr = gn._expr->Clone();
}
DefinitionNode::~DefinitionNode() {
    delete _expr;
}

std::string DefinitionNode::Interpret(SymbolTable& st) const {
    if (st.VariableDefined(_name))
        yyerror("Promenljiva vec definisana");

    std::string result = _expr->Interpret(st);
    st.DefineVariable(_name, result);
    return result;
}
void DefinitionNode::Print(std::ostream& s) const {

    s << "string " << _name << " = " << (*_expr) << ";";
}
SyntaxTreeNode* DefinitionNode::Clone() const {
    return new DefinitionNode(*this);
}

std::string PrintAllNode::Interpret(SymbolTable& st) const {
    std::cout << st << std::endl;
    return "0";
}
void PrintAllNode::Print(std::ostream& s) const { 

    s << "print_ALL;";
}
SyntaxTreeNode* PrintAllNode::Clone() const {
    return new PrintAllNode(*this);
}

OutputNode::OutputNode(const std::string& dest, SyntaxTreeNode* e) {
    _dest = dest;
    _expr = e;
}
OutputNode::OutputNode(const OutputNode& gn) {
    _dest = gn._dest;
    _expr = gn._expr->Clone();
}
OutputNode::~OutputNode() {
    delete _expr;
}

std::string OutputNode::Interpret(SymbolTable& st) const {
    if (_dest == "out") {
        std::cout << _expr->Interpret(st) << std::endl;
    }
    else if (_dest == "err") {
        std::cerr << _expr->Interpret(st) << std::endl;
    }
    else {
        yyerror("Nepoznat izlaz");
    }
    return "0";
}
void OutputNode::Print(std::ostream& s) const {
    if (_dest == "out") {
        s << "std_output << " << (*_expr) << ";";
    }
    else if (_dest == "err") {
        s << "std_error << " << (*_expr) << ";";
    }
    else {
        yyerror("Nepoznat izlaz");
    }
}
SyntaxTreeNode* OutputNode::Clone() const {
    return new OutputNode(*this);
}

InputNode::InputNode(const std::string& name) {
    _name = name;
}

std::string InputNode::Interpret(SymbolTable& st) const {
    if (!st.VariableDefined(_name))
        yyerror("Promenljiva nije definisana");
    
    std::string s;
    std::cin >> s;
    st.UpdateVariable(_name, s);
    return s;
}
void InputNode::Print(std::ostream& s) const {
    s << "std_input >> " << _name << ";";
}
SyntaxTreeNode* InputNode::Clone() const {
    return new InputNode(*this);
}

SequenceNode::SequenceNode(const SequenceNode& sn) {
    for (int i = 0; i < sn._stmts.size(); i++) {
        _stmts.push_back(sn._stmts[i]->Clone());
    }
}
SequenceNode::~SequenceNode() {
    for (int i = 0; i < _stmts.size(); i++) {
        delete _stmts[i];
    }
}

void SequenceNode::Add(SyntaxTreeNode* stmt) {
    _stmts.push_back(stmt);
}

std::string SequenceNode::Interpret(SymbolTable& st) const {
    for (int i = 0; i < _stmts.size(); i++) {
        _stmts[i]->Interpret(st);
    }
    return "0";
}
void SequenceNode::Print(std::ostream& s) const {
    for (int i = 0; i < _stmts.size(); i++) {
        s << (*(_stmts[i])) << std::endl;
    }
}
SyntaxTreeNode* SequenceNode::Clone() const {
    return new SequenceNode(*this);
}