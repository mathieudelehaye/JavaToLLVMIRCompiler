#include "../../../include/cpp/AST/ExprAST.h"
#include "../../../include/cpp/generator_functions.h"  // theContext


llvm::Value * NumberExprAST::codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements)
{
    return llvm::ConstantFP::get(*(theContext.get()), llvm::APFloat(val));
}

double NumberExprAST::getVal() const 
{
    return val;
}

llvm::Value * StringExprAST::codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements)
{
    const std::string strName = ".str";
    std::vector<llvm::Constant *> chars(val.size() + 1);
    for(unsigned int i = 0; i < val.size(); i++)
    {
        chars[i] = llvm::ConstantInt::get(llvm::Type::getInt8Ty(*theContext), val[i]);
    }
    // Add the string terminal '0'
    chars[val.size()] = llvm::ConstantInt::get(llvm::Type::getInt8Ty
        (*theContext), 0);

    auto init = llvm::ConstantArray::get(llvm::ArrayType::get   
        (llvm::Type::getInt8Ty(*theContext), chars.size()), chars);

    // Global variable declaration
    // TODO: replace it by a smart pointer
    llvm::GlobalVariable * gVar = 
        new llvm::GlobalVariable(*(theModule.get()), init->getType(), true,
        llvm::GlobalVariable::ExternalLinkage, init, strName);
    
    gVar->setLinkage(llvm::GlobalValue::PrivateLinkage);
    gVar->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);

    // Push straightforwad the IR expression to the stack. So no
    // need to return it.
    decl.push_back(gVar);

    // Local variable initialization
    // builder->CreateGEP(llvm::Type::getInt8Ty(*theContext), chars[0], 0);
    
    return nullptr;
}

std::string StringExprAST::getVal() const 
{
    return val;
}

llvm::Value * IdentifierExprAST::codegen(
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements)
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
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements)
{
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
    std::vector<llvm::Value *>& decl, 
    std::vector<llvm::Value *>& statements)
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
    // by a local variable. Moreover:
    // - A global variable must be declared for the string literal
    // - The local variable must be declared and initialized with 
    // the address of the global variable.
    if (auto * strLit = dynamic_cast<StringExprAST*>(args[0].get()))
    {
        // Global variable declaration and local variable initialization 
        strLit->codegen(decl, statements);

        // Remove the string literal argument
        args.pop_back();
    }

    std::vector<llvm::Value *> argsV;
    for (unsigned i = 0, e = args.size(); i != e; ++i) 
    {
        argsV.push_back(args[i]->codegen(decl, statements));

        if (!argsV.back())
        {
            return nullptr;
        }
    }

    return builder->CreateCall(calleeF, argsV, "calltmp");
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