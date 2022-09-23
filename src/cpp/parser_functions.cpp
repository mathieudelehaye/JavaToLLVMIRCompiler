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

std::unique_ptr<ExprAST> parseStringExpr()
{
  std::string text = yyget_text();

  // Remove the first and last '"' chars if they have 
  // been lexed. Add a new line at the end of the 
  // string.
  if (text[0] == '"')
  {
    text = text.substr(1, text.length() - 1);
  }

  if (text[text.length() - 1] == '"')
  {
    text = text.substr(0, text.length() - 1);
  }

  if (text[text.length() - 1] != '\n')
  {
    text += "\n";
  }

  auto result = std::make_unique<StringExprAST>(text);
  return std::move(result);
}

std::unique_ptr<ExprAST> LogError(const char *errorMessage)
{
  std::cerr<<"LogError: "<<errorMessage<<std::endl;
  return nullptr;
}