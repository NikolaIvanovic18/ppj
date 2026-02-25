#ifndef SYN_TREE_H
#define SYN_TREE_H

#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>

#include "SymbolTable.hpp"

class SyntaxTreeNode {
public:
    virtual ~SyntaxTreeNode() {}

    virtual std::string Interpret(SymbolTable& st) const = 0;
    virtual void Print(std::ostream& s) const = 0;
    virtual SyntaxTreeNode* Clone() const = 0;
};

std::ostream& operator <<(std::ostream& s, const SyntaxTreeNode& stn);

class ConstNode : public SyntaxTreeNode {
private:
    std::string _value;
public:
    ConstNode(const std::string& s);

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class IdentifierNode : public SyntaxTreeNode {
private:
    std::string _name;
public:
    IdentifierNode(const std::string& s);

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class GroupNode : public SyntaxTreeNode {
private:
    SyntaxTreeNode* _expr;
public:
    GroupNode(SyntaxTreeNode* expr);
    GroupNode(const GroupNode& gn);
    ~GroupNode();

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class ReverseNode : public SyntaxTreeNode {
private:
    SyntaxTreeNode* _expr;
public:
    ReverseNode(SyntaxTreeNode* expr);
    ReverseNode(const ReverseNode& gn);
    ~ReverseNode();

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class BinaryNode : public SyntaxTreeNode {
private:
    std::string _symbol;
    SyntaxTreeNode* _left;
    SyntaxTreeNode* _right;
public:
    BinaryNode(const std::string& sym, SyntaxTreeNode* l, SyntaxTreeNode* r);
    BinaryNode(const BinaryNode& gn);
    ~BinaryNode();

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class IfNoElseNode : public SyntaxTreeNode {
private:
    SyntaxTreeNode* _cond;
    SyntaxTreeNode* _expr;
public:
    IfNoElseNode(SyntaxTreeNode* c, SyntaxTreeNode* e);
    IfNoElseNode(const IfNoElseNode& gn);
    ~IfNoElseNode();

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class IfElseNode : public SyntaxTreeNode {
    private:
    SyntaxTreeNode* _cond;
    SyntaxTreeNode* _if_expr;
    SyntaxTreeNode* _else_expr;
public:
    IfElseNode(SyntaxTreeNode* c, SyntaxTreeNode* e1, SyntaxTreeNode* e2);
    IfElseNode(const IfElseNode& gn);
    ~IfElseNode();

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class AssignmentNode : public SyntaxTreeNode {
private:
    std::string _name;
    SyntaxTreeNode* _expr;
public:
    AssignmentNode(const std::string& n, SyntaxTreeNode* val);
    AssignmentNode(const AssignmentNode& gn);
    ~AssignmentNode();

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class DeclarationNode : public SyntaxTreeNode {
private:
    std::string _name;
public:
    DeclarationNode(const std::string& n);

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class DefinitionNode : public SyntaxTreeNode {
private:
    std::string _name;
    SyntaxTreeNode* _expr;
public:
    DefinitionNode(const std::string& n, SyntaxTreeNode* val);
    DefinitionNode(const DefinitionNode& gn);
    ~DefinitionNode();

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class PrintAllNode : public SyntaxTreeNode {
public: 
    PrintAllNode() {}

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class OutputNode : public SyntaxTreeNode {
private:
    std::string _dest;
    SyntaxTreeNode* _expr;
public: 
    OutputNode(const std::string& dest, SyntaxTreeNode* e);
    OutputNode(const OutputNode& gn);
    ~OutputNode();

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class InputNode : public SyntaxTreeNode {
private:
    std::string _name;
public: 
    InputNode(const std::string& name);

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

class SequenceNode : public SyntaxTreeNode {
private:
    std::vector<SyntaxTreeNode*> _stmts;
public:
    SequenceNode() {}
    SequenceNode(const SequenceNode& sn);
    ~SequenceNode();

    void Add(SyntaxTreeNode* stmt);

    virtual std::string Interpret(SymbolTable& st) const;
    virtual void Print(std::ostream& s) const;
    virtual SyntaxTreeNode* Clone() const;
};

#endif
