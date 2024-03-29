#pragma once

#include "../../include/parser/java.tab.h" // yyget_text, yylex, yylval

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