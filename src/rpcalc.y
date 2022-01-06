/* Reverse polish notation (RPN) calculator. */

%{
#include <math.h> // pow
#include <stdio.h> // printf
#include <ctype.h>

#define YYSTYPE double

// forward declarations
int yylex ();
void yyerror (char *s);
%}

/* Bison (BI) Declarations */
%token NUM

%% 
/* Grammar Rules and Actions follow */
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

#include "../src/calc_main.h"
