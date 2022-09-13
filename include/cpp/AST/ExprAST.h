#pragma once

#include "AST.h"

// Base class for all expression nodes
class ExprAST 
{
public:
  virtual ~ExprAST() {}
};

// Expression class for numeric literals: e.g. 1.0
class NumberExprAST : public ExprAST 
{
  double val;

public:
  NumberExprAST(double _val) : val(_val) {}

  double getVal() const 
  {
    return val;
  }
};

// Expression class for referencing a variable
class VariableExprAST : public ExprAST 
{
  std::string name;

public:
  VariableExprAST(const std::string &_name) : name(_name) {}

  std::string getName() 
  {
    return name;
  }
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

    std::string getText() 
    {
      auto exprASTToString = [] (std::unique_ptr<ExprAST>& expr) -> std::string 
      {
          const auto varExpr = dynamic_cast<VariableExprAST*>(expr.get());
          if (varExpr)
          {
            return varExpr->getName();
          }

          const auto numberExpr = dynamic_cast<NumberExprAST*>(expr.get());
          if (numberExpr)
          {
            return std::to_string(static_cast<int>(numberExpr->getVal()));
          }

          return "";
      };

      return (exprASTToString(lhs) + op + exprASTToString(rhs));
  }
};

// Expression class for function calls
class CallExprAST : public ExprAST 
{
  std::string callee;
  std::vector<std::unique_ptr<ExprAST>> args;

public:
  CallExprAST(const std::string &_callee,
              std::vector<std::unique_ptr<ExprAST>> _args)
    : callee(_callee), args(std::move(_args)) {}
};
