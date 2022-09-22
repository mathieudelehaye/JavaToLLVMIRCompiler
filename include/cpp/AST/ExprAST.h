#pragma once

#include "AST.h"

// Base class for all expression nodes
class ExprAST 
{
public:
  virtual ~ExprAST() = default;
  virtual llvm::Value *codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements) = 0;
};

// Expression class for numeric literals: e.g. 1.0
class NumberExprAST : public ExprAST 
{
  double val;

public:
  NumberExprAST(double _val) : val(_val) {}

  llvm::Value *codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements) override;

  double getVal() const;
};

// Expression class for string literals: e.g. "a string\n"
class StringExprAST : public ExprAST 
{
  std::string val;

public:
  StringExprAST(const std::string& _val) : val(_val) {}

  llvm::Value *codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements) override;

  std::string getVal() const;
};

// Expression class for referencing an identifier
class IdentifierExprAST : public ExprAST 
{
  std::string name;

public:
  IdentifierExprAST(const std::string &_name) : name(_name) {}

  llvm::Value *codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements) override;

  std::string getName();
};

// Expression class for a binary operator
class BinaryExprAST : public ExprAST 
{
  char op;
  std::unique_ptr<ExprAST> lhs, rhs;

public:
  BinaryExprAST(char _op, std::unique_ptr<ExprAST> _lhs,
    std::unique_ptr<ExprAST> _rhs)
    : op(_op), lhs(std::move(_lhs)), rhs(std::move(_rhs)) {}

  llvm::Value *codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements) override;

  std::string getText();
};

// Expression class for function calls
class CallExprAST : public ExprAST 
{
  std::string callee;
  std::vector<std::unique_ptr<ExprAST>> args;

public:
  CallExprAST(const std::string &_callee,
    std::vector<std::unique_ptr<ExprAST>>& _args): 
    callee(_callee), 
    args(std::move(_args)) {}

  llvm::Value *codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements) override;

  std::string getText();
};
