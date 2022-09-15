#include "../../include/cpp/AST/FunctionAST.h"  // PrototypeAST
#include "../../include/cpp/generator_functions.h"

#include <filesystem> // std::filesystem::current_path, std::filesystem::path
#include <fstream>  // std::ofstream


std::unique_ptr<llvm::LLVMContext> theContext;
std::unique_ptr<llvm::Module> theModule;
std::unique_ptr<llvm::IRBuilder<>> builder;
std::map<std::string, llvm::Value *> namedValues;

std::filesystem::path outputFilePath;
std::vector<PrototypeAST> prototypes;

void initializeGenerator() 
{
  // Open a new context and module.
  theContext = std::make_unique<llvm::LLVMContext>();
  theModule = std::make_unique<llvm::Module>("my own jit", *theContext);

  // Create a new builder for the module.
  builder = std::make_unique<llvm::IRBuilder<>>(*theContext);

  // Create the output file.
  outputFilePath = std::filesystem::current_path();
  outputFilePath /= "output.ll";
  std::ofstream outputFile{outputFilePath};
  
  // Declare the extern functions.
  prototypes.push_back(PrototypeAST("puts", { "text" }));

  // Write the declarations to the output file.
  auto & functProto = prototypes.back();

  if (auto * fnIR = functProto.codegen()) 
  {
    std::string output;
    llvm::raw_string_ostream os(output);
    os << *fnIR;
    os.flush();
    
    outputFile<<output<<std::endl;
  }
}
