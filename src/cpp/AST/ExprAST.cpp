#include "../../../include/cpp/AST/ExprAST.h"
#include "../../../include/cpp/generator_functions.h"  // theContext


llvm::Value * NumberExprAST::codegen()
{
    return llvm::ConstantFP::get(*(theContext.get()), llvm::APFloat(val));
}

double NumberExprAST::getVal() const 
{
    return val;
}

llvm::Value * StringExprAST::codegen() 
{
    return nullptr;
}

std::string StringExprAST::getVal() const 
{
    return val;
}

llvm::Value * IdentifierExprAST::codegen() 
{
    return nullptr;
}

std::string IdentifierExprAST::getName() 
{
    return name;
}

llvm::Value * BinaryExprAST::codegen() 
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

llvm::Value * CallExprAST::codegen() 
{
    return nullptr;
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