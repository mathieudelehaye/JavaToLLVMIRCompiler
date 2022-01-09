/* Multi-Function (MF) calculator */

/* C Declarations */
%{
#include <stdio.h> // printf
#include <math.h>  // math functions: cos(), sin(), etc.
#include "../../src/mf/calc_rec.h"  // symrec

// forward declarations
int yylex ();
void yyerror (char *s);
%}

/* Bison (BI) Declarations */
%union {
double     val;  // returning numbers
symrec  *tptr;   // returning symbol-table pointers
}

%token <val>  NUM        /* Simple double precision number   */
%token <tptr> VAR FNCT   /* Variable and Function            */
%type  <val>  exp

%right '='
%left '-' '+'
%left '*' '/'
%left NEG     /* Negation--unary minus */
%right '^'    /* Exponentiation        */

/* Grammar Rule */
%%
input:   /* empty */
    | input line
;

line:
    '\n'
    | exp '\n'   { printf ("\t%.10g\n", $1); }
    | error '\n' { yyerrok;                  }
;

exp:      NUM            { $$ = $1;                         }
    | VAR                { $$ = $1->value.var;              }
    | VAR '=' exp        { $$ = $3; $1->value.var = $3;     }
    | FNCT '(' exp ')'   { $$ = (*($1->value.fnctptr))($3); }
    | exp '+' exp        { $$ = $1 + $3;                    }
    | exp '-' exp        { $$ = $1 - $3;                    }
    | exp '*' exp        { $$ = $1 * $3;                    }
    | exp '/' exp        { $$ = $1 / $3;                    }
    | '-' exp  %prec NEG { $$ = -$2;                        }
    | exp '^' exp        { $$ = pow ($1, $3);               }
    | '(' exp ')'        { $$ = $2;                         }
;
/* End of grammar */
%%

/* Additional C code */

#include "../../src/mf/mfcalc_main.h"
