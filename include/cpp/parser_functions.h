#pragma once

#include "../../include/cpp/AST/ExprAST.h"

#include "memory"   // unique_ptr

// Parse a number expression object from a token 
std::unique_ptr<ExprAST> ParseNumberExpr();