#include "../java/java.tab.h" // yytokentype

#include <iostream>
#include <stdio.h>

#define YYSTYPE double

// defined in the lexer and declared here
extern char *yytext;
extern FILE *yyin;
extern int yylex ();

// defined in the parser, which this main module replaces in standalone mode
YYSTYPE yylval;

class Token
{
public:
    static std::string getName(yytokentype type) 
    {   
        switch(type)
        {
            case PUBLIC:
                return "public_keyword";
            case PRIVATE:
                return "private_keyword";
            case PROTECTED:
                return "protected_keyword";
            case STATIC:
                return "static_keyword";
            case IMPLEMENTS:
                return "implements_keyword";
            case EXTENDS:
                return "extends_keyword";
            case CLASS:
                return "class_keyword";
            case INTERFACE:
                return "interface_keyword";
            case IF:
                return "if_keyword";
            case WHILE:
                return "while_keyword";
            case RETURN:
                return "return_keyword";
            case INT_TYPE:
                return "int_type";
            case STRING_TYPE:
                return "string_type";
            case STRING_ARRAY_TYPE:
                return "string_array_type";
            case BOOLEAN_TYPE:
                return "bool_type";
            case VOID_TYPE:
                return "void_type";
            case INT:
                return "<integer>";
            case NAME:
                return "<identifier>";
            case STRING:
                return "<string>";
            case BOOLEAN:
                return "<bool>";
            case OPERATOR:
                return "<operator>";
            default:
                return "<unknown value>";
        }
    }
};

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
    while((ret = yylex()) != 0)
    {
        // printf("%d: %lf\n",ret, yylval);
        std::cout<<Token::getName(static_cast<yytokentype>(ret))<<std::endl;
    }

    printf("Returing: EOF received\n");

    if(fp)
    {
        fclose(fp);
    }
    
    return 0;
}