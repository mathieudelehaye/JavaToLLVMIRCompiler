#pragma once
#include "../../include/cpp/AST/AST.h"

#include <map>


extern std::unique_ptr<llvm::LLVMContext> theContext;
extern std::unique_ptr<llvm::Module> theModule;
extern std::unique_ptr<llvm::IRBuilder<>> builder;
extern std::map<std::string, llvm::Value *> namedValues;

extern std::vector<llvm::Value *> globalDeclarations;
extern std::vector<llvm::Value *> localStatements;

void initializeGenerator();
llvm::Value *LogErrorV(const char *Str);