#pragma once

#include "../../include/cpp/AST/ExprAST.h"


std::unique_ptr<ExprAST> parseIdentifierExpr();
std::unique_ptr<ExprAST> parseNumberExpr();
std::unique_ptr<ExprAST> parseStringArgExpr();
std::unique_ptr<ExprAST> LogError(const char *errorMessage);