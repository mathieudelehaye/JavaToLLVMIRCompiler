/* C Declaration */ 
%{
#include "../../include/cpp/parser_functions.h"
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
std::unique_ptr<ExprAST> varAssignment;

std::vector<std::unique_ptr<ExprAST>> callPackages;
std::vector<std::unique_ptr<ExprAST>> callArgs;
std::unique_ptr<ExprAST> functionCall;

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

   functionCall = std::make_unique<CallExprAST>(functionName, callArgs);

#ifdef DEBUG_PARSER
   const auto expr = dynamic_cast<CallExprAST*>(functionCall.get())->getText();
   std::cout<<"Call expr = \""<<expr<<"\""<<std::endl;
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
   callArgs.push_back(parseStringArgExpr());

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
   varAssignment = std::make_unique<BinaryExprAST>('=', std::move(varIdentifier), std::move(varValue));

#ifdef DEBUG_PARSER
   const auto expr = dynamic_cast<BinaryExprAST*>(varAssignment.get())->getText();
   // TODO: store the actual variable type, so we don't need to hardcode it.
   std::cout<<"Declaration expr = \"int "<<expr<<"\""<<std::endl;
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
};

%%

/* Additional C Code */
int main (int argc, char *argv[])
{
   // Parser debug messages sent to standard parser_error
   yydebug=1;

   if (argc != 2) {
      std::cout<<"OVERVIEW: Java language parser"<<std::endl;
      std::cout<<"USAGE: parser file"<<std::endl;
      return -1;
   }

   FILE *fp;
   char * filename = argv[1];
   yyin = fopen(filename,"r");

   int ret = 0;
   ret = yyparse();
   std::cout<<"Parser: return value: "<<ret<<", buffer: \""<<yytext<<"\""<<std::endl;

   fclose(fp);

   return ret;
}