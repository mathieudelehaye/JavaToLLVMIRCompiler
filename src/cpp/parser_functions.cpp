#include "../../include/cpp/parser_functions.h"

#include "../../include/cpp/AST/AST.h"

// dummy f and var
double NumVal;

void getNextToken()
{

}

std::unique_ptr<ExprAST> ParseNumberExpr() {
  auto Result = std::make_unique<NumberExprAST>(NumVal);
  getNextToken(); // consume the number
  return std::move(Result);
}