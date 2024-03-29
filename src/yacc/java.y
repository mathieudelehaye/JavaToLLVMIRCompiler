/* C Declaration */ 
%{
#include "../../include/cpp/parser_functions.h"
#include "../../include/cpp/generator_functions.h"
#include "../../include/parser/java.tab.h"   // yyget_text, yylex, yylval

#define YYDEBUG 1

int classes=0;
int funcs=0;
int method_calls=0;

void yyerror(const char* msg) {
   std::cout<<"Error: "<<msg<<std::endl;
}

int yylex (void);

extern char *yytext;
extern FILE *yyin;

// Global variables to build the AST
std::unique_ptr<ExprAST> varIdentifier;
std::unique_ptr<ExprAST> varValue;

std::vector<std::unique_ptr<ExprAST>> callPackages;
std::vector<std::unique_ptr<ExprAST>> callArgs;

std::vector<std::unique_ptr<ExprAST>> statementList;
%}

/* Bison Declarations */
%token LEFT_ROUND_BRACKET 40
%token RIGHT_ROUND_BRACKET 41
%token TIMES 42
%token PLUS 43
%token MINUS 45
%token DOT 46
%token RETURN 47
%token SEMICOLON 59
%token SMALLER_THAN 60
%token ASSIGN_OPERATOR 61
%token LEFT_CURLY_BRACKET 123
%token RIGHT_CURLY_BRACKET 125
%token PUBLIC
%token PRIVATE
%token PROTECTED
%token STATIC
%token NAME
%token INT_TYPE
%token STRING_TYPE
%token STRING_ARRAY_TYPE
%token BOOLEAN_TYPE
%token VOID_TYPE
%token IMPLEMENTS
%token EXTENDS
%token CLASS
%token INTERFACE
%token IF
%token WHILE
%token STRING
%token BOOLEAN
%token OPERATOR
%token INT

/* Grammar Rules*/
%%

Root: Class Root 
   | /*empty*/ { 
#ifdef DEBUG_PARSER
   std::cout<<"classes: "<<classes<<std::endl;
   std::cout<<"functions: "<<funcs<<std::endl;
   std::cout<<"method_calls: "<<method_calls<<std::endl; 
#endif   // DEBUG_PARSER
};

Class: ClassType NAME LEFT_CURLY_BRACKET Functions RIGHT_CURLY_BRACKET 
{ 
   classes++;
};

ClassType: CLASS;

Functions: Function Functions | /*empty*/ ;

Function: Modifier Static Type NAME LEFT_ROUND_BRACKET FormalArguments RIGHT_ROUND_BRACKET LEFT_CURLY_BRACKET Commands RIGHT_CURLY_BRACKET {
   
   funcs++;

   // TODO: for the moment, only the `main` function can be defined.
   // So, ensure it can be done as well for other custom functions.
   std::vector<std::string> formalArgs = {};
   auto proto = std::make_unique<PrototypeAST>("main", formalArgs);

   auto funct = FunctionAST(proto, statementList);
   
   statementList.clear();

   if (auto * functIR = funct.codegen(globalDeclarations))
   {
      globalDeclarations.push_back(functIR);
   }
};

Modifier: PUBLIC | PRIVATE | PROTECTED ;

Static: STATIC | /*empty*/ ;

Type: STRING_TYPE | STRING_ARRAY_TYPE | INT_TYPE | BOOLEAN_TYPE | VOID_TYPE ;

FormalArguments: FormalArgument FormalArguments | /*empty*/ ;

FormalArgument: Type NAME ArgumentSeparator ;

ArgumentSeparator: ',' | /*empty*/ ;

Commands: Command Commands | /*empty*/ ;

Command: VarDeclaration SEMICOLON
   | MethodCall SEMICOLON ;

MethodCall: References LEFT_ROUND_BRACKET ActualArguments RIGHT_ROUND_BRACKET 
{
   method_calls++;

   auto functionName = std::string("");
   auto itr = callPackages.begin();
   while(itr != callPackages.end()) 
   {
      functionName += dynamic_cast<IdentifierExprAST*>((*itr++).get())->getName();
      if (itr != callPackages.end())
      {
         // Add separator if not the last item 
         functionName += ".";
      }
   }

   auto call = std::make_unique<CallExprAST>(functionName, callArgs);
   statementList.push_back(std::move(call));

#ifdef DEBUG_PARSER
   if (!statementList.empty())
   {
      const auto expr = dynamic_cast<CallExprAST*>(statementList.back().get())->getText();
      std::cout<<"Call expr = \""<<expr<<"\""<<std::endl;
   }
#endif   // DEBUG_PARSER
}; 

References: Reference References | /*empty*/ ;

Reference: PackageName DOT 
   | PackageName ;

PackageName: NAME 
{
   callPackages.push_back(parseIdentifierExpr());

#ifdef DEBUG_PARSER
   if (!callPackages.empty())
   {
      const auto name = (dynamic_cast<IdentifierExprAST*>(callPackages.back().get()))->getName();
      std::cout<<"Called package name = "<<name<<std::endl;
   }
#endif   // DEBUG_PARSER
};

ActualArguments: ActualArgument ActualArguments | /*empty*/ ;

ActualArgument: ActualStringArgument ArgumentSeparator ;

ActualStringArgument: STRING 
{
   callArgs.push_back(parseStringExpr());

#ifdef DEBUG_PARSER
   if (!callArgs.empty())
   {
      const auto val = (dynamic_cast<StringExprAST*>(callArgs.back().get()))->getVal();
      std::cout<<"Actual argument = "<<val<<std::endl;
   }
#endif   // DEBUG_PARSER
};

VarDeclaration: Type VarName ASSIGN_OPERATOR VarValue
{
   auto decl = std::make_unique<BinaryExprAST>('=', std::move(varIdentifier), std::move(varValue));

   // Append to the statement list
   statementList.push_back(std::move(decl));

#ifdef DEBUG_PARSER
   if (!statementList.empty())
   {
      const auto expr = dynamic_cast<BinaryExprAST*>(statementList.back().get())->getText();
      // TODO: store the actual variable type, so we don't need to hardcode it.
      std::cout<<"Declaration expr = \"int "<<expr<<"\""<<std::endl;
   }
#endif   // DEBUG_PARSER
};

VarName: NAME 
{
   varIdentifier = parseIdentifierExpr();

#ifdef DEBUG_PARSER
   const auto name = (dynamic_cast<IdentifierExprAST*>(varIdentifier.get()))->getName();
   std::cout<<"Variable name = "<<name<<std::endl;
#endif   // DEBUG_PARSER
};

VarValue: INT
{
   varValue = parseNumberExpr();
   
#ifdef DEBUG_PARSER
   const auto value = (dynamic_cast<NumberExprAST*>(varValue.get()))->getVal();
   std::cout<<"Variable value = "<<value<<std::endl;
#endif   // DEBUG_PARSER

   if (auto *FnIR = varValue->codegen(globalDeclarations)) {
      std::cerr << "Read top-level expression:" ;
      FnIR->print(llvm::errs());
      std::cerr << "\n";
   }
};

%%

/* Additional C Code */
int main (int argc, char *argv[])
{
   // Parser debug messages sent to standard parser_error
   yydebug=1;

   if (argc != 2) 
   {
      std::cout<<"OVERVIEW: Java language parser"<<std::endl;
      std::cout<<"USAGE: parser file"<<std::endl;
      return -1;
   }

   initializeGenerator();

   FILE *fp;
   char * filename = argv[1];
   yyin = fopen(filename,"r");

   int ret = 0;
   ret = yyparse();
   std::cout<<"Parser: return value: "<<ret<<", buffer: \""<<yytext<<"\""<<std::endl;

   fclose(fp);

   writeOutputFile("output.ll");

   return ret;
}