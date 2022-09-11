#include "../../include/cpp/parser_functions.h"
#include "../../include/cpp/AST/AST.h"
#include "../../include/parser/java.tab.h"  // yyget_text, yylex, yytokentype 

#include <map>
#include <string> // stod


static std::map<int, int> binOpPrecedence;

static yytokentype currTokenType;

// Forward function declarations
static std::unique_ptr<ExprAST> parsePrimary();
static std::unique_ptr<ExprAST> parseBinOpRHS(int exprPrec,
  std::unique_ptr<ExprAST> lhs);
static std::unique_ptr<ExprAST> parseParenExpr();

// TODO: create class with proper constructor
void initParserFunctions() 
{
  binOpPrecedence.insert(std::make_pair(SMALLER_THAN, 10));  
  binOpPrecedence.insert(std::make_pair(PLUS, 20));  
  binOpPrecedence.insert(std::make_pair(MINUS, 20));  
  binOpPrecedence.insert(std::make_pair(TIMES, 20));  
}

static yytokentype getToken() {
  currTokenType = static_cast<yytokentype>(yylex());
  return currTokenType;
}

static std::unique_ptr<ExprAST> LogError(const char *errorMessage) {
  std::cerr<<"LogError: "<<errorMessage<<std::endl;
  return nullptr;
}

static std::unique_ptr<ExprAST> parseNumberExpr()
{
  auto result = std::make_unique<NumberExprAST>(std::stod(std::string(yyget_text())));
  getToken();
  return std::move(result);
}

static std::unique_ptr<ExprAST> parseExpression() 
{
  auto lhs = parsePrimary();
  if (!lhs)
  {
    return nullptr;
  }

  return parseBinOpRHS(0, std::move(lhs));
}

std::unique_ptr<ExprAST> ParseIdentifierExpr() {

  std::string idName = yyget_text();

  yylex(); // eat the identifier

  if (std::string(yyget_text()) != "(") // Simple variable reference
  {
    return std::make_unique<VariableExprAST>(idName);
  }

  // Call
  yylex(); // eat '('
  std::vector<std::unique_ptr<ExprAST>> Args;

  if (std::string(yyget_text()) != ")")
  {
    while (true) 
    {
      if (auto Arg = parseExpression())
      {
        Args.push_back(std::move(Arg));
      }
      else
      {
        return nullptr;
      }

      if (std::string(yyget_text()) == ")")
      {
        break;
      }

      if (std::string(yyget_text()) != ",")
      {
        return LogError("Expected ')' or ',' in argument list");
      }
      
      yylex();
    }
  }

  // Eat the ')'
  yylex();

  return std::make_unique<CallExprAST>(idName, std::move(Args));
}

static std::unique_ptr<ExprAST> parsePrimary() 
{
  switch (currTokenType) 
  {
  default:
    return LogError("unknown token when expecting an expression");
  case NAME:
    return ParseIdentifierExpr();
  case INT:
    return parseNumberExpr();
  case LEFT_CURLY_BRACKET:
    return parseParenExpr();
  }
}

static std::unique_ptr<ExprAST> parseParenExpr() 
{
  getToken(); // eat '('
  
  auto v = parseExpression();
  if (!v)
  {
    return nullptr;
  }

  if (currTokenType != ')')
  {
    return LogError("expected ')'");
  }

  getToken(); // eat ')'
  
  return v;
}

static int getTokPrecedence() 
{
  if (!isascii(currTokenType))
  {
    return -1;
  }

  // TODO: check this is a declared binary operator
  int tokPrec = binOpPrecedence[currTokenType];
  
  if (tokPrec <= 0)
  {
    return -1;
  }
  
  return tokPrec;
}

static std::unique_ptr<ExprAST> parseBinOpRHS(int exprPrec,
  std::unique_ptr<ExprAST> lhs) 
{
  // If this is a binary operator, find its precedence
  while (true)
  {
    const int tokPrec = getTokPrecedence();

    // If this is a binary operator that binds at least as tightly as the current binary operator,
    // consume it, otherwise we are done
    if (tokPrec < exprPrec)
    {
      return lhs;
    }

    // Okay, we know this is a binary operator
    const int binOp = currTokenType;
    getToken(); // eat binary operator

    // Parse the primary expression after the binary operator
    auto rhs = parsePrimary();
    if (!rhs)
    {
      return nullptr;
    }

    // If binary operator binds less tightly with RHS than the operator after RHS, let
    // the pending operator take RHS as its LHS
    int NextPrec = getTokPrecedence();
    if (tokPrec < NextPrec) {
      rhs = parseBinOpRHS(tokPrec + 1, std::move(rhs));
      
      if (!rhs)
      {
        return nullptr;
      }
    }

    // Merge LHS/RHS
    lhs =
        std::make_unique<BinaryExprAST>(binOp, std::move(lhs), std::move(rhs));
  }
}