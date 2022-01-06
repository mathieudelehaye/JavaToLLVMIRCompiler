#include <stdio.h> // printf

int yyparse ();

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