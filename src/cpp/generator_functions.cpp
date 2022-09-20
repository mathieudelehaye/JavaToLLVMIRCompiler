#include "../../include/cpp/generator_functions.h"

#include "../../include/cpp/AST/FunctionAST.h"  // PrototypeAST
#include "../../include/cpp/parser_functions.h" // LogError

#include <filesystem> // std::filesystem::current_path, std::filesystem::path
#include <fstream>  // std::ofstream


std::unique_ptr<llvm::LLVMContext> theContext;
std::unique_ptr<llvm::Module> theModule;
std::unique_ptr<llvm::IRBuilder<>> builder;
std::map<std::string, llvm::Value *> namedValues;

std::filesystem::path outputFilePath;
std::vector<PrototypeAST> externDecl;
std::vector<PrototypeAST> functionDef;

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
  externDecl.push_back(PrototypeAST("puts", { "text" }));

  // Write the declarations to the output file.
  for(auto& functProto: externDecl)
  {
    if (auto * functIR = functProto.codegen()) 
    {
      std::string output;
      llvm::raw_string_ostream os(output);
      os << *functIR;
      os.flush();
      
      outputFile<<output<<std::endl;
    }
  }

  // Define the functions.
  std::unique_ptr<FunctionAST> functDef;
  {
    std::vector<std::string> formalArgs = { "text" };
    auto proto = std::make_unique<PrototypeAST>("System.out.println", formalArgs);

    std::vector<std::unique_ptr<ExprAST>> calleeArgs;
    calleeArgs.push_back(std::make_unique<IdentifierExprAST>("text"));

    std::unique_ptr<ExprAST> call = std::make_unique<CallExprAST>("puts", calleeArgs);
    functDef = std::make_unique<FunctionAST>(proto, call);
  }

  // Write the function definition to the output file.
  {
    if (auto * functIR = functDef->codegen()) 
    {
      std::string output;
      llvm::raw_string_ostream os(output);
      os << *functIR;
      os.flush();
      
      outputFile<<output<<std::endl;
    }
  }
}

llvm::Value *LogErrorV(const char *Str)
{
  LogError(Str);
  return nullptr;
}