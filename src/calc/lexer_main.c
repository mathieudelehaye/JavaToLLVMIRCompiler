#include <stdio.h>

#define YYSTYPE double

extern char *yytext;
YYSTYPE yylval;
extern FILE *yyin;
extern int yylex ();

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
        printf("%d: %lf\n",ret, yylval);
    }

    printf("Returing: EOF received\n");

    if(fp)
    {
        fclose(fp);
    }
    
    return 0;
}