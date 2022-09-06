#!/bin/bash

flex ./src/lex/java.l; mv ./lex.yy.c ./build/generated/lexer.cpp; make; ./build/bin/lexer test_data/hello.java > output.txt