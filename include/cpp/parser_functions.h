#pragma once

#include "../../include/cpp/AST/ExprAST.h"
#include "../../include/parser/java.tab.h"  // yyget_text, yylex, yytokentype 


std::unique_ptr<ExprAST> parseVariableIdentifierExpr();
std::unique_ptr<ExprAST> parseNumberExpr();
std::unique_ptr<ExprAST> LogError(const char *errorMessage);