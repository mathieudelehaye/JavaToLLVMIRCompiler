#include "../../../include/cpp/AST/FunctionAST.h"   // PrototypeAST
#include "../../../include/cpp/generator_functions.h"  // theContext


llvm::Function * PrototypeAST::codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements)
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

llvm::Function * FunctionAST::codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements)
{
    // First, check for an existing function from a previous 'extern' declaration.
    llvm::Function *theFunction = theModule->getFunction(proto->getName());

    if (!theFunction)
    {
        theFunction = proto->codegen(decl, statements);
    }

    if (!theFunction)
    {
        return nullptr;
    }

    // Create a new basic block to start insertion into.
    llvm::BasicBlock *bb = llvm::BasicBlock::Create(*theContext, "entry", theFunction);
    builder->SetInsertPoint(bb);

    // Record the function arguments in the namedValues map.
    namedValues.clear();
    
    for (auto &arg : theFunction->args())
    {
        namedValues[std::string(arg.getName())] = &arg;
    }

    // Add a store instruction to the function body
    // auto *ptr = builder->CreateAlloca(
    //     llvm::Type::getInt32Ty(*theContext),
    //     llvm::ConstantInt::get(llvm::Type::getInt8Ty(*theContext), 1), "p");
    
    // builder->CreateStore(
    //     llvm::ConstantInt::get(llvm::Type::getInt32Ty(*theContext), 3), 
    //     ptr);

    if (llvm::Value *retVal = returnExpression->codegen(
        decl, statements))
    {
        // Finish off the function.
        builder->CreateRet(retVal);

        // Validate the generated code, checking for consistency.
        llvm::verifyFunction(*theFunction);

        return theFunction;
    }

    // Error reading body, remove function.
    theFunction->eraseFromParent();
    return nullptr;
}