# BisonParsers
Some parsers and lexical analyzers created with GNU Bison and Flex open source tools.

A parser for the Java language has been added, which is able to parse a simple Java program.
TODO: generate an abstract syntax tree (AST) and LLVM-IR intermediate code from the syntactic 
analysis.

Use examples:
- Java parser:
```
cd src/java
flex java.l; bison java.y; clang java.tab.c lex.yy.c -o parser; ./parser hello.java

```

- Calculators:
```
cd src/calculators
make rp -B
../build/rp/rpcalc # Ctrl+D to leave
make clean
```
