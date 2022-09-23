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
    std::vector<llvm::Value *>& decl);

  const std::string &getName() const { return name; }
};

// Class which represents a function definition itself.
class FunctionAST 
{
  std::unique_ptr<PrototypeAST> proto;

  // Function statements not providing the return value
  std::vector<std::unique_ptr<ExprAST>> statements;

  // Expression whose value will be returned by the function
  std::unique_ptr<ExprAST> returnExpression;

public:
  FunctionAST(std::unique_ptr<PrototypeAST>& _proto, 
    std::vector<std::unique_ptr<ExprAST>>& _statements, 
    std::unique_ptr<ExprAST>& _retExpr): 
    proto(std::move(_proto)),
    returnExpression(std::move(_retExpr)) 
    {
      setStatements(_statements);
    }

  FunctionAST(std::unique_ptr<PrototypeAST>& _proto, 
    std::vector<std::unique_ptr<ExprAST>>& _statements): 
    proto(std::move(_proto))
    {
      setStatements(_statements);
    }

  void setStatements(std::vector<std::unique_ptr<ExprAST>>& _statements)
  {
    for (auto & statement : _statements)
    {
      statements.push_back(std::move(statement));
    }
  }

  llvm::Function *codegen(
    std::vector<llvm::Value *>& decl);
};