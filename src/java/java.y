/* C Declaration */ 
%{
#include <stdio.h>

//#define YYDEBUG 1

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
%token RETURN 47
%token INT

/* Grammar Rules*/
%%

Root: Class Root | /*empty*/ {printf("classes: %d\n", classes); printf("functions: %d\n", funcs); printf("method_calls: %d\n", method_calls);} ;
Class: ClassType NAME '{' Functions '}' {classes++;};
ClassType: CLASS;
Functions: Function Functions | /*empty*/ ;
Function: Modifier Static Type NAME '(' FormalArguments ')' '{' Commands '}' {funcs++;} ;
Modifier: PUBLIC | PRIVATE | PROTECTED ;
Static: STATIC | /*empty*/ ;
Type: STRING_TYPE | STRING_ARRAY_TYPE | INT_TYPE | BOOLEAN_TYPE | VOID_TYPE ;
FormalArguments: FormalArgument FormalArguments | /*empty*/ ;
FormalArgument: Type NAME ArgumentSeparator ;
ArgumentSeparator: ',' | /*empty*/ ;
Commands: Command Commands | /*empty*/ ;
Command: MethodCall ';' ;
MethodCall: References '(' ActualArguments ')' {method_calls++;};
References: Reference References | /*empty*/ ;
Reference: NAME '.' | NAME ;
ActualArguments: ActualArgument ActualArguments | /*empty*/ ;
ActualArgument: STRING  ArgumentSeparator ;

%%

/* Additional C Code */
int main (int argc, char *argv[])
{
   //yydebug=1;

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