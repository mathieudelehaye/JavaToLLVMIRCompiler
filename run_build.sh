#!/bin/bash

# generate the lexer
flex -o build/generated/lexer.cpp ./src/lex/java.l

# generate the parser
bison -o ./build/generated/parser.cpp ./src/yacc/java.y

# build the tools
make clean
make build/bin/lexer
make build/bin/parser
