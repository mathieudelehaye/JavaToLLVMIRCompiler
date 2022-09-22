#pragma once

#include "AST.h"
#include "ExprAST.h"


// Class which represents the "prototype" for a function, which 
// captures its name, and its argument names (thus implicitly the 
// number of arguments the function takes).
class PrototypeAST 
{
  std::string name;
  std::vector<std::string> args;

public:
  PrototypeAST(const std::string &_name, std::vector<std::string> _args)
    : name(_name), args(std::move(_args)) {}

  llvm::Function *codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements);

  const std::string &getName() const { return name; }
};

// Class which represents a function definition itself.
class FunctionAST 
{
  std::unique_ptr<PrototypeAST> proto;
  std::unique_ptr<ExprAST> body;

public:
  FunctionAST(std::unique_ptr<PrototypeAST>& _proto,
    std::unique_ptr<ExprAST>& _body)
    : proto(std::move(_proto)), body(std::move(_body)) {}

  llvm::Function *codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements);
};