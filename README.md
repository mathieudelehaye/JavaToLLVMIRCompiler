# BisonParsers
A parser and lexical analyzer (lexer) for the Java language, created with the GNU Bison (https://www.gnu.org/software/bison/) and Flex (https://github.com/westes/flex) open source tools. It is able to parse a simple Java program.

TODO: 
- generate an abstract syntax tree (AST) and LLVM-IR code from the syntactic analysis.
- use cmake.

Use:
```
cd /project/root

# Build the tools
./run_build.sh

# Run the lexer (standalone mode)
./build/bin/lexer test_data/hello.java > lexer_output.txt

# Run the parser
./build/bin/parser test_data/hello.java > parser_output.txt
```