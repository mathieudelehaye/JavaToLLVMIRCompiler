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

std::vector<llvm::Value *> globalDeclarations;
std::vector<llvm::Value *> localStatements;


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
  auto functProto = PrototypeAST("puts", { "text" });
  
  if (auto * functIR = functProto.codegen()) 
  {
    globalDeclarations.push_back(functIR);
  }

  // Define the string literals.
  {
    auto strLit = std::make_unique<StringExprAST>("hello world");

    if (auto * strLitIR = strLit->codegen())
    {
      globalDeclarations.push_back(strLitIR);
    }
  }

  // Define the functions.
  {
    std::vector<std::string> formalArgs = { "text" };
    auto proto = std::make_unique<PrototypeAST>("System.out.println", formalArgs);

    std::vector<std::unique_ptr<ExprAST>> calleeArgs;
    calleeArgs.push_back(std::make_unique<IdentifierExprAST>("text"));

    std::unique_ptr<ExprAST> call = std::make_unique<CallExprAST>("puts", calleeArgs);
    auto funct = FunctionAST(proto, call);

    if (auto * functIR = funct.codegen()) 
    {
      globalDeclarations.push_back(functIR);
    }
  }

  // Write to the output file
  for (auto& functIR: globalDeclarations)
  {
    std::string output;
    llvm::raw_string_ostream os(output);
    os << *functIR;
    os.flush();

    if (output[output.length()-1] != '\n')
    {
      output += "\n";
    }

    outputFile<<output<<std::endl;
  }
}

llvm::Value *LogErrorV(const char *Str)
{
  LogError(Str);
  return nullptr;
}