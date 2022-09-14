#include "../../include/cpp/AST/AST.h"
#include "../../include/cpp/parser_functions.h"
#include "../../include/parser/java.tab.h"  // yyget_text 

#include <map>
#include <memory> // unique_ptr
#include <string> // stod


std::unique_ptr<ExprAST> parseIdentifierExpr()
{
  std::string idName = yyget_text();

  return std::make_unique<IdentifierExprAST>(idName);
}

std::unique_ptr<ExprAST> parseNumberExpr()
{
  auto result = std::make_unique<NumberExprAST>(std::stod(std::string(yyget_text())));
  return std::move(result);
}

std::unique_ptr<ExprAST> parseStringArgExpr()
{
  // TODO: manage other types of argument than `std::string`.
  auto result = std::make_unique<StringExprAST>(yyget_text());
  return std::move(result);
}

std::unique_ptr<ExprAST> LogError(const char *errorMessage)
{
  std::cerr<<"LogError: "<<errorMessage<<std::endl;
  return nullptr;
}