#include "../../include/cpp/TokenOutput.h"
#include "../../include/parser/java.tab.h" // yytokentype, yyget_text, yylex

#include <iostream>
#include <sstream>

#define YYSTYPE double

// defined in the parser, which this main module replaces in standalone mode
YYSTYPE yylval;


int main(int argc, char ** argv)
{
    FILE *fp;

    std::stringstream tokenIds, semanticValues;
    
    if (argc < 1 || argc > 2) 
    {
        printf("OVERVIEW: positive decimal number lexer\n");
        printf("USAGE: lexer [file]\n");
        return -1;
    }
    
    if (argc == 2)
    {
        const char * filename = argv[1];
        FILE* yyin = fopen(filename,"r");
        yyset_in(yyin);
    }

    int ret = 0;

    TokenOutput output {};
    while((ret = yylex()) != 0)
    {
        tokenIds << output.getName(static_cast<yytokentype>(ret));
        semanticValues << yyget_text() << " ";
    }
    std::cout<<std::endl;

    std::cout<<"tokenIds.str() = "<<tokenIds.str()<<std::endl;
    std::cout<<"semanticValues.str() = "<<semanticValues.str()<<std::endl;

    printf("Returing: EOF received\n");

    if(fp)
    {
        fclose(fp);
    }
    
    return 0;
}