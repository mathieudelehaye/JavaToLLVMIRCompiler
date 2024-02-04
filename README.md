# JavaToLLVMIRCompiler

A compiler front-end for the Java language.

It compiles a simple Java program, as an input, and generate an intermediate 
representation in LLVM-IR bitcodes (rather than the usual JVM bytecodes).

The compiler has been developed in C++.

It uses the following components:
- A lexical analyzer (lexer), created with the Flex (https://github.com/westes/flex) open source tool and written in the lex language.
- A parser, created with the GNU Bison (https://www.gnu.org/software/bison/) open source tool and written in the yacc language.
- An abstract syntax tree (AST) is then generated, before emitting the output using
the LLVM C++ API (https://llvm.org/docs/ProgrammersManual.html).

Use:
```
cd /project/root

# Build the tools
./run_build.sh

# Run the lexer (standalone mode)
./build/bin/lexer test_data/hello.java > lexer_output.txt

# Run the parser
./build/bin/parser test_data/hello.java > parser_output.txt 2> parser_error.txt 

# Build the output
clang output.ll -o output-j -Wno-override-module
```
