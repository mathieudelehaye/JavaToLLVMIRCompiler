CXXFLAGS = -g -Wno-deprecated-register -I/usr/local/Cellar/llvm/14.0.6_1/include -std=c++14 -stdlib=libc++ -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -L/usr/local/Cellar/llvm/14.0.6_1/lib -Wl,-search_paths_first -Wl,-headerpad_max_install_names -lLLVM-14

CXX=clang++ $(CXXFLAGS)

CPP_SRC_DIR = src/cpp
BIN_DIR = build/bin
OBJ_DIR = build/tmp
GEN_DIR = build/generated

# Parser
$(BIN_DIR)/parser: $(OBJ_DIR)/parser.o $(OBJ_DIR)/lexer.o $(OBJ_DIR)/parser_functions.o $(OBJ_DIR)/ExprAST.o $(OBJ_DIR)/FunctionAST.o $(OBJ_DIR)/generator_functions.o
	$(CXX) $(OBJ_DIR)/parser.o $(OBJ_DIR)/lexer.o $(OBJ_DIR)/parser_functions.o $(OBJ_DIR)/ExprAST.o $(OBJ_DIR)/FunctionAST.o $(OBJ_DIR)/generator_functions.o -o $(BIN_DIR)/parser

$(OBJ_DIR)/parser.o: $(GEN_DIR)/parser.cpp
	$(CXX) -c $(GEN_DIR)/parser.cpp -o $(OBJ_DIR)/parser.o

$(OBJ_DIR)/parser_functions.o: $(CPP_SRC_DIR)/parser_functions.cpp
	$(CXX) -c $(CPP_SRC_DIR)/parser_functions.cpp -o $(OBJ_DIR)/parser_functions.o

$(OBJ_DIR)/ExprAST.o: $(CPP_SRC_DIR)/AST/ExprAST.cpp
	$(CXX) -c $(CPP_SRC_DIR)/AST/ExprAST.cpp -o $(OBJ_DIR)/ExprAST.o

$(OBJ_DIR)/FunctionAST.o: $(CPP_SRC_DIR)/AST/FunctionAST.cpp
	$(CXX) -c $(CPP_SRC_DIR)/AST/FunctionAST.cpp -o $(OBJ_DIR)/FunctionAST.o

$(OBJ_DIR)/generator_functions.o: $(CPP_SRC_DIR)/generator_functions.cpp
	$(CXX) -c $(CPP_SRC_DIR)/generator_functions.cpp -o $(OBJ_DIR)/generator_functions.o

# Lexer
$(BIN_DIR)/lexer: $(OBJ_DIR)/lexer.o $(OBJ_DIR)/lexer_main.o $(OBJ_DIR)/TokenOutput.o
	$(CXX) $(OBJ_DIR)/lexer.o $(OBJ_DIR)/lexer_main.o $(OBJ_DIR)/TokenOutput.o -o $(BIN_DIR)/lexer 

$(OBJ_DIR)/lexer.o: $(GEN_DIR)/lexer.cpp
	$(CXX) -c $(GEN_DIR)/lexer.cpp -o $(OBJ_DIR)/lexer.o

$(OBJ_DIR)/lexer_main.o: $(CPP_SRC_DIR)/lexer_main.cpp
	$(CXX) -c $(CPP_SRC_DIR)/lexer_main.cpp -o $(OBJ_DIR)/lexer_main.o

$(OBJ_DIR)/TokenOutput.o: $(CPP_SRC_DIR)/TokenOutput.cpp
	$(CXX) -c $(CPP_SRC_DIR)/TokenOutput.cpp -o $(OBJ_DIR)/TokenOutput.o
