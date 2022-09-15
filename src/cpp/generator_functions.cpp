#include "../../include/cpp/AST/FunctionAST.h"  // PrototypeAST
#include "../../include/cpp/generator_functions.h"

#include <iostream>  // std::cerr


std::unique_ptr<llvm::LLVMContext> theContext;
std::unique_ptr<llvm::Module> theModule;
std::unique_ptr<llvm::IRBuilder<>> builder;
std::map<std::string, llvm::Value *> namedValues;
std::vector<PrototypeAST> prototypes;

void initializeGenerator() 
{
  // Open a new context and module.
  theContext = std::make_unique<llvm::LLVMContext>();
  theModule = std::make_unique<llvm::Module>("my own jit", *theContext);

  // Create a new builder for the module.
  builder = std::make_unique<llvm::IRBuilder<>>(*theContext);

  // Declare the extern functions.
  prototypes.push_back(PrototypeAST("puts", { "text" }));

  auto & functProto = prototypes.back();

  if (auto * fnIR = functProto.codegen()) 
  {
    std::cerr<<"fnIR->print(llvm::errs()) = ";
    fnIR->print(llvm::errs());
    std::cerr<<"\n";
  }
}
