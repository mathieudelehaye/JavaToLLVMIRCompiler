#include <stdio.h>   // FILE

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
      PUBLIC = 258,
      PRIVATE = 259,
      PROTECTED = 260,
      STATIC = 261,
      NAME = 262,
      INT_TYPE = 263,
      STRING_TYPE = 264,
      STRING_ARRAY_TYPE = 265,
      BOOLEAN_TYPE = 266,
      VOID_TYPE = 267,
      IMPLEMENTS = 268,
      EXTENDS = 269,
      CLASS = 270,
      INTERFACE = 271,
      IF = 272,
      WHILE = 273,
      STRING = 274,
      BOOLEAN = 275,
      OPERATOR = 276,
      ASSIGNMENT_OPERATOR = 277,
      RETURN = 47,
      INT = 278,
      LEFT_CURLY_BRACKET = 279,
      RIGHT_CURLY_BRACKET = 280,  
      LEFT_ROUND_BRACKET = 281,
      RIGHT_ROUND_BRACKET = 282,
      SEMICOLON = 283,
      DOT = 284,
   };
#endif
/* Tokens.  */
#define PUBLIC 258
#define PRIVATE 259
#define PROTECTED 260
#define STATIC 261
#define NAME 262
#define INT_TYPE 263
#define STRING_TYPE 264
#define STRING_ARRAY_TYPE 265
#define BOOLEAN_TYPE 266
#define VOID_TYPE 267
#define IMPLEMENTS 268
#define EXTENDS 269
#define CLASS 270
#define INTERFACE 271
#define IF 272
#define WHILE 273
#define STRING 274
#define BOOLEAN 275
#define OPERATOR 276
#define ASSIGNMENT_OPERATOR 277
#define RETURN 47
#define INT 278
#define LEFT_CURLY_BRACKET 279
#define RIGHT_CURLY_BRACKET 280
#define LEFT_ROUND_BRACKET 281
#define RIGHT_ROUND_BRACKET 282
#define SEMICOLON 283
#define DOT 284

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef char* YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;
