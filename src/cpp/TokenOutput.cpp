#include "../../include/cpp/TokenOutput.h"

std::string TokenOutput::getName(yytokentype type)
{
    std::string outputBuffer{""};

    if (newLine)
    {
        newLine = false;

        outputBuffer += "\n";
        for (int i = 0; i < nestingLevel; i++)
        {
            outputBuffer += "\t";
        }
    }

    switch(type)
    {
        // Keywords
        case PUBLIC:
            outputBuffer += "public_keyword";
            break;
        case PRIVATE:
            outputBuffer += "private_keyword";
            break;
        case PROTECTED:
            outputBuffer += "protected_keyword";
            break;
        case STATIC:
            outputBuffer += "static_keyword";
            break;
        case IMPLEMENTS:
            outputBuffer += "implements_keyword";
            break;
        case EXTENDS:
            outputBuffer += "extends_keyword";
            break;
        case CLASS:
            outputBuffer += "class_keyword";
            break;
        case INTERFACE:
            outputBuffer += "interface_keyword";
            break;
        case IF:
            outputBuffer += "if_keyword";
            break;
        case WHILE:
            outputBuffer += "while_keyword";
            break;
        case RETURN:
            outputBuffer += "return_keyword";
            break;
        // Separators
        case LEFT_CURLY_BRACKET:
            outputBuffer += "\n";
            for (int i = 0; i < nestingLevel; i++)
            {
                outputBuffer += "\t";
            }
            outputBuffer += "{";

            nestingLevel++;
            newLine = true; 
            break;
        case RIGHT_CURLY_BRACKET:
            nestingLevel--;

            outputBuffer += "\n";
            for (int i = 0; i < nestingLevel; i++)
            {
                outputBuffer += "\t";
            }
            outputBuffer += "}";
            
            newLine = true;
            break;
        case LEFT_ROUND_BRACKET:
            outputBuffer += "(";
            break;
        case RIGHT_ROUND_BRACKET:
            outputBuffer += ")";
            break;
        case SEMICOLON:
            outputBuffer += ";";
            newLine = true;
            break;
        case DOT:
            outputBuffer += ".";
            break;
        // Types
        case INT_TYPE:
            outputBuffer += "int_type";
            break;
        case STRING_TYPE:
            outputBuffer += "string_type";
            break;
        case STRING_ARRAY_TYPE:
            outputBuffer += "string_array_type";
            break;
        case BOOLEAN_TYPE:
            outputBuffer += "bool_type";
            break;
        case VOID_TYPE:
            outputBuffer += "void_type";
            break;
        // Values
        case INT:
            outputBuffer += "<integer>";
            break;
        case NAME:
            outputBuffer += "<identifier>";
            break;
        case STRING:
            outputBuffer += "<string>";
            break;
        case BOOLEAN:
            outputBuffer += "<bool>";
            break;
        case OPERATOR:
            outputBuffer += "<operator>";
            break;
        // Default
        default:
            outputBuffer += "<unknown value>";
            break;
    }

    outputBuffer += " ";

    return outputBuffer;
}