#include "../../include/cpp/parser_functions.h"
#include "../../include/cpp/AST/AST.h"
#include "../../include/parser/java.tab.h"

#include <string> // stod


std::unique_ptr<ExprAST> ParseNumberExpr() {
  auto Result = std::make_unique<NumberExprAST>(std::stod(std::string(yyget_text())));
  yylex();  // get next token
  return std::move(Result);
}