# BisonParsers
A parser and lexical analyzer (lexer) for the Java language, created with the GNU Bison and Flex open source tools. It is able to parse a simple Java program.

TODO: 
- generate an abstract syntax tree (AST) and LLVM-IR intermediate code from the syntactic analysis.
- implement cmake.

Use example:
```
cd src/java

# Run lexer in standalone mode
flex ./src/lex/java.l; mv ./lex.yy.c ./build/generated/lexer.cpp; clang++ ./build/generated/lexer.cpp ./src/cpp/lexer_main.cpp -o build/bin/lexer; ./build/bin/lexer test_data/hello.java

# Run parser
flex java.l; bison java.y; clang java.tab.c lex.yy.c -o parser; ./parser hello.java

```