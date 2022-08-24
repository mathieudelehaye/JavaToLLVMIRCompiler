# BisonParsers
A parser and lexical analyzer (lexer) for the Java language, created with the GNU Bison and Flex open source tools. It is able to parse a simple Java program.

TODO: 
- generate an abstract syntax tree (AST) and LLVM-IR intermediate code from the syntactic analysis.
- implement cmake.

Use:
```
cd /project/root

# Run lexer in standalone mode
./run_lexer.sh

# Run parser
flex java.l; bison java.y; clang java.tab.c lex.yy.c -o parser; ./parser hello.java

```