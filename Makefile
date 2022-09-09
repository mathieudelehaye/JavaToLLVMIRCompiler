CXXFLAGS = -g -std=c++14 -Wno-deprecated-register

CXX=clang++ $(CXXFLAGS)

BIN_DIR = build/bin
OBJ_DIR = build/tmp

$(BIN_DIR)/parser: $(OBJ_DIR)/parser.o $(OBJ_DIR)/lexer.o
	$(CXX) $(OBJ_DIR)/parser.o $(OBJ_DIR)/lexer.o -o $(BIN_DIR)/parser 

$(BIN_DIR)/lexer: $(OBJ_DIR)/lexer.o $(OBJ_DIR)/lexer_main.o $(OBJ_DIR)/TokenOutput.o
	$(CXX) $(OBJ_DIR)/lexer.o $(OBJ_DIR)/lexer_main.o $(OBJ_DIR)/TokenOutput.o -o $(BIN_DIR)/lexer 

$(OBJ_DIR)/parser.o: build/generated/parser.cpp
	$(CXX) -c build/generated/parser.cpp -o $(OBJ_DIR)/parser.o

$(OBJ_DIR)/lexer.o: build/generated/lexer.cpp
	$(CXX) -c build/generated/lexer.cpp -o $(OBJ_DIR)/lexer.o

$(OBJ_DIR)/lexer_main.o: src/cpp/lexer_main.cpp
	$(CXX) -c src/cpp/lexer_main.cpp -o $(OBJ_DIR)/lexer_main.o

$(OBJ_DIR)/TokenOutput.o: src/cpp/TokenOutput.cpp
	$(CXX) -c src/cpp/TokenOutput.cpp -o $(OBJ_DIR)/TokenOutput.o
