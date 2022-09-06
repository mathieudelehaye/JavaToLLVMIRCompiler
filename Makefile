CXXFLAGS = -g -std=c++14 -Wno-deprecated-register

CXX=clang++ $(CXXFLAGS)

build/bin/lexer:  lexer.o lexer_main.o TokenOutput.o
	$(CXX) lexer.o lexer_main.o TokenOutput.o -o build/bin/lexer 

lexer.o: ./build/generated/lexer.cpp
	$(CXX) -c ./build/generated/lexer.cpp

lexer_main.o: ./src/cpp/lexer_main.cpp
	$(CXX) -c ./src/cpp/lexer_main.cpp

TokenOutput.o: ./src/cpp/TokenOutput.cpp
	$(CXX) -c ./src/cpp/TokenOutput.cpp
