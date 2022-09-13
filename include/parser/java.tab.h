#include <stdio.h>   // FILE
#include <iostream>

#define DEBUG_PARSER

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
      LEFT_ROUND_BRACKET = 40,
      RIGHT_ROUND_BRACKET = 41,
      TIMES = 42,
      PLUS = 43,
      MINUS = 45,
      DOT = 46,
      RETURN = 47,
      SEMICOLON = 59,
      SMALLER_THAN = 60,
      ASSIGN_OPERATOR = 61,
      LEFT_CURLY_BRACKET = 123,
      RIGHT_CURLY_BRACKET = 125,
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
      INT = 277
   };
#endif
/* Tokens.  */
#define LEFT_ROUND_BRACKET 40
#define RIGHT_ROUND_BRACKET 41
#define TIMES 42
#define PLUS 43
#define MINUS 45
#define DOT 46
#define RETURN 47
#define SEMICOLON 59
#define SMALLER_THAN 60
#define ASSIGN_OPERATOR 61
#define LEFT_CURLY_BRACKET 123
#define RIGHT_CURLY_BRACKET 125
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
#define INT 277

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef double YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

char *yyget_text  (void);
int yylex (void);
extern YYSTYPE yylval;
