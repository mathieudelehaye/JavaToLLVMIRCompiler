#include <stdio.h> // printf
#include <stdlib.h> // malloc
#include <string.h> // strlen, strcpy, strcmp
#include "calc_rec.h" // symrec

// Forward Declarations
int yyparse ();
void init_table ();

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
    printf ("%s\n", s);
}

/* The symbol table: a chain of `struct symrec'.  */
symrec *sym_table = (symrec *)0;

symrec *
putsym (sym_name,sym_type)
    char *sym_name;
    int sym_type;
{
    symrec *ptr;
    ptr = (symrec *) malloc (sizeof (symrec));
    ptr->name = (char *) malloc (strlen (sym_name) + 1);
    strcpy (ptr->name,sym_name);
    ptr->type = sym_type;
    ptr->value.var = 0; /* set value to 0 even if fctn.  */
    ptr->next = (struct symrec *)sym_table;
    sym_table = ptr;
    return ptr;
}

symrec *
getsym (sym_name)
    char *sym_name;
{
    symrec *ptr;
    for (ptr = sym_table; ptr != (symrec *) 0;
        ptr = (symrec *)ptr->next)
        if (strcmp (ptr->name,sym_name) == 0)
            return ptr;
    return 0;
}

int main ()
{
    init_table ();
    yyparse ();
}
