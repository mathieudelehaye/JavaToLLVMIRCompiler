#include <ctype.h>
#include <stdlib.h> // realloc

// Forward Declarations
double sin();
double cos();
double tan();
double atan();
double log();
double log10();
double exp();
double sqrt();
double ceil();
double floor();

struct init
{
    char *fname;
    double (*fnct)();
};

struct constant_init
{
    char *fname;
    double var;
};

struct init arith_fncts[]
    = {
        "sin", sin,
        "cos", cos,
        "tan", tan,
        "atan", atan,
        "ln", log,
        "log", log10,
        "exp", exp,
        "sqrt", sqrt,
        "ceil", ceil,
        "floor", floor,
        0, 0
    };

struct constant_init constants[]
    = {
        "pi",       3.141592653589793,
        "e",        2.718281828459045,
        "gold",     1.618033988749894,
        0, 0
    };

int yylex ()
{
    int c;

    /* Ignore whitespace, get first nonwhite character.  */
    while ((c = getchar ()) == ' ' || c == '\t');

    if (c == EOF)
        return 0;

    /* Char starts a number => parse the number.         */
    if (c == '.' || isdigit (c))
    {
        ungetc (c, stdin);
        scanf ("%lf", &yylval.val);
        return NUM;
    }

    /* Char starts an identifier => read the name.       */
    if (isalpha (c))
    {
        symrec *s;
        static char *symbuf = 0;
        static int length = 0;
        int i;

        /* Initially make the buffer long enough
         for a 40-character symbol name.  */
        if (length == 0)
            length = 40, symbuf = (char *)malloc (length + 1);

        i = 0;
        do
        {
            /* If buffer is full, make it bigger.        */
            if (i == length)
            {
                length *= 2;
                symbuf = (char *)realloc (symbuf, length + 1);
            }
            /* Add this character to the buffer.         */
            symbuf[i++] = c;
            /* Get another character.                    */
            c = getchar ();
        }
        while (c != EOF && isalnum (c));

        ungetc (c, stdin);
        symbuf[i] = '\0';

        s = getsym (symbuf);
        
        int rval;
        if (s == 0)
        {
            s = putsym (symbuf, VAR);
            rval = NVAR;
        }
        else 
        {
            rval = s->type;
        }
        yylval.tptr = s;
        return rval;
    }

    /* Any other character is a token by itself.        */
    return c;
}

void init_table ()  /* puts arithmetic functions in table. */
{
    int i, secondArrStartIdx;
    symrec *ptr;
    for (i = 0; arith_fncts[i].fname != 0; i++)
    {
        ptr = putsym (arith_fncts[i].fname, FNCT);
        ptr->value.fnctptr = arith_fncts[i].fnct;
    }
    secondArrStartIdx = i;
    for (i = 0; constants[i].fname != 0; i++)
    {
        ptr = putsym (constants[i].fname, VAR);
        ptr->value.var = constants[i].var;
    }
}
