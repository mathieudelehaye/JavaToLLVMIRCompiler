#define YYSTYPE double

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     NEG = 259
   };
#endif
/* Tokens.  */
#define NUM 258
#define NEG 259