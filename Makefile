CXXFLAGS = -g -std=c++14 -Wno-deprecated-register

CXX=clang++ $(CXXFLAGS)

build/bin/lexer: build/tmp/lexer.o build/tmp/lexer_main.o build/tmp/TokenOutput.o
	$(CXX) build/tmp/lexer.o build/tmp/lexer_main.o build/tmp/TokenOutput.o -o build/bin/lexer 

lexer.o: build/generated/lexer.cpp
	$(CXX) -c build/generated/lexer.cpp -o build/tmp/lexer.o

lexer_main.o: src/cpp/lexer_main.cpp
	$(CXX) -c src/cpp/lexer_main.cpp -o build/tmp/lexer_main.o

TokenOutput.o: src/cpp/TokenOutput.cpp
	$(CXX) -c src/cpp/TokenOutput.cpp -o build/tmp/TokenOutput.o
