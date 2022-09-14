#pragma once
#include "../../include/cpp/AST/AST.h"

#include <map>


extern std::unique_ptr<llvm::LLVMContext> TheContext;
extern std::unique_ptr<llvm::Module> TheModule;
extern std::unique_ptr<llvm::IRBuilder<>> Builder;
extern std::map<std::string, llvm::Value *> NamedValues;

void InitializeGenerator();