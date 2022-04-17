/* Definitions */ 
%{
#include "java.tab.h"
%}

/* Flex options */
/* Reads only one input file */
%option noyywrap

/* Rules */
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

[A-z][A-z0-9]* {return NAME;}

"\""[A-z0-9 ,!]*"\"" {return STRING;}
"-"?[1-9][0-9]* {return INT;}

"+"|"-"|"*"|"/"|"="|"==" {return OPERATOR;}

. { return yytext[0]; }

%%

/* User code */

// Uncomment to unit test the lexer

/*
int main(int argc, char ** argv)
{
    if (argc != 2) {
        printf("OVERVIEW: Java language lexer\n");
        printf("USAGE: lexer file\n");
        return -1;
    }

    FILE *fp;
    char * filename = argv[1];
    yyin = fopen(filename,"r");

    int ret = 0;
    do
    {
        ret = yylex();
        printf("%d: %s\n",ret, yytext);
    } while (ret != 0);

	fclose(fp);

    return 0;
}
*/