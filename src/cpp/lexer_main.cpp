#include "../../include/cpp/TokenOutput.h"
#include "../../include/parser/java.tab.h" // yytokentype

#include <iostream>
#include <stdio.h>

#define YYSTYPE double

// defined in the lexer and declared here
extern char *yytext;
extern FILE *yyin;
extern int yylex ();

// defined in the parser, which this main module replaces in standalone mode
YYSTYPE yylval;


int main(int argc, char ** argv)
{
    FILE *fp;
    
    if (argc < 1 || argc > 2) 
    {
        printf("OVERVIEW: positive decimal number lexer\n");
        printf("USAGE: lexer [file]\n");
        return -1;
    }
    
    if (argc == 2)
    {
        const char * filename = argv[1];
        yyin = fopen(filename,"r");
    }

    int ret = 0;

    TokenOutput output {};
    while((ret = yylex()) != 0)
    {
        std::cout<<output.getName(static_cast<yytokentype>(ret));
    }
    std::cout<<std::endl;

    printf("Returing: EOF received\n");

    if(fp)
    {
        fclose(fp);
    }
    
    return 0;
}