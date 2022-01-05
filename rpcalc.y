/* Reverse polish notation (RPN) calculator. */

%{
#define YYSTYPE double

#include <math.h> // pow
#include <stdio.h> // printf
#include <ctype.h>

// forward declarations
int yylex();
void yyerror();
%}

/* Bison (BI) declarations */
%token NUM

%% 
/* Grammar rules and actions follow */
input:    /* empty */
        | input line
;

line:     '\n' // we ignore a blank line
        | exp '\n'  { printf ("\t%.10g\n", $1); } // no value assigned to $$: the semantic value associated with the line is uninitialized / unpredictable
;

exp:      NUM             { $$ = $1;         }
        | exp exp '+'     { $$ = $1 + $2;    }
        | exp exp '-'     { $$ = $1 - $2;    }
        | exp exp '*'     { $$ = $1 * $2;    }
        | exp exp '/'     { $$ = $1 / $2;    }
      /* Exponentiation */
        | exp exp '^'     { $$ = pow ($1, $2); }
      /* Unary minus    */
        | exp 'n'         { $$ = -$1;        }
;
%%

/* Additional C code */

/* Lexical analyzer returns a double floating point 
   number on the stack and the token NUM, or the ASCII
   character read if not a number.  Skips all blanks
   and tabs, returns 0 for EOF. */

int yylex ()
{
  int c;

  /* skip white space  */
  while ((c = getchar ()) == ' ' || c == '\t')  
    ;
  /* process numbers   */
  if (c == '.' || isdigit (c))                
    {
      ungetc (c, stdin);
      scanf ("%lf", &yylval);
      return NUM;
    }
  /* return end-of-file  */
  if (c == EOF)                            
    return 0;
  /* return single chars */
  return c;                                
}

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s\n", s);
}

int main ()
{
  yyparse ();

  return 0;
}
