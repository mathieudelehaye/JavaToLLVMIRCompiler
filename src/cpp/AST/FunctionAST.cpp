#include "../../../include/cpp/AST/FunctionAST.h"   // PrototypeAST
#include "../../../include/cpp/generator_functions.h"  // theContext


llvm::Function * PrototypeAST::codegen()
{
    std::vector<llvm::Type *> strings(args.size(), llvm::Type::getInt8PtrTy(*theContext));
    
    llvm::FunctionType * ft =
        llvm::FunctionType::get(llvm::Type::getInt32Ty(*theContext), strings, false);

    llvm::Function * f =
        llvm::Function::Create(ft, llvm::Function::ExternalLinkage, name, theModule.get());

    // Set names for all arguments.
    unsigned idx = 0;
    for (auto &arg : f->args())
    {
        arg.setName(args[idx++]);
    }

    return f;
}