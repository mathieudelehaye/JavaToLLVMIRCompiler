// TokenOutput.h
#pragma once

#include "../../include/parser/java.tab.h" // yytokentype

#include <string>


class TokenOutput
{
public:
    TokenOutput():
        nestingLevel{0},
        newLine{false}
    {}

    std::string getName(yytokentype type);

private:
    int nestingLevel;
    bool newLine; 
};