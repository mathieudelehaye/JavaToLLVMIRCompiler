CXXFLAGS = -g -std=c++14 -Wno-deprecated-register

CXX=clang++ $(CXXFLAGS)

CPP_SRC_DIR = src/cpp
BIN_DIR = build/bin
OBJ_DIR = build/tmp
GEN_DIR = build/generated

# Parser
$(BIN_DIR)/parser: $(OBJ_DIR)/parser.o $(OBJ_DIR)/lexer.o $(OBJ_DIR)/parser_functions.o 
	$(CXX) $(OBJ_DIR)/parser.o $(OBJ_DIR)/lexer.o $(OBJ_DIR)/parser_functions.o -o $(BIN_DIR)/parser 

$(OBJ_DIR)/parser.o: $(GEN_DIR)/parser.cpp
	$(CXX) -c $(GEN_DIR)/parser.cpp -o $(OBJ_DIR)/parser.o

$(OBJ_DIR)/parser_functions.o: $(CPP_SRC_DIR)/parser_functions.cpp
	$(CXX) -c $(CPP_SRC_DIR)/parser_functions.cpp -o $(OBJ_DIR)/parser_functions.o

# Lexer
$(BIN_DIR)/lexer: $(OBJ_DIR)/lexer.o $(OBJ_DIR)/lexer_main.o $(OBJ_DIR)/TokenOutput.o
	$(CXX) $(OBJ_DIR)/lexer.o $(OBJ_DIR)/lexer_main.o $(OBJ_DIR)/TokenOutput.o -o $(BIN_DIR)/lexer 

$(OBJ_DIR)/lexer.o: $(GEN_DIR)/lexer.cpp
	$(CXX) -c $(GEN_DIR)/lexer.cpp -o $(OBJ_DIR)/lexer.o

$(OBJ_DIR)/lexer_main.o: $(CPP_SRC_DIR)/lexer_main.cpp
	$(CXX) -c $(CPP_SRC_DIR)/lexer_main.cpp -o $(OBJ_DIR)/lexer_main.o

$(OBJ_DIR)/TokenOutput.o: $(CPP_SRC_DIR)/TokenOutput.cpp
	$(CXX) -c $(CPP_SRC_DIR)/TokenOutput.cpp -o $(OBJ_DIR)/TokenOutput.o
