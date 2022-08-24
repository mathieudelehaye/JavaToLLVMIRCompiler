# BisonParsers
Some parsers and lexical analyzers created with the GNU Bison and Flex open source tools.

A parser for the Java language has been added, which is able to parse a simple Java program.

TODO: generate an abstract syntax tree (AST) and LLVM-IR intermediate code from the syntactic 
analysis.

Use examples:
- Java parser:
```
cd src/java

# Run lexer in standalone mode
flex java.l; clang lex.yy.c ../common/lexer_main.c -o lexer; ./lexer

# Run parser
flex java.l; bison java.y; clang java.tab.c lex.yy.c -o parser; ./parser hello.java

```

- Calculator:
```
cd src/calc

# Run lexer in standalone mode
flex calc.l; clang lex.yy.c ../common/lexer_main.c -o lexer; ./lexer # Ctrl+D to leave

# Run parser
flex calc.l; bison calc.y; clang calc.tab.c lex.yy.c -o calc; ./calc # Ctrl+D to leave
```
