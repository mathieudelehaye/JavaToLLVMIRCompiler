#pragma once

#include "../../include/cpp/AST/ExprAST.h"


std::unique_ptr<ExprAST> parseVariableIdentifierExpr();
std::unique_ptr<ExprAST> parseNumberExpr();
std::unique_ptr<ExprAST> LogError(const char *errorMessage);