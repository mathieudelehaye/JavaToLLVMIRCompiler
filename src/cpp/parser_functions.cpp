#include "../../include/cpp/AST/AST.h"
#include "../../include/cpp/parser_functions.h"

#include <map>
#include <memory> // unique_ptr
#include <string> // stod


std::unique_ptr<ExprAST> parseVariableIdentifierExpr()
{
  std::string idName = yyget_text();

  return std::make_unique<VariableExprAST>(idName);
}

std::unique_ptr<ExprAST> parseNumberExpr()
{
  auto result = std::make_unique<NumberExprAST>(std::stod(std::string(yyget_text())));
  return std::move(result);
}

std::unique_ptr<ExprAST> LogError(const char *errorMessage)
{
  std::cerr<<"LogError: "<<errorMessage<<std::endl;
  return nullptr;
}