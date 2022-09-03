#!/bin/bash

flex ./src/lex/java.l; mv ./lex.yy.c ./build/generated/lexer.cpp; clang++ ./build/generated/lexer.cpp ./src/cpp/lexer_main.cpp ./src/cpp/TokenOutput.cpp -std=c++14 -Wno-deprecated-register -o build/bin/lexer; ./build/bin/lexer test_data/hello.java > output.txt