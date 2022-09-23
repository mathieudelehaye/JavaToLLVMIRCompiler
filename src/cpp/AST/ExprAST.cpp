#include "../../../include/cpp/AST/ExprAST.h"
#include "../../../include/cpp/generator_functions.h"  // theContext


llvm::Value * NumberExprAST::codegen(
    std::vector<llvm::Value *>& decl)
{
    return llvm::ConstantFP::get(*(theContext.get()), llvm::APFloat(val));
}

double NumberExprAST::getVal() const 
{
    return val;
}

llvm::Value * StringExprAST::codegen(
    std::vector<llvm::Value *>& decl)
{
    const std::string strName = ".str";
    const u_int64_t strSize = val.size() + 1;
    
    auto * arrayType = llvm::ArrayType::get(llvm::Type::getInt8Ty(*theContext), strSize);

    // Store the string chars in an int array
    std::vector<llvm::Constant *> chars(strSize);
    for(unsigned int i = 0; i < val.size(); i++)
    {
        chars[i] = llvm::ConstantInt::get(llvm::Type::getInt8Ty(*theContext), val[i]);
    }
    // Add the string terminal '0'
    chars[val.size()] = llvm::ConstantInt::get(llvm::Type::getInt8Ty
        (*theContext), 0);

    // Store the initialized vector into a proper data structure
    auto init = llvm::ConstantArray::get(arrayType, chars);

    // Global variable declaration
    // TODO: replace it by a smart pointer
    llvm::GlobalVariable * gVar = 
        new llvm::GlobalVariable(*(theModule.get()), arrayType, true,
        llvm::GlobalVariable::ExternalLinkage, init, strName);
    
    gVar->setLinkage(llvm::GlobalValue::PrivateLinkage);
    gVar->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);

    // Push straightforwad the IR declaration to the stack. So no
    // need to return it.
    decl.push_back(gVar);

    // Store the global variable address to a local variable
    const std::string localVarName = "cast210";

    llvm::GetElementPtrInst * inst = llvm::GetElementPtrInst::Create(
        arrayType,
        gVar, 
        { 
            llvm::ConstantInt::get(*theContext, llvm::APInt(64, 0)),
            llvm::ConstantInt::get(*theContext, llvm::APInt(64, 0))
        });

    namedValues[localVarName] = inst;
    
    // Insert the instruction in the function definition
    builder->Insert(
        inst,
        localVarName);

    return nullptr;
}

std::string StringExprAST::getVal() const 
{
    return val;
}

llvm::Value * IdentifierExprAST::codegen(
    std::vector<llvm::Value *>& decl)
{
    // Look this variable up in the function.
    llvm::Value *V = namedValues[name];

    if (!V)
    {
        LogErrorV("Unknown variable name");
    }
    
    return V;
}

std::string IdentifierExprAST::getName() 
{
    return name;
}

llvm::Value * BinaryExprAST::codegen(
    std::vector<llvm::Value *>& decl)
{
    // Add a store instruction to the function body
    // auto *ptr = builder->CreateAlloca(
    //     llvm::Type::getInt32Ty(*theContext),
    //     llvm::ConstantInt::get(llvm::Type::getInt8Ty(*theContext), 1), "p");
    
    // builder->CreateStore(
    //     llvm::ConstantInt::get(llvm::Type::getInt32Ty(*theContext), 3), 
    //     ptr);

    return nullptr;
}

std::string BinaryExprAST::getText() 
{
    auto exprASTToString = [] (std::unique_ptr<ExprAST>& expr) -> std::string 
    {
        const auto varExpr = dynamic_cast<IdentifierExprAST*>(expr.get());
        if (varExpr)
        {
            return varExpr->getName();
        }

        const auto numberExpr = dynamic_cast<NumberExprAST*>(expr.get());
        if (numberExpr)
        {
            return std::to_string(static_cast<int>(numberExpr->getVal()));
        }

        return "";
    };

    return (exprASTToString(lhs) + op + exprASTToString(rhs));
}

llvm::Value * CallExprAST::codegen(
    std::vector<llvm::Value *>& decl)
{
    // Look up the name in the global module table.
    llvm::Function *calleeF = theModule->getFunction(callee);

    if (!calleeF)
    {
        return LogErrorV("Unknown function referenced");
    }

    // If argument mismatch error.
    if (calleeF->arg_size() != args.size())
    {
        return LogErrorV("Incorrect # arguments passed");
    }

    // If the callee argument is a string literal, replace it
    // by a local variable identifier. Moreover:
    // - A global variable must be declared for the string literal
    // - The local variable must be declared and initialized with 
    // the address of the global variable.
    if (auto * strLit = dynamic_cast<StringExprAST*>(args[0].get()))
    {
        // Global variable declaration and local variable initialization 
        strLit->codegen(decl);

        // Remove the string literal
        args.pop_back();

        // Add the identifier
        args.push_back(std::make_unique<IdentifierExprAST>("cast210"));
    }

    std::vector<llvm::Value *> argsV;
    for (unsigned i = 0, e = args.size(); i != e; ++i) 
    {
        argsV.push_back(args[i]->codegen(decl));

        if (!argsV.back())
        {
            return nullptr;
        }
    }

    if (storeReturn)
    {
        return builder->CreateCall(calleeF, argsV, "calltmp");
    }
    else
    {
        return builder->CreateCall(calleeF, argsV);
    }
}

std::string CallExprAST::getText() 
{
    auto text = callee + " (";

    auto argsText = std::string("");
    auto itr = args.begin();
    while(itr != args.end()) 
    {
      argsText += dynamic_cast<StringExprAST*>((*itr++).get())->getVal();

      if (itr != args.end())
      {
        // Add separator if not the last item 
        argsText += ", ";
      }
    }

    text += argsText;
    text += ");";

    return text;
}