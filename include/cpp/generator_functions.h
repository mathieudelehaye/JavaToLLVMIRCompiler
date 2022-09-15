#pragma once
#include "../../include/cpp/AST/AST.h"

#include <map>


extern std::unique_ptr<llvm::LLVMContext> theContext;
extern std::unique_ptr<llvm::Module> theModule;
extern std::unique_ptr<llvm::IRBuilder<>> builder;
extern std::map<std::string, llvm::Value *> namedValues;

void initializeGenerator();