/* C Declaration */ 
%{
#include <stdio.h>

#include "../../include/cpp/parser_functions.h"
#include "../../include/parser/java.tab.h"   // yyget_text, yylex

#define YYDEBUG 1

#define YYSTYPE char*

int classes=0;
int funcs=0;
int method_calls=0;

void yyerror(const char* msg){printf("Error: %s\n", msg);}

int yylex (void);

extern char *yytext;
extern FILE *yyin;
%}

/* Bison Declarations */
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
%token ASSIGNMENT_OPERATOR
%token RETURN 47
%token INT
%token LEFT_CURLY_BRACKET
%token RIGHT_CURLY_BRACKET
%token LEFT_ROUND_BRACKET
%token RIGHT_ROUND_BRACKET
%token SEMICOLON
%token DOT

/* Grammar Rules*/
%%

Root: Class Root 
   | /*empty*/ { printf("classes: %d\n", classes); printf("functions: %d\n", funcs); printf("method_calls: %d\n", method_calls); } 
;

Class: ClassType NAME LEFT_CURLY_BRACKET Functions RIGHT_CURLY_BRACKET 
{ 
   classes++;
};

ClassType: CLASS;

Functions: Function Functions | /*empty*/ ;

Function: Modifier Static Type NAME LEFT_ROUND_BRACKET 

FormalArguments RIGHT_ROUND_BRACKET LEFT_CURLY_BRACKET Commands RIGHT_CURLY_BRACKET {funcs++;} ;

Modifier: PUBLIC | PRIVATE | PROTECTED ;

Static: STATIC | /*empty*/ ;

Type: STRING_TYPE | STRING_ARRAY_TYPE | INT_TYPE | BOOLEAN_TYPE | VOID_TYPE ;

FormalArguments: FormalArgument FormalArguments | /*empty*/ ;

FormalArgument: Type NAME ArgumentSeparator ;

ArgumentSeparator: ',' | /*empty*/ ;

Commands: Command Commands | /*empty*/ ;

Command: VarDeclaration SEMICOLON
   | MethodCall SEMICOLON ;

MethodCall: References LEFT_ROUND_BRACKET ActualArguments 

RIGHT_ROUND_BRACKET {method_calls++;};

References: Reference References | /*empty*/ ;

Reference: NAME DOT 
   | NAME 
{ 
   //printf("%s\n", yyval);
};

ActualArguments: ActualArgument ActualArguments | /*empty*/ ;

ActualArgument: STRING  ArgumentSeparator ;

VarDeclaration: INT_TYPE NAME ASSIGNMENT_OPERATOR INT 
{
   ParseNumberExpr();
   printf("Integer variable declared: %s\n", yylval); 
};

%%

/* Additional C Code */
int main (int argc, char *argv[])
{
   yydebug=1;

   if (argc != 2) {
      printf("OVERVIEW: Java language parser\n");
      printf("USAGE: parser file\n");
      return -1;
   }

   FILE *fp;
   char * filename = argv[1];
   yyin = fopen(filename,"r");

   int ret = 0;
   ret = yyparse();
   printf("Parser: return value: %d, buffer: \"%s\"\n",ret, yytext);

   fclose(fp);

   return ret;
}