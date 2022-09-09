#!/bin/bash

# generate the lexer
flex ./src/lex/java.l
mv ./lex.yy.c ./build/generated/lexer.cpp

# generate the parser
bison ./src/yacc/java.y
mv ./java.tab.c ./build/generated/parser.cpp

# build the tools
make
