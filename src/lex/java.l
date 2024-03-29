/* Definitions */ 
%{
#include "../../include/parser/java.tab.h"  // yyget_text, yylex, yylval

#include <string>   // stod
%}

/* Flex options */
/* Reads only one input file */
%option noyywrap

/* Rules for token / terminal symbol lexing:
- Separators
- Reserved words
- Identifiers
- String and integer literals
- Operators
- Dot character
*/
%%

[ \n] ;
[ \t] ;

"private" {return PRIVATE;}
"public" {return PUBLIC;}
"protected" {return PROTECTED;}
"static" {return STATIC;}
"implements" {return IMPLEMENTS;}
"extends" {return EXTENDS;}
"class" {return CLASS;}
"interface" {return INTERFACE;}
"if" {return IF;}
"while" {return WHILE;}
"return" {return RETURN;}
"true" {return BOOLEAN;}
"false" {return BOOLEAN;}
"int" {return INT_TYPE;}
"String[]" {return STRING_ARRAY_TYPE;}
"String" {return STRING_TYPE;}
"boolean" {return BOOLEAN_TYPE;}
"void" {return VOID_TYPE;}

"{" {return LEFT_CURLY_BRACKET;}
"}" {return RIGHT_CURLY_BRACKET;}

"(" {return LEFT_ROUND_BRACKET;}
")" {return RIGHT_ROUND_BRACKET;}

";" {return SEMICOLON;}
"." {return DOT;}

[A-z][A-z0-9]* {return NAME;}

"\""[A-z0-9 ,!]*"\"" {return STRING;}

"-"?[1-9][0-9]* { 
    yylval = std::stod(yytext); 
    return INT;
}

"+"|"-"|"*"|"/"|"==" {return OPERATOR;}

"=" {return ASSIGN_OPERATOR;}

. { return yytext[0]; }

%%

/* User code */
