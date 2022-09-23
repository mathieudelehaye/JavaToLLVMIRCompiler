#pragma once

#include "../../include/cpp/AST/ExprAST.h"
#include "../../include/cpp/AST/FunctionAST.h"


std::unique_ptr<ExprAST> parseIdentifierExpr();
std::unique_ptr<ExprAST> parseNumberExpr();
std::unique_ptr<ExprAST> parseStringExpr();
std::unique_ptr<ExprAST> LogError(const char *errorMessage);