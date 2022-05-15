/* Definitions */ 
%{
#include "calc.tab.h"

extern YYSTYPE yylval;
%}

/* Flex options */
/* Reads only one input file: stop lexing when the first EOF is reached */
%option noyywrap

/* Rules for token / terminal symbol lexing:
- Separators
- Positive decimal numbers
- New line
- Any other character
*/
%%

[ \t] ;

[1-9][0-9]*.?[0-9]* { sscanf (yytext, "%lf", &yylval); return NUM; }

[ \n] { yylval = 0; return yytext[0]; }

. { yylval = 0; return yytext[0]; }

%%

/* User code */

/* Called by yyparse on error */
void yyerror (char *s)  
{
  printf ("%s\n", s);
}
